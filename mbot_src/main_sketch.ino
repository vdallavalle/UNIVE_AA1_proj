#include <Arduino.h>
#include "Wire.h"
#include "Makeblock/MeAuriga.h"


MeUltrasonicSensor ultraSensor(
        PORT_7); /* Ultrasonic module can ONLY be connected to port 3, 4, 6, 7, 8 of base shield. */

#define LEDNUM 12

MeRGBLed led(0, LEDNUM);
MeGyro gyro(0, 0x69);

MeEncoderOnBoard MotorR(SLOT1);
MeEncoderOnBoard MotorL(SLOT2);

int counter = 0;
const int MAX_COUNT = 200;
const int PWM = 64;

struct LoopStrategy {
    virtual void loop() = 0;
};

struct NoOpStrategy : public LoopStrategy {
    void loop() override {
        Serial.println("NOP");
    }
};

LoopStrategy *strategy = new NoOpStrategy();

/**
 * @param angleA in radians, max 2.0 * PI
 * @param angleB in radians, max 2.0 * PI
 * @return angular distance between them, can be negative.
 */
double angleDistance(double angleA, double angleB) {
    return angleA - angleB;
}

void setRotationSpeed(float wheel_rpm, int pwm) {
    MotorR.setMotorPwm(pwm);
    MotorL.setMotorPwm(pwm);
    MotorR.setSpeed(wheel_rpm);
    MotorL.setSpeed(wheel_rpm);
}

struct PrintStrategyDecorator : public LoopStrategy {
    LoopStrategy* decorated;

    explicit PrintStrategyDecorator(LoopStrategy *decorated) : decorated(decorated) {}

    void loop() override {
        Serial.println("Print");
        decorated -> loop();
    }
};

struct GoToTargetZAngleStrategy : public LoopStrategy {

    float speedRPM;
    double targetAngle;
    double threshold;

    bool printed = false;

    GoToTargetZAngleStrategy(float speedRpm, double targetAngle,
                             double threshold) : speedRPM(speedRpm),
                                                 targetAngle(targetAngle),
                                                 threshold(threshold) {}

    void loop() override {

        double zAngle = (2.0 * PI / 360.0) * (gyro.getAngleZ() + 180);
        double distanceToTarget = angleDistance(zAngle, targetAngle);

        Serial.print("Target ");
        Serial.print(targetAngle);
        Serial.print(" zAngle ");
        Serial.print(zAngle);
        Serial.print(" distance ");
        Serial.println(distanceToTarget);

        bool done = fabs(distanceToTarget) <= threshold;

        if (done) {
            Serial.println("Target angle reached");
            setRotationSpeed(0.0, 0);
            if (! printed) {
                strategy = new PrintStrategyDecorator(strategy);
                printed = true;
            }
        } else {
            if (distanceToTarget < 0.0) {
                setRotationSpeed(-speedRPM, PWM);
            } else {
                setRotationSpeed(speedRPM, PWM);
            }
        }
    }
};


void setup() {
    Serial.begin(9600);
    gyro.begin();
    // LED Ring controller is on Auriga D44/PWM
    led.setpin(44);

    led.setColor(0, 0, 0);

    MotorR.setPulse(
            9); // This function used to set the pulse number of encoder code disc.
    MotorL.setPulse(9);
    MotorR.setRatio(
            39.267); // This function used to set the ratio of encoder motor.
    MotorL.setRatio(39.267);
    MotorR.setPosPid(1.8, 0,
                     1.2); // This function used to set the PID parameters for encoder motor's pos.
    MotorL.setPosPid(1.8, 0, 1.2);
    MotorR.setSpeedPid(0.18, 0,
                       0); // This function used to set the PID parameters for encoder motor's speed.
    MotorL.setSpeedPid(0.18, 0, 0);
    MotorR.setMotionMode(
            DIRECT_MODE); // This function used to set the motion mode of encoder motor. (0x00)
    MotorL.setMotionMode(DIRECT_MODE);
    MotorR.setMotorPwm(128);
    MotorL.setMotorPwm(128);
    MotorR.setSpeed(0.0);
    MotorL.setSpeed(0.0);
    strategy = new GoToTargetZAngleStrategy(0.0001, PI * 0.5, 0.1);
    Serial.println("Setup Done!");
}

void loop() {

    MotorR.loop();
    MotorL.loop();
    gyro.update();
    Serial.read();

    strategy->loop();

    double distance = ultraSensor.distanceCm();

    if (counter < MAX_COUNT) {
        Serial.print(counter);
        Serial.print(";");

        Serial.print(distance);
        Serial.print(";");

        Serial.print(gyro.getAngleX());
        Serial.print(";");

        Serial.print(gyro.getAngleY());
        Serial.print(";");

        Serial.print(gyro.getAngleZ());
        Serial.print(";");
        Serial.println("");

        counter += 1;
    }
}
