#pragma once
#include "Core/Game.h"
#include "Ball.h"
#include "Brick.h"
#include "Paddle.h"

namespace sf
{
class RenderTarget;
class RenderStates;
}

class SoloGame : public Game
{
public:

	SoloGame();
	~SoloGame();

private:

	std::unique_ptr<Ball> m_Ball;
	std::unique_ptr<Brick> m_Brick;
	std::unique_ptr<Paddle> m_Paddle;

private:

	// Inherited via Game
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void Update(float dt) override;
};
