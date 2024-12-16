#pragma once
#include "Core/IUpdatable.h"
#include <SFML/Graphics.hpp>

class Brick : public sf::Drawable
{
public:

	Brick(const sf::Texture texture, const sf::IntRect& rect, unsigned int hp);

private:

	sf::Sprite m_Sprite;
	int m_Hp;

private:

	// Inherited via Drawable
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
