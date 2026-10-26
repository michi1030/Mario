#pragma once
#include "DxLib.h"

class SuperStar {
private:
    float x;
    float y;
    float vx;
    float vy;
    float boundPower;
    int width;
    int height;
    int state;
    float startY;
    bool active;
    int imageHandle;

public:
    SuperStar();

    void Spawn(float startX, float startYPos, int handle);
    void Update(float groundY);
    void Draw();
    void Deactivate();

    bool IsActive();
    float GetX();
    float GetY();
    int GetWidth();
    int GetHeight();
};