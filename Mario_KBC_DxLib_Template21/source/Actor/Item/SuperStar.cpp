#include "SuperStar.h"

SuperStar::SuperStar() {
    x = 0.0f;
    y = 0.0f;
    vx = 2.0f;
    vy = 0.0f;
    boundPower = -7.0f;
    width = 32;
    height = 32;
    state = 0;
    startY = 0.0f;
    active = false;
    imageHandle = -1;
}

void SuperStar::Spawn(float startX, float startYPos, int handle) {
    x = startX;
    y = startYPos;
    startY = startYPos;
    imageHandle = handle;
    vx = 2.0f;
    vy = 0.0f;
    state = 0;
    active = true;
}

void SuperStar::Update(float groundY) {
    if (active == false) return;

    if (state == 0) {
        y -= 1.0f;
        if (startY - y >= height) {
            state = 1;
            vy = boundPower;
        }
    }
    else if (state == 1) {
        x += vx;

        vy += 0.4f;
        y += vy;

        if (y + height >= groundY) {
            y = groundY - height;
            vy = boundPower;
        }
    }
}

void SuperStar::Draw() {
    if (active == false || imageHandle == -1) return;
    DrawGraph((int)x, (int)y, imageHandle, TRUE);
}

void SuperStar::Deactivate() {
    active = false;
}

bool SuperStar::IsActive() { return active; }
float SuperStar::GetX() { return x; }
float SuperStar::GetY() { return y; }
int SuperStar::GetWidth() { return width; }
int SuperStar::GetHeight() { return height; }