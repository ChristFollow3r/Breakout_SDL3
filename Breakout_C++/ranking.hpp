// rankingScene.hpp
#pragma once
#include "scene.hpp"
#include "utils.hpp"
#include "button.hpp"
#include "saving.hpp"

class RankingScene : public Scene {

    SDLState& state;
    TTF_Font* font;
    std::unique_ptr<Button> backButton;

public:

    GameState request = RANKING;
    RankingScene(SDLState& state, TTF_Font* font);
    void HandleEvent(const SDL_Event& event) override;
    void Update(float dt) override;
    void Render() override;
};