#pragma once
#include "Entity.h"

class EntityWithVelocity : public Entity
{
public:

	EntityWithVelocity(const sf::Texture& tex, const sf::FloatRect& rect)
		: Entity(tex, rect)
	{
	}

	sf::Vector2f GetVelocity() const { return m_Velocity; }
	void SetVelocity(sf::Vector2f vel) { m_Velocity = vel; }

	void ApplyVelocity(float dt) { m_Sprite.move(m_Velocity * dt); }

protected:

	sf::Vector2f m_Velocity;
};
