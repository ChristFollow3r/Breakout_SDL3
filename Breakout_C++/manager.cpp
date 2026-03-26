#include "manager.hpp"

void initialize(SDLState& state){

	int width = 1280;
	int height = 720;

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

void render(SDLState& state) {
	SDL_SetRenderDrawColor(state.renderer, 0, 0, 0, 255);
	SDL_RenderClear(state.renderer);
	SDL_RenderPresent(state.renderer);
}

void cleanUp(SDLState& state) {
	SDL_DestroyRenderer(state.renderer);
	SDL_DestroyWindow(state.window);
	SDL_Quit();
}