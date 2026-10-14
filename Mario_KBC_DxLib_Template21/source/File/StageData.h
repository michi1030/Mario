#pragma once

#include "../Utility/Math/Vector2.h"
#include <unordered_map>
#include <vector>

enum class ePanelID : unsigned char
{
	eNone,
	eWall,
	eBranch,
	eGate,
};

enum class eAdjacentDirection : unsigned char
{
	eUp,
	eDown,
	eLeft,
	eRight,
};

class StageData final
{
public:
	static const float CHIP_SIZE;
	static const float STAGE_OFFSET_X;
	static const float STAGE_OFFSET_Y;
	static const Vector2 STAGE_OFFSET;

private:
	static StageData* instance;
	std::vector<std::vector<ePanelID>> data;

private:
	StageData() = default;
	StageData(const StageData&) = delete;
	StageData& operator = (StageData&) = delete;
	~StageData() = default;

public:
	static StageData* Get();
	static void Destroy();

public:
	const std::vector<std::vector<ePanelID>>& GetAll();
	const std::unordered_map<eAdjacentDirection, ePanelID> GetAdjacentPanelData(const Vector2& location) const;
	const ePanelID GetPanelData(const Vector2& location) const;
	void SetPanelData(ePanelID id, const Vector2& location, int mx, int my);
	void ConvertToIndex(const Vector2& location, int& x, int& y) const;

private:
	void Load();
	void Unload();

};
