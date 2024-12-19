#pragma once
#include "Core/EntityWithVelocity.h"

class Ball : public EntityWithVelocity
{
public:

	Ball(sf::Vector2f position);

	bool ReactToCollision(const sf::FloatRect& rectangle);
};
