#pragma once

#include <string>
#include <vector>

class Sprite
{
private:
	int orignal_handle;
	int orignal_width;
	int orignal_height;

public:
	Sprite(const std::string& file_name);
	virtual ~Sprite() = default;

public:
	int GetHandle() const;
	int GetWidth() const;
	int GetHeight() const;

};

class DivSprite : public Sprite
{
private:
	std::vector<int> split_handle;

public:
	DivSprite(const std::string file_name, int dx, int dy);
	virtual ~DivSprite();

public:
	int operator [] (int index) const;
	int At(int index) const;
	int GetSize() const;

};
