#include "MotorBridgeVNH2SP30.h"

bool MotorBridgeVNH2SP30::begin() {
    if (!Motor::begin())
        return false;

    initPin(ina);
    initPin(inb);
    initPin(pwm);
    if (status > 0) 
        pinMode(status, INPUT_PULLUP);
    this->enable();

    return true;
}

void MotorBridgeVNH2SP30::_off() {
    digitalWrite(ina, LOW);
    digitalWrite(inb, LOW);
    this->speed = 0;
    analogWrite(pwm, 0);
}

void MotorBridgeVNH2SP30::enable() {

}

void MotorBridgeVNH2SP30::_dir_cw() {
    setSpeed(CW, MIN_SPEED);
    this->enable();
}

void MotorBridgeVNH2SP30::_dir_ccw() {
    setSpeed(CCW, MIN_SPEED);
    this->enable();
}

void MotorBridgeVNH2SP30::setSpeed(MotorState state, uint8_t speed) {
    if (state == OFF) {
        return;
    }
    this->speed = speed;
    LOG("m | speed:%d", speed);

    if (state == CCW) {
        digitalWrite(ina, LOW);
        digitalWrite(inb, HIGH);
    } else if (state == CW) {
        digitalWrite(ina, HIGH);
        digitalWrite(inb, LOW);
    }
    analogWrite(pwm, speed);
}

void MotorBridgeVNH2SP30::cycle() {
    if (elapsed >= SPEED_STEP_DURATION && speed < MAX_SPEED && speed >= MIN_SPEED) {
        setSpeed(get_state(), speed + 5 % (MAX_SPEED + 1));
        elapsed = 0;
    }

    Motor::cycle();
}