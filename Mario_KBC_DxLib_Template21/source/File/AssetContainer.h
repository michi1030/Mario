#pragma once

#include <unordered_map>
#include <string>

/// <summary>
/// 素材管理クラス
/// </summary>
class AssetContainer final
{
private:
	//自クラスのポインタ
	static AssetContainer* instance;
	//画像保存用のコンテナ
	std::unordered_map<std::string, int> image_container;
	//音声保存用のコンテナ
	std::unordered_map<std::string, int> sound_container;

private:
	AssetContainer() = default;
	AssetContainer& operator = (const AssetContainer&) = delete;
	AssetContainer& operator = (AssetContainer&&) = delete;
	~AssetContainer() = default;

public:
	//インスタンスの取得
	static AssetContainer* Get();
	//インスタンスの破棄
	static void Destroy();

public:
	/// <summary>
	/// 画像の取得
	/// </summary>
	/// <param name="file_name">画像ファイル名</param>
	/// <returns>画像ハンドル情報</returns>
	const int GetImages(const std::string& file_name);

	/// <summary>
	/// 音源の取得
	/// </summary>
	/// <param name="file_name">音源ファイル名</param>
	/// <returns>音源はドル情報</returns>
	const int GetSound(const std::string& file_name);

private:
	/// <summary>
	/// 素材データの解放
	/// </summary>
	void AllUnloadAssets();
	/// <summary>
	/// 画像データの解放
	/// </summary>
	void UnloadImages();
	/// <summary>
	/// 音源データの解放
	/// </summary>
	void UnloadSounds();

};

