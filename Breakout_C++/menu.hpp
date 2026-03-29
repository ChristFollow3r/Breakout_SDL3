#pragma once
#include "manager.hpp"
#include "button.hpp"
#include "ball.hpp"

void drawButton(SDLState state, Button* button);

void menu(SDLState state,
	TTF_Font* font,
	std::vector<std::vector<std::shared_ptr<Brick>>>& gridOfBricks,
	std::shared_ptr<Rectangle> lPaddle,
	std::shared_ptr<Rectangle> mPaddle,
	std::shared_ptr<Rectangle> rPaddle,
	std::shared_ptr<Ball> ball,
	float dt);

void rankingScreen();
