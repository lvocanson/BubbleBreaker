#include "App.h"
#include "Game/SoloGame.h"
#include "Resources.h"
#include "ResourcesManager.h"
#include "Utils/Logger.h"
#include <iostream>

App::App(int argc, char* argv[])
{
	Logger::Create(std::cout);
	Logger::Instance() << "Initializing app...\n";

	ResourcesManager::Create(Resources::TexturePaths.size());
	for (auto path : Resources::TexturePaths)
	{
		if (!ResourcesManager::Instance().LoadTexture(path))
		{
			Logger::Instance() << "Failed: load texture at path `" << path << "`.\n";
			return;
		}
	}

	m_Window.create(sf::VideoMode({ 1600u, 900u }), "BubbleBreaker");
	if (!m_Window.isOpen())
	{
		Logger::Instance() << "Failed: window creation.\n";
		return;
	}
	m_Window.setFramerateLimit(144u);

	m_Game = std::make_unique<SoloGame>(Resources::SoloGameStartHp);
	if (!m_Game.get())
	{
		Logger::Instance() << "Failed: game creation.\n";
		return;
	}
	m_Game->SetGameLimits({ {0.f, 0.f}, {300.f, 300.f} });

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
	const float dt = m_FrameClock.restart().asSeconds();
	m_Game->Update(dt);
}

void App::Draw()
{
	m_Window.clear();
	m_Game->DrawOn(m_Window, sf::RenderStates::Default);
	m_Window.display();
}
