# Dependencies

chiventure requires the following software/libraries:

- [CMake](https://cmake.org) 3.10 or higher
- [Protobuf](https://github.com/google/protobuf) 2.6.1 or higher
- [protobuf-c](https://github.com/protobuf-c/protobuf-c) 1.2.1 or higher
- [LibYAML](https://pyyaml.org/wiki/LibYAML) 0.2.2 or higher
- [ncurses](https://invisible-island.net/ncurses/announce.html) 6.0 or higher, with support for wide characters (`ncursesw`)
- [Criterion](https://github.com/Snaipe/Criterion) 2.3.1 or higher
- [Lua](https://www.lua.org/) 5.3 or 

CMake will warn if any of these are not installed with an error of the form "Could NOT find `<library>`"

Right now, chiventure has only been tested on Linux. The following installation instructions are specifically for Ubuntu 16.04, and may require adjustments in other platforms.

## Installing CMake

Ubuntu 16.04 includes an older version of CMake, so you will need to follow the instructions in the [Kitware APT Repository](https://apt.kitware.com/) to install the latest version of CMake.

## Installing `protobuf` and `protobuf-c`

[Protobuf](https://github.com/google/protobuf) (and [protobuf-c](https://github.com/protobuf-c/protobuf-c)) are data serialization libraries.

Run the following to install `protobuf`:
```
wget https://github.com/google/protobuf/releases/download/v2.6.1/protobuf-2.6.1.tar.gz
tar xvzf protobuf-2.6.1.tar.gz
cd protobuf-2.6.1/
./configure --prefix=/usr
make
sudo make install
```

And the following to install `protobuf-c`:
```
wget https://github.com/protobuf-c/protobuf-c/releases/download/v1.2.1/protobuf-c-1.2.1.tar.gz
tar xvzf protobuf-c-1.2.1.tar.gz
cd protobuf-c-1.2.1/
./configure --prefix=/usr
make
sudo make install
```

Please note the use of `--prefix=/usr`. If you omit this parameter, the libraries will be installed in `/usr/local/lib`, which can cause problems on some systems. If you encounter an error like this:
```
error while loading shared libraries: libprotoc.so.N: cannot open shared object file:
                                                                       No such file or directory
```

you will need to explicitly add `/usr/local/lib` (or any alternate prefix you specify when installing) to the `LD_LIBRARY_PATH` environment variable:
```
export LD_LIBRARY_PATH=\$LD_LIBRARY_PATH:/usr/local/lib
```

## Installing `LibYAML` 

[LibYAML](https://pyyaml.org/wiki/LibYAML) is a YAML parser and emitter library.

To install, download the source package from [here](http://pyyaml.org/download/libyaml/yaml-0.2.2.tar.gz)

To build and install `LibYAML`, in the folder you downloaded the `.tar.gz` file in, run
```
tar -xvf <yaml tarball name>
cd <newly created yaml folder>
./configure
make
sudo make install
```

## Installing `ncurses`

Curses is a terminal UI framework. You can install it by running:
```
sudo apt-get install libncurses5-dev libncursesw5-dev
```

## Installing `criterion`

[Criterion](https://github.com/Snaipe/Criterion) is a testing framework for C/C++. You can install it by running the following:
```
sudo add-apt-repository ppa:snaipewastaken/ppa
sudo apt-get update
sudo apt-get install criterion-dev
```

## Installing `Lua` 

Step 1: Download and install Lua to the CSIL machines through the following commands:
```
curl -R -O http://www.lua.org/ftp/lua-5.3.5.tar.gz -o ~/
tar zxf ~/lua-5.3.5.tar.gz
cd ~/lua-5.3.5
make linux test
```
Step 2: In your chiventure directory on the CSIL machines, follow the process below to build the code:
```
mkdir build
cd build
cmake -DLUA_INCLUDE_DIR=~/lua-5.3.5/src/ -DLUA_LIBRARY=~/lua-5.3.5/src/liblua.a ..
make
```
Note: if you are on an unsupported ubuntu release for Criterion (like ubuntu 19), you can try to add a different release repository to your apt sources. To do so, open software updater, click the "Other Software" tab, and click the "Add" button. Then, add the line `deb http://ppa.launchpad.net/snaipewastaken/ppa/ubuntu cosmic main` (to add the Ubuntu 18 version) as the source. You should probably remove the source afterwards, since it's a different Ubuntu release and might cause issues the next time you use apt.
