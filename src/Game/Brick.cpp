#include "Brick.h"
#include "Core/Resources.h"
#include "Core/ResourcesManager.h"
#include <SFML/Graphics.hpp>

Brick::Brick(sf::Vector2f position, int hp)
	: m_Sprite(ResourcesManager::Instance().GetTexture(Resources::BrickTexture))
	, m_Hp(hp)
{
	const auto currentSize = m_Sprite.getLocalBounds().size;
	const auto currentScale = m_Sprite.getScale();
	const sf::Vector2f newScale
	{
		(Resources::BrickSize.x / currentSize.x) * currentScale.x,
		(Resources::BrickSize.y / currentSize.y) * currentScale.y
	};
	m_Sprite.setScale(newScale);
	m_Sprite.setPosition(position);
	m_Sprite.setColor(Resources::BrickColors[m_Hp]);
}

void Brick::LooseHp(int qty)
{
	m_Hp -= qty;
	if (m_Hp <= 0)
	{
		//destroy brick
	}
	else
	{
		m_Sprite.setColor(Resources::BrickColors[m_Hp]);
	}
}

