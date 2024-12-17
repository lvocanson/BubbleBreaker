#pragma once
#include <SFML/Graphics.hpp>

class Ball
{
public:

	Ball(sf::Vector2f position);

	void SetVelocity(sf::Vector2f vel) { m_Velocity = vel; }

	bool CheckForCollision(sf::FloatRect rectangle);

	void Update(float dt);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const { target.draw(m_Sprite, states);	}

private:

	sf::Sprite m_Sprite;
	sf::Vector2f m_Velocity;
};
