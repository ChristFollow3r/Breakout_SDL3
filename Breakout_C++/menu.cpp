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

	std::string buttonText = "Play";
	SDL_Surface* playButtonSurface = TTF_RenderText_Blended(font, buttonText.c_str(), sizeof(char) * 4, {0, 0, 0, 255});
	SDL_Texture* playButtonTexture = SDL_CreateTextureFromSurface(state.renderer, playButtonSurface);

	buttonText = "Ranking";
	SDL_Surface* rankingButtonSurface = TTF_RenderText_Blended(font, buttonText.c_str(), sizeof(char) * 4, { 0, 0, 0, 255 });
	SDL_Texture* rankingButtonTexture = SDL_CreateTextureFromSurface(state.renderer, rankingButtonSurface);

	buttonText = "Exit";
	SDL_Surface* exitButtonSurface = TTF_RenderText_Blended(font, buttonText.c_str(), sizeof(char) * 4, { 0, 0, 0, 255 });
	SDL_Texture* exitButtonTexture = SDL_CreateTextureFromSurface(state.renderer, rankingButtonSurface);

	int buttonWidth = 200;
	int buttonHeight = 100;

	float playButtonTextWidth, playButtonTextHeight;
	SDL_GetTextureSize(playButtonTexture, &playButtonTextWidth, &playButtonTextHeight);


	SDL_FRect playbuttonRect = { (width - buttonWidth) / 2, (height - buttonHeight) / 2, buttonWidth, buttonHeight };
	SDL_FRect playbuttonTextRect = { (width - playButtonTextWidth) / 2, (height - playButtonTextHeight) / 2, playButtonTextWidth, playButtonTextHeight };
	SDL_Color buttonColor = { 255, 255, 255, 255 };

	auto playButton = std::make_unique<Button>(playbuttonRect, state.renderer, buttonColor, playButtonTexture, playbuttonTextRect);
	drawButton(state, playButton.get()); // Get is only for smart pointers. It returns a raw pointer without transfering ownership

}

void drawButton(SDLState state, Button* button) {

	SDL_SetRenderDrawColor(state.renderer, 0, 0, 0, 255); 
	SDL_RenderClear(state.renderer);
	button->draw(state, button->rect, button->color);
	button->AddText(state.renderer);
	button->Hovered();
	SDL_RenderPresent(state.renderer);
}