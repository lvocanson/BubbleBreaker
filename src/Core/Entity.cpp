#include "Entity.h"

Entity::Entity(const sf::Texture& tex, const sf::FloatRect& rect)
	: m_Sprite(tex)
{
	SetPosition(rect.position);
	SetSize(rect.size);
}

void Entity::SetSize(sf::Vector2f size)
{
	const auto currentSize = m_Sprite.getLocalBounds().size;
	const sf::Vector2f newScale
	{
		size.x / currentSize.x,
		size.y / currentSize.y
	};
	m_Sprite.setScale(newScale);
}
