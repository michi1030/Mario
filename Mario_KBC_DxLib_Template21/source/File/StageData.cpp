#include "StageData.h"

StageData* StageData::instance = nullptr;
const float StageData::CHIP_SIZE = 24.0f;
const float StageData::STAGE_OFFSET_X = 0.0f;
const float StageData::STAGE_OFFSET_Y = (CHIP_SIZE * 3.0f);
const Vector2 StageData::STAGE_OFFSET = Vector2(STAGE_OFFSET_X, STAGE_OFFSET_Y);

StageData* StageData::Get()
{
	if (instance == nullptr)
	{
		instance = new StageData();
		instance->Load();
	}
	return instance;
}

void StageData::Destroy()
{
	if (instance != nullptr)
	{
		instance->Unload();
		delete instance;
		instance = nullptr;
	}
}

const std::vector<std::vector<ePanelID>>& StageData::GetAll()
{
	return data;
}

const std::unordered_map<eAdjacentDirection, ePanelID> StageData::GetAdjacentPanelData(const Vector2& location) const
{
	std::unordered_map<eAdjacentDirection, ePanelID> result = {
		{ eAdjacentDirection::eUp, ePanelID::eNone },
		{ eAdjacentDirection::eDown, ePanelID::eNone },
		{ eAdjacentDirection::eLeft, ePanelID::eNone },
		{ eAdjacentDirection::eRight, ePanelID::eNone }
	};

	int x, y;
	ConvertToIndex(location, x, y);

	if ((0 <= y) && (y < data.size()))
	{
		if (0 <= (x - 1))
		{
			result[eAdjacentDirection::eLeft] = data[y][x - 1];
		}

		if ((x + 1) < data[y].size())
		{
			result[eAdjacentDirection::eRight] = data[y][x + 1];
		}

		if ((0 <= x) && (x < data[y].size()))
		{
			if (0 <= (y - 1))
			{
				result[eAdjacentDirection::eUp] = data[y - 1][x];
			}

			if ((y + 1) < data.size())
			{
				result[eAdjacentDirection::eUp] = data[y + 1][x];
			}
		}
	}

	return result;
}

const ePanelID StageData::GetPanelData(const Vector2& location) const
{
	int x, y;
	ConvertToIndex(location, x, y);

	if ((x < 0) || (y < 0) || (data.size() <= y) || (data[y].size() <= x))
	{
		return ePanelID::eNone;
	}

	return data[y][x];
}

void StageData::SetPanelData(ePanelID id, const Vector2& location, int mx, int my)
{
	int x, y;
	ConvertToIndex(location, x, y);

	for (int i = y; i < y + my; ++i)
	{
		for (int j = x; j < x + mx; ++j)
		{
			data[i][j] = id;
		}
	}
}

void StageData::ConvertToIndex(const Vector2& location, int& x, int& y) const
{
	Vector2 v = (location - STAGE_OFFSET);
	x = static_cast<int>(v.x / CHIP_SIZE);
	y = static_cast<int>(v.y / CHIP_SIZE);
}

void StageData::Load()
{
	std::vector<ePanelID> init_data(28, ePanelID::eNone);
	data = std::vector<std::vector<ePanelID>>(31, init_data);
}

void StageData::Unload()
{
	for (auto& d : data)
	{
		d.clear();
	}
	data.clear();
}
