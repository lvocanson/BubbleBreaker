#pragma once
#include "Core/Entity.h"

class Brick : public Entity
{
public:

	/**
	* @brief Create a new brick.
	* 
	* @param position The spawn position of the brick. will be the top left coordinate of the spawned brick.
	* @param hp The number of hit this brick can take before being destroyed. Negative values means the brick cannot be destroyed
	*/
	Brick(sf::Vector2f position, int hp);

	void LooseHp(int qty);
	int GetHp() const { return m_Hp; }

private:

	int m_Hp;
};
