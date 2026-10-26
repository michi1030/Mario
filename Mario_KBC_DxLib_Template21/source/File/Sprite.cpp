#include "Sprite.h"
#include "AssetContainer.h"
#include <DxLib.h>
#include <stdexcept>

Sprite::Sprite(const std::string& file_name)
{
	//アセットコンテナから、画像情報を取得する
	orignal_handle = AssetContainer::Get()->GetImages(file_name);
	//画像も大きさを取得する
	GetGraphSize(orignal_handle, &orignal_width, &orignal_height);
}

int Sprite::GetHandle() const
{
	return orignal_handle;
}

int Sprite::GetWidth() const
{
	return orignal_width;
}

int Sprite::GetHeight() const
{
	return orignal_height;
}

DivSprite::DivSprite(const std::string file_name, int dx, int dy)
	: Sprite(file_name)//親クラスのコンストラクタを呼び出す
{
	int w = GetWidth() / dx;//分割1枚分の幅を計算
	int h = GetHeight() / dy;//分割1枚分の高さを計算

	for (int y = 0; y < dy; ++y)
	{
		for (int x = 0; x < dx; ++x)
		{
			//1枚画像の分割を行う
			int handle = DerivationGraph(w * x, h * y, w, h, GetHandle());
			//エラーチェック
			if (handle == -1)
			{
				//例外をスローする
				throw std::runtime_error(file_name + "の分割に失敗しました。\n");
			}
			//分割した画像を配列内に格納する
			split_handle.emplace_back(handle);
		}
	}
}

DivSprite::~DivSprite()
{
	//動的配列の解放
	split_handle.clear();
}

int DivSprite::operator[](int index) const
{
	return split_handle[index];
}

int DivSprite::At(int index) const
{
	return split_handle[index];
}

int DivSprite::GetSize() const
{
	return (int)split_handle.size();
}
