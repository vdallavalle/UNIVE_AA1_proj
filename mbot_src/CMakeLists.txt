cmake_minimum_required(VERSION 2.8.4)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/cmake/ArduinoToolchain.cmake)
set(CMAKE_CXX_STANDARD 14)
set(PROJECT_NAME mbot_clion)

set(${PROJECT_NAME}_BOARD mega)
set(ARDUINO_CPU atmega2560)
project(${PROJECT_NAME} LANGUAGES C CXX ASM)

# Define additional source and header files or default arduino sketch files
set(${PROJECT_NAME}_SRCS
        ${CMAKE_CURRENT_SOURCE_DIR}/Makeblock/utility/avr/Servo.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Makeblock/Me4Button.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Makeblock/MeGyro.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Makeblock/MeMegaPiPro4DcMotor.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Makeblock/MeShutter.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Makeblock/Me7SegmentDisplay.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Makeblock/MeHostParser.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Makeblock/MeMegaPiProESCMotor.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Makeblock/MeSmartServo.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Makeblock/MeBluetooth.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Makeblock/MeHumitureSensor.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Makeblock/MeOnBoardTemp.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Makeblock/MeSoundSensor.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Makeblock/MeBuzzer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Makeblock/MeIR.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Makeblock/MeOneWire.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Makeblock/MeStepper.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Makeblock/MeColorSensor.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Makeblock/MeInfraredReceiver.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Makeblock/MePIRMotionSensor.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Makeblock/MeStepperOnBoard.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Makeblock/MeCompass.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Makeblock/MeJoystick.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Makeblock/MePS2.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Makeblock/MeTemperature.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Makeblock/MeDCMotor.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Makeblock/MeLEDMatrix.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Makeblock/MePm25Sensor.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Makeblock/MeTouchSensor.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Makeblock/MeEncoderMotor.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Makeblock/MeLightSensor.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Makeblock/MePort.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Makeblock/MeUSBHost.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Makeblock/MeEncoderNew.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Makeblock/MeLimitSwitch.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Makeblock/MePotentiometer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Makeblock/MeUltrasonicSensor.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Makeblock/MeEncoderOnBoard.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Makeblock/MeLineFollower.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Makeblock/MePressureSensor.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Makeblock/MeVoice.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Makeblock/MeFlameSensor.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Makeblock/MeMbotDCMotor.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Makeblock/MeRGBLed.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Makeblock/MeWifi.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Makeblock/MeGasSensor.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Makeblock/MeMegaPiDCMotor.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Makeblock/MeSerial.cpp
        )
set(${PROJECT_NAME}_HDRS
        ${CMAKE_CURRENT_SOURCE_DIR}/Makeblock/utility/avr/ServoTimers.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Makeblock/utility/EEPROM.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Makeblock/utility/SPI.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Makeblock/utility/Servo.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Makeblock/utility/SoftwareSerial.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Makeblock/utility/Wire.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Makeblock/utility/twi.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Makeblock/MeColorSensor.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Makeblock/MeLimitSwitch.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Makeblock/MeSerial.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Makeblock/MeCompass.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Makeblock/MeLineFollower.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Makeblock/MeShield.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Makeblock/MeConfig.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Makeblock/MeMCore.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Makeblock/MeShutter.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Makeblock/MeDCMotor.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Makeblock/MeMbotDCMotor.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Makeblock/MeSmartServo.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Makeblock/MeEEPROM.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Makeblock/MeMegaPi.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Makeblock/MeSoundSensor.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Makeblock/MeEncoderMotor.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Makeblock/MeMegaPiDCMotor.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Makeblock/MeStepper.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Makeblock/MeEncoderNew.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Makeblock/MeMegaPiPro.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Makeblock/MeStepperOnBoard.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Makeblock/MeEncoderOnBoard.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Makeblock/MeMegaPiPro4DcMotor.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Makeblock/MeTemperature.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Makeblock/MeFlameSensor.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Makeblock/MeMegaPiProESCMotor.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Makeblock/MeTouchSensor.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Makeblock/MeGasSensor.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Makeblock/MeOnBoardTemp.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Makeblock/MeUSBHost.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Makeblock/MeGyro.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Makeblock/MeOneWire.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Makeblock/MeUltrasonicSensor.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Makeblock/MeHostParser.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Makeblock/MeOrion.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Makeblock/MeVoice.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Makeblock/MeHumitureSensor.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Makeblock/MePIRMotionSensor.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Makeblock/MeWifi.h
        )

### Additional static libraries to include in the target.
# set(${PROJECT_NAME}_LIBS)

### Main sketch file
set(${PROJECT_NAME}_SKETCH main_sketch.ino)

### Add project directories into the build
# add_subdirectory()

### Additional settings to add non-standard or your own Arduino libraries.
# For this example (libs will contain additional arduino libraries)
# An Arduino library my_lib will contain files in libs/my_lib/: my_lib.h, my_lib.cpp + any other cpp files
# link_directories(${CMAKE_CURRENT_SOURCE_DIR}/Makeblock)

# For nested library sources replace ${LIB_NAME} with library name for each library
# set(_RECURSE true)

#### Additional settings for programmer. From programmers.txt
# set(${PROJECT_NAME}_PROGRAMMER avrispmkii)
set(${PROJECT_NAME}_PORT /dev/ttyS6)
# set(mega.upload.speed 9600)

## Verbose build process
set(${PROJECT_NAME}_AFLAGS -v)

generate_arduino_firmware(${PROJECT_NAME})


print_board_list()
print_programmer_list()
