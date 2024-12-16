#pragma once
#include "Core/IUpdatable.h"
#include <SFML/Graphics.hpp>

class Paddle : public sf::Drawable, public IUpdatable
{
public:

	Paddle(const sf::Texture texture, const sf::IntRect& rect, unsigned int hp);

private:

	sf::Sprite m_Sprite;

private:

	// Inherited via Drawable
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	// Inherited via IUpdatable
	void Update(float dt) override;
};
