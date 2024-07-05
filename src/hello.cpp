#include <M5Stack.h>    // M5Stackライブラリを使いますという宣言です。Core2の場合はM5Core2.hです
#include "hello.h"

// M5Stackが起動した時に行われる処理を書きます。
void hello_setup() {
    M5.begin();        // M5Stackを初期化します。
    M5.Power.begin();  // バッテリーを初期化します。
    M5.Lcd.print("Hello World!!");  // ディスプレイに文字を出力します。
}

// 繰り返し行う処理を書きます。今回はないので空欄です。
void hello_loop() {
}