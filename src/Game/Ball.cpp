#include "Ball.h"

Ball::Ball(const sf::Texture& texture, sf::Vector2f position)
	: m_Sprite(texture)
{
	m_Sprite.setPosition(position);
}

void Ball::CheckForCollision(sf::FloatRect rectangle)
{
	sf::Vector2f distance;
	distance.x = abs(m_Sprite.getPosition().x - rectangle.position.x);
	distance.y = abs(m_Sprite.getPosition().y - rectangle.position.y);
	float radius = m_Sprite.getTextureRect().size.x;

	if (distance.x > (rectangle.size.x / 2 + radius)) return;
	if (distance.y > (rectangle.size.y / 2 + radius)) return;

	float ballSpeed = sqrt(m_Velocity.x * m_Velocity.x + m_Velocity.y * m_Velocity.y); // get ball speed relative to bat

	if (distance.x <= (rectangle.size.x / 2))
	{
		//vertical collision
	}

	if (distance.y <= (rectangle.size.y / 2))
	{
		//horizontal collision
	}

	float cDist_sq = powf((distance.x - rectangle.size.x / 2), 2) + powf((distance.y - rectangle.size.y / 2), 2);
	if (cDist_sq <= powf(radius, 2))
	{

		float u = ((rectangle.size.x / 2 - m_Sprite.getPosition().x) * m_Velocity.x + (rectangle.size.y / 2 - m_Sprite.getPosition().y) * m_Velocity.y) / (ballSpeed * ballSpeed);
		// get the closest point on the line to the corner
		float cpx = m_Sprite.getPosition().x + m_Velocity.x * u;
		float cpy = m_Sprite.getPosition().y + m_Velocity.y * u;

		// get the distance from the ball current pos to the intercept point
		float d = sqrt(powf(cpx - m_Sprite.getPosition().x, 2) + powf(cpy - m_Sprite.getPosition().y, 2));

		// intercept point is closest to line start
		cpx -= m_Velocity.x * d;
		cpy -= m_Velocity.y * d;

		// find the normalised tangent at intercept point 
		float ty = (cpx - rectangle.size.x / 2) / radius;
		float tx = -(cpy - rectangle.size.y / 2) / radius;

		// calculate the reflection vector
		float bsx = m_Velocity.x / ballSpeed;   // normalise ball speed
		float bsy = m_Velocity.y / ballSpeed;
		float dot = (bsx * tx + bsy * ty) * 2;

		// get the distance the ball travels past the intercept
		d = ballSpeed - d;

		// the reflected vector is the balls new delta (this delta is normalised)
		m_Velocity.x = (tx * dot - bsx);
		m_Velocity.y = (ty * dot - bsy);

		// move the ball the remaining distance away from corner
		m_Sprite.setPosition(m_Sprite.getPosition() + m_Velocity * d);

		// set the ball delta to the balls speed
		m_Velocity.x *= ballSpeed;
		m_Velocity.y *= ballSpeed;
	}
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
