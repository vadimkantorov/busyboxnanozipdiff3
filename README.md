Inspired by https://github.com/tbfleming/em-busybox and https://github.com/tbfleming/em-shell, this repo contains build script of BusyBox for WebAssembly without being a full fork of BusyBox, so upgrading to a new version of BusyBox is easier.

`em-shell.c`, `em-shell.h`, `em-shell.js`, [`arch/em/Makefile`](https://github.com/tbfleming/em-busybox/blob/master/arch/em/Makefile) are taken from excellent [tbfleming/em-shell](https://github.com/tbfleming/em-shell) and [tbfleming/em-busybox](https://github.com/tbfleming/em-shell) by [Todd Fleming](https://tbfleming.github.io/).

Patches not used for now:
- https://github.com/tbfleming/em-busybox/commit/8c592ed5e13a7c35e0e318112bbdbc281798b6d7
- https://github.com/tbfleming/em-busybox/commit/5fbe7c016af61b21c073652fed3b4ee4d744238d


```shell
# native version 
make build/native/busybox

# wasm version
make build/wasm/busybox_unstripped.js
```
