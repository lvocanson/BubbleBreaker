#pragma once
#include "Core/Entity.h"
#include <SFML/Window/Keyboard.hpp>

class Paddle : public Entity
{
public:

	Paddle(sf::Vector2f position, sf::Keyboard::Key leftKey, sf::Keyboard::Key rightKey);

	void ReactToInput(float dt);

	/**
	* @brief Calculate the bounce angle of an object against the paddle.
	* 
	* @param objRect Position and size of the object
	* @param angle The angle where this object is heading AFTER the bounce.
	*/
	sf::Angle CalculateBounceAngle(const sf::FloatRect& objRect, sf::Angle angle) const;

private:

	sf::Keyboard::Key m_LeftKey;
	sf::Keyboard::Key m_RigthKey;
};
