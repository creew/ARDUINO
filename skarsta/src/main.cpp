#include <vector>
#include <Arduino.h>
#include <Display.h>
#include <Calibrator.h>
#include <Keypad.h>
#include <configuration.h>
#include <Watchdog.h>

#ifdef __H_BRIDGE_MOTOR__
#ifdef __VNH2SP30__
#include <MotorBridgeVNH2SP30.h>
#else
#include <MotorBridgeBTS7960.h>
#endif
#else
#include <MotorRelay.h>
#endif

#ifdef __EEPROM__

bool eeprom_valid() {
    for (uint16_t i = ADDRESS_MODE + 4 * sizeof(unsigned int); i < EEPROM.length(); ++i) {
        if (EEPROM[i] != 0) {
            return false;
        }
    }
    return true;
}

void eeprom_reset() {
    LOG("reset eeprom");
    for (unsigned int i = 0; i < EEPROM.length(); ++i)
        updateEEPROM(i, 0);
}

#endif

#ifdef __H_BRIDGE_MOTOR__
#ifdef __VNH2SP30__
MotorBridgeVNH2SP30 motor(SENSOR_PIN0, SENSOR_PIN1, MOTOR_CONTROL_INA, MOTOR_CONTROL_INB, MOTOR_PWM, MOTOR_STATUS, MOTOR_CURRENT, STOP_POS_DIFF, MINIMUM_POS_CHANGE);
#else
MotorBridgeBTS7960 motor(SENSOR_PIN0, SENSOR_PIN1, R_EN, L_EN, R_PWM, L_PWM, STOP_POS_DIFF, MINIMUM_POS_CHANGE);
#endif
#else
MotorRelay motor(SENSOR_PIN0, SENSOR_PIN1, POWER_RELAY, DIRECTION_RELAY, STOP_POS_DIFF, MINIMUM_POS_CHANGE);
#endif
Display display(DISPLAY_PIN_CLK, DISPLAY_PIN_DIO, FADE_TIMEOUT);
Watchdog watchdog(&motor, WATCHDOG_TIMEOUT, WATCHDOG_DEADLOCK_CHANGE, WATCHDOG_OTHER_CHANGE);
Calibrator calibrator(&motor);
Keypad keypad(&motor, &display, &calibrator, BUTTON_DOWN, BUTTON_UP, BUTTON_RST, BUTTON_P0, BUTTON_P1, BUTTON_P2);
Service * services[] = {&calibrator, &watchdog, &keypad, &motor, &display};

#ifdef __WATCHDOG__
SafetyTrigger stallTrigger(&motor, &display, STOPPED, WATCHDOG_TOLERANCE);
SafetyTrigger runawayTrigger(&motor, &display, STARTED, WATCHDOG_TOLERANCE);
#endif

void setup() {
    LOG_INIT(Serial.begin(9600), &Serial);
    LOG("starting");
#ifdef __EEPROM__
    if (!eeprom_valid())
        eeprom_reset();
#endif
    watchdog.add_trigger(&calibrator);
#ifdef __WATCHDOG__
    watchdog.add_trigger(&stallTrigger);
    watchdog.add_trigger(&runawayTrigger);
#endif
    bool failed = false;
    for (const auto &service: services)
        failed |= !service->begin();

    if (failed) {
        for (const auto &service: services)
            service->disable(INIT);
    }
    LOG("started");
}

void loop() {
    for (const auto &service: services)
        service->cycle();
}