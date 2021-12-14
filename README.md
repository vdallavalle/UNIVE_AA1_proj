# UNIVE_AA1_proj

Advanced Algorithms [470-1] project.

## mBot build and upload setup
### WSL
We were unable to get CLion's [Arduino Support Plugin](https://github.com/vsch/CLionArduinoPlugin) and [Arduino CMake](https://github.com/francoiscampbell/arduino-cmake)
working on Windows directly, so the build toolchain **must** be configured either on WSL or directly on Linux (not tested at time
of writing).  

#### WSL Version 1
Because of some issues related to serial ports mapping in WSL 2 the WSL image needs to be running on version 1 of
the subsystem. To check the version of your image `wsl --list --verbose` in a Windows shell will yield something similar to this:
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


## External Dependencies
### [C++ language bindings for ev3dev](https://github.com/ddemidov/ev3dev-lang-cpp)
The library's README offers instruction for compiling while using it.
We still need to configure our project level CMake to accomodate it.
### [Makeblock Library](https://github.com/Makeblock-official/Makeblock-Libraries)
