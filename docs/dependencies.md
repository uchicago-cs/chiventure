# Dependencies

chiventure requires the following software/libraries:

- [CMake](https://cmake.org) 3.10 or higher
- [Protobuf](https://github.com/google/protobuf) 2.6.1 or higher
- [protobuf-c](https://github.com/protobuf-c/protobuf-c) 1.2.1 or higher
- [LibYAML](https://pyyaml.org/wiki/LibYAML) 0.2.2 or higher
- [ncurses](https://invisible-island.net/ncurses/announce.html) 6.0 or higher, with support for wide characters (`ncursesw`)
- [Criterion](https://github.com/Snaipe/Criterion) 2.3.1 or higher
- [Lua](https://www.lua.org/) 5.3 or higher
- [json-c](https://github.com/json-c/json-c.git) 
- [libzip](https://github.com/nih-at/libzip.git)

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
Note: if you are on an unsupported Ubuntu release for Criterion (i.e. Ubuntu 19.XX and higher), you can try to add a different release repository for your apt sources. To do so, open the "Software Updater" application, click on the "Other Software" tab, and then click on the "Add" button. Then, add the line `deb http://ppa.launchpad.net/snaipewastaken/ppa/ubuntu cosmic main` as the source; this will add the Ubuntu 18.XX release version. (You should probably remove the source after the installation, since it's a different Ubuntu release and might cause issues the next time you use apt.)

## Installing `json-c` and `libzip`

json-c and libzip are required for the new iteration of WDL, allowing parsing and working with zip archives, respectively. They currently are not installed on the CSIL machines, so a temporary workaround for their installation and use is in place.

Right now, a workaround is to checkout this repositories and then point pCMake to the local folders that will be stored in your home directory on the CSIL machines. The following (written by Maxine) will describe how to achieve the local library linking process.

**Step 1**: Set up a directory to store your installations in
```
cd ~
mkdir libfiles
cd libfiles
mkdir json-c
mkdir libzip
```

**Step 2**: download, make, and install json-c
```
cd ~
git clone https://github.com/json-c/json-c.git
mkdir json-c-build
cd json-c-build
cmake -DCMAKE_INSTALL_PREFIX=~/libfiles/json-c ../json-c
make
make test
make install
```

**Step 3**: download, make, and install libzip
```
cd ~
git clone https://github.com/nih-at/libzip.git
mkdir libzip-build
cd libzip-build/
cmake -DCMAKE_INSTALL_PREFIX=~/libfiles/libzip ../libzip
make
make test
make install
```

**Step 4**: From inside `chiventure/build`, run
```
cmake -DJSONC_INCLUDE_DIR="~/libfiles/json-c/include/json-c/" -DJSONC_LIBRARY=~/libfiles/json-c/lib/libjson-c.so -DLIBZIP_INCLUDE_DIR="~/libfiles/libzip/include/" -DLIBZIP_LIBRARY=~/libfiles/libzip/lib/libzip.so ..
```

You should now be able to make & test as usual.

