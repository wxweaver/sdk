# wxWeaver

Fork of wxFormBuilder.

## Install From Source

### Windows (MSYS2)

Install [MSYS2](http://msys2.github.io/) and run the following inside a MinGW 32 bit shell:

```sh
pacman -S --needed mingw-w64-i686-gcc mingw-w64-i686-wxWidgets make git
git clone --recursive --depth=1 https://github.com/wxFormBuilder/wxFormBuilder
cd wxFormBuilder
cmd.exe /C "create_build_files4.bat --wx-root=/mingw32/bin --force-wx-config --disable-mediactrl"
ln -s /mingw32/include/binutils/ansidecl.h /mingw32/include/ansidecl.h
ln -s /mingw32/include/binutils/bfd.h /mingw32/include/bfd.h
ln -s /mingw32/include/binutils/bfd_stdint.h /mingw32/include/bfd_stdint.h
ln -s /mingw32/include/binutils/diagnostics.h /mingw32/include/diagnostics.h
ln -s /mingw32/include/binutils/symcat.h /mingw32/include/symcat.h
ln -s /mingw32/lib/binutils/libbfd.a /mingw32/lib/libbfd.a
ln -s /mingw32/lib/binutils/libiberty.a /mingw32/lib/libiberty.a
cd build/3.0/gmake
sed 's!\$(LDFLAGS) \$(RESOURCES) \$(ARCH) \$(LIBS)!\$(LIBS) \$(LDFLAGS) \$(RESOURCES) \$(ARCH)!g' *.make -i
make config=release
```

Run:

```sh
cd ../../../output/
./wxWeaver.exe
```

### Linux

Pre-requisites for Ubuntu:

```sh
sudo apt install libwxgtk3.0-gtk3-dev libwxgtk-media3.0-gtk3-dev meson
```

Pre-requisites for Arch Linux:

```sh
sudo pacman -Syu --needed meson wxgtk2
```

Build and run:

```sh
git clone --recursive --depth=1 https://github.com/wxweaver/wxWeaver
cd wxWeaver
meson _build --prefix $PWD/_install --buildtype=release
ninja -C _build install
./_install/bin/wxweaver
```

### macOS

Pre-requisites for macOS can be installed via [Homebrew](https://brew.sh/):

```sh
brew install wxmac boost dylibbundler make
```

Note: Building with Xcode currently does not work.

```sh
git clone --recursive --depth=1 https://github.com/wxweaver/wxWeaver
cd wxWeaver
./create_build_files4.sh
cd build/3.0/gmake
make config=release
```

Run:

```sh
cd ../../../output/
open wxWeaver.app
```
