
#include "SuperStar.h"

SuperStar::SuperStar()
    : x(0), y(0), vx(2.0f), vy(0), boundPower(-7.0f), width(32), height(32),
    state(STAR_STATE_EMERGING), startY(0), active(false), imageHandle(-1) {
}

SuperStar::~SuperStar() {}

void SuperStar::Spawn(float startX, float startYPos, int handle) {
    x = startX;
    y = startYPos;
    startY = startYPos;
    imageHandle = handle;
    vx = 2.0f;
    vy = 0.0f;
    state = STAR_STATE_EMERGING;
    active = true;
}

void SuperStar::Update(float groundY) {
    if (!active) return;

    if (state == STAR_STATE_EMERGING) {
        y -= 1.0f;
        if (startY - y >= height) {
            state = STAR_STATE_BOUNCING;
            vy = boundPower; // 出現直後に最初のジャンプ
        }
    }
    else if (state == STAR_STATE_BOUNCING) {
        x += vx;

        // 重力加算
        vy += 0.4f;
        y += vy;

        // 床に着地したら跳ね返る（バウンド）
        if (y + height >= groundY) {
            y = groundY - height;
            vy = boundPower; // 上方向への速度を与える
        }
    }
}

void SuperStar::Draw() const {
    if (!active || imageHandle == -1) return;
    DrawGraph((int)x, (int)y, imageHandle, TRUE);
}