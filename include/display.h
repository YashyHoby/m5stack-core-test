#ifndef DISPLAY_H
#define DISPLAY_H

#include <M5Stack.h>
#include <FS.h>
#include <SPIFFS.h>
#include "controller.h"

// グリッドの位置とカラーを格納する構造体
struct GridSquare {
    int x;
    int y;
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

// 定数の宣言
const int gridSize = 25; // 正方形のサイズ（ピクセル単位）
const int gridSpacing = 5; // 正方形間の間隔（ピクセル単位）
const int rows = 9;      // 行数
const int cols = 9;      // 列数

// グリッドデータを格納する配列の宣言
extern GridSquare gridData[rows][cols];

// 関数の宣言
void initializeGridData();
void moveCursor();
void selectSquare();
void drawGrid();
void display_setup();
void display_loop();

#endif // DISPLAY_H
