#include "display.h"
#include "controller.h"

// グローバル変数の定義
int cursorX = 0;         // カーソルのX座標
int cursorY = 0;         // カーソルのY座標
int selectedX = -1;      // 選択された正方形のX座標
int selectedY = -1;      // 選択された正方形のY座標

// タイミング制御用の変数
unsigned long lastMoveTime = 0;
unsigned long pressStartTime = 0;
bool isPressing = false;

// 前回のボタン状態を保持する変数
bool lastUpState = false;
bool lastDownState = false;
bool lastLeftState = false;
bool lastRightState = false;
bool lastSelectState = false;

// グリッドデータを格納する配列の宣言
GridSquare gridData[rows][cols];

// オフスクリーンバッファの宣言
TFT_eSprite buffer = TFT_eSprite(&M5.Lcd);

// カラフルなグラデーションデータを初期化する関数
void initializeGridData() {
    // カラーデータ（画像のカラーパレットを元に設定）
    const uint8_t colorData[rows][cols][3] = {
        { {255, 0, 0}, {255, 64, 0}, {255, 128, 0}, {255, 192, 0}, {255, 255, 0}, {192, 255, 0}, {128, 255, 0}, {64, 255, 0}, {0, 255, 0}, {0, 255, 64}, {0, 255, 128} },
        { {255, 0, 64}, {255, 64, 64}, {255, 128, 64}, {255, 192, 64}, {255, 255, 64}, {192, 255, 64}, {128, 255, 64}, {64, 255, 64}, {0, 255, 64}, {0, 255, 128}, {0, 255, 192} },
        { {255, 0, 128}, {255, 64, 128}, {255, 128, 128}, {255, 192, 128}, {255, 255, 128}, {192, 255, 128}, {128, 255, 128}, {64, 255, 128}, {0, 255, 128}, {0, 255, 192}, {0, 255, 255} },
        { {255, 0, 192}, {255, 64, 192}, {255, 128, 192}, {255, 192, 192}, {255, 255, 192}, {192, 255, 192}, {128, 255, 192}, {64, 255, 192}, {0, 255, 192}, {0, 255, 255}, {64, 255, 255} },
        { {255, 0, 255}, {255, 64, 255}, {255, 128, 255}, {255, 192, 255}, {255, 255, 255}, {192, 255, 255}, {128, 255, 255}, {64, 255, 255}, {0, 255, 255}, {64, 255, 255}, {128, 255, 255} },
        { {192, 0, 255}, {192, 64, 255}, {192, 128, 255}, {192, 192, 255}, {192, 255, 255}, {128, 255, 255}, {64, 255, 255}, {0, 255, 255}, {0, 192, 255}, {0, 128, 255}, {0, 64, 255} },
        { {128, 0, 255}, {128, 64, 255}, {128, 128, 255}, {128, 192, 255}, {128, 255, 255}, {64, 255, 255}, {0, 255, 255}, {0, 192, 255}, {0, 128, 255}, {0, 64, 255}, {0, 0, 255} }
    };

    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++) {
            gridData[y][x] = {x, y, colorData[y][x][0], colorData[y][x][1], colorData[y][x][2]};
        }
    }
}

// カーソルを移動する関数
bool moveCursor() {
    unsigned long currentTime = millis();
    bool moved = false;

    // 長押し処理
    if (moveBottons["up"].state || moveBottons["down"].state || moveBottons["left"].state || moveBottons["right"].state) {
        if (!isPressing) {
            isPressing = true;
            pressStartTime = currentTime;
        }

        if ((currentTime - pressStartTime > 800) && (currentTime - lastMoveTime > 200)) {
            if (moveBottons["up"].state && cursorY > 0) {
                cursorY--;
                moved = true;
            } else if (moveBottons["down"].state && cursorY < rows - 1) {
                cursorY++;
                moved = true;
            } else if (moveBottons["left"].state && cursorX > 0) {
                cursorX--;
                moved = true;
            } else if (moveBottons["right"].state && cursorX < cols - 1) {
                cursorX++;
                moved = true;
            }
            lastMoveTime = currentTime;
        }
    } else {
        isPressing = false;
    }

    // クリック処理
    if (currentTime - lastMoveTime > 200) {
        if (moveBottons["up"].state && cursorY > 0) {
            cursorY--;
            lastMoveTime = currentTime;
            moved = true;
        } else if (moveBottons["down"].state && cursorY < rows - 1) {
            cursorY++;
            lastMoveTime = currentTime;
            moved = true;
        } else if (moveBottons["left"].state && cursorX > 0) {
            cursorX--;
            lastMoveTime = currentTime;
            moved = true;
        } else if (moveBottons["right"].state && cursorX < cols - 1) {
            cursorX++;
            lastMoveTime = currentTime;
            moved = true;
        }
    }

    return moved;
}

// カーソルがある位置の正方形を選択する関数
bool selectSquare() {
    if (actionBottons["select"].state && !lastSelectState) {
        selectedX = cursorX;
        selectedY = cursorY;
        lastSelectState = actionBottons["select"].state;
        return true;
    }
    lastSelectState = actionBottons["select"].state;
    return false;
}

// 太い線を描画する関数
void drawThickRect(int x, int y, int w, int h, uint16_t color, int thickness) {
    for (int i = 0; i < thickness; i++) {
        buffer.drawRect(x + i, y + i, w - (2 * i), h - (2 * i), color);
    }
}

// グリッドを描画する関数
void drawGrid() {
    // オフスクリーンバッファの初期化
    buffer.createSprite(displayWidth, displayHeight);
    buffer.fillScreen(TFT_BLACK);

    // 画面の中央にグリッドを配置するためのオフセットを計算
    int totalGridWidth = cols * (gridSize + gridSpacing) - gridSpacing;
    int totalGridHeight = rows * (gridSize + gridSpacing) - gridSpacing;
    int offsetX = (displayWidth - totalGridWidth) / 2;
    int offsetY = (displayHeight - totalGridHeight) / 2;

    int borderThickness = 4; // 線の太さ
    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++) {
            GridSquare& square = gridData[y][x];
            uint16_t color = buffer.color565(square.r, square.g, square.b);
            int posX = offsetX + x * (gridSize + gridSpacing);
            int posY = offsetY + y * (gridSize + gridSpacing);
            buffer.fillRect(posX, posY, gridSize, gridSize, color);
            drawThickRect(posX - 1, posY - 1, gridSize + 2, gridSize + 2, TFT_BLACK, borderThickness); // 線の太さを指定
        }
    }
    // カーソルを描画
    int cursorPosX = offsetX + cursorX * (gridSize + gridSpacing);
    int cursorPosY = offsetY + cursorY * (gridSize + gridSpacing);
    drawThickRect(cursorPosX - 1, cursorPosY - 1, gridSize + 2, gridSize + 2, TFT_WHITE, borderThickness); // 線の太さを指定

    // オフスクリーンバッファから画面に転送
    buffer.pushSprite(0, 0);

    // バッファを削除
    buffer.deleteSprite();
}

// ディスプレイの初期設定を行う関数
void display_setup() {
    M5.Power.begin(); // バッテリーの初期化
    M5.begin();       // M5Stackの初期化

    setupSwitchPins(); // スイッチピンの設定

    initializeGridData(); // グリッドデータを初期化

    // 画面をクリアして、初期メッセージを表示
    M5.Lcd.clear();
    M5.Lcd.setCursor(0, 0);
    M5.Lcd.setTextSize(2);
}

// ディスプレイのループ処理を行う関数
void display_loop() {
    updateSwitches(); // スイッチの状態を更新

    // カーソル移動または正方形選択が発生した場合のみ画面を更新
    if (moveCursor() || selectSquare()) {
        drawGrid();       // グリッドを描画
    }

    delay(100);       // 状態更新のために少し待つ
}
