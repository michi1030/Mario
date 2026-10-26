#include "OneUpMushroom.h"

OneUpMushroom::OneUpMushroom() {
    x = 0.0f;
    y = 0.0f;
    vx = 1.5f;
    vy = 0.0f;
    width = 32;
    height = 32;
    state = 0;
    startY = 0.0f;
    active = false;
    imageHandle = -1;
}

void OneUpMushroom::Spawn(float startX, float startYPos, int handle) {
    x = startX;
    y = startYPos;
    startY = startYPos;
    imageHandle = handle;
    vx = 1.5f;
    vy = 0.0f;
    state = 0;
    active = true;
}

void OneUpMushroom::Update(float groundY) {
    if (active == false) return;

    if (state == 0) {
        y -= 1.0f;
        if (startY - y >= height) {
            state = 1;
        }
    }
    else if (state == 1) {
        x += vx;

        vy += 0.5f;
        y += vy;

        if (y + height >= groundY) {
            y = groundY - height;
            vy = 0.0f;
        }
    }
}

void OneUpMushroom::Draw() {
    if (active == false || imageHandle == -1) return;
    DrawGraph((int)x, (int)y, imageHandle, TRUE);
}

void OneUpMushroom::Deactivate() {
    active = false;
}

bool OneUpMushroom::IsActive() { return active; }
float OneUpMushroom::GetX() { return x; }
float OneUpMushroom::GetY() { return y; }
int OneUpMushroom::GetWidth() { return width; }
int OneUpMushroom::GetHeight() { return height; }