#pragma once
#include "Core/EntityWithVelocity.h"

class Ball : public EntityWithVelocity
{
public:

	Ball(sf::Vector2f position);

	bool ReactToCollision(sf::FloatRect rectangle);
};
