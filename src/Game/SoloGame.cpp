#include "SoloGame.h"
#include "Ball.h"
#include "Brick.h"
#include "Paddle.h"
#include "Utils/Logger.h"

SoloGame::SoloGame()
{
}

SoloGame::~SoloGame()
{
	if (!m_Ball.expired())
	{
		DestroyObject(m_Ball);
	}
}

void SoloGame::Init()
{
	m_Ball = CreateObject<Ball>(sf::Vector2f{0.f, 0.f});
	m_Ball.lock()->SetVelocity({20.f, 15.f}); 

	m_Brick = CreateObject<Brick>(sf::Vector2f{100.f, 100.f}, 1);

	m_Paddle = CreateObject<Paddle>(sf::Vector2f{100.f, 800.f}, sf::Keyboard::Key::Left, sf::Keyboard::Key::Right);
}
