#pragma once
#include "Game/Ball.h"
#include "Game/Brick.h"
#include "Game/Paddle.h"
#include <SFML/Graphics/Drawable.hpp>
#include <vector>

template <typename T>
concept HasGetRectAndSetPosition = requires(T obj, sf::Vector2f vec2f)
{
	{ obj.GetRect() } -> std::same_as<sf::FloatRect>;
	{ obj.SetPosition(vec2f) } -> std::same_as<void>;
};

template <typename T>
concept HasVelocity = requires(T obj, sf::Vector2f velocity)
{
	{ obj.GetVelocity() } -> std::same_as<sf::Vector2f>;
	{ obj.SetVelocity(velocity) } -> std::same_as<void>;
};

class Game
{
public:

	enum class State : char
	{
		Ongoing = 0,
		Ended
	};

	Game(std::vector<Ball>&& balls, std::vector<Brick>&& bricks, std::vector<Paddle>&& paddles);
	virtual State Update(float dt);
	virtual ~Game() = default;

	void SetGameLimits(const sf::FloatRect& limits) { m_GameLimits = limits; }
	void DrawOn(sf::RenderTarget& target);

protected:

	template <HasGetRectAndSetPosition T>
	void KeepInGameLimits(T& obj)
	{
		const sf::FloatRect objRect = obj.GetRect();
		const sf::FloatRect intersection = m_GameLimits.findIntersection(objRect).value_or(sf::FloatRect());
		if (intersection == objRect)
		{
			// Still in limits
			return;
		}

		sf::Vector2f position = objRect.position;
		const float minX = m_GameLimits.position.x;
		const float maxX = m_GameLimits.position.x + m_GameLimits.size.x - objRect.size.x;
		const float minY = m_GameLimits.position.y;
		const float maxY = m_GameLimits.position.y + m_GameLimits.size.y - objRect.size.y;

		// Bounce if has velocity
		if constexpr (HasVelocity<T>)
		{
			sf::Vector2f velocity = obj.GetVelocity();

			if (position.x < minX)
			{
				position.x = 2 * minX - position.x;
				velocity.x = -velocity.x;
			}
			else if (position.x > maxX)
			{
				position.x = 2 * maxX - position.x;
				velocity.x = -velocity.x;
			}

			if (position.y < minY)
			{
				position.y = 2 * minY - position.y;
				velocity.y = -velocity.y;
			}
			else if (position.y > maxY)
			{
				position.y = 2 * maxY - position.y;
				velocity.y = -velocity.y;
			}

			obj.SetVelocity(velocity);
		}

		// otherwise simple clamp
		else position =
		{
			std::clamp(position.x, minX, maxX),
			std::clamp(position.y, minY, maxY)
		};

		obj.SetPosition(position);
	}

	void CollisionResolution(Paddle currentPaddle);

protected:

	std::vector<Ball> m_Balls;
	std::vector<Brick> m_Bricks;
	std::vector<Paddle> m_Paddles;
	sf::FloatRect m_GameLimits;
};
