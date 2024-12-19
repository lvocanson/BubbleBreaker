#include "SoloGame.h"
#include "Core/Resources.h"
#include "Utils/Logger.h"
#include <random>

SoloGame::SoloGame()
	: Game(
		{ // Balls
			{{50.f, 50.f}},
		},
		{ // Bricks
			//{{100,100},3},
		},
		{ // Paddles
			{{100.f, 800.f}, sf::Keyboard::Key::Left, sf::Keyboard::Key::Right},
		})
{
	std::random_device rd;
	std::mt19937 gen(rd());
	static constexpr float PI = 3.14159265358979323846f;
	std::uniform_real_distribution<float> angleDist(PI, PI * 2);

	const sf::Angle angle = sf::radians(angleDist(gen));
	m_Balls[0].SetVelocity({ Resources::MinBallSpeed, angle });
}

Game::State SoloGame::Update(float dt)
{
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