# gr-music
MUSIC algorithm for GnuRadio

## Build
```sh
cmake -S . -B build -DCMAKE_INSTALL_PREFIX:PATH=/usr
cmake --build build
```
### Debian package
```sh
cd build
checkinstall --install=<yes/no> --pkgname=gnuradio-music --pkgversion=<version> -A <arch> --pkgrelease=<release> --pkglicense=GPLv3+ --requires=gnuradio
```
