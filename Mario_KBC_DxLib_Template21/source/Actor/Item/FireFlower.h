#pragma once
#include "DxLib.h"

class FireFlower {
private:
    float x;
    float y;
    int width;
    int height;
    int state;
    float startY;
    bool active;
    int imageHandle;

public:
    FireFlower();

    void Spawn(float startX, float startYPos, int handle);
    void Update();
    void Draw();
    void Deactivate();

    bool IsActive();
    float GetX();
    float GetY();
    int GetWidth();
    int GetHeight();
};