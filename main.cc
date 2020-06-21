#include <stdio.h>
#include <sstream>

#include <v8.h>
#include <libplatform/libplatform.h>

static v8::Local<v8::String>
v8str(v8::Isolate *isolate, const char *s)
{
    return v8::String::NewFromUtf8(isolate, s, v8::NewStringType::kNormal).ToLocalChecked();
}

static v8::Local<v8::Value>
run_script(v8::Isolate *isolate, std::string path)
{
    std::ifstream f(path);
    std::stringstream buf;        
    buf << f.rdbuf();
    std::string src = buf.str();
    v8::Local<v8::Context> ctx = isolate->GetCurrentContext();
    v8::Local<v8::Script> script = v8::Script::Compile(ctx, v8str(isolate, src.c_str())).ToLocalChecked();
    return script->Run(ctx).ToLocalChecked();
}

static void
log_cb(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    v8::Isolate *isolate = args.GetIsolate();
    v8::HandleScope handle_scope(isolate);

    printf("v8/log:");
    for (int i = 0; i < args.Length(); i++) {
        v8::String::Utf8Value utf8(isolate, args[i]);
        printf(" %s", *utf8);
    }
    printf("\n");
}

static void
include_cb(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    v8::Isolate *isolate = args.GetIsolate();
    v8::HandleScope handle_scope(isolate);

    v8::String::Utf8Value filename(isolate, args[0]);
    printf("v8/include: %s\n", *filename);
    run_script(isolate, std::string("./scripts/") + *filename);
}

int
main(int argc, char *argv[])
{
    printf("hello world\n");

    // init v8
    v8::V8::InitializeICUDefaultLocation(argv[0]);
    v8::V8::InitializeExternalStartupData(argv[0]);
    std::unique_ptr<v8::Platform> platform = v8::platform::NewDefaultPlatform();
    v8::V8::InitializePlatform(platform.get());
    v8::V8::Initialize();

    // create isolate
    v8::Isolate::CreateParams create_params;
    create_params.array_buffer_allocator = v8::ArrayBuffer::Allocator::NewDefaultAllocator();
    v8::Isolate *isolate = v8::Isolate::New(create_params);

    {
        v8::Isolate::Scope isolate_scope(isolate);
        v8::HandleScope handle_scope(isolate);

        // set up global context template
        v8::Local<v8::ObjectTemplate> builtin = v8::ObjectTemplate::New(isolate);
        builtin->Set(isolate, "log", v8::FunctionTemplate::New(isolate, log_cb));
        builtin->Set(isolate, "include", v8::FunctionTemplate::New(isolate, include_cb));
        v8::Local<v8::ObjectTemplate> global = v8::ObjectTemplate::New(isolate);
        global->Set(isolate, "builtin", builtin);

        // create context
        v8::Local<v8::Context> ctx = v8::Context::New(isolate, NULL, global);
        v8::Context::Scope ctx_scope(ctx);

        // run entry script
        v8::Local<v8::Value> result = run_script(isolate, "./scripts/entry.js");

        // convert result to str and print
        v8::String::Utf8Value utf8(isolate, result);
        printf("entry.js result: %s\n", *utf8);

        // pump v8 message loop...?
        while (v8::platform::PumpMessageLoop(platform.get(), isolate));
    }

    isolate->Dispose();
    v8::V8::Dispose();
    v8::V8::ShutdownPlatform();
    delete create_params.array_buffer_allocator;

    printf("done\n");
    return 0;
}
