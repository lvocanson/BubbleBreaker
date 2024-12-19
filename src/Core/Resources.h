#pragma once
#include <array>
#include <SFML/Graphics.hpp>

namespace Resources
{
static constexpr auto WindowSize = sf::Vector2u{1600u, 900u};

static constexpr auto BallTexture = "res/ball.png";
static constexpr auto BallSize = sf::Vector2f{25.f, 25.f};
static constexpr auto MinBallSpeed = 300.f;
static constexpr auto MaxBallSpeed = 1000.f;
static constexpr auto BounceSpeedFactor = 1.01f;

static constexpr auto BrickTexture = "res/brick.png";
static constexpr auto BrickSize = sf::Vector2f{100.f, 50.f};

static constexpr auto PaddleTexture = "res/paddle.png";
static constexpr auto PaddleSize = sf::Vector2f{100.f, 25.f};
static constexpr auto PaddleSpeed = 300.f;
static constexpr auto PaddleMaxBounceAngleDelta = sf::degrees(45.f);
static constexpr auto PaddleMinBounceAngleResult = sf::degrees(10.f);
static constexpr auto PaddleMaxBounceAngleResult = sf::degrees(180.f) - PaddleMinBounceAngleResult;

static constexpr auto BackgroundTexture = "res/bg.png";

static constexpr int SoloGameStartHp = 3;
static constexpr auto BallSpawnPoint = sf::Vector2f(25.f, 25.f);


static constexpr auto TexturePaths = std::array
{
	BallTexture,
	BrickTexture,
	PaddleTexture,
	BackgroundTexture
};

static constexpr auto BrickColors = std::array
{
	sf::Color::White,
	sf::Color::Blue,
	sf::Color::Green,
	sf::Color::Yellow,
};
}
