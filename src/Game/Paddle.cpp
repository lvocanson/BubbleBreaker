#include "Paddle.h"

Paddle::Paddle(const sf::Texture texture, const sf::IntRect& rect)
	: m_Sprite(texture, rect)
{
}

void Paddle::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_Sprite, states);
}

void Paddle::Update(float dt)
{
	if (sf::Keyboard::isKeyPressed(m_LeftKey))
	{
		m_Sprite.move({ 1 * m_Speed * dt, 0 });
	}
	else if (sf::Keyboard::isKeyPressed(m_RigthKey))
	{
		m_Sprite.move({ -1 * m_Speed * dt, 0 });
	}
}
