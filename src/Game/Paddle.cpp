#include "Paddle.h"
#include "Core/Resources.h"
#include "Core/ResourcesManager.h"
#include <SFML/Graphics.hpp>

Paddle::Paddle(sf::Vector2f position, sf::Keyboard::Key leftKey, sf::Keyboard::Key rightKey)
	: Entity(ResourcesManager::Instance().GetTexture(Resources::PaddleTexture), {position, Resources::PaddleSize})
	, m_LeftKey(leftKey)
	, m_RigthKey(rightKey)
{
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
