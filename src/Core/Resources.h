#pragma once
#include <array>

namespace Resources
{
static constexpr auto BallTexture = "res/ball.png";
static constexpr auto BrickTexture = "res/brick.png";
static constexpr auto PaddleTexture = "res/paddle.png";
static constexpr auto BackgroundTexture = "res/bg.png"; 

static constexpr auto TexturePaths = std::array
{
	BallTexture,
	BrickTexture,
	PaddleTexture,
	BackgroundTexture
};
}
