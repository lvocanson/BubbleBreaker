#pragma once
#include "Game/Ball.h"
#include "Game/Brick.h"
#include "Game/Paddle.h"
#include <SFML/Graphics/Drawable.hpp>
#include <vector>

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

	void DrawOn(sf::RenderTarget& target);

protected:

	std::vector<Ball> m_Balls;
	std::vector<Brick> m_Bricks;
	std::vector<Paddle> m_Paddles;
};
