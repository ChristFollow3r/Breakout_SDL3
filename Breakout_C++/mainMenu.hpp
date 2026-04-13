#pragma once
#include "scene.hpp"
#include "gameState.hpp"
#include "button.hpp"
#include <memory>


class MainMenu : public Scene {

	SDLState& state;
	TTF_Font* font;

	std::unique_ptr<Button> playButton;
	std::unique_ptr<Button> rankingButton;
	std::unique_ptr<Button> creditsButton;
	std::unique_ptr<Button> exitButton;

public:

	MainMenu(SDLState& state, TTF_Font* font);
	GameState gameState = MENU;

	void HandleEvent(const SDL_Event& event) override;
	void Update(float dt) override;
	void Render() override;

};