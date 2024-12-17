#pragma once
#include <SFML/Graphics/Drawable.hpp>

class Game : public sf::Drawable
{
public:

	virtual ~Game() = default;

	virtual void Update(float dt) = 0;
};
