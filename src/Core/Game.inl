#include "Game.h"
#include "Resources.h"

template <typename T>
concept HasVelocity = requires(T obj, sf::Vector2f velocity)
{
	{ obj.GetVelocity() } -> std::same_as<sf::Vector2f>;
	{ obj.SetVelocity(velocity) } -> std::same_as<void>;
};

template<HasGetRectAndSetPosition T>
void Game::KeepInGameLimits(T& obj)
{
	const sf::FloatRect objRect = obj.GetRect();
	const sf::FloatRect gameRect = {{}, sf::Vector2f(Resources::WindowSize)};
	const sf::FloatRect intersection = gameRect.findIntersection(objRect).value_or(sf::FloatRect());
	if (intersection == objRect)
	{
		// Still in limits
		return;
	}

	sf::Vector2f position = objRect.position;
	const float maxX = gameRect.size.x - objRect.size.x;
	const float maxY = gameRect.size.y - objRect.size.y;

	// Bounce if has velocity
	if constexpr (HasVelocity<T>)
	{
		sf::Vector2f velocity = obj.GetVelocity();

		if (position.x < 0.f)
		{
			position.x = -position.x;
			velocity.x = -velocity.x;
		}
		else if (position.x > maxX)
		{
			position.x = 2.f * maxX - position.x;
			velocity.x = -velocity.x;
		}

		if (position.y < 0.f)
		{
			position.y = -position.y;
			velocity.y = -velocity.y;
		}
		else if (position.y > maxY)
		{
			position.y = 2.f * maxY - position.y;
			velocity.y = -velocity.y;
		}

		obj.SetVelocity(velocity);
	}

	// otherwise simple clamp
	else position =
	{
		std::clamp(position.x, 0.f, maxX),
		std::clamp(position.y, 0.f, maxY)
	};

	obj.SetPosition(position);
}
