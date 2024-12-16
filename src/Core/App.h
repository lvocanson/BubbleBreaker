#pragma once
#include "ResourcesManager.h"
#include <SFML/Graphics.hpp>

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
	ResourcesManager m_Resources;
	sf::RenderWindow m_Window;
	sf::Clock m_FrameClock;
};
