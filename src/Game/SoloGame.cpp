#include "SoloGame.h"
#include "Utils/Logger.h"

SoloGame::SoloGame()
	: m_Ball(std::make_unique<Ball>(sf::Vector2f{0.f, 0.f}))
	, m_Brick(std::make_unique<Brick>(sf::Vector2f{100.f, 100.f}, 0))
	, m_Paddle(std::make_unique<Paddle>(sf::Vector2f(100.f, 800.f), sf::Keyboard::Key::Left, sf::Keyboard::Key::Right))
{
	m_Ball->SetVelocity({20.f, 10.f});
}

SoloGame::~SoloGame()
{
}

void SoloGame::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	m_Ball->draw(target, states);
	m_Brick->draw(target, states);
	m_Paddle->draw(target, states);
}

void SoloGame::Update(float dt)
{
	m_Ball->Update(dt);
	m_Paddle->Update(dt);
}

