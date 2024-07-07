#include <M5Stack.h>    // M5Stackライブラリを使いますという宣言です。Core2の場合はM5Core2.hです
#include <Encoder.h>

#include "rotary_encoder_test.h"

// エンコーダのピン設定
Encoder myEnc(32,33); // AピンとBピンを接続したM5Stackのピン番号

int oldPosition  = -999;
void rotary_encoder_test_setup() {
  M5.Power.begin(); // バッテリーの初期化
  M5.begin();
  
  // LCDの初期化と基本設定
  M5.Lcd.clear();
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.setTextSize(2);
  M5.Lcd.setTextColor(TFT_WHITE);
  M5.Lcd.println("LCD Initialized");
}

void rotary_encoder_test_loop() {
//   long newPosition = myEnc.read();
//   if (newPosition != oldPosition) {
//     oldPosition = newPosition;

//     // M5.Lcdを使用して画面に表示
//     M5.Lcd.clear();
//     M5.Lcd.setCursor(0, 30);
//     M5.Lcd.printf("Encoder Position: %ld", newPosition);
//   }

  delay(100); // ループの待機時間
}