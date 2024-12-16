#include "Paddle.h"

void Paddle::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_Sprite, states);
}

void Paddle::Update(float dt)
{
	// TODO: Inputs
}
