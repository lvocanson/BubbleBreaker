#include "Ball.h"
#include "Core/Resources.h"
#include "Core/ResourcesManager.h"
#include "Utils/Logger.h"

Ball::Ball(sf::Vector2f position)
	: EntityWithVelocity(ResourcesManager::Instance().GetTexture(Resources::BallTexture), { position, Resources::BallSize })
{
}

bool Ball::ReactToCollision(sf::FloatRect rectangle)
{
	sf::Vector2f rectOrigin
	{
		rectangle.position.x + rectangle.size.x / 2,
		rectangle.position.y + rectangle.size.y / 2
	};

	sf::FloatRect ballBounds = m_Sprite.getGlobalBounds();
	const float radius = ballBounds.size.x / 2;
	sf::Vector2f ballPos
	{
		ballBounds.position.x + radius,
		ballBounds.position.y + radius
	};

	sf::Vector2f distance
	{
		abs(ballPos.x - rectOrigin.x),
		abs(ballPos.y - rectOrigin.y)
	};

	if (distance.x > (rectangle.size.x / 2 + radius)) return false;
	if (distance.y > (rectangle.size.y / 2 + radius)) return false;

	float cornerDistance_sq = (distance.x - rectangle.size.x / 2) * (distance.x - rectangle.size.x / 2) +
		(distance.y - rectangle.size.y / 2) * (distance.y - rectangle.size.y / 2);

	if (cornerDistance_sq < radius * radius)
	{
		//set BallPos relative to rectPos
		ballPos -= rectOrigin;

		const float ballSpeed = m_Velocity.length();
		// find the distance that the corner is from the line segment from the balls pos to the next pos
		const float u = (((rectangle.size.x / 2) - ballPos.x) * m_Velocity.x + ((rectangle.size.y / 2) - ballPos.y) * m_Velocity.y) / (ballSpeed * ballSpeed);
		// get the closest point on the line to the corner
		sf::Vector2f cp
		{
			ballPos.x + m_Velocity.x * u,
			ballPos.y + m_Velocity.y * u
		};

		// get the distance of that point from the corner squared
		const float dist = (cp.x - (rectangle.size.x / 2)) * (cp.x - (rectangle.size.x / 2)) + (cp.y - (rectangle.size.y / 2)) * (cp.y - (rectangle.size.y / 2));

		// solves the triangle from center to closest point on balls trajectory
		float d = sqrt(abs((radius * radius) - dist)) / ballSpeed;

		cp.x -= m_Velocity.x * d;
		cp.y -= m_Velocity.y * d;

		// get the distance from the ball current pos to the intercept point
		d = sqrt((cp.x - ballPos.x) * (cp.x - ballPos.x) + (cp.y - ballPos.y) * (cp.y - ballPos.y));

		//move the ball form the remaining distance away from the corner
		const float gap = sqrt((cp.x - ballPos.x) * (cp.x - ballPos.x) + (cp.y - ballPos.y) * (cp.y - ballPos.y));
		Logger::Instance() << gap << '\n';
		m_Sprite.move(m_Velocity.normalized() * gap);


		// find the normalised tangent at intercept point 
		const float ty = (cp.x - (rectangle.size.x / 2)) / radius;
		const float tx = -(cp.y - (rectangle.size.y / 2)) / radius;

		m_Velocity = m_Velocity.normalized();

		Logger::Instance() << cp.x << " ; " << cp.y << " /// " << ballPos.x << " ; " << ballPos.y << '\n';

		//reflectionVector
		const float dot = (m_Velocity.x * tx + m_Velocity.y * ty) * 2;

		m_Velocity.x = (tx * dot - m_Velocity.x);
		m_Velocity.y = (ty * dot - m_Velocity.y);
		m_Velocity = m_Velocity.normalized();


		m_Velocity *= ballSpeed;

		return true;
	}

	if (distance.x <= (rectangle.size.x / 2) + radius && distance.x >= (rectangle.size.x / 2) - radius)
	{
		m_Velocity.x *= -1;
		if (m_Velocity.lengthSquared() < Resources::MaxBallSpeed * Resources::MaxBallSpeed)
			m_Velocity *= Resources::BounceSpeedFactor;
		return true;
	}

	if (distance.y <= (rectangle.size.y / 2) + radius && distance.y >= (rectangle.size.y / 2) - radius)
	{
		m_Velocity.y *= -1;
		if (m_Velocity.lengthSquared() < Resources::MaxBallSpeed * Resources::MaxBallSpeed)
			m_Velocity *= Resources::BounceSpeedFactor;
		return true;
	}


	return false;
}
