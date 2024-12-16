#include "Brick.h"
#include <SFML/Graphics.hpp>

Brick::Brick(const sf::Texture texture, const sf::IntRect& rect, unsigned int hp)
	: m_Sprite(texture, rect)
	, m_Hp(hp)
{
}

void Brick::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_Sprite, states);
}
