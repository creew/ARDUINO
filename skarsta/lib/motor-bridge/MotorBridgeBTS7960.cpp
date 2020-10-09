#include "MotorBridgeBTS7960.h"

bool MotorBridgeBTS7960::begin() {
    if (!Motor::begin())
        return false;

    initPin(r_enable);
    initPin(l_enable);
    initPin(r_pwm);
    initPin(l_pwm);
    this->enable();

    return true;
}

void MotorBridgeBTS7960::_off() {
    digitalWrite(r_enable, LOW);
    digitalWrite(l_enable, LOW);
    this->speed = 0;
    analogWrite(r_pwm, 0);
    analogWrite(l_pwm, 0);
}

void MotorBridgeBTS7960::enable() {
    digitalWrite(r_enable, HIGH);
    digitalWrite(l_enable, HIGH);
}

void MotorBridgeBTS7960::_dir_cw() {
    setSpeed(CW, MIN_SPEED);
    this->enable();
}

void MotorBridgeBTS7960::_dir_ccw() {
    setSpeed(CCW, MIN_SPEED);
    this->enable();
}

void MotorBridgeBTS7960::setSpeed(MotorState state, uint8_t speed) {
    if (state == OFF) {
        return;
    }
    this->speed = speed;
    LOG("m | speed:%d", speed);

    if (state == CCW) {
        analogWrite(l_pwm, 0);
        analogWrite(r_pwm, speed);
    } else if (state == CW) {
        analogWrite(r_pwm, 0);
        analogWrite(l_pwm, speed);
    }
}

void MotorBridgeBTS7960::cycle() {
    if (elapsed >= SPEED_STEP_DURATION && speed < MAX_SPEED && speed >= MIN_SPEED) {
        setSpeed(get_state(), speed + 5 % (MAX_SPEED + 1));
        elapsed = 0;
    }

    Motor::cycle();
}