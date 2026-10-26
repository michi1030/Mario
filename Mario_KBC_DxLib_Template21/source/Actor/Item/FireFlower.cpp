#include "FireFlower.h"

FireFlower::FireFlower() {
    x = 0.0f;
    y = 0.0f;
    width = 32;
    height = 32;
    state = 0;
    startY = 0.0f;
    active = false;
    imageHandle = -1;
}

void FireFlower::Spawn(float startX, float startYPos, int handle) {
    x = startX;
    y = startYPos;
    startY = startYPos;
    imageHandle = handle;
    state = 0;
    active = true;
}

void FireFlower::Update() {
    if (active == false) return;

    if (state == 0) {
        y -= 1.0f;
        if (startY - y >= height) {
            state = 1;
        }
    }
}

void FireFlower::Draw() {
    if (active == false || imageHandle == -1) return;
    DrawGraph((int)x, (int)y, imageHandle, TRUE);
}

void FireFlower::Deactivate() {
    active = false;
}

bool FireFlower::IsActive() { return active; }
float FireFlower::GetX() { return x; }
float FireFlower::GetY() { return y; }
int FireFlower::GetWidth() { return width; }
int FireFlower::GetHeight() { return height; }