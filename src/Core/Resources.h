#pragma once
#include <array>
#include <SFML/Graphics.hpp>

namespace Resources
{
static constexpr auto BallTexture = "res/ball.png";
static constexpr auto BallSize = sf::Vector2f{10.f, 10.f};
static constexpr auto MinBallSpeed = 100.f;
static constexpr auto MaxBallSpeed = 100.f;
static constexpr auto BounceSpeedFactor = 1.01f;

static constexpr auto BrickTexture = "res/brick.png";
static constexpr auto BrickSize = sf::Vector2f{100.f, 50.f};

static constexpr auto PaddleTexture = "res/paddle.png";
static constexpr auto PaddleSize = sf::Vector2f{100.f, 50.f};
static constexpr auto PaddleSpeed = 150.f;

static constexpr auto BackgroundTexture = "res/bg.png";

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
