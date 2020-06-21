linux (tested on buster):

```
$ ./get_linux_deps
$ make
$ ./main
hello world
result: 69
done
```

main.cc mainly follows https://chromium.googlesource.com/v8/v8/+/branch-heads/6.8/samples/hello-world.cc

more @ https://v8.dev/docs/embed

um for some reason Tonal.node.midi('A4') returns 69 but the README says it returns 60. i verified this is correct in browser

On linux we link against libv8.a v8.0.426.8 from https://github.com/blazerod/v8-prebuilt (also has darwin builds)

```
$ du -h main
18M main
$ ldd main
    linux-vdso.so.1 (0x00007ffca9be6000)
    libpthread.so.0 => /lib/x86_64-linux-gnu/libpthread.so.0 (0x00007f8c113b9000)
    libstdc++.so.6 => /lib/x86_64-linux-gnu/libstdc++.so.6 (0x00007f8c11235000)
    libm.so.6 => /lib/x86_64-linux-gnu/libm.so.6 (0x00007f8c110f0000)
    libgcc_s.so.1 => /lib/x86_64-linux-gnu/libgcc_s.so.1 (0x00007f8c110d6000)
    libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007f8c10f13000)
    /lib64/ld-linux-x86-64.so.2 (0x00007f8c1219b000)
```

On windows there's a NuGet package https://www.nuget.org/packages/v8-v140-x64/
