#include "App.h"
#include "Resources.h"
#include "Utils/Logger.h"
#include <iostream>

App::App(int argc, char* argv[])
	: m_Resources(Resources::TexturePaths.size())
{
	Logger::Create(std::cout);
	Logger::Instance() << "Initializing app...\n";

	for (auto path : Resources::TexturePaths)
	{
		if (!m_Resources.LoadTexture(path))
		{
			Logger::Instance() << "Failed: load texture at path `" << path << "`.\n";
			return;
		}
	}

	m_Window.create(sf::VideoMode({1600u, 900u}), "BubbleBreaker");
	m_Window.setFramerateLimit(144u);
	if (!m_Window.isOpen())
	{
		Logger::Instance() << "Failed: window creation.\n";
		return;
	}

	m_IsReadyToRun = true;
}

int App::Run()
{
	if (!m_IsReadyToRun)
	{
		Logger::Instance() << "An error occured during initialization. Terminating app...\n";
		return EXIT_FAILURE;
	}

	Logger::Instance() << "Initialization succeeded. Starting...\n";
	while (m_Window.isOpen())
	{
		PollEvents();
		Update();
		Draw();
	}

	return EXIT_SUCCESS;
}

void App::PollEvents()
{
	while (const std::optional event = m_Window.pollEvent())
	{
		if (event->is<sf::Event::Closed>())
		{
			Logger::Instance() << "Close event received. Closing window...\n";
			m_Window.close();
		}
	}
}

void App::Update()
{
	float dt = m_FrameClock.restart().asSeconds();
}

void App::Draw()
{
	m_Window.clear();
	m_Window.display();
}
