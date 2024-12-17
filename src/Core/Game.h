#pragma once
#include <SFML/Graphics/Drawable.hpp>
#include <memory>

class IUpdatable;
class Game : public sf::Drawable
{
public:

	virtual ~Game() = default;

	virtual void Update(float dt) = 0;

private:

};
