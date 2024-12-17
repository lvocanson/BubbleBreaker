#pragma once
#include "Core/IUpdatable.h"
#include <SFML/Graphics.hpp>

class Brick : public sf::Drawable
{
public:

	Brick(sf::Vector2f position, int hp);

	void LooseHp(int qty);

	// Inherited via Drawable
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:

	sf::Sprite m_Sprite;
	int m_Hp;
};
