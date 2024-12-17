#pragma once
#include "Game.h"
#include <SFML/Graphics/RenderWindow.hpp>

class IUpdatable;

class App
{
public:

	App(int argc, char* argv[]);
	int Run();

private:

	void PollEvents();
	void Update();
	void Draw();

private:

	bool m_IsReadyToRun = false;
	sf::RenderWindow m_Window;
	sf::Clock m_FrameClock;
	std::unique_ptr<Game> m_Game;
};
