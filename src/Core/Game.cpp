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
		ball.ApplyVelocity(dt);
		KeepInGameLimits(ball);
	}
	for (auto& paddle : m_Paddles)
	{
		paddle.ReactToInput(dt);
		KeepInGameLimits(paddle);
	}

	return State::Ongoing;
}

void Game::DrawOn(sf::RenderTarget& target, const sf::RenderStates& states)
{
	for (auto& ball : m_Balls)
	{
		ball.Draw(target, states);
	}
	for (auto& brick : m_Bricks)
	{
		if (brick.GetHp() != 0)
			brick.Draw(target, states);
	}
	for (auto& paddle : m_Paddles)
	{
		paddle.Draw(target, states);
	}
}

void Game::CollisionResolution(const Paddle& currentPaddle)
{
	for (Ball& ball : m_Balls)
	{
		for (Brick& brick : m_Bricks)
		{
			if (brick.GetHp() == 0)
				continue;
			if (ball.ReactToCollision(brick.GetRect()))
				brick.LooseHp(1);
		}

		if (ball.ReactToCollision(currentPaddle.GetRect()))
		{
			const auto velocity = ball.GetVelocity();
			const auto currentAngle = velocity.angle();
			const auto bounceAngle = currentPaddle.CalculateBounceAngle(ball.GetRect(), currentAngle);
			ball.SetVelocity({velocity.length(), bounceAngle});
		}
	}
}

bool Game::IsOutsideOfLimits(const Ball& ball, float dt) const
{
	sf::FloatRect rect = ball.GetRect();

	const float maxY = static_cast<float>(Resources::WindowSize.y) - rect.size.y;
	if (rect.position.y + ball.GetVelocity().y * dt >= maxY)
	{
		return true;
	}
	return false;
}
