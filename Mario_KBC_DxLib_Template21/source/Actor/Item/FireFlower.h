#pragma once
#include "DxLib.h"

enum FireFlowerState {
    FLOWER_STATE_EMERGING,
    FLOWER_STATE_IDLE // èoåªäÆóπÅEÇªÇÃèÍÇ…Ç∆Ç«Ç‹ÇÈ
};

class FireFlower {
private:
    float x, y;
    int width, height;
    int state;
    float startY;
    bool active;
    int imageHandle;

public:
    FireFlower();
    ~FireFlower();

    void Spawn(float startX, float startYPos, int handle);
    void Update();
    void Draw() const;

    bool IsActive() const { return active; }
    float GetX() const { return x; }
    float GetY() const { return y; }
    int GetWidth() const { return width; }
    int GetHeight() const { return height; }
    void Deactivate() { active = false; }
};