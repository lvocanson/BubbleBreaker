#pragma once
#include <SFML/Graphics.hpp>

class Ball
{
public:

	Ball(sf::Vector2f position);

	sf::Vector2f GetVelocity() const { return m_Velocity; }
	void SetVelocity(sf::Vector2f vel) { m_Velocity = vel; }

	sf::FloatRect GetRect() { return m_Sprite.getGlobalBounds(); }
	void SetPosition(sf::Vector2f position) { m_Sprite.setPosition(position); }

	bool CheckForCollision(sf::FloatRect rectangle);

	void Update(float dt);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const { target.draw(m_Sprite, states);	}

private:

	sf::Sprite m_Sprite;
	sf::Vector2f m_Velocity;
};
