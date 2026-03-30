#pragma once
#include "manager.hpp"
#include "ball.hpp"


static inline float waitTimer = 0.0f; // Static inline makes it so that the second time the compiler sees this it ignores it and keeps on with the program
// I used it a lot in my sand simlator cause I was using an array with multiple colors for creating the materials and everytime I created a material
// the array would create itself again throwing erros. That's how I learned about this. You can check it out on my github page, repo is open.

void breakoutGameplay(SDLState state,
	std::vector<std::vector<std::shared_ptr<Brick>>>& gridOfBricks, 
	std::shared_ptr<Rectangle> lPaddle, 
	std::shared_ptr<Rectangle> mPaddle,
	std::shared_ptr<Rectangle> rPaddle,
	std::shared_ptr<Ball> ball, 
	float dt,
	int& lifes, 
	GameState& gameState);
