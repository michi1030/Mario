#pragma once

#include "DxLib.h"

// キノコの状態
enum MushroomState {
    STATE_EMERGING, // 出現中
    STATE_MOVING    // 移動中
};

class Mushroom {
private:
    float x, y;             // 位置
    float vx, vy;           // 速度
    int width, height;      // サイズ
    int state;              // 状態
    float startY;           // 出現開始のY座標
    bool active;            // 存在フラグ
    int imageHandle;        // 画像ハンドル

public:
    Mushroom();
    ~Mushroom();

    // 初期化（出現させる位置と画像ハンドルを渡す）
    void Spawn(float startX, float startY, int handle);

    // 更新処理（位置の計算）
    void Update(float groundY);

    // 描画処理
    void Draw() const;

    // ゲッター（プレイヤーとの当たり判定などで使用）
    bool IsActive() const { return active; }
    float GetX() const { return x; }
    float GetY() const { return y; }
    int GetWidth() const { return width; }
    int GetHeight() const { return height; }

    // 非アクティブ化（プレイヤーが取った時用）
    void Deactivate() { active = false; }
};