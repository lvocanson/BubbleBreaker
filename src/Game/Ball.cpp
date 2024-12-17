#include "Ball.h"
#include "Core/Resources.h"
#include "Core/ResourcesManager.h"

Ball::Ball(sf::Vector2f position)
	: m_Sprite(ResourcesManager::Instance().GetTexture(Resources::BallTexture))
{
	const auto currentSize = m_Sprite.getLocalBounds().size;
	const auto currentScale = m_Sprite.getScale();
	const sf::Vector2f newScale
	{
		(Resources::BallSize.x / currentSize.x) * currentScale.x,
		(Resources::BallSize.y / currentSize.y) * currentScale.y
	};
	m_Sprite.setScale(newScale);
	m_Sprite.setPosition(position);
	m_Sprite.setOrigin(Resources::BallSize);
}

bool Ball::CheckForCollision(sf::FloatRect rectangle)
{
	sf::Vector2f distance;
	distance.x = abs(m_Sprite.getGlobalBounds().getCenter().x - rectangle.position.x);
	distance.y = abs(m_Sprite.getGlobalBounds().getCenter().y - rectangle.position.y);

	const float radius = m_Sprite.getGlobalBounds().size.x;
	const float ballSpeed = sqrt(m_Velocity.x * m_Velocity.x + m_Velocity.y * m_Velocity.y); // get ball speed relative to bat

	if (distance.x > (rectangle.size.x / 2 + radius)) return false;
	if (distance.y > (rectangle.size.y / 2 + radius)) return false;

	// bat now only has a bottom, right sides and bottom right corner
	const float distY = ((rectangle.size.y / 2 + radius) - m_Sprite.getPosition().y); // distance from bottom 
	const float distX = ((rectangle.size.x / 2 + radius) - m_Sprite.getPosition().x); // distance from right

	// get x location of intercept for bottom of bat
	const float bottomX = m_Sprite.getPosition().x + (m_Velocity.x / m_Velocity.y) * distY;

	// get y location of intercept for right of bat
	const float rightY = m_Sprite.getPosition().y + (m_Velocity.y / m_Velocity.x) * distX;

	const float distBottom = powf((bottomX - m_Sprite.getPosition().x), 2) + powf((rectangle.size.x / 2 + radius - m_Sprite.getPosition().y), 2);
	const float distRight = powf((rectangle.size.x / 2 + radius - m_Sprite.getPosition().x), 2) + powf((rightY - m_Sprite.getPosition().y), 2);

	if (distance.x <= (rectangle.size.x / 2))
	{
		//vertical collision
		sf::Vector2f vect(rectangle.size.x / 2 + radius + m_Velocity.x * ((ballSpeed - distRight) / ballSpeed), 0);
		m_Sprite.setPosition(m_Sprite.getPosition() + vect);
		m_Velocity.x *= -1;
		return true;
	}

	if (distance.y <= (rectangle.size.y / 2))
	{
		//horizontal collision
		sf::Vector2f vect(0, rectangle.size.y / 2 + radius + m_Velocity.y * ((ballSpeed - distBottom) / ballSpeed));
		m_Sprite.setPosition(m_Sprite.getPosition() + vect);
		m_Velocity.y *= -1;
		return true;
	}

	const float distFromCircleToRect = powf((distance.x - rectangle.size.x / 2), 2) + powf((distance.y - rectangle.size.y / 2), 2);

	if (distFromCircleToRect <= powf(radius, 2))
	{
		// find the distance that the corner is from the line segment from the balls pos to the next pos
		const float u = ((rectangle.size.x / 2 - m_Sprite.getPosition().x) * m_Velocity.x + (rectangle.size.y / 2 - m_Sprite.getPosition().y) * m_Velocity.y) / (ballSpeed * ballSpeed);

		// get the closest point on the line to the corner
		float closestPointX = m_Sprite.getPosition().x + m_Velocity.x * u;
		float closestPointY = m_Sprite.getPosition().y + m_Velocity.y * u;

		// get the distance from the ball current pos to the intercept point
		float distanceToInterceptPoint = sqrt(powf(closestPointX - m_Sprite.getPosition().x, 2) + powf(closestPointY - m_Sprite.getPosition().y, 2));

		// intercept point is closest to line start
		closestPointX -= m_Velocity.x * distanceToInterceptPoint;
		closestPointY -= m_Velocity.y * distanceToInterceptPoint;

		// find the normalised tangent at intercept point 
		const float tangentY = (closestPointX - rectangle.size.x / 2) / radius;
		const float tangentX = -(closestPointY - rectangle.size.y / 2) / radius;

		// calculate the reflection vector
		const float ballSpeedX = m_Velocity.x / ballSpeed;   // normalise ball speed
		const float ballSpeedY = m_Velocity.y / ballSpeed;
		const float dotProduct = (ballSpeedX * tangentX + ballSpeedY * tangentY) * 2;

		// the reflected vector is the balls new delta (this delta is normalised)
		m_Velocity.x = (tangentX * dotProduct - ballSpeedX);
		m_Velocity.y = (tangentY * dotProduct - ballSpeedY);

		// get the distance the ball travels past the intercept
		distanceToInterceptPoint = ballSpeed - distanceToInterceptPoint;

		// move the ball the remaining distance away from corner
		//m_Sprite.setPosition(m_Sprite.getPosition() + m_Velocity * distanceToInterceptPoint);

		// set the ball delta to the balls speed
		m_Velocity.x *= ballSpeed;
		m_Velocity.y *= ballSpeed;

		return true;
	}
	return false;
}

void Ball::Update(float dt)
{
	m_Sprite.move(m_Velocity * dt);
}
