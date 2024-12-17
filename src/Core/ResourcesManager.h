#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>

class ResourcesManager
{
public:

	ResourcesManager(size_t textureCount);
	static void Create(size_t textureCount) { s_Instance = std::make_unique<ResourcesManager>(textureCount); }
	static ResourcesManager& Instance() { return *s_Instance; }

	bool LoadTexture(const char* path);
	sf::Texture& GetTexture(const char* path) { return m_Textures.at(path); }

private:

	static inline std::unique_ptr<ResourcesManager> s_Instance;

	// Map texture path -> texture ref
	std::unordered_map<const char*, sf::Texture> m_Textures;
};
