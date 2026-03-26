#include <SDL3/SDL_main.h>
#include <iostream>
#include <memory>
#include "manager.hpp"
#include "rectangle.hpp"

int main(int arg, char* argv[]) {
	
	SDLState state;
	initialize(state);

	bool running = true;
	

	while (running) {

		SDL_Event event{0};

		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_EVENT_QUIT:
				cleanUp(state);
				running = false;
				break;
			}
		}


		SDL_Color color = { 255, 0, 0, 255 };
		SDL_FRect rect = { 100, 100, 100, 100 };
		auto rectangleTest = std::make_shared<Rectangle>(rect, state.renderer, color);

		SDL_SetRenderDrawColor(state.renderer, 0, 0, 0, 255);
		SDL_RenderClear(state.renderer);
		rectangleTest->draw(state, rect, color);
		SDL_RenderPresent(state.renderer);

		//render(state);

	}

	cleanUp(state);
	return 0;

}
