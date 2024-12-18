#include "Ball.h"
#include "Core/Resources.h"
#include "Core/ResourcesManager.h"

Ball::Ball(sf::Vector2f position)
	: EntityWithVelocity(ResourcesManager::Instance().GetTexture(Resources::BallTexture), {position, Resources::BallSize})
{
}

bool Ball::CheckForCollision(sf::FloatRect rectangle)
{
	sf::Vector2f rectOrigin
	{
		rectangle.position.x + rectangle.size.x / 2,
		rectangle.position.y + rectangle.size.y / 2
	};

	const float radius = m_Sprite.getGlobalBounds().size.x / 2;
	sf::Vector2f ballPos
	{
		m_Sprite.getGlobalBounds().position.x + radius,
		m_Sprite.getGlobalBounds().position.y + radius
	};

	sf::Vector2f distance
	{
		abs(ballPos.x - rectOrigin.x),
		abs(ballPos.y - rectOrigin.y)
	};

	if (distance.x > (rectangle.size.x / 2 + radius)) return false;
	if (distance.y > (rectangle.size.y / 2 + radius)) return false;

	if (distance.x <= (rectangle.size.x / 2) + radius && distance.x >= (rectangle.size.x / 2) - radius)
	{
		m_Velocity.x *= -1;
		m_Velocity *= Resources::BounceSpeedFactor;
		return true;
	}

	if (distance.y <= (rectangle.size.y / 2) + radius && distance.y >= (rectangle.size.y / 2) - radius)
	{
		m_Velocity.y *= -1;
		m_Velocity *= Resources::BounceSpeedFactor;
		return true;
	}
	return false;
}

void Ball::Update(float dt)
{
	ApplyVelocity(dt);
}
