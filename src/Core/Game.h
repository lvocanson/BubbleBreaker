#pragma once
#include "Game/Ball.h"
#include "Game/Brick.h"
#include "Game/Paddle.h"
#include <SFML/Graphics/Drawable.hpp>
#include <algorithm>
#include <variant>
#include <vector>

template <typename T>
concept HasGetRectAndSetPosition = requires(T obj, sf::Vector2f vec2f)
{
	{ obj.GetRect() } -> std::same_as<sf::FloatRect>;
	{ obj.SetPosition(vec2f) } -> std::same_as<void>;
};

class Game
{
public:

	enum class State : char
	{
		Ongoing = 0,
		Ended
	};

	/**
	* @brief New game
	* 
	* @param limits The limits of the game, should be the window size
	* @param size The original size of the game, the game will be scaled to fit in the limits (keeping ratio)
	*/
	Game(std::vector<Ball>&& balls, std::vector<Brick>&& bricks, std::vector<Paddle>&& paddles);
	virtual State Update(float dt);
	virtual ~Game() = default;

	void DrawOn(sf::RenderTarget& target, const sf::RenderStates& states);

protected:

	template <HasGetRectAndSetPosition T>
	void KeepInGameLimits(T& obj);

	void CollisionResolution(const Paddle& currentPaddle);

	bool IsOutsideOfLimits(const Ball& ball, float dt) const;


protected:

	class GameIterator
	{
	public:
		using BallIt = typename std::vector<Ball>::iterator;
		using BrickIt = typename std::vector<Brick>::iterator;
		using PaddleIt = typename std::vector<Paddle>::iterator;
		using VariantType = std::variant<BallIt, BrickIt, PaddleIt>;

		GameIterator(VariantType it, Game* owner = nullptr)
			: m_Current(std::move(it))
			, m_Owner(owner)
		{
		}

		GameIterator& operator++();
		Entity& operator*();

		bool operator==(const GameIterator& other) const { return m_Current == other.m_Current; }
		bool operator!=(const GameIterator& other) const { return !(*this == other); }

	private:

		VariantType m_Current;
		Game* m_Owner;
	};

	GameIterator begin() { return {m_Balls.begin(), this}; }
	GameIterator end() { return {m_Paddles.end()}; }

protected:

	std::vector<Ball> m_Balls;
	std::vector<Brick> m_Bricks;
	std::vector<Paddle> m_Paddles;
	Entity m_Background;
};

#include "Game.inl"
