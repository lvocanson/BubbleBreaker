#pragma once
#include "Core/Game.h"

class SoloGame : public Game
{
public:

	SoloGame();
	State Update(float dt) override;
	~SoloGame();
};
