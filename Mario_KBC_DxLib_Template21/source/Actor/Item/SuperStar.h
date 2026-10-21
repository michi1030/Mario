#pragma once
#include "DxLib.h"

enum StarState {
    STAR_STATE_EMERGING,
    STAR_STATE_BOUNCING
};

class SuperStar {
private:
    float x, y;
    float vx, vy;
    float boundPower;  // ’µ‚Ë•Ô‚é‹­‚³
    int width, height;
    int state;
    float startY;
    bool active;
    int imageHandle;

public:
    SuperStar();
    ~SuperStar();

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