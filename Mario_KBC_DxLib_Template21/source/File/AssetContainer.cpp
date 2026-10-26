#include "AssetContainer.h"
#include <DxLib.h>
#include <stdexcept>

//静的メンバ変数の定義
AssetContainer* AssetContainer::instance = nullptr;

AssetContainer* AssetContainer::Get()
{
	//インスタンスの中身チェック
	if (instance == nullptr)
	{
		//中身がない場合、クラスを生成する
		instance = new AssetContainer();
	}
	//インスタンスのポインタを返す
	return instance;
}

void AssetContainer::Destroy()
{
	//インスタンスの中身チェック
	if (instance != nullptr)
	{
		//素材データの解放
		instance->AllUnloadAssets();
		//インスタンスの破棄
		delete instance;
		//インスタンスをヌルポインタにする
		instance = nullptr;
	}
}

const int AssetContainer::GetImages(const std::string& file_name)
{
	//コンテナ内を走査する
	auto iter = image_container.find(file_name);
	//コンテナの終端チェック
	if (iter != image_container.end())
	{
		//見つかった場所のハンドルログを返す
		return iter->second;
	}

	//ファイルパスを作成する
	std::string full_path = "assets/images/" + file_name;
	//画像の読み込み
	int handle = LoadGraph(full_path.c_str());
	//エラーチェック
	if (handle == -1)
	{
		//例外をスローする
		throw std::runtime_error(file_name + "が読み込まれませんでした\n");
	}

	//コンテナ内に登録を行う
	image_container.emplace(file_name, handle);

	//読み込んだ画像ハンドル情報を返す
	return handle;
}

const int AssetContainer::GetSound(const std::string& file_name)
{
	//コンテナ内を走査する
	auto iter = sound_container.find(file_name);
	//終端チェックする
	if (iter != sound_container.end())
	{
		//見つかった場所のハンドル情報を返す
		return iter->second;
	}

	//ファイルパスの設定
	std::string full_path = "assets/sounds/" + file_name;
	//音源の読み込み
	int handle = LoadSoundMem(full_path.c_str());
	//エラーチェック
	if (handle == -1)
	{
		//例外をスローする
		throw std::runtime_error(file_name + "が読み込まれませんでした\n");
	}

	//コンテナ内に登録する
	sound_container.emplace(file_name, handle);

	//音源ハンドル情報を返す
	return handle;
}

void AssetContainer::AllUnloadAssets()
{
	//画像データの解放
	UnloadImages();
	//音源データの解放
	UnloadSounds();
}

void AssetContainer::UnloadImages()
{
	//コンテナの中身があるかをチェックする
	if (image_container.empty())
	{
		//中身がない場合は、処理を終了する
		return;
	}

	//登録した画像情報を削除する
	for (auto& pair : image_container)
	{
		DeleteSharingGraph(pair.second);
	}
	//コンテナの解放
	image_container.clear();
}

void AssetContainer::UnloadSounds()
{
	//コンテナの中身があるかチェックする
	if (sound_container.empty())
	{
		//中身がない場合は処理終了
		return;
	}

	//登録した音源情報を削除する
	for (auto& pair : sound_container)
	{
		DeleteSoundMem(pair.second);
	}

	//コンテナの開放
	sound_container.clear();
}
