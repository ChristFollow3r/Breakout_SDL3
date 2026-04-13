#pragma once
#include "scene.hpp"
#include "utils.hpp"
#include "ball.hpp"
#include "brick.hpp"
#include <vector>
#include <string>

class GameScene : public Scene {

	SDLState& state;
	TTF_Font* font;

	const float paddleSpeed = 600.0f;
	const int paddleLength = 33;
	const int paddleRightLimit = width - paddleLength;
	const int paddleLeftLimit = 0;

	std::unique_ptr<Ball> ball;
	std::unique_ptr<Rectangle> lPaddle;
	std::unique_ptr<Rectangle> mPaddle;
	std::unique_ptr<Rectangle> rPaddle;

	std::vector<std::vector<std::unique_ptr<Brick>>> gridOfBricks;

	int lifes;
	int points;
	float pointAdder = 0.0f;
	float waitTimer = 0.0f;

	std::vector<std::vector<std::unique_ptr<Brick>>> CreateBricks();
	void PaddleMovement(float dt);
	void PaddleBorderCollisions();
	bool BrickCollisions();

public:

	GameScene(SDLState& state, TTF_Font* font);

	void HandleEvent(const SDL_Event& event) override;
	void Update(float dt) override;
	void Render() override;

	void Reset();

};
