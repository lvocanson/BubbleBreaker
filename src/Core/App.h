#pragma once
#include "Game.h";
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

	void AddUpdatable(IUpdatable&);
	void RemoveUpdatable(IUpdatable&);
	void AddDrawable(sf::Drawable&);
	void RemoveDrawable(sf::Drawable&);

	void PollEvents();
	void Update();
	void Draw();

private:

	bool m_IsReadyToRun = false;
	sf::RenderWindow m_Window;
	sf::Clock m_FrameClock;

	std::unique_ptr<Game> m_Game;
	std::vector<std::reference_wrapper<IUpdatable>> m_Updatables;
	std::vector<std::reference_wrapper<sf::Drawable>> m_Drawables;
};
