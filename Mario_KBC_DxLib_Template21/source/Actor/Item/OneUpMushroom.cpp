#include "OneUpMushroom.h"

OneUpMushroom::OneUpMushroom()
    : x(0), y(0), vx(1.5f), vy(0), width(32), height(32),
    state(ONEUP_STATE_EMERGING), startY(0), active(false), imageHandle(-1) {
}

OneUpMushroom::~OneUpMushroom() {}

void OneUpMushroom::Spawn(float startX, float startYPos, int handle) {
    x = startX;
    y = startYPos;
    startY = startYPos;
    imageHandle = handle;
    vx = 1.5f;
    vy = 0.0f;
    state = ONEUP_STATE_EMERGING;
    active = true;
}

void OneUpMushroom::Update(float groundY) {
    if (!active) return;

    if (state == ONEUP_STATE_EMERGING) {
        y -= 1.0f;
        if (startY - y >= height) {
            state = ONEUP_STATE_MOVING;
        }
    }
    else if (state == ONEUP_STATE_MOVING) {
        x += vx;
        vy += 0.5f; // d—Í
        y += vy;

        if (y + height >= groundY) {
            y = groundY - height;
            vy = 0.0f;
        }
    }
}

void OneUpMushroom::Draw() const {
    if (!active || imageHandle == -1) return;
    DrawGraph((int)x, (int)y, imageHandle, TRUE);
}