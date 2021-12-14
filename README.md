# UNIVE_AA1_proj

Advanced Algorithms [470-1] project.

## mBot build and upload setup
### WSL
We were unable to get CLion's [Arduino Support Plugin](https://github.com/vsch/CLionArduinoPlugin) and 
[Arduino CMake](https://github.com/francoiscampbell/arduino-cmake) working on Windows directly, so the build toolchain 
**must** be configured either on WSL or directly on Linux (not tested at time of writing). To build for mBot you will 
need to open the CLion project in the `mbot_src` folder.

#### WSL Version 1
Because of some issues related to serial ports mapping in WSL 2 the WSL image needs to be running on version 1 of
the subsystem. To check the version of your image `wsl --list --verbose` in a Windows shell will yield something similar
to this:
```
  NAME      STATE           VERSION
* <Name>    Running         2
```
If your image has `VERSION 2` then it can be changed by running `wsl --set-version <Name> 1`, this command will take
a few minutes. Run it at your own risk, as an alternative a new image could be created and needs to be configured for
C++ and CMake.

#### Arduino SDK
Arduino CMake will look for the Arduino SDK into one of the following paths:
`/usr/share/arduino*`, `/opt/local/arduino*`, `/opt/arduino*`, `/usr/local/share/arduino*`.  
**If you are using Ubuntu do not install the SDK via `apt`.**   
Ideally you want either to create a symlink to the SDK folder or to extract the `tar.xz` archive directly in one of the
mentioned paths.

#### Arduino Support Plugin
This software is highly unstable, the `mbot_src` CLion project has already been configured for the most part.
`main_sketch.ino` is the entrypoint for code execution of the project.
To **change the serial port** you have to edit **manually** `mbot_src/CMakeLists.txt` and change 
`set(${PROJECT_NAME}_PORT <port name>)`. In WSL 1 there is an automatic mapping of the COMx ports to `/dev/ttySx`. 
In my computer I'm using COM6 so I've set the port to `/dev/ttyS6`.

You are encouraged to **avoid using the plugin tooling** for changing configurations.

To build and upload the mBot sketch, after the port has been configured, you will need to select the 
**upload target** in the upper-right corner of CLion and **then press the build** (green hammer) button. **Do not**
use the run button, it will not correctly execute the build and upload processes.

## Lego Mindstorm and ev3dev 
### Docker

Docker is a light-weight virtual machine with excellent cross-platform support. This allows us to run something very close to the ev3dev OS on any desktop or notebook computer. This means that we get the same versions of all of the libraries running on the EV3 but compile with the power of a desktop processor.

Docker has excellent documentation, so we will just send you to their [install page](https://docs.docker.com/get-docker/).
If you use Linux also install `sudo apt-get install qemu-user-static`, otherwise you will get an error: `exec user process caused "exec format error"`.

Once Docker is installed, download the ev3dev cross-compiler image:
```
docker pull ev3dev/debian-stretch-cross
docker tag ev3dev/debian-stretch-cross ev3cc
```

### C++ language bindings for ev3dev 

First we run a new docker container:
```
docker run --rm -it -v <host-path>:<container-path> -w /<container-path> ev3cc
```
For example:
```
docker run --rm -it -v C:\Users\myname\example\:/src -w /src ev3cc
```
Install the ARM compiler by typing `sudo apt-get install gcc-arm-linux-gnueabi g++-arm-linux-gnueabi`.

Now use git clone to clone this repository to the directory of your choice, e.g.,
```
git clone https://github.com/ddemidov/ev3dev-lang-cpp.git
```
will clone the repo into a directory called `/ev3dev-lang-cpp.git`. If you don't have git install it through this command `sudo apt-get install git`.

You need to make some changes to the top-level `CMakeLists.txt` file. First, go into the directory
```
cd ev3dev-lang-cpp
```
Now, edit the `CMakeLists.txt` file with a text editor of your choice, e.g.,
```
vi CMakeLists.txt
```
Just after the `project(...)` declaration, set the C/C++ compilers by adding the following lines:
```
set(CMAKE_C_COMPILER "arm-linux-gnueabi-gcc")
set(CMAKE_CC_COMPILER "arm-linux-gnueabi-gcc")
set(CMAKE_CXX_COMPILER "arm-linux-gnueabi-g++")
```
Now compile your programs and the generated binaries will be ready for EV3. This assumes that you have build tools such as `make` and `cmake` installed - if not, install them with `sudo apt-get install build-essential` (for make) and `sudo apt-get install cmake` for cmake. You can then perform compilation by invoking the following commands (inside `ev3dev-lang-cpp` directory):
```
mkdir build && cd build
cmake .. -DEV3DEV_PLATFORM=EV3
make
```
In the `ev3dev-lang-cpp/build/demos` folder you will find test executables that you can switch to EV3, or run in the docker container for testing.
In the docker container, inside `ev3dev-lang-cpp/build/demos`, run for example:

```
./ev3dev-lang-demo
```

Note: if encountered `/lib/ld-linux.so.3: No such file or directory` error while running `./ev3dev-lang-demo` in the docker environment, try `qemu-arm-static -L /usr/arm-linux-gnueabi/ ./ev3dev-lang-demo`.

### Set up a network connection and Connect to the EV3 via SSH (Requires EV3)

Follow this [guide](https://www.ev3dev.org/docs/tutorials/connecting-to-the-internet-via-usb/) for set up a network connection in base on your OS.

Follow this [guide](https://www.ev3dev.org/docs/tutorials/connecting-to-ev3dev-with-ssh/) to connect to the EV3 via SSH in base on your OS

## External Dependencies
### [C++ language bindings for ev3dev](https://github.com/ddemidov/ev3dev-lang-cpp)
The library's README offers instruction for compiling while using it.
We still need to configure our project level CMake to accomodate it.
### [Makeblock Library](https://github.com/Makeblock-official/Makeblock-Libraries)
