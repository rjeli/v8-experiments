```
$ sudo apt install libnode-dev # works on buster, maybe works on ubongo
$ make
$ ./main
hello world
result: 69
done
```

main.cc mainly follows https://chromium.googlesource.com/v8/v8/+/branch-heads/6.8/samples/hello-world.cc

more @ https://v8.dev/docs/embed

this compiles & links against v8 headers & .so's from debian buster `libnode-dev`, for some reason it doesn't provide .a's 

but for a release build, there are prebuilts available at https://github.com/denoland/rusty_v8/releases (byo header)

um for some reason Tonal.node.midi('A4') returns 69 but the README says it returns 60. i verified this is correct in browser

todo: console.log

https://explorerplusplus.com/blog/2019/03/07/embedding-v8-c++-application

