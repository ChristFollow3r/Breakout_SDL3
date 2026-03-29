#include <SDL3/SDL_main.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <iostream>
#include <memory>
#include "manager.hpp"
#include "menu.hpp"
#include "gameplay.hpp"
#include "rectangle.hpp"
#include "button.hpp"
#include "ball.hpp"

int main(int arg, char* argv[]) {

	SDLState state;
	initialize(state);

	bool running = true;
	int lifes = 3;

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
	ball->ballYSpeed = -ball->ballYSpeed; // I have to flip the ball speed so it starts the game going upwards. I could start with a negative value but this is already done

	// This is for the text stuff

	TTF_Init();
	TTF_Font* font = TTF_OpenFont("Emasland_Trial.ttf", 142);

	// Loading screen ********************************************************************************************************************************************
	SDL_Surface* starterSceneTextSurface = TTF_RenderText_Blended(font, "BREAKOUT", 0, { 255, 255, 255, 255 });
	SDL_Texture* texture = SDL_CreateTextureFromSurface(state.renderer, starterSceneTextSurface);
	SDL_DestroySurface(starterSceneTextSurface);

	float textWidht, textHeight;
	SDL_GetTextureSize(texture, &textWidht, &textHeight); // I got this function from AI
	SDL_FRect textRect = { (width - textWidht) / 2, (height - textHeight) / 2, textWidht, textHeight };
	// Loading screen ********************************************************************************************************************************************

	// Buttons        ********************************************************************************************************************************************
	TTF_SetFontSize(font, 24);
	int buttonWidth = 200;
	int buttonHeight = 100;
	int gap = 20;

	auto playButton = createButton(font, state, "Play", (width - buttonWidth) / 2, buttonHeight);
	auto rankingButton = createButton(font, state, "Ranking", (width - buttonWidth) / 2, (buttonHeight * 2) + gap);
	auto creditsButton = createButton(font, state, "Credits", (width - buttonWidth) / 2, (buttonHeight * 3) + gap * 2);
	auto exitButton = createButton(font, state, "Exit", (width - buttonWidth) / 2, (buttonHeight * 4) + gap * 3);
	// ***********************************************************************************************************************************************************

	bool buttonClicked = false;

	while (running) {

		SDL_Event event{ 0 };
		float dt = deltaTime(lastTick);

		if (loadingScreen(state, dt, font, texture, textRect)) continue;
		GameState gameState = menu(state, playButton.get(), rankingButton.get(), exitButton.get());

		while (SDL_PollEvent(&event)) {

			switch (event.type) {

			case SDL_EVENT_QUIT:
				cleanUp(state);
				running = false;
				break;

			case SDL_EVENT_MOUSE_BUTTON_DOWN:

				if (event.button.button == SDL_BUTTON_LEFT) {

					switch (gameState) {

					case GameState::MENU:
						// To add
						break;

					case GameState::GAME:
						breakoutGameplay(state, gridOfBricks, lPaddle, mPaddle, rPaddle, ball, dt, lifes);
						break;

					default:
						break;
					}
				}

			}


		}

		SDL_SetRenderDrawColor(state.renderer, 0, 0, 0, 255);
		SDL_RenderClear(state.renderer);
		drawButton(state, playButton.get());
		drawButton(state, rankingButton.get());
		drawButton(state, creditsButton.get());
		drawButton(state, exitButton.get());
		SDL_RenderPresent(state.renderer);
		continue;


	}

	cleanUp(state);
	return 0;

}