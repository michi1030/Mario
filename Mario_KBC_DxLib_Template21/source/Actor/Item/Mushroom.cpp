#include "Mushroom.h"

Mushroom::Mushroom()
    : x(0), y(0), vx(1.5f), vy(0), width(32), height(32),
    state(STATE_EMERGING), startY(0), active(false), imageHandle(-1) {
}

Mushroom::~Mushroom() {
}

void Mushroom::Spawn(float startX, float startYPos, int handle) {
    x = startX;
    y = startYPos;
    startY = startYPos;
    imageHandle = handle;
    vx = 1.5f;             // 右方向に動く
    vy = 0.0f;
    state = STATE_EMERGING;
    active = true;         // 画面上に存在させる
}

void Mushroom::Update(float groundY) {
    if (!active) return;

    // 【状態1】ニョキッと出てくる処理
    if (state == STATE_EMERGING) {
        y -= 1.0f;
        if (startY - y >= height) {
            state = STATE_MOVING;
        }
    }
    // 【状態2】出現後の通常移動
    else if (state == STATE_MOVING) {
        x += vx;

        // 重力
        vy += 0.5f;
        y += vy;

        // 着地判定（仮の地表判定）
        if (y + height >= groundY) {
            y = groundY - height;
            vy = 0.0f;
        }
    }
}

void Mushroom::Draw() const {
    if (!active || imageHandle == -1) return;

    // キノコの描画（透過ON）
    DrawGraph((int)x, (int)y, imageHandle, TRUE);
}