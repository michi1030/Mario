#include "AssetContainer.h"
#include <DxLib.h>
#include <stdexcept>

AssetContainer* AssetContainer::instance = nullptr;

AssetContainer* AssetContainer::Get()
{
	if (instance == nullptr)
	{
		instance = new AssetContainer();
	}
	return instance;
}

void AssetContainer::Destroy()
{
	if (instance != nullptr)
	{
		instance->AllUnloadAssets();
		delete instance;
		instance = nullptr;
	}
}

const int AssetContainer::GetImages(const std::string& file_name)
{
	auto iter = image_container.find(file_name);
	if (iter != image_container.end())
	{
		return iter->second;
	}

	std::string full_path = "assets/images/" + file_name;
	int handle = LoadGraph(full_path.c_str());
	if (handle == -1)
	{
		throw std::runtime_error(file_name + "Ç™ì«Ç›çûÇ‹ÇÍÇ‹ÇπÇÒÇ≈ÇµÇΩ\n");
	}

	image_container.emplace(file_name, handle);

	return handle;
}

const int AssetContainer::GetSound(const std::string& file_name)
{
	auto iter = sound_container.find(file_name);
	if (iter != sound_container.end())
	{
		return iter->second;
	}

	std::string full_path = "assets/sounds/" + file_name;
	int handle = LoadSoundMem(full_path.c_str());
	if (handle == -1)
	{
		throw std::runtime_error(file_name + "Ç™ì«Ç›çûÇ‹ÇÍÇ‹ÇπÇÒÇ≈ÇµÇΩ\n");
	}

	sound_container.emplace(file_name, handle);

	return handle;
}

void AssetContainer::AllUnloadAssets()
{
	UnloadImages();
	UnloadSounds();
}

void AssetContainer::UnloadImages()
{
	if (image_container.empty())
	{
		return;
	}

	for (auto& pair : image_container)
	{
		DeleteSharingGraph(pair.second);
	}

	image_container.clear();
}

void AssetContainer::UnloadSounds()
{
	if (sound_container.empty())
	{
		return;
	}

	for (auto& pair : sound_container)
	{
		DeleteSoundMem(pair.second);
	}

	sound_container.clear();
}
