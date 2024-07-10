#include "controller.h"

// グローバル変数の実体定義
std::map<std::string, pinStates> switchPins;
std::map<int, int> switchState;
ESP32Encoder encoder;
std::string lastPressedSwitch = "";
unsigned long lastDebounceTime = 0; // デバウンス用のタイムスタンプ
const unsigned long debounceDelay = 50; // デバウンスの遅延時間（ミリ秒）

void setupSwitchPins() {
    // ピンの番号・状態を、役割をキーとして辞書登録
    switchPins["up"] = {3, LOW};       // up
    switchPins["down"] = {1, LOW};     // down
    switchPins["left"] = {16, LOW};    // left
    switchPins["right"] = {17, LOW};   // right
    switchPins["on"] = {2, LOW};       // on
    switchPins["off"] = {5, LOW};      // off

    // 各スイッチピンを入力モードに設定し、内部プルアップ抵抗を有効にする
    for (const auto& switchPin : switchPins) {
        pinMode(switchPin.second.number, INPUT_PULLUP);
    }
}

std::string getPressedSwitch() {
    static std::string lastSwitch = "";
    static unsigned long lastDebounceTime = 0; // デバウンス用のタイムスタンプ

    std::string pressedSwitch = "";
    unsigned long currentTime = millis(); // 現在の時間を取得

    for (const auto& switchPin : switchPins) {
        int reading = digitalRead(switchPin.second.number);
        if (reading == LOW) {
            if (pressedSwitch.empty()) {
                pressedSwitch = switchPin.first;
            } else {
                // 同時押しが発生した場合、前回の状態を維持
                return lastSwitch;
            }
        }
    }

    if (pressedSwitch != lastSwitch) {
        lastDebounceTime = currentTime; // 最後の状態変化の時間を記録
    }

    if ((currentTime - lastDebounceTime) > debounceDelay) {
        if (pressedSwitch != lastSwitch) {
            lastSwitch = pressedSwitch;
            return pressedSwitch;
        }
    }

    return lastSwitch; // どのスイッチも押されていない場合または状態が変わらない場合
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
    std::string pressedSwitch = getPressedSwitch();

    // 画面がチカチカしないように、スイッチの状態が変わったときのみ画面を更新
    static std::string lastDisplayedSwitch = "";
    if (pressedSwitch != lastDisplayedSwitch) {
        M5.Lcd.clear();
        M5.Lcd.setCursor(0, 0);
        M5.Lcd.setTextSize(2);
        if (!pressedSwitch.empty()) {
            M5.Lcd.print("Switch Pressed: ");
            M5.Lcd.print(pressedSwitch.c_str());
        } else {
            M5.Lcd.print("No Switch Pressed");
        }
        lastDisplayedSwitch = pressedSwitch;
    }

    delay(100); // 状態更新のために少し待つ
}