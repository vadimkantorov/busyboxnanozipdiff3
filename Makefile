URL ?= https://busybox.net/downloads/busybox-1.32.0.tar.bz2

ROOT = $(CURDIR)

source/busybox.tar.gz:
	mkdir -p source/busybox
	wget -nc $(URL) -O source/busybox.tar.gz

build/native/busybox: source/busybox.tar.gz
	mkdir -p build/native
	tar -xf source/busybox.tar.gz --strip-components=1 --directory=build/native
	cp .config build/native
	$(MAKE) -C build/native

build/wasm/busybox: source/busybox.tar.gz
	mkdir -p build/wasm
	tar -xf source/busybox.tar.gz --strip-components=1 --directory=build/wasm
	cp .config build/wasm
	mkdir -p build/wasm/arch/em 
	echo 'SKIP_STRIP=y' > build/wasm/arch/em/Makefile
	echo 'cmd_busybox__ = $$(CC) -o $$@ -Wl,--start-group -s ERROR_ON_UNDEFINED_SYMBOLS=0 -O2 $(ROOT)/em-shell.c -include $(ROOT)/em-shell.h --js-library $(ROOT)/em-shell.js $$(CFLAGS) $$(CFLAGS_busybox) $$(LDFLAGS) $$(EM_LDFLAGS) $$(EXTRA_LDFLAGS) $$(core-y) $$(libs-y) $$(patsubst %,-l%,$$(subst :, ,$$(LDLIBS))) -Wl,--end-group' >> build/wasm/arch/em/Makefile
	$(MAKE) -C build/wasm ARCH=em CROSS_COMPILE=em
