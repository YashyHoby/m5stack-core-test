#include "display.h"
#include "controller.h"

// rotary_encoder_test
// hello
// serial_test
// swicth_test


void setup() {
    //controller_setup();  // 選択したプログラムのsetup関数を呼び出す
    display_setup();
}

void loop() {
    //controller_loop();  // 選択したプログラムのloop関数を呼び出す
    display_loop();
}