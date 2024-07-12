#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <M5Stack.h>
#include <map>
#include <string>
#include <ESP32Encoder.h>

// pinStates 構造体の宣言
struct pinStates {
    int pin;
    bool state;
};

// グローバル変数の宣言
extern std::map<std::string, pinStates> moveBottons;
extern std::map<std::string, pinStates> actionBottons;
extern std::map<std::string, bool> rotaryBotton;
extern ESP32Encoder encoder;

extern int oldEncoderPosition;
// extern int testCnt;

// 関数の宣言
void setupSwitchPins();
void updateSwitches();
void displaySwitchStates();
void controller_setup();
void controller_loop();

#endif // CONTROLLER_H
