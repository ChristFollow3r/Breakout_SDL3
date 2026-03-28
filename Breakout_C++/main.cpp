#include <SDL3/SDL_main.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <iostream>
#include <memory>
#include "manager.hpp"
#include "gameplay.hpp"
#include "button.hpp"
#include "rectangle.hpp"
#include "ball.hpp"

int main(int arg, char* argv[]) {
	
	SDLState state;
	initialize(state);

	bool running = true;

	Uint64 lastTick = SDL_GetTicks();
	deltaTime(lastTick);

	// Brick creation

	std::vector<std::vector<std::shared_ptr<Brick>>> gridOfBricks = createBricks(state);
	
	// This is for the paddle

	SDL_Color paddleColor = { 255, 0, 0, 255 }; // I could use a vector but I don't think it's worth it
	SDL_FRect rect = { 640, 640, paddleLength, 10 };
	auto lPaddle = std::make_shared<Rectangle>(rect, state.renderer, paddleColor); 
	rect.x += paddleLength;
	auto mPaddle = std::make_shared<Rectangle>(rect, state.renderer, paddleColor);
	rect.x += paddleLength;
	auto rPaddle = std::make_shared<Rectangle>(rect, state.renderer, paddleColor);

	//This is for the ball

	SDL_Color ballColor = { 0, 0, 0, 255 };
	rect = { 720, 550, Ball::ballSize , Ball::ballSize };
	auto ball = std::make_shared<Ball>(rect, state.renderer, ballColor);
	ball->ballYSpeed = -ball->ballYSpeed;

	// This is for the text stuff

	TTF_Init();
	TTF_Font* font = TTF_OpenFont("Emasland_Trial.ttf", 142);

	SDL_Surface* starterSceneTextSurface = TTF_RenderText_Solid(font, "BREAKOUT", 0, { 255, 255, 255, 255 });
	SDL_Texture* texture = SDL_CreateTextureFromSurface(state.renderer, starterSceneTextSurface);
	SDL_DestroySurface(starterSceneTextSurface);

	float textWidht, textHeight;
	SDL_GetTextureSize(texture, &textWidht, &textHeight); // AI gave me this too

	SDL_FRect textRect = { (width - textWidht) / 2, (height - textHeight) / 2, textWidht, textHeight }; // AI gave me the x and y formula I was hardcoding the values

	SDL_Color buttonColor = { 255, 34, 65, 255 }; // I could use a vector but I don't think it's worth it
	SDL_FRect buttonRect = { width / 2, height / 2, 100, 100 };
	SDL_Surface* buttonSurface = TTF_RenderText_Solid(font, "PLAY", 0, { 255, 255, 255, 255 });
	SDL_Texture* buttonTextTexture = SDL_CreateTextureFromSurface(state.renderer, buttonSurface);
	SDL_FRect buttonTextRect = { (width - textWidht) / 2, (height - textHeight) / 2, textWidht, textHeight };
	SDL_DestroySurface(buttonSurface);

	auto testButton = std::make_shared<Button>(buttonRect, state.renderer, buttonColor, buttonTextTexture, buttonTextRect);

	bool buttonClicked = false;

	while (running) {

		SDL_Event event{0};
		float dt = deltaTime(lastTick);
		
		buttonClicked = false;

		while (SDL_PollEvent(&event)) {
			switch (event.type) {

			case SDL_EVENT_QUIT:
				cleanUp(state);
				running = false;
				break;
			case SDL_EVENT_MOUSE_BUTTON_DOWN:
				buttonClicked = true;
				testButton->Clicked(buttonClicked);
				break;
			}
		}

		SDL_SetRenderDrawColor(state.renderer, 0, 0, 0, 255);
		SDL_RenderClear(state.renderer);
		testButton->draw(state, testButton->rect, testButton->color);
		testButton->Hovered();
		SDL_RenderPresent(state.renderer);

		//if (loadingScreen(state, dt, font, texture, textRect)) continue;
		//breakoutGameplay(state, gridOfBricks, lPaddle, mPaddle, rPaddle, ball, dt);

	}

	cleanUp(state);
	return 0;

}
