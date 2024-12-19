#include "SoloGame.h"
#include "Core/Resources.h"
#include "Utils/Logger.h"
#include <random>

SoloGame::SoloGame(int hp)
	: Game(
		{ // Balls
			{{50.f, 50.f}},
		},
		{ // Bricks
			{{100,100}, 3},
		},
		{ // Paddles
			{{100.f, 800.f}, sf::Keyboard::Key::Left, sf::Keyboard::Key::Right},
		}),
		m_PlayerHp(hp)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> angleDist(sf::priv::pi, sf::priv::pi * 2.f);

	const sf::Angle angle = sf::radians(angleDist(gen));
	m_Balls[0].SetVelocity({Resources::MinBallSpeed, angle});
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