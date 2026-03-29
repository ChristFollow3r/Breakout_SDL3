#include "menu.hpp"

void menu(SDLState state,
	TTF_Font* font,
	std::vector<std::vector<std::shared_ptr<Brick>>>& gridOfBricks,
	std::shared_ptr<Rectangle> lPaddle,
	std::shared_ptr<Rectangle> mPaddle,
	std::shared_ptr<Rectangle> rPaddle,
	std::shared_ptr<Ball> ball,
	float dt) {

	TTF_SetFontSize(font, 24);
	SDL_Surface* playButtonSurface = TTF_RenderText_Blended(font, "PLAY", sizeof(char) * 4, { 0, 0, 0, 255 });
	SDL_Texture* playButtonTexture = SDL_CreateTextureFromSurface(state.renderer, playButtonSurface);

	int buttonWidth = 200;
	int buttonHeight = 100;

	float textWidth, textHeight;
	SDL_GetTextureSize(playButtonTexture, &textWidth, &textHeight);


	SDL_FRect playbuttonRect = { (width - buttonWidth) / 2, (height - buttonHeight) / 2, buttonWidth, buttonHeight };
	SDL_FRect playbuttonTextRect = { (width - textWidth) / 2, (height - textHeight) / 2 + buttonHeight, textWidth, textHeight };
	SDL_Color buttonColor = { 255, 255, 255, 255 };

	auto playButton = std::make_unique<Button>(playbuttonRect, state.renderer, buttonColor, playButtonTexture, playbuttonTextRect);
	SDL_SetRenderDrawColor(state.renderer, 0, 0, 0, 255); 
	SDL_RenderClear(state.renderer);
	playButton->draw(state, playButton->rect, playButton->color);
	playButton->Hovered();
	SDL_RenderPresent(state.renderer);
}