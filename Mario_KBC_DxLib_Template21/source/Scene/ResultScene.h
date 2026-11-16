#pragma once

#include "SceneBase.h"

class Sprite;
class DivSprite;
/**
 * @class ResultScene
 * @brief ゲームのリザルト（結果表示）画面を制御するクラス
 * @details SceneBaseを継承し、リザルト画面の描画や遷移、文字の点滅エフェクトなどを管理します。
 */
class ResultScene : public SceneBase
{
private:

    // UI用スプライト
    Sprite* world_image;
    Sprite* time_image;


    // 分割スプライト
    DivSprite* mario_image;
    DivSprite* mario_stock;
    DivSprite* mario_name;
    DivSprite* stage_number;
    DivSprite* score_image;
    DivSprite* coin_image;


    // === メンバ変数 ===
    int stock;
    int coin_count;
    int score;
    int font_handle;   ///< フォント描画用のハンドル
    float blink_time;  ///< 点滅エフェクトの経過時間カウント
    bool is_blink;     ///< 現在文字を表示する（点滅のON/OFF）フラグ

public:
    // === コンストラクタ / デストラクタ ===
    ResultScene();
    virtual ~ResultScene();

public:
    // === シーン制御オーバーライド関数 ===

    /**
     * @brief 初期化処理
     * @details 画像やフォントのリソース読み込み、変数の初期化を行います。
     */
    virtual void Initialize() override;

    /**
     * @brief 更新処理
     * @param[in] delta_second 前フレームからの経過時間（秒）
     * @return 遷移先のシーンタイプ（継続の場合は自身のリザルトシーンタイプ）
     */
    virtual eSceneType Update(float delta_second) override;

    /**
     * @brief 描画処理
     * @details 背景やテキスト、点滅エフェクトなどを画面に描画します。
     */
    virtual void Draw() const override;

    /**
     * @brief 終了（解放）処理
     * @details 読み込んだリソースの解放や、後片付けを行います。
     */
    virtual void Finalize() override;

public:
    // === 情報取得関数 ===

    /**
     * @brief 現在のシーンタイプを取得
     * @return eSceneType リザルトシーンを表す識別子
     */
    virtual eSceneType GetNowSceneType() const override;
};
