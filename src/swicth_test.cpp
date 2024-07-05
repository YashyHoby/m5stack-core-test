#include <M5Stack.h>    // M5Stackライブラリを使いますという宣言です。Core2の場合はM5Core2.hです
#include "swicth_test.h"

const int switchPin1 = 21;  // タクトスイッチ1を接続するGPIOピン
const int switchPin2 = 22;  // タクトスイッチ2を接続するGPIOピン
const int switchPin3 = 23;  // タクトスイッチ3を接続するGPIOピン

// M5Stackが起動した時に行われる処理を書きます。
void swicth_test_setup() {
    M5.begin();       // M5Stackの初期化
    M5.Power.begin(); // バッテリーの初期化

    // スイッチピンを入力モードに設定し、内部プルアップ抵抗を有効にする
    pinMode(switchPin1, INPUT_PULLUP);
    pinMode(switchPin2, INPUT_PULLUP);
    pinMode(switchPin3, INPUT_PULLUP);

    // 画面をクリアして、初期メッセージを表示
    M5.Lcd.clear();
    M5.Lcd.setCursor(0, 0);
    M5.Lcd.setTextSize(2);
    M5.Lcd.print("Switch State:");
}

// 繰り返し行う処理を書きます。今回はないので空欄です。
void swicth_test_loop() {
        // スイッチ1の状態をチェック
    int state1 = digitalRead(switchPin1);
    if (state1 == LOW) {
        M5.Lcd.setCursor(0, 30);
        M5.Lcd.print("Switch 1: Pressed ");
    } else {
        M5.Lcd.setCursor(0, 30);
        M5.Lcd.print("Switch 1: Released");
    }

    // スイッチ2の状態をチェック
    int state2 = digitalRead(switchPin2);
    if (state2 == LOW) {
        M5.Lcd.setCursor(0, 60);
        M5.Lcd.print("Switch 2: Pressed ");
    } else {
        M5.Lcd.setCursor(0, 60);
        M5.Lcd.print("Switch 2: Released");
    }

    // スイッチ3の状態をチェック
    int state3 = digitalRead(switchPin3);
    if (state3 == LOW) {
        M5.Lcd.setCursor(0, 90);
        M5.Lcd.print("Switch 3: Pressed ");
    } else {
        M5.Lcd.setCursor(0, 90);
        M5.Lcd.print("Switch 3: Released");
    }

    delay(100); // 状態更新のために少し待つ
}