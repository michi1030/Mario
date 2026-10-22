
#pragma once
#include "DxLib.h"

enum OneUpState {
    ONEUP_STATE_EMERGING,
    ONEUP_STATE_MOVING
};

class OneUpMushroom {
private:
    float x, y;
    float vx, vy;
    int width, height;
    int state;
    float startY;
    bool active;
    int imageHandle;

public:
    OneUpMushroom();
    ~OneUpMushroom();

    void Spawn(float startX, float startYPos, int handle);
    void Update(float groundY);
    void Draw() const;

    bool IsActive() const { return active; }
    float GetX() const { return x; }
    float GetY() const { return y; }
    int GetWidth() const { return width; }
    int GetHeight() const { return height; }
    void Deactivate() { active = false; }
};