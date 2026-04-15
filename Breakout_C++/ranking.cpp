#include "ranking.hpp"

RankingScene::RankingScene(SDLState& state, TTF_Font* font) : state(state), font(font) {
    backButton = std::make_unique<Button>(font, state, "Back", width - 240, height - 140);
}

void RankingScene::HandleEvent(const SDL_Event& event) {
    if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN && event.button.button == SDL_BUTTON_LEFT)
        if (backButton->Clicked()) gameState = MENU;
}

void RankingScene::Update(float dt) {}

void RankingScene::Render() {
    SDL_SetRenderDrawColor(state.renderer, 10, 25, 45, 255);
    SDL_RenderClear(state.renderer);
    backButton->DrawButton(state);
    RankingScene::DisplayRanking(font);
    SDL_RenderPresent(state.renderer);
}

std::vector<std::pair<std::string, int>> RankingScene::SortRanking() {

    std::vector<std::pair<std::string, int>> sortedRankingContent = RankingScene::GetBinaryInfo();
    std::vector<std::pair<std::string, int>> top5;

    // AI gave me this lambda; if the first value of the std::pair was the int I wouldn't need the lambda. I would just need something for the descending order
    std::sort(sortedRankingContent.begin(), sortedRankingContent.end(), [](auto& a, auto& b) { return a.second > b.second; }); // I asked AI if sorting like that would sort by the int (the second) or by the strinig (the first)
    // and it said it would do it by the string and that I need a lambda to tell the sorting alogrythm how to sort the vector of pairs.
    // Theres also this function called std::greater whichs appears to do the same as im doing here but the documentation: https://en.cppreference.com/w/cpp/utility/functional/greater.html it's so ugly
    // that I won't bother to try and understand it

    for (int i = 0; i < sortedRankingContent.size(); i++)
    {
        if (i > 4) break;
        top5.push_back(sortedRankingContent[i]);
    }

    return top5;
}

std::vector<std::pair<std::string, int>> RankingScene::GetBinaryInfo() {

    std::vector<std::pair<std::string, int>> rankingContent;
    std::fstream file("ranking.bin", std::ios::in | std::ios::binary);
    if (!file.is_open()) SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "ERROR", "Failed to open binary", state.window);


    while (file.peek() != EOF) { // Claude is telling me that this loop was reading garbage values and that thats why the release was freaking out
        // I got a binary with 2 million bytes or something like that (only happening with the release though, not with the debugger...).
        int size;
        std::pair<std::string, int> temp;

        file.read(reinterpret_cast<char*>(&size), sizeof(int)); // Int string length
        temp.first.resize(size);
        file.read(&temp.first[0], size); // String
        file.read(reinterpret_cast<char*>(&temp.second), sizeof(int)); // Int score

        rankingContent.push_back(temp);
    }
    file.close();

    return rankingContent;


}

void RankingScene::DisplayRanking(TTF_Font* font) {

    std::vector<std::pair<std::string, int>> top5 = RankingScene::SortRanking();
    int gap = 150;

    for (auto x : top5) {

        std::string nameAndScore = x.first + ": " + std::to_string(x.second);
        drawText(state, font, nameAndScore, 32, (width / 2), gap, { 255, 255, 255, 255 });
        gap += 80;

    }

}