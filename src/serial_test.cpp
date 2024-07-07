#include <M5Stack.h>    // M5Stackライブラリを使いますという宣言です。Core2の場合はM5Core2.hです

#include "serial_test.h"


void serial_test_setup() {
  M5.Power.begin(); // バッテリーの初期化
  M5.begin(true, false, true, true); 
  Serial.begin(115200);

  while (!Serial);  // シリアルポートが開かれるのを待つ
  Serial.println("Serial Monitor Test");

// LCDの初期化と基本設定
  M5.Lcd.clear();
  M5.Lcd.setCursor(0, 60);
  M5.Lcd.setTextSize(2);
  M5.Lcd.setTextColor(TFT_WHITE);
  M5.Lcd.println("LCD Initialized");
}

void serial_test_loop() {
  // デバッグメッセージを1秒ごとに送信
  Serial.println("Loop Running");
  delay(1000);
}
