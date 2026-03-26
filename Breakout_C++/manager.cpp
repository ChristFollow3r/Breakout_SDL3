#include "manager.hpp"

void initialize(SDLState& state){

	int width = 720;
	int height = 480;

	state.window = SDL_CreateWindow("Breakout", width, height, NULL);

	if (!SDL_Init(SDL_INIT_VIDEO)) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Unable to initialize SDL3", nullptr);
	}

	if (!state.window) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Error creating window", nullptr);
	}
}

void cleanup(SDLState& state) {
	SDL_DestroyWindow(state.window);
	SDL_Quit();
}