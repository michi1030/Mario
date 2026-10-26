#pragma once

#include <string>
#include <vector>

/// <summary>
/// 画像クラス
/// </summary>
class Sprite
{
private:
	int orignal_handle;//画像ハンドル情報
	int orignal_width;//画像の幅
	int orignal_height;//画像の高さ

public:
	/// <summary>
	/// 引数付きコンストラクタ
	/// </summary>
	/// <param name="file_name">画像のファイル名</param>
	Sprite(const std::string& file_name);
	virtual ~Sprite() = default;

public:
	int GetHandle() const;
	int GetWidth() const;
	int GetHeight() const;

};

/// <summary>
/// 分割画像クラス
/// </summary>
class DivSprite : public Sprite
{
private:
	//分割した画像を保存する配列
	std::vector<int> split_handle;

public:
	/// <summary>
	/// 引数付きコンストラクタ
	/// </summary>
	/// <param name="file_name">ファイルの名前</param>
	/// <param name="dx">横の分割数</param>
	/// <param name="dy">縦の分割数</param>
	DivSprite(const std::string file_name, int dx, int dy);
	virtual ~DivSprite();

public:
	//要素番目の情報を取得する
	int operator [] (int index) const;
	//要素番目の倍数を取得する
	int At(int index) const;
	//配列の大きさを取得
	int GetSize() const;

};
