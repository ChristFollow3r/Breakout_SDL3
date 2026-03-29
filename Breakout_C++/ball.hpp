#pragma once
#include "rectangle.hpp"
#include <memory>

class Ball : public Rectangle {

public:

	static const int ballSize = 20;
	static constexpr float ballSpawnTimer = 3.0f; // I had to ask AI this. WHY THE FUCK CAN'T I DO STATIC CONST OF A FLOAT WHAT A FUCKING STUPID RULE THAT IS

	const float ballXConstSpeed = 320.0f;

	float ballYSpeed = 320.0f; // Should this be a struct called velocity or sm like that?
	float ballXSpeed = 320.0f;

	Ball(SDL_FRect rect, SDL_Renderer* renderer, SDL_Color color) : Rectangle(rect, renderer, color) {};

	void UpdateBallPhysics(std::shared_ptr<Rectangle> lPaddle, std::shared_ptr<Rectangle> mPaddle, std::shared_ptr<Rectangle> rPaddle, float dt, int& lifes);
	void CheckCollisions(std::shared_ptr<Rectangle> lPaddle, std::shared_ptr<Rectangle> mPaddle, std::shared_ptr<Rectangle> rPaddle);
	//int GetBallSize() { return ballSize; }

private:


};
