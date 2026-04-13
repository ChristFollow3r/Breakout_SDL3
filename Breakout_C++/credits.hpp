#pragma once
#include "scene.hpp"
#include "button.hpp"

class CreditsScene : public Scene {

	SDLState& state;
	TTF_Font* font;
	std::unique_ptr<Button> backButton;

public:

	GameState gameState = CREDITS;

	CreditsScene(SDLState& state, TTF_Font* font);
	void HandleEvent(const SDL_Event& event) override;
	void Update(float dt) override;
	void Render() override;

};