#include "manager.hpp"
#include "ball.hpp"

void initialize(SDLState& state){

	state.window = SDL_CreateWindow("Breakout", width, height, NULL);
	state.renderer = SDL_CreateRenderer(state.window, nullptr);

	if (!SDL_Init(SDL_INIT_VIDEO)) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Unable to initialize SDL3", nullptr);
	}

	if (!state.window) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Error creating window", nullptr);
	}

	if (!state.renderer) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Error initializingh renderer.", nullptr);
	}
}

void render(SDLState& state, std::shared_ptr<Rectangle> lPaddle, std::shared_ptr<Rectangle> mPaddle, std::shared_ptr<Rectangle> rPaddle, std::shared_ptr<Rectangle> ball, std::vector<std::vector<std::shared_ptr<Brick>>> gridOfBricks, GameState& gameState) {
	SDL_SetRenderDrawColor(state.renderer, 255, 255, 255, 255);
	SDL_RenderClear(state.renderer);
	ball->draw(state, ball->rect, ball->color);
	lPaddle->draw(state, lPaddle->rect, lPaddle->color);
	mPaddle->draw(state, mPaddle->rect, mPaddle->color);
	rPaddle->draw(state, rPaddle->rect, rPaddle->color);
	int counter = 0;
	for (auto x : gridOfBricks)
	{
		if (x.empty()) counter++;
		if (counter >= gridOfBricks.size()) {
			gameState = NAME_INPUT;
			counter = 0;
		}
	}

	for (int i = 0; i < gridOfBricks.size(); i++) {
		for (auto x : gridOfBricks[i]) x->draw(state, x->rect, x->color);
	}
}


bool loadingScreen(SDLState state, float dt, TTF_Font* font, SDL_Texture* texture, SDL_FRect textRect) {

	if (!font) SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Couldn't load the font", state.window);

	loadScreenWaitingTime -= dt;

	if (loadScreenWaitingTime > 0) {
		SDL_SetRenderDrawColor(state.renderer, 15, 20, 40, 255);
		SDL_RenderClear(state.renderer);
		SDL_RenderTexture(state.renderer, texture, nullptr, &textRect);
		SDL_RenderPresent(state.renderer);
		return true;
	}

	else return false;
}


void cleanUp(SDLState& state) {
	SDL_DestroyRenderer(state.renderer);
	SDL_DestroyWindow(state.window);
	SDL_Quit();
}