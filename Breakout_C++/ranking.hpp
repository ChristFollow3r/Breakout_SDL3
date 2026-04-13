#pragma once
#include "scene.hpp"
#include "button.hpp"
#include "saving.hpp"
#include "algorithm"

class RankingScene : public Scene {

    SDLState& state;
    TTF_Font* font;
    std::unique_ptr<Button> backButton;

    void DisplayRanking(TTF_Font* font);
    std::vector<std::pair<std::string, int>> SortRanking();
    std::vector<std::pair<std::string, int>> GetBinaryInfo();


public:

    GameState request = RANKING;
    RankingScene(SDLState& state, TTF_Font* font);
    void HandleEvent(const SDL_Event& event) override;
    void Update(float dt) override;
    void Render() override;
};