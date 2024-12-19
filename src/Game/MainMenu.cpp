#include "MainMenu.h"
#include "SoloGame.h"
#include "Core/ResourcesManager.h"

MainMenu::MainMenu(const sf::WindowBase& parent, std::unique_ptr<Game>& gameInstance)
	: Game({}, {}, {})
	, m_Parent(parent)
	, m_GameInstance(gameInstance)
	, m_PlaySoloButton(ResourcesManager::Instance().GetTexture(Resources::PlaySoloTexture), {(sf::Vector2f(Resources::WindowSize) - Resources::PlaySoloSize) / 2.f, Resources::PlaySoloSize})
{
}

Game::State MainMenu::Update(float dt)
{
	using namespace sf::Mouse;
	if (isButtonPressed(Button::Left) &&
		m_PlaySoloButton.GetRect().contains(sf::Vector2f(getPosition(m_Parent))))
	{
		m_GameInstance = std::make_unique<SoloGame>();
	}

	return State::Ongoing;
}

void MainMenu::DrawOn(sf::RenderTarget& target, const sf::RenderStates& states)
{
	// Draw bg
	Game::DrawOn(target, states);

	m_PlaySoloButton.Draw(target, states);
}

MainMenu::~MainMenu()
{
}
