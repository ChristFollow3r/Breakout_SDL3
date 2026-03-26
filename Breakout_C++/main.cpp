#include <SDL3/SDL_main.h>
#include <iostream>
#include <memory>
#include "manager.hpp"
#include "rectangle.hpp"

int main(int arg, char* argv[]) {
	
	SDLState state;
	initialize(state);

	bool running = true;
	
	SDL_Color color = { 255, 0, 0, 255 };
	SDL_FRect rect = { 100, 100, 100, 100 };
	auto rectangleTest = std::make_shared<Rectangle>(rect, state.renderer, color);

	while (running) {

		SDL_Event event{0};

		while (SDL_PollEvent(&event)) {
			switch (event.type) {

			case SDL_EVENT_QUIT:
				cleanUp(state);
				running = false;
				break;

			case SDL_EVENT_KEY_DOWN:
				if (event.key.key == SDLK_A) rectangleTest->rect.x += 1.0f;
				break;
			}
		}



		SDL_SetRenderDrawColor(state.renderer, 0, 0, 0, 255);
		SDL_RenderClear(state.renderer);
		rectangleTest->draw(state, rectangleTest->rect, color);
		SDL_RenderPresent(state.renderer);

		//render(state);

	}

	cleanUp(state);
	return 0;

}
