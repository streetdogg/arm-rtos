#!/bin/bash
echo "Installing openOCD build dependencies"
sudo apt install -y make libtool pkg-config autoconf automake texinfo libusb-1.0

echo "Downloading the openOCD source code"
git clone http://git.code.sf.net/p/openocd/code openocd
cd openocd
./bootstrap 
./configure --enable-maintainer-mode --enable-ti-icdi
make

echo "Installing openOCD"
sudo make install
cd ../
rm -rf openocd