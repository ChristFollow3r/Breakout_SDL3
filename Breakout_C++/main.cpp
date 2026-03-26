#include <iostream>
#include <SDL3/SDL_main.h>
#include "manager.hpp"

int main(int arg, char* argv[]) {
	
	SDLState state;
	initialize(state);

	bool running = true;
	

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

	cleanup(state);
	return 0;

}
