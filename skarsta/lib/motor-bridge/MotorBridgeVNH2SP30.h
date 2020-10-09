#ifndef ARDUINO_PROJECTS_ROOT_MOTOR_BRIDGEVNH2SP30_H
#define ARDUINO_PROJECTS_ROOT_MOTOR_BRIDGEVNH2SP30_H

#include <Arduino.h>
#include <MotorBridge.h>

#define MIN_SPEED 150
#define MAX_SPEED 255
#define SPEED_STEP_DURATION 15

class MotorBridgeVNH2SP30 : public MotorBridge {
private:
    uint8_t pwm= 0, ina = 0, inb = 0, status = 0, curr = 0, speed = 0;
protected:
    void _off() override;

    void _dir_cw() override;

    void _dir_ccw() override;

    void setSpeed(MotorState state, uint8_t speed) override;

    void enable() override;

public:
    MotorBridgeVNH2SP30(uint8_t _pin1, uint8_t _pin2, uint8_t _ina, uint8_t _inb, uint8_t _pwm, uint8_t _status, uint8_t _curr,
                uint8_t stop_diff, uint8_t min_change)
            : MotorBridge(_pin1, _pin2, stop_diff, min_change),
              pwm(_pwm), ina(_ina), inb(_inb), status(_status), curr(_curr) {};

    bool begin() override;

    void cycle() override;
};

#endif //ARDUINO_PROJECTS_ROOT_MOTOR_BRIDGEVNH2SP30_H
