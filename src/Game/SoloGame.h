#pragma once
#include "Core/Game.h"

class Ball;
class Brick;
class Paddle;

class SoloGame : public Game
{
public:

	SoloGame();
	~SoloGame();

private:

	std::weak_ptr<Ball> m_Ball;
	std::weak_ptr<Brick> m_Brick;
	std::weak_ptr<Paddle> m_Paddle;

	// Inherited via Game
	void Init() override;
};
