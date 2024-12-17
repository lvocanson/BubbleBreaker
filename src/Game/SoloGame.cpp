#include "SoloGame.h"
#include "Utils/Logger.h"

SoloGame::SoloGame()
	: Game(
		{ // Balls
			{{0.f, 0.f}},
		},
		{ // Bricks
			{{100.f, 100.f}, 0},
		},
		{ // Paddles
			{{100.f, 800.f}, sf::Keyboard::Key::Left, sf::Keyboard::Key::Right},
		})
{
	m_Balls[0].SetVelocity({20.f, 10.f});
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

