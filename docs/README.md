# chiventure Documentation

* [Developer Guidelines](developer.md)
* [Actions Specification](actions.md)

## Building chiventure

chiventure uses CMake. To build, run
```
mkdir build
cd build
cmake ..
```

### Dependencies

If you are missing CMake, run 
```
sudo apt install cmake
```

chiventure depends on `protobuf-c`, `LibYAML` (`Yaml`), and `Curses`. `cmake ..` will warn if any of these are not installed with an error of the form "Could NOT find <library>"

#### Installing `protobuf` and `protobuf-c`

On most UNIX systems, you should be able to install `protobuf` by running the following:
```
wget https://github.com/google/protobuf/releases/download/v2.6.1/protobuf-2.6.1.tar.gz
tar xvzf protobuf-2.6.1.tar.gz
cd protobuf-2.6.1/
./configure --prefix=/usr
make
sudo make install
```

And `protobuf-c` by running the following:
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

#### Installing `LibYAML` 

LibYAML is a YAML parser and emitter library. You can read more about it [here](https://pyyaml.org/wiki/LibYAML)

To install, download the source package from [here](http://pyyaml.org/download/libyaml/yaml-0.2.2.tar.gz)

To build and install `LibYAML`, in the folder you downloaded the `.tar.gz` file in, run
```
tar -xvf <yaml tarball name>
cd <newly created yaml folder>
./configure
make
sudo make install
```

#### Installing `Curses`


