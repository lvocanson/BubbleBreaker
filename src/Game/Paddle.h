#pragma once
#include "Core/IUpdatable.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>

class Paddle : public sf::Drawable, public IUpdatable
{
public:

	Paddle(const sf::Texture texture, const sf::IntRect& rect);

private:

	sf::Sprite m_Sprite;
	sf::Keyboard::Key  m_LeftKey;
	sf::Keyboard::Key m_RigthKey;
	float m_Speed;

private:

	// Inherited via Drawable
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	// Inherited via IUpdatable
	void Update(float dt) override;
};
