#pragma once
#include "Core/IUpdatable.h"
#include <SFML/Graphics.hpp>

class Brick : public sf::Drawable
{
public:

	Brick(const sf::Texture texture, sf::Vector2f position, unsigned int hp);

	void LooseHp(int qty);

private:

	sf::Sprite m_Sprite;
	int m_Hp;

private:

	// Inherited via Drawable
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
