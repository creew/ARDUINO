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
    MotorBridgeBTS7960(uint8_t _sensor1, uint8_t _sensor2, uint8_t _r_enable, uint8_t _l_enable, uint8_t _r_pwm, uint8_t _l_pwm,
                uint8_t stop_diff, uint8_t min_change)
            : MotorBridge(_sensor1, _sensor2, stop_diff, min_change),
              r_pwm(_r_pwm), l_pwm(_l_pwm), r_enable(_r_enable), l_enable(_l_enable) {};

    bool begin() override;

    void cycle() override;
};

#endif //ARDUINO_PROJECTS_ROOT_MOTOR_BRIDGEBTS7960_H
