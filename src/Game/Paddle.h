#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>

class Paddle
{
public:

	Paddle(sf::Vector2f position, sf::Keyboard::Key leftKey, sf::Keyboard::Key rightKey);

	void Update(float dt);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const { target.draw(m_Sprite, states); }
	
	sf::FloatRect GetRect() { return m_Sprite.getGlobalBounds(); }
	void SetPosition(sf::Vector2f position) { m_Sprite.setPosition(position); }

private:

	sf::Sprite m_Sprite;
	sf::Keyboard::Key m_LeftKey;
	sf::Keyboard::Key m_RigthKey;
};
