#include "Brick.h"
#include "Core/Resources.h"
#include "Core/ResourcesManager.h"
#include <SFML/Graphics.hpp>

Brick::Brick(sf::Vector2f position, unsigned int hp)
	: m_Sprite(ResourcesManager::Instance().GetTexture(Resources::BrickTexture))
	, m_Hp(hp)
{
	m_Sprite.setPosition(position);
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
		//set Tint accordingly with hp
	}
}

void Brick::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_Sprite, states);
}
