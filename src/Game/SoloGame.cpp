#include "SoloGame.h"
#include "Core/Resources.h"
#include "Utils/Logger.h"
#include <random>

static constexpr std::vector<Brick> MakeWallOfBricks(size_t height)
{
	std::vector<Brick> bricks;
	const float spaceAround = 50.f;
	const size_t numBricksInWidth = (Resources::WindowSize.x - 2 * spaceAround) / Resources::BrickSize.x;
	float startY = spaceAround;
	float startX = (Resources::WindowSize.x - numBricksInWidth * Resources::BrickSize.x) / 2.f;

	for (size_t y = 0; y < height; ++y)
	{
		for (size_t x = 0; x < numBricksInWidth; ++x)
		{
			sf::Vector2f position{startX + x * Resources::BrickSize.x, startY + y * Resources::BrickSize.y};
			bricks.emplace_back(position, 3);
		}
	}

	return bricks;
}

SoloGame::SoloGame()
	: Game(
		{ // Balls
			{{50.f, 50.f}},
		},
		MakeWallOfBricks(14),
		{ // Paddles
			{{100.f, 800.f}, sf::Keyboard::Key::Left, sf::Keyboard::Key::Right},
		})
		, m_PlayerHp(Resources::SoloGameStartHp)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> angleDist(sf::priv::pi, sf::priv::pi * 2.f);

	const sf::Angle angle = sf::radians(angleDist(gen));
	m_Balls[0].SetVelocity({ Resources::MinBallSpeed, angle });
}

Game::State SoloGame::Update(float dt)
{
	bool isBallOut = false;
	for (Ball& ball : m_Balls)
	{
		if (IsOutsideOfLimits(ball, dt))
		{
			--m_PlayerHp;
			isBallOut = true;
		}
	}

	if (isBallOut)
	{
		if (m_PlayerHp == 0) return State::Ended;
		isBallOut = false;
		m_Balls.clear();
		m_Balls.emplace_back(Ball(Resources::BallSpawnPoint));
		std::random_device rd;
		std::mt19937 gen(rd());
		static constexpr float PI = 3.14159265358979323846f;
		std::uniform_real_distribution<float> angleDist(PI, PI * 2);

		const sf::Angle angle = sf::radians(angleDist(gen));
		m_Balls[0].SetVelocity({ Resources::MinBallSpeed, angle });
	}

	m_Bricks.erase(
		std::remove_if(m_Bricks.begin(), m_Bricks.end(), [](const auto& brick)
			{
				return brick.GetHp() == 0;
			}),
		m_Bricks.end()
	);

	if (m_Bricks.size() == 0)
	{
		//Game Won
		return State::Ended;
	}

	// Update balls & paddle
	Game::Update(dt);

	// Check and resolve collisions
	Game::CollisionResolution(m_Paddles[0]);

	// TODO: end conditions
	return State::Ongoing;
}

SoloGame::~SoloGame()
{
}