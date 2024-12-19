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
	for (Entity& e : *this)
	{
		e.Draw(target, states);
	}
}

void Game::CollisionResolution(const Paddle& currentPaddle)
{
	for (Ball& ball : m_Balls)
	{
		for (Brick& brick : m_Bricks)
		{
			if (ball.ReactToCollision(brick.GetRect()))
				brick.LooseHp(1);
		}

		if (ball.ReactToCollision(currentPaddle.GetRect()))
		{
			const auto velocity = ball.GetVelocity();
			const auto currentAngle = velocity.angle();
			const auto bounceAngle = currentPaddle.CalculateBounceAngle(ball.GetRect(), currentAngle);
			ball.SetVelocity({ velocity.length(), bounceAngle });
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

Game::GameIterator& Game::GameIterator::operator++()
{
	std::visit([this](auto& it) -> void
		{
			++it;
			using ItType = decltype(it);
			if constexpr (std::equality_comparable_with<ItType, BallIt>)
			{
				if (it == m_Owner->m_Balls.end())
					m_Current = m_Owner->m_Bricks.begin();
			}
			if constexpr (std::equality_comparable_with<ItType, BrickIt>)
			{
				if (it == m_Owner->m_Bricks.end())
					m_Current = m_Owner->m_Paddles.begin();
			}
		}, m_Current);
	return *this;
}

Entity& Game::GameIterator::operator*()
{
	return std::visit([](auto& it) -> Entity&
		{
			return *it;
		}, m_Current);
}
