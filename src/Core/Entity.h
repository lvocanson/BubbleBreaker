#pragma once
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>

// Wrapper around SFML sprite
class Entity
{
public:

	Entity(const sf::Texture& tex, const sf::FloatRect& rect);

	sf::FloatRect GetRect() const { return m_Sprite.getGlobalBounds(); }
	void SetPosition(sf::Vector2f position) { m_Sprite.setPosition(position); }
	void SetSize(sf::Vector2f size);

	void Draw(sf::RenderTarget& target, const sf::RenderStates& states) const { target.draw(m_Sprite, states); }

protected:

	sf::Sprite m_Sprite;
};
