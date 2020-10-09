#ifndef ARDUINO_PROJECTS_ROOT_MOTOR_BRIDGE_H
#define ARDUINO_PROJECTS_ROOT_MOTOR_BRIDGE_H

#include <Arduino.h>
#include <Motor.h>

class MotorBridge : public Motor {
protected:
    virtual void _off() = 0;

    virtual void _dir_cw() = 0;

    virtual void _dir_ccw() = 0;

    virtual void setSpeed(MotorState state, uint8_t speed) = 0;

    virtual void enable() = 0;

public:
    MotorBridge(uint8_t _pin1, uint8_t _pin2, uint8_t stop_diff, uint8_t min_change)
            : Motor(_pin1, _pin2, stop_diff, min_change){};

    virtual bool begin() = 0;

    virtual void cycle() = 0;
};

#endif //ARDUINO_PROJECTS_ROOT_MOTOR_BRIDGE_H
