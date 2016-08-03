#!/bin/bash

git clone http://git.code.sf.net/p/openocd/code openocd
cd openocd
./bootstrap 
./configure --enable-maintainer-mode --enable-ti-icdi
make
make install
cd ../
rm -rf openocd
