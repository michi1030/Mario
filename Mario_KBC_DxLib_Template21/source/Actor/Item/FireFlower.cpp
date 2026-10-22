#include "FireFlower.h"

FireFlower::FireFlower()
    : x(0), y(0), width(32), height(32),
    state(FLOWER_STATE_EMERGING), startY(0), active(false), imageHandle(-1) {
}

FireFlower::~FireFlower() {}

void FireFlower::Spawn(float startX, float startYPos, int handle) {
    x = startX;
    y = startYPos;
    startY = startYPos;
    imageHandle = handle;
    state = FLOWER_STATE_EMERGING;
    active = true;
}

void FireFlower::Update() {
    if (!active) return;

    // ブロックからニョキッと出てくる処理のみ（横移動はしない）
    if (state == FLOWER_STATE_EMERGING) {
        y -= 1.0f;
        if (startY - y >= height) {
            state = FLOWER_STATE_IDLE;
        }
    }
}

void FireFlower::Draw() const {
    if (!active || imageHandle == -1) return;
    DrawGraph((int)x, (int)y, imageHandle, TRUE);
}