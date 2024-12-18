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
			{{100.f, 100.f}, 0},
		},
		{ // Paddles
			{{100.f, 800.f}, sf::Keyboard::Key::Left, sf::Keyboard::Key::Right},
		})
{
	std::random_device rd;
	std::mt19937 gen(rd());
	static constexpr float PI = 3.14159265358979323846f;
	std::uniform_real_distribution<float> angleDist(PI, PI * 2);

	const float angle = angleDist(gen);
	const sf::Vector2f randomUpUnitVec
	{
		std::cos(angle),
		std::sin(angle)
	};

	m_Balls[0].SetVelocity(randomUpUnitVec * Resources::MinBallSpeed);
}

Game::State SoloGame::Update(float dt)
{
	// Update balls & paddle
	Game::Update(dt);

	// TODO: end conditions
	return State::Ongoing;
}

SoloGame::~SoloGame()
{
}

