#pragma once
#include <functional>

class IUpdatable;
namespace sf
{
class Drawable;
}

class Game
{
	using UpdatableCallback = std::function<void(IUpdatable&)>;
	using DrawableCallback = std::function<void(sf::Drawable&)>;

public:

	virtual ~Game() = default;

	UpdatableCallback OnUpdatableCreated;
	UpdatableCallback OnUpdatableDestroyed;
	DrawableCallback OnDrawableCreated;
	DrawableCallback OnDrawableDestroyed;
};
