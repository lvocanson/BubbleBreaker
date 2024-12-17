#pragma once
#include <SFML/Graphics.hpp>

class Brick
{
public:

	Brick(sf::Vector2f position, int hp);

	void LooseHp(int qty);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const { target.draw(m_Sprite, states); }

private:

	sf::Sprite m_Sprite;
	int m_Hp;
};
