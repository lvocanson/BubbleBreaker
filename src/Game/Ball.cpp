#include "Ball.h"

Ball::Ball(const sf::Texture& texture, const sf::IntRect rect)
	: m_Sprite(texture, rect)
{
}

void Ball::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_Sprite, states);
}

void Ball::Update(float dt)
{
	auto pos = m_Sprite.getPosition();
	pos += dt * m_Velocity;
	m_Sprite.setPosition(pos);
}
