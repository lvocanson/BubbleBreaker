#pragma once
#include <SFML/Graphics.hpp>

class Brick
{
public:

	Brick(sf::Vector2f position, int hp);

	void LooseHp(int qty);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const { target.draw(m_Sprite, states); }

	sf::FloatRect GetRect() { return m_Sprite.getGlobalBounds(); }
	void SetPosition(sf::Vector2f position) { m_Sprite.setPosition(position); }

private:

	sf::Sprite m_Sprite;
	int m_Hp;
};
