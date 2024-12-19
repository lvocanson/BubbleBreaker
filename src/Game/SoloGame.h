#pragma once
#include "Core/Game.h"

class SoloGame : public Game
{
public:

	SoloGame(int hp);
	State Update(float dt) override;
	~SoloGame();

private:

	int m_PlayerHp;
};
