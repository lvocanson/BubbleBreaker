#include "Paddle.h"
#include "Core/Resources.h"
#include "Core/ResourcesManager.h"

Paddle::Paddle(sf::Vector2f position, sf::Keyboard::Key leftKey, sf::Keyboard::Key rightKey)
	: m_Sprite(ResourcesManager::Instance().GetTexture(Resources::PaddleTexture)), m_LeftKey(leftKey), m_RigthKey(rightKey)
{
	const auto currentSize = m_Sprite.getLocalBounds().size;
	const auto currentScale = m_Sprite.getScale();
	const sf::Vector2f newScale
	{
		(Resources::PaddleSize.x / currentSize.x) * currentScale.x,
		(Resources::PaddleSize.y / currentSize.y) * currentScale.y
	};
	m_Sprite.setScale(newScale);
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
		m_Sprite.move({ -Resources::PaddleSpeed * dt, 0.f });
	}
	else if (sf::Keyboard::isKeyPressed(m_RigthKey))
	{
		m_Sprite.move({ Resources::PaddleSpeed * dt, 0.f });
	}
}
