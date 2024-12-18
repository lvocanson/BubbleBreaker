#include "Entity.h"

Entity::Entity(const sf::Texture& tex, const sf::FloatRect& rect)
	: m_Sprite(tex)
{
	const auto currentSize = m_Sprite.getLocalBounds().size;
	const auto currentScale = m_Sprite.getScale();
	const sf::Vector2f newScale
	{
		(rect.size.x / currentSize.x) * currentScale.x,
		(rect.size.y / currentSize.y) * currentScale.y
	};
	m_Sprite.setScale(newScale);
	m_Sprite.setPosition(rect.position);
}
