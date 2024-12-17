#include "Paddle.h"
#include "Core/Resources.h"
#include "Core/ResourcesManager.h"

Paddle::Paddle(sf::Vector2f position)
	: m_Sprite(ResourcesManager::Instance().GetTexture(Resources::PaddleTexture))
{
	m_Sprite.setPosition(position);
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
