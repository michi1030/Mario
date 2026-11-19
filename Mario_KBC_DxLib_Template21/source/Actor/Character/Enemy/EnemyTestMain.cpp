//#include "DxLib.h"
//#include "kuribo-.h"
//#include "nokonoko.h"
//#include "../../../File/AssetContainer.h"
//
//// ※注意：プロジェクト内の別のファイルにすでに WinMain がある場合は、
////   テストする時だけ元の WinMain 側をコメントアウトするか、ビルドから除外してください。
//int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
//{
//	// ウィンドウモード設定・DXライブラリ初期化
//	ChangeWindowMode(TRUE);
//	SetGraphMode(640, 480, 32);
//
//	if (DxLib_Init() == -1)
//	{
//		return -1;
//	}
//
//	SetDrawScreen(DX_SCREEN_BACK);
//
//	// 敵の生成と初期化
//	Kuribo* kuribo = new Kuribo(Vector2(350.0f, 300.0f));
//	kuribo->Initialize();
//
//	Nokonoko* nokonoko = new Nokonoko(Vector2(500.0f, 300.0f));
//	nokonoko->Initialize();
//
//	int prev_time = GetNowCount();
//	bool prev_key_1 = false;
//	bool prev_key_2 = false;
//	bool prev_key_r = false;
//
//	// メインループ
//	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
//	{
//		// デルタタイム計測
//		int now_time = GetNowCount();
//		float delta_second = (now_time - prev_time) / 1000.0f;
//		prev_time = now_time;
//
//		// キー入力（押した瞬間だけ反応させる）
//		bool now_key_1 = (CheckHitKey(KEY_INPUT_1) != 0);
//		bool now_key_2 = (CheckHitKey(KEY_INPUT_2) != 0);
//		bool now_key_r = (CheckHitKey(KEY_INPUT_R) != 0);
//
//		// [1]キー：クリボーを踏む（潰れ画像に切り替わる）
//		if (now_key_1 && !prev_key_1 && kuribo != nullptr)
//		{
//			kuribo->Crush();
//		}
//
//		// [2]キー：ノコノコを踏む（歩き → 甲羅静止 → 甲羅滑走 → 停止）
//		if (now_key_2 && !prev_key_2 && nokonoko != nullptr)
//		{
//			// 仮のプレイヤーX座標(200.0f)を渡して右方向へ蹴り出すテスト
//			nokonoko->OnStomped(200.0f);
//		}
//
//		// [R]キー：位置と状態をリセット（画面外に行った時用）
//		if (now_key_r && !prev_key_r)
//		{
//			delete kuribo;
//			delete nokonoko;
//
//			kuribo = new Kuribo(Vector2(350.0f, 300.0f));
//			kuribo->Initialize();
//
//			nokonoko = new Nokonoko(Vector2(500.0f, 300.0f));
//			nokonoko->Initialize();
//		}
//
//		prev_key_1 = now_key_1;
//		prev_key_2 = now_key_2;
//		prev_key_r = now_key_r;
//
//		// 更新処理
//		if (kuribo != nullptr) kuribo->Update(delta_second);
//		if (nokonoko != nullptr) nokonoko->Update(delta_second);
//
//		// 描画処理
//		ClearDrawScreen();
//
//		// 仮地面のガイド線（Y = 300）
//		DrawLine(0, 316, 640, 316, GetColor(255, 255, 255));
//		DrawString(10, 10, "[1]: Kuribo Crush  [2]: Nokonoko Stomp  [R]: Reset  [ESC]: Exit", GetColor(255, 255, 255));
//
//		if (kuribo != nullptr) kuribo->Draw();
//		if (nokonoko != nullptr) nokonoko->Draw();
//
//		ScreenFlip();
//	}
//
//	// 終了処理
//	delete kuribo;
//	delete nokonoko;
//	AssetContainer::Destroy();
//
//	DxLib_End();
//	return 0;
//}