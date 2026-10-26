#pragma once
#include "DxLib.h"

class Mushroom {
private:
    // 外部から直接書き換えられたくない変数はすべて private
    float x;
    float y;
    float vx;
    float vy;
    int width;
    int height;
    int state;          // 0: 出現中, 1: 移動中
    float startY;
    bool active;        // 画面に存在するかどうか
    int imageHandle;

public:
    Mushroom();

    // 操作・更新・描画用関数
    void Spawn(float startX, float startYPos, int handle);
    void Update(float groundY);
    void Draw();
    void Deactivate(); // 安全に非アクティブ（消滅）にする関数

    // 値を取得するための関数（ゲッター）
    bool IsActive();
    float GetX();
    float GetY();
    int GetWidth();
    int GetHeight();
};