#pragma once
#include "scene.hpp"
#include "utils.hpp"
#include "saving.hpp"
#include "gameState.hpp"
#include <string>

class NameInput : public Scene {

    SDLState& state;
    TTF_Font* font;
    std::string playerName = "";
    int points;

public:

    GameState gameState = NAME_INPUT;

    NameInput(SDLState& state, TTF_Font* font, int points);
    void HandleEvent(const SDL_Event& event) override;
    void Update(float dt) override;
    void Render() override;

};