#include "SoloGame.h"
#include "Utils/Logger.h"

SoloGame::SoloGame()
{
	Logger::Instance() << "Hi from solo game!\n";
}

SoloGame::~SoloGame()
{
	Logger::Instance() << "goodbye from solo game!\n";
}
