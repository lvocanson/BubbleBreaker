#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>

class ResourcesManager
{
public:

private:

	std::unordered_map<const char*, std::shared_ptr<sf::Texture>> m_Textures;
};
