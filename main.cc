#include <stdio.h>
#include <sstream>

#include <libplatform/libplatform.h>
#include <v8.h>

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
        v8::Local<v8::Context> ctx = v8::Context::New(isolate);
        v8::Context::Scope ctx_scope(ctx);

        std::string src_str;
        if (0) {
            // print hello world
            src_str = "'Hello' + ' world' + ', from v8!'";
        } else {
            // read src from file
            // c++ is silly
            std::ifstream f("tonal.min.js");
            std::stringstream buf;        
            buf << f.rdbuf();
            buf << std::endl;
            buf << "Tonal.Note.midi('A4')";
            src_str = buf.str();
        }

        v8::Local<v8::String> src = v8::String::NewFromUtf8(
            isolate, src_str.c_str(), v8::NewStringType::kNormal).ToLocalChecked();

        // compile script
        v8::Local<v8::Script> script = v8::Script::Compile(ctx, src).ToLocalChecked();
        // run script
        v8::Local<v8::Value> result = script->Run(ctx).ToLocalChecked();
        // convert result to str and print
        v8::String::Utf8Value utf8(isolate, result);
        printf("result: %s\n", *utf8);
    }

    isolate->Dispose();
    v8::V8::Dispose();
    v8::V8::ShutdownPlatform();
    delete create_params.array_buffer_allocator;

    printf("done\n");
    return 0;
}
