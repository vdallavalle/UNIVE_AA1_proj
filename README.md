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

## External Dependencies
### [C++ language bindings for ev3dev](https://github.com/ddemidov/ev3dev-lang-cpp)
The library's README offers instruction for compiling while using it.
We still need to configure our project level CMake to accomodate it.
### [Makeblock Library](https://github.com/Makeblock-official/Makeblock-Libraries)
