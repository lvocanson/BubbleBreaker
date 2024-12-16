#include "ResourcesManager.h"

ResourcesManager::ResourcesManager(size_t textureCount)
	: m_Textures(textureCount)
{
}

bool ResourcesManager::LoadTexture(const char* path)
{
	sf::Texture tex;
	if (tex.loadFromFile(path))
	{
		m_Textures.emplace(path, std::move(tex));
		return true;
	}
	return false;
}
