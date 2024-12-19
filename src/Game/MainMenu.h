#pragma once
#include "Core/Game.h"

class MainMenu : public Game
{
public:

	MainMenu(const sf::WindowBase& parent, std::unique_ptr<Game>& gameInstance);
	State Update(float dt) override;
	void DrawOn(sf::RenderTarget& target, const sf::RenderStates& states) override;
	~MainMenu();

private:

	const sf::WindowBase& m_Parent;
	std::unique_ptr<Game>& m_GameInstance;
	Entity m_PlaySoloButton;
};
