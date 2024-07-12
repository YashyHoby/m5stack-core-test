#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <M5Stack.h>
#include <map>
#include <string>
#include <ESP32Encoder.h>

struct pinStates {
    int pin;
    bool state;
};

// グローバル変数の宣言
extern std::map<std::string, pinStates> switchPins;
extern std::map<int, int> switchState;
extern ESP32Encoder encoder;
extern std::string lastPressedSwitch;
extern unsigned long lastDebounceTime;
extern const unsigned long debounceDelay;

// 関数のプロトタイプ宣言
void setupSwitchPins();
void controller_setup();
void controller_loop();
std::string getPressedSwitch();

#endif // CONTROLLER_H
