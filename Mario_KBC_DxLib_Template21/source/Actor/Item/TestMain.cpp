//#include <DxLib.h>
//#include <vector>
//#include "../Actor.h"
//#include "../../File/AssetContainer.h"
//#include "../Item/Mushroom.h"
//#include "../Item/SuperStar.h"
//#include "../Item/FireFlower.h"
//#include "../Item/OneUpMushroom.h"
//
//// ----------------------------------------------------
//// テスト用の独立ダミープレイヤー
//// ----------------------------------------------------
//class TestPlayer : public Actor
//{
//public:
//    TestPlayer(float startX, float startY)
//    {
//        location.x = startX;
//        location.y = startY;
//        radius = 16.0f; // プレイヤーの判定半径
//        actor_state = eActorState::eActive;
//    }
//
//    virtual void Update(float delta_second) override
//    {
//        float speed = 400.0f * delta_second;
//        // 矢印キーでプレイヤーを移動
//        if (CheckHitKey(KEY_INPUT_LEFT))  location.x -= speed;
//        if (CheckHitKey(KEY_INPUT_RIGHT)) location.x += speed;
//        if (CheckHitKey(KEY_INPUT_UP))    location.y -= speed;
//        if (CheckHitKey(KEY_INPUT_DOWN))  location.y += speed;
//    }
//
//    virtual void Draw() const override
//    {
//        // 青い円でプレイヤーを描画
//        DrawCircle((int)location.x, (int)location.y, (int)radius, GetColor(0, 120, 255), TRUE);
//        DrawString((int)location.x - 20, (int)location.y - 25, "PLAYER", GetColor(255, 255, 255));
//    }
//
//    virtual void OnHitCollisionEnter(Actor* actor) override
//    {
//        if (!actor) return;
//        // 当たったアイテムのタグを出力
//        printfDx("Hit Item Tag: %d\n", (int)actor->GetActorTag());
//    }
//
//    virtual eActorTag GetActorTag() const override { return eActorTag::ePlayer; }
//};
//
//// ----------------------------------------------------
//// エントリーポイント (メイン関数)
//// ----------------------------------------------------
//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
//{
//    // DxLibの初期化設定
//    ChangeWindowMode(TRUE);
//    SetGraphMode(1024, 768, 32);
//    if (DxLib_Init() == -1) return -1;
//    SetDrawScreen(DX_SCREEN_BACK);
//
//    // 1. ダミープレイヤーの準備
//    TestPlayer* player = new TestPlayer(100.0f, 300.0f);
//
//    // 2. テスト用アイテムの準備と生成
//    std::vector<Actor*> items;
//
//    Mushroom* mushroom = new Mushroom();
//    mushroom->Initialize();
//    mushroom->Spawn(200.0f, 300.0f);
//    items.push_back(mushroom);
//
//    SuperStar* star = new SuperStar();
//    star->Initialize();
//    star->Spawn(300.0f, 300.0f);
//    items.push_back(star);
//
//    FireFlower* flower = new FireFlower();
//    flower->Initialize();
//    flower->Spawn(400.0f, 300.0f);
//    items.push_back(flower);
//
//    OneUpMushroom* oneup = new OneUpMushroom();
//    oneup->Initialize();
//    oneup->Spawn(500.0f, 300.0f);
//    items.push_back(oneup);
//
//    // デルタタイム計算用変数
//    int prevTime = GetNowCount();
//
//    // ----------------------------------------------------
//    // ゲームループ
//    // ----------------------------------------------------
//    while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
//    {
//        ClearDrawScreen();
//
//        // デルタ秒の計算
//        int currentTime = GetNowCount();
//        float delta_second = (currentTime - prevTime) / 1000.0f;
//        prevTime = currentTime;
//
//        // --- A. 更新処理 (Update) ---
//        if (player) player->Update(delta_second);
//
//        for (auto item : items)
//        {
//            if (item->GetState() != eActorState::eActive) continue;
//
//            item->Update(delta_second);
//
//            // 当たり判定チェック（円判定）
//            Vector2 diff = player->GetLocation() - item->GetLocation();
//            float distSq = (diff.x * diff.x) + (diff.y * diff.y);
//            float radiusSum = player->GetRadius() + item->GetRadius();
//
//            if (distSq <= (radiusSum * radiusSum))
//            {
//                // 衝突時にお互いの OnHitCollisionEnter を呼び出す
//                player->OnHitCollisionEnter(item);
//                item->OnHitCollisionEnter(player);
//            }
//        }
//
//        // --- B. 描画処理 (Draw) ---
//        // 背景
//        DrawBox(0, 0, 1024, 768, GetColor(30, 30, 30), TRUE);
//
//        // UI表示
//        DrawString(20, 20, "=== ITEM COLLISION TEST (appmain) ===", GetColor(255, 255, 0));
//        DrawString(20, 40, "Use ARROW KEYS to move Blue Player", GetColor(255, 255, 255));
//
//        // アイテムの描画
//        for (auto item : items)
//        {
//            if (item->GetState() == eActorState::eActive)
//            {
//                item->Draw();
//                // 判定確認用：判定の円を赤い枠で可視化
//                DrawCircle((int)item->GetLocation().x + 16, (int)item->GetLocation().y + 16, (int)item->GetRadius(), GetColor(255, 0, 0), FALSE);
//            }
//        }
//
//        // プレイヤーの描画
//        if (player) player->Draw();
//
//        ScreenFlip();
//    }
//
//    // メモリ解放
//    delete player;
//    for (auto item : items)
//    {
//        delete item;
//    }
//    items.clear();
//
//    AssetContainer::Destroy();
//    DxLib_End();
//    return 0;
//}