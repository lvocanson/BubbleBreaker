#pragma once
#include "Core/IUpdatable.h"
#include <SFML/Graphics.hpp>

class Ball : public sf::Drawable, public IUpdatable
{
public:

	Ball(const sf::Texture& texture, const sf::IntRect rect);

	void SetVelocity(sf::Vector2f vel) { m_Velocity = vel; }

	void CheckForCollision(sf::FloatRect rectangle);

private:

	sf::Sprite m_Sprite;
	sf::Vector2f m_Velocity;
	float m_SpeedFactor;

private:

	// Inherited via Drawable
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	// Inherited via IUpdatable
	void Update(float dt) override;
};
