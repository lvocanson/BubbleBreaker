#pragma once
#include "Game.h"
#include <SFML/Graphics.hpp>

class IUpdatable;

class App
{
public:

	App(int argc, char* argv[]);
	int Run();

private:

	template <typename G, typename... Args>
		requires std::derived_from<G, Game> && std::constructible_from<G, Args...>
	void NewGame(Args&&... args);

	void AddUpdatable(std::weak_ptr<IUpdatable>&);
	void RemoveUpdatable(std::weak_ptr<IUpdatable>&);
	void AddDrawable(std::weak_ptr<sf::Drawable>&);
	void RemoveDrawable(std::weak_ptr<sf::Drawable>&);

	void PollEvents();
	void Update();
	void Draw();

private:

	bool m_IsReadyToRun = false;
	sf::RenderWindow m_Window;
	sf::Clock m_FrameClock;

	std::unique_ptr<Game> m_Game;
	std::vector<std::weak_ptr<IUpdatable>> m_Updatables;
	std::vector<std::weak_ptr<sf::Drawable>> m_Drawables;
};
