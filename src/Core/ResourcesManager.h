#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>

class ResourcesManager
{
public:

	ResourcesManager(size_t textureCount);
	bool LoadTexture(const char* path);
	sf::Texture& GetTexture(const char* path) { return m_Textures.at(path); }

private:

	// Map texture path -> texture ref
	std::unordered_map<const char*, sf::Texture> m_Textures;
};
