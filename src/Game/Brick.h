#pragma once
#include "Core/Entity.h"

class Brick : public Entity
{
public:

	Brick(sf::Vector2f position, int hp);

	void LooseHp(int qty);
	int GetHp() { return m_Hp; }

private:

	int m_Hp;
};
