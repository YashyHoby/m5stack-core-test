#include "controller.h"

// グローバル変数の実体定義
std::map<std::string, pinStates> moveBottons;
std::map<std::string, pinStates> actionBottons;
std::map<std::string, bool> rotaryBotton;
ESP32Encoder encoder;

int oldEncoderPosition  = -999;
//int testCnt  = 0;


void setupSwitchPins() {
    // ピンの番号・状態を、役割をキーとして辞書登録
    moveBottons["up"] = {3, false};       // up
    moveBottons["down"] = {1, false};     // down
    moveBottons["left"] = {16, false};    // left
    moveBottons["right"] = {17, false};   // right
    actionBottons["select"] = {2, false};       // on
    actionBottons["cancel"] = {5, false};      // off
    rotaryBotton["turnRight"] = false;
    rotaryBotton["turnLeft"] = false;

    // 各スイッチピンを入力モードに設定し、内部プルアップ抵抗を有効にする
    for (const auto& moveBotton : moveBottons) {
        pinMode(moveBotton.second.pin, INPUT_PULLUP);
    }
    // 各スイッチピンを入力モードに設定し、内部プルアップ抵抗を有効にする
    for (const auto& actionBotton : actionBottons) {
        pinMode(actionBotton.second.pin, INPUT_PULLUP);
    }

    pinMode(35, INPUT_PULLUP); // 内部プルアップ抵抗の設定
    pinMode(36, INPUT_PULLUP); // 内部プルアップ抵抗の設定

    // エンコーダの初期化
    encoder.attachSingleEdge(35, 36); // A相とB相のピンを指定
    encoder.clearCount(); // カウンタの初期化
}

void updateSwitches() {
    for (auto& moveBotton : moveBottons){
        if (digitalRead(moveBotton.second.pin) == LOW) {
            moveBotton.second.state = true;
        } else {
            moveBotton.second.state = false;
        }
    }
    for (auto& actionBotton : actionBottons){
        if (digitalRead(actionBotton.second.pin) == LOW) {
            actionBotton.second.state = true;
        } else {
            actionBotton.second.state = false;
        }
    }

    long encoderPosition = encoder.getCount();
    if (encoderPosition > oldEncoderPosition){
        rotaryBotton["turnRight"] = true;
        rotaryBotton["turnLeft"] = false;
        //testCnt++;
    } else if (encoderPosition < oldEncoderPosition) {
        rotaryBotton["turnRight"] = false;
        rotaryBotton["turnLeft"] = true;
        //testCnt--;
    } else {
        rotaryBotton["turnRight"] = false;
        rotaryBotton["turnLeft"] = false;
    }
    oldEncoderPosition = encoderPosition;
}

void displaySwitchStates() {
    // M5.Lcd.clear();
    M5.Lcd.setCursor(0, 0);
    // M5.Lcd.setTextSize(2);
    
    // Move Buttons
    M5.Lcd.print("Move Buttons:\n");
    for (const auto& moveBotton : moveBottons) {
        M5.Lcd.print(moveBotton.first.c_str());
        M5.Lcd.print(": ");
        M5.Lcd.println(moveBotton.second.state ? "Pressed" : "Released");
    }

    // Action Buttons
    M5.Lcd.print("Action Buttons:\n");
    for (const auto& actionBotton : actionBottons) {
        M5.Lcd.print(actionBotton.first.c_str());
        M5.Lcd.print(": ");
        M5.Lcd.println(actionBotton.second.state ? "Pressed" : "Released");
    }

    // Rotary Buttons
    M5.Lcd.print("Rotary Buttons:\n");
    for (const auto& rotary : rotaryBotton) {
        M5.Lcd.print(rotary.first.c_str());
        M5.Lcd.print(": ");
        M5.Lcd.println(rotary.second ? "Active" : "Inactive");
        //M5.Lcd.println(testCnt);
    }
}

void controller_setup() {
    M5.Power.begin(); // バッテリーの初期化
    M5.begin();       // M5Stackの初期化

    setupSwitchPins();

    // 画面をクリアして、初期メッセージを表示
    M5.Lcd.clear();
    M5.Lcd.setCursor(0, 0);
    M5.Lcd.setTextSize(2);
    M5.Lcd.print("Switch States:");
}

void controller_loop() {
    updateSwitches();
    displaySwitchStates();
    delay(100); // 状態更新のために少し待つ
}
