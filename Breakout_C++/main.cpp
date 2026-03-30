#include <SDL3/SDL_main.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <iostream>
#include <memory>
#include "manager.hpp"
#include "menu.hpp"
#include "gameplay.hpp"
#include "gameState.hpp"
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
	ball->ballYSpeed = -ball->ballYSpeed; // I have to flip the ball speed so it starts the game going upwards. I could start with a negative value but this is already done

	// This is for the text stuff

	TTF_Init();
	TTF_Font* font = TTF_OpenFont("Roboto.ttf", 142);

	// Loading screen ********************************************************************************************************************************************
	SDL_Surface* starterSceneTextSurface = TTF_RenderText_Blended(font, "BREAKOUT", 0, { 255, 255, 255, 255 });
	SDL_Texture* texture = SDL_CreateTextureFromSurface(state.renderer, starterSceneTextSurface);
	SDL_DestroySurface(starterSceneTextSurface);

	float textWidth, textHeight;
	SDL_GetTextureSize(texture, &textWidth, &textHeight); // I got this function from AI
	SDL_FRect textRect = { (width - textWidth) / 2, (height - textHeight) / 2, textWidth, textHeight };
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
	auto backButton = createButton(font, state, "Back", (width - 240), (height - 140));
	// ***********************************************************************************************************************************************************
	GameState gameState = MENU;
	// Ranking stuff
	std::vector<std::string> rankingValues;
	std::string playerName = "";

	//lifes = 0;
	int lifes = 3;
	int points = 0;

	SDL_FRect textRectangleRect = { (width - 200) / 2, (height - 100) / 2, 200, 100 };
	SDL_Color textRectangleColor = { 255, 255, 255, 255 };

	while (running) {

		SDL_Event event{ 0 };
		float dt = deltaTime(lastTick);

		if (loadingScreen(state, dt, font, texture, textRect)) continue;

		while (SDL_PollEvent(&event)) {

			switch (event.type) {

			case SDL_EVENT_QUIT:
				cleanUp(state);
				running = false;
				break;

			case SDL_EVENT_MOUSE_BUTTON_DOWN:

				if (event.button.button == SDL_BUTTON_LEFT) {

					if (playButton->Clicked()) gameState = GAME;
					if (rankingButton->Clicked()) gameState = RANKING;
					if (creditsButton->Clicked()) gameState = CREDITS;
					if (backButton->Clicked()) gameState = MENU;
					if (exitButton->Clicked()) running = false;

				}
				break;

			case SDL_EVENT_TEXT_INPUT: // It's always listening for keyboard events when the start text input function is called

				if (gameState == NAME_INPUT) { // When the game state switches to NAME_INPUT we add every keayboard event to the playerName string.
					playerName += event.text.text;
					std::cout << playerName;
					break;
				}

			case SDL_EVENT_KEY_DOWN:
				if (event.key.key == SDLK_BACKSPACE && !playerName.empty()) playerName.pop_back();
				if (event.key.key == SDLK_RETURN) {
					// Ranking bullshit here
					gameState = MENU;
					playerName = "";
					break;
				}

			}

		}

		switch (gameState) {

		case GameState::MENU: {
			SDL_SetRenderDrawColor(state.renderer, 0, 0, 0, 255); // I could do a function for this but I'm super tired rn perhaps I don't even change it LOL
			SDL_RenderClear(state.renderer);
			drawButton(state, playButton.get());
			drawButton(state, rankingButton.get());
			drawButton(state, creditsButton.get());
			drawButton(state, exitButton.get());
			SDL_RenderPresent(state.renderer);
			break;
		}

		case GameState::GAME: // I have to reset the gameplay here
			breakoutGameplay(state, gridOfBricks, lPaddle, mPaddle, rPaddle, ball, dt, lifes, points, gameState, font);
			break;

		case GameState::NAME_INPUT:
			SDL_StartTextInput(state.window);
			SDL_SetRenderDrawColor(state.renderer, 0, 0, 0, 255);
			SDL_RenderClear(state.renderer);

			drawText(state, font, "ENTER YOUR NAME", 68, (width / 2), 150, {255, 255, 255, 255}); // I'm thinking I should've made a const of a color long ago but whataver
			if (!playerName.empty()) drawText(state, font, playerName, 24, width / 2, height / 2, { 255, 255, 255, 255 });

			SDL_RenderPresent(state.renderer);
			break;

		case GameState::CREDITS:
			SDL_SetRenderDrawColor(state.renderer, 0, 0, 0, 255);
			SDL_RenderClear(state.renderer);
			drawButton(state, backButton.get());
			drawText(state, font, "MADE BY", 68, (width / 2), 150, { 255, 255, 255, 255 });
			drawText(state, font, "NIL BADIA GIMENEZ", 128, (width / 2), (height / 2 - 100), { 255, 255, 255, 255 });
			SDL_RenderPresent(state.renderer);
			break;

		default:
			break;
		}



	}

	cleanUp(state);
	return 0;

}

