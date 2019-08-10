#!/bin/bash

#
# Copyright (c) 2019, Piyush Itankar <pitankar@gmail.com>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.
#
#

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