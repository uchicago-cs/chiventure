# Dependencies

chiventure requires the following software/libraries:

- [CMake](https://cmake.org) 3.10 or higher
- [JSON-C](https://github.com/json-c/json-c) 0.13 or higher  
- [ncurses](https://invisible-island.net/ncurses/announce.html) 6.0 or higher, with support for wide characters (`ncursesw`)
- [Criterion](https://github.com/Snaipe/Criterion) 2.3.1 or higher
  
Optional dependencies:

- [Lua](https://www.lua.org/) 5.3 or higher. If not present, chiventure will not have support for custom scripts.   

CMake will warn you if any of these are not installed with an error of the form "Could NOT find `<library>`"

Right now, chiventure has only been tested on Ubuntu 16.04 and 20.04. We provide instructions for installing dependencies on both these platforms. Other Linux distributions may provide the same packages, but other may require installing dependencies manually, following the instructions provided by each library.

## Installing on Ubuntu 20.04

If you are using Ubuntu 20.04, you can install most of the dependencies by running the following:

```
sudo apt-get update
sudo apt install pkg-config cmake libjson-c4 libjson-c-dev libzip5 libzip-dev libncurses-dev liblua5.3-0 liblua5.3-dev  
```

The Criterion testing library does not provide packages for Ubuntu 20.04 but, fortunately, their 18.04 packages work just fine. You can manually install them like this:

```
wget https://launchpad.net/~snaipewastaken/+archive/ubuntu/ppa/+files/criterion-dev_2.3.2-6-ubuntu1~bionic1_amd64.deb
wget https://launchpad.net/~snaipewastaken/+archive/ubuntu/ppa/+files/criterion_2.3.2-6-ubuntu1~bionic1_amd64.deb
sudo dpkg -i criterion_2.3.2-6-ubuntu1~bionic1_amd64.deb criterion-dev_2.3.2-6-ubuntu1~bionic1_amd64.deb
```

## Installing on Ubuntu 16.04

If you are using Ubuntu 16.04, you can install most of the dependencies by running the following:

```
sudo apt-get update
sudo apt install pkg-config libyaml-0-2 libyaml-dev libjson-c2 libjson-c-dev libzip4 libzip-dev libncurses5-dev libncursesw5-dev liblua5.3-0 liblua5.3-dev
```

Ubuntu 16.04 includes an older version of CMake, so you will need to follow the instructions in the [Kitware APT Repository](https://apt.kitware.com/) to install the latest version of CMake:

```
sudo apt-get install apt-transport-https ca-certificates gnupg software-properties-common wget
wget -O - https://apt.kitware.com/keys/kitware-archive-latest.asc 2>/dev/null | gpg --dearmor - | sudo tee /etc/apt/trusted.gpg.d/kitware.gpg >/dev/null
sudo apt-add-repository 'deb https://apt.kitware.com/ubuntu/ xenial main'
sudo apt-get update
sudo apt-get install cmake
```

Criterion must be installed from their PPA (Personal Package Archive):

```
sudo add-apt-repository ppa:snaipewastaken/ppa
sudo apt-get update
sudo apt-get install criterion-dev
```


