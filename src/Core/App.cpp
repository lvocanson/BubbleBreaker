#include "App.h"
#include "IUpdatable.h"
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

	m_Window.create(sf::VideoMode({1600u, 900u}), "BubbleBreaker");
	m_Window.setFramerateLimit(144u);
	if (!m_Window.isOpen())
	{
		Logger::Instance() << "Failed: window creation.\n";
		return;
	}

	NewGame<SoloGame>();

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

template <typename G, typename... Args>
	requires std::derived_from<G, Game>&& std::constructible_from<G, Args...>
inline void App::NewGame(Args&&... args)
{
	m_Game = std::make_unique<G>(std::forward<Args>(args)...);

	using namespace std::placeholders;
	m_Game->OnUpdatableCreated = std::bind(&App::AddUpdatable, this, _1);
	m_Game->OnUpdatableDestroyed = std::bind(&App::RemoveUpdatable, this, _1);
	m_Game->OnDrawableCreated = std::bind(&App::AddDrawable, this, _1);
	m_Game->OnDrawableDestroyed = std::bind(&App::RemoveDrawable, this, _1);
}

void App::AddUpdatable(IUpdatable& updatable)
{
	m_Updatables.emplace_back(updatable);
}

void App::RemoveUpdatable(IUpdatable& updatable)
{
	for (auto it = m_Updatables.begin(); it != m_Updatables.end(); ++it)
	{
		if (&(*it).get() == &updatable)
		{
			m_Updatables.erase(it);
			return;
		}
	}
}

void App::AddDrawable(sf::Drawable& drawable)
{
	m_Drawables.emplace_back(drawable);
}

void App::RemoveDrawable(sf::Drawable& drawable)
{
	for (auto it = m_Drawables.begin(); it != m_Drawables.end(); ++it)
	{
		if (&(*it).get() == &drawable)
		{
			m_Drawables.erase(it);
			return;
		}
	}
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
	for (IUpdatable& updatable : m_Updatables)
	{
		updatable.Update(dt);
	}
}

void App::Draw()
{
	m_Window.clear();
	for (sf::Drawable& drawable : m_Drawables)
	{
		m_Window.draw(drawable);
	}
	m_Window.display();
}
