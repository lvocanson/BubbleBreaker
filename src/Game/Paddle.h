#pragma once
#include "Core/Entity.h"
#include <SFML/Window/Keyboard.hpp>

class Paddle : public Entity
{
public:

	Paddle(sf::Vector2f position, sf::Keyboard::Key leftKey, sf::Keyboard::Key rightKey);

	void ReactToInput(float dt);

private:

	sf::Keyboard::Key m_LeftKey;
	sf::Keyboard::Key m_RigthKey;
};
