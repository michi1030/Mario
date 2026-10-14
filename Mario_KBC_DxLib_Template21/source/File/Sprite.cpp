#include "Sprite.h"
#include "AssetContainer.h"
#include <DxLib.h>
#include <stdexcept>

Sprite::Sprite(const std::string& file_name)
{
	orignal_handle = AssetContainer::Get()->GetImages(file_name);
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
	: Sprite(file_name)
{
	int w = GetWidth() / dx;
	int h = GetHeight() / dy;

	for (int y = 0; y < dy; ++y)
	{
		for (int x = 0; x < dx; ++x)
		{
			int handle = DerivationGraph(w * x, h * y, w, h, GetHandle());
			if (handle == -1)
			{
				throw std::runtime_error(file_name + "‚Ì•ªŠ„‚ÉŽ¸”s‚µ‚Ü‚µ‚½B\n");
			}
			split_handle.emplace_back(handle);
		}
	}
}

DivSprite::~DivSprite()
{
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
