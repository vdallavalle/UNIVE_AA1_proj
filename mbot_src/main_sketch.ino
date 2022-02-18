#include <Arduino.h>
#include "Wire.h"
#include "Makeblock/MeAuriga.h"


MeUltrasonicSensor ultraSensor(PORT_7); /* Ultrasonic module can ONLY be connected to port 3, 4, 6, 7, 8 of base shield. */

#define LEDNUM 12

MeRGBLed led( 0, LEDNUM );
MeGyro gyro(0, 0x69);

void setup()
{
    Serial.begin(9600);
    gyro.begin();
    // LED Ring controller is on Auriga D44/PWM
    led.setpin( 44 );

    led.setColor(0, 0, 0);

    Serial.println("Ciccio pasticcio");
}

void loop()
{
    gyro.update();
    Serial.read();

    double distance = ultraSensor.distanceCm();

    uint8_t red = 255 ;
    if (distance < 40) {
        red = 255 * (distance / 40.0);
    }
    uint8_t green = 255 - red;

    led.setColorAt(0, red, green, 0);
    led.show();

    Serial.print("Distance : ");
    Serial.print(distance);
    Serial.print(" cm");
    Serial.print(" Red: "); Serial.print(red);
    Serial.print(" Green: "); Serial.print(green);
    Serial.println("");
    Serial.print("X ");
    Serial.print(gyro.getAngleX());
    Serial.print(" Y ");
    Serial.print(gyro.getAngleY());
    Serial.println("");
}
