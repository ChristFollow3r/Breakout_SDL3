#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>


struct SDLState {
	SDL_Window* window;
	SDL_Renderer* renderer;
};

void cleanup(SDLState& state);

int main(int arg, char* argv[]) {
	
	SDLState state;

	int width = 720;
	int height = 480;
	bool running = true;

	state.window = SDL_CreateWindow("Breakout", width, height, NULL);

	if (!SDL_Init(SDL_INIT_VIDEO)) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Unable to initialize SDL3", nullptr);
	}
	
	if (!state.window) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Error creating window", nullptr);
	}


	while (running) {

		SDL_Event event{0};

		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_EVENT_QUIT:
				cleanup(state);
				running = false;
				break;
			}
		}
	}

	return 0;

}

void cleanup(SDLState& state) {
	SDL_DestroyWindow(state.window);
	SDL_Quit();
}