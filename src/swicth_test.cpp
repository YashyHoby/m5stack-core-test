#include <M5Stack.h>    // M5Stackライブラリを使いますという宣言です。Core2の場合はM5Core2.hです
#include <map>
#include <string>

#include "swicth_test.h"

// スイッチのラベルをキー、GPIOピンを値とする辞書
std::map<std::string, int> switchPins;

void swicth_test_setup() {
    M5.Power.begin(); // バッテリーの初期化
    M5.begin();       // M5Stackの初期化

    switchPins["up"] = 21;
    switchPins["down"] = 2;
    switchPins["left"] = 12;
    switchPins["right"] = 15;

    // 各スイッチピンを入力モードに設定し、内部プルアップ抵抗を有効にする
    for (const auto& switchPin : switchPins) {
        pinMode(switchPin.second, INPUT_PULLUP);
    }

    // 画面をクリアして、初期メッセージを表示
    M5.Lcd.clear();
    M5.Lcd.setCursor(0, 0);
    M5.Lcd.setTextSize(2);
    M5.Lcd.print("Switch States:");
}

void swicth_test_loop() {
    int line = 1;
    // 各スイッチの状態をチェックして表示
    for (const auto& switchPin : switchPins) {
        int state = digitalRead(switchPin.second);
        M5.Lcd.setCursor(0, 30 * line);  // 表示位置を調整
        M5.Lcd.print(switchPin.first.c_str());
        M5.Lcd.print(": ");
        if (state == LOW) {
            M5.Lcd.print("Pressed ");
        } else {
            M5.Lcd.print("Released");
        }
        line++;
    }

    delay(100); // 状態更新のために少し待つ
}