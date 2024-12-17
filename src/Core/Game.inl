#include "Game.h"
#include <cassert>

template<typename T, typename ...Args>
	requires std::constructible_from<T, Args...>
inline std::weak_ptr<T> Game::CreateObject(Args&&... args)
{
	std::shared_ptr shared = std::make_shared<T>(std::forward<Args>(args)...);

	if constexpr (std::derived_from<T, IUpdatable>)
	{
		std::weak_ptr weak = std::static_pointer_cast<IUpdatable>(shared);
		OnUpdatableCreated(weak);
	}
	if constexpr (std::derived_from<T, sf::Drawable>)
	{
		std::weak_ptr weak = std::static_pointer_cast<sf::Drawable>(shared);
		OnDrawableCreated(weak);
	}

	std::weak_ptr weak = shared;
	m_Objects.emplace_back(std::move(shared));
	return weak;
}

template<typename T>
inline void Game::DestroyObject(std::weak_ptr<T> ptr)
{
	auto shared = ptr.lock();
	auto it = m_Objects.begin();
	for (; it != m_Objects.end(); ++it)
	{
		if (*it == shared) break;
	}

	assert(it != m_Objects.end());

	if constexpr (std::derived_from<T, IUpdatable>)
	{
		std::weak_ptr weak = std::static_pointer_cast<IUpdatable>(shared);
		OnUpdatableDestroyed(weak);
	}
	if constexpr (std::derived_from<T, sf::Drawable>)
	{
		std::weak_ptr weak = std::static_pointer_cast<sf::Drawable>(shared);
		OnDrawableDestroyed(weak);
	}

	m_Objects.erase(it);
}
