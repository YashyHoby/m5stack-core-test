#ifndef DISPLAY_H
#define DISPLAY_H

#include <M5Stack.h>

// グリッドサイズや行列の定義
const int rows = 7;
const int cols = 11;
const int gridSize = 20;
const int gridSpacing = 5;
const int displayWidth = 320;
const int displayHeight = 240;

// グリッドデータ構造の定義
struct GridSquare {
    int x, y;
    uint8_t r, g, b;
};

// 外部からアクセス可能なグローバル変数の宣言
extern int cursorX;
extern int cursorY;
extern int selectedX;
extern int selectedY;

// 関数の宣言
void display_setup();
void display_loop();
void initializeGridData();
bool moveCursor(); // 戻り値をboolに変更
bool selectSquare(); // 戻り値をboolに変更
void drawGrid();
void drawThickRect(int x, int y, int w, int h, uint16_t color, int thickness);

#endif // DISPLAY_H
