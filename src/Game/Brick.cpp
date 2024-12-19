#include "Brick.h"
#include "Core/Resources.h"
#include "Core/ResourcesManager.h"
#include <SFML/Graphics.hpp>

Brick::Brick(sf::Vector2f position, int hp)
	: Entity(ResourcesManager::Instance().GetTexture(Resources::BrickTexture), {position, Resources::BrickSize})
	, m_Hp(hp)
{
	m_Sprite.setColor(Resources::BrickColors[m_Hp]);
}

void Brick::LooseHp(int qty)
{
	if (m_Hp <= 0)
	{
		return;
	}

	m_Hp -= qty;
	if (m_Hp < 0)
	{
		m_Hp = 0;
	}
	else
	{
		m_Sprite.setColor(Resources::BrickColors[m_Hp]);
	}
}
