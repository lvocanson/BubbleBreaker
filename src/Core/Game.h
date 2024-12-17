#pragma once
#include <functional>
#include <memory>

class IUpdatable;
namespace sf
{
class Drawable;
}

class Game
{
	using UpdatableCallback = std::function<void(std::weak_ptr<IUpdatable>&)>;
	using DrawableCallback = std::function<void(std::weak_ptr<sf::Drawable>&)>;

public:

	virtual ~Game() = default;

	// Called by the app after callbacks are set
	virtual void Init() = 0;

	template <typename T, typename... Args>
		requires std::constructible_from<T, Args...>
	std::weak_ptr<T> CreateObject(Args&&... args);

	template <typename T>
	void DestroyObject(std::weak_ptr<T> obj);

	UpdatableCallback OnUpdatableCreated;
	UpdatableCallback OnUpdatableDestroyed;
	DrawableCallback OnDrawableCreated;
	DrawableCallback OnDrawableDestroyed;

private:

	std::vector<std::shared_ptr<void>> m_Objects;
};

#include "Game.inl"
