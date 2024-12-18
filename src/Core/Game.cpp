#include "Game.h"

Game::Game(std::vector<Ball>&& balls, std::vector<Brick>&& bricks, std::vector<Paddle>&& paddles)
	: m_Balls(std::move(balls))
	, m_Bricks(std::move(bricks))
	, m_Paddles(std::move(paddles))
{
}

Game::State Game::Update(float dt)
{
	for (auto& ball : m_Balls)
	{
		ball.Update(dt);
		KeepInGameLimits(ball);
	}
	for (auto& paddle : m_Paddles)
	{
		paddle.Update(dt);
		KeepInGameLimits(paddle);
	}

	return State::Ongoing;
}

void Game::DrawOn(sf::RenderTarget& target)
{
	for (auto& ball : m_Balls)
	{
		ball.draw(target, sf::RenderStates::Default);
	}
	for (auto& brick : m_Bricks)
	{
		brick.draw(target, sf::RenderStates::Default);
	}
	for (auto& paddle : m_Paddles)
	{
		paddle.draw(target, sf::RenderStates::Default);
	}
}

void Game::CollisionResolution(Paddle currentPaddle)
{
	for (Ball& ball : m_Balls)
	{
		for (Brick& brick : m_Bricks)
		{
			if (ball.CheckForCollision(brick.GetRect()))
				brick.LooseHp(1);
		}
		if (ball.CheckForCollision(currentPaddle.GetRect()))
			return;
	}
}
