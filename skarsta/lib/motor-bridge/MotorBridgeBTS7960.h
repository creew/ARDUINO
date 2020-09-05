#ifndef ARDUINO_PROJECTS_ROOT_MOTOR_BRIDGEBTS7960_H
#define ARDUINO_PROJECTS_ROOT_MOTOR_BRIDGEBTS7960_H

#include <Arduino.h>
#include <MotorBridge.h>

#define MIN_SPEED 150
#define MAX_SPEED 255
#define SPEED_STEP_DURATION 15

class MotorBridgeBTS7960 : public MotorBridge {
private:
    uint8_t r_pwm = 0, l_pwm = 0, r_enable = 0, l_enable = 0, speed = 0;
protected:
    void _off() override;

    void _dir_cw() override;

    void _dir_ccw() override;

    void setSpeed(MotorState state, uint8_t speed) override;

    void enable() override;

public:
    MotorBridgeBTS7960(uint8_t _pin1, uint8_t _pin2, uint8_t _pin3, uint8_t _pin4, uint8_t _pin5, uint8_t _pin6,
                uint8_t stop_diff, uint8_t min_change)
            : MotorBridge(_pin1, _pin2, stop_diff, min_change),
              r_pwm(_pin5), l_pwm(_pin6), r_enable(_pin3), l_enable(_pin4) {};

    bool begin() override;

    void cycle() override;
};

#endif //ARDUINO_PROJECTS_ROOT_MOTOR_BRIDGEBTS7960_H