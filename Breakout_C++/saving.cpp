#include "saving.hpp"
#include <algorithm>
	

// This is bullshit

void saveToBinary(std::string playerName, int points, SDLState state) {
	
	std::fstream file("ranking.bin", std::ios::in | std::ios::binary);
	std::vector<std::pair<std::string, int>> rankingContent;

	while (file.peek() != EOF) { // Explanation of why I changed this below

		int size;
		std::pair<std::string, int> temp;

		file.read(reinterpret_cast<char*>(&size), sizeof(int)); // Int string length
		temp.first.resize(size);
		file.read(&temp.first[0], size); // String
		file.read(reinterpret_cast<char*>(&temp.second), sizeof(int)); // Int score

		rankingContent.push_back(temp);
	}
	file.close();
	

	file.open("ranking.bin", std::ios::out | std::ios::binary); // MARTI AIXÒ DEL RANKING ES TAN INNECESSARI!!! QUE TENEN A VEURE BINARIS AMB CLASSES???????????????????????????????????
	if (!file.is_open()) SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "ERROR", "Failed to open binary", state.window);

	int playerNameSize = playerName.size();
	file.write(reinterpret_cast<char*>(&playerNameSize), sizeof(int));
	file.write(playerName.c_str(), playerNameSize);
	file.write(reinterpret_cast<char*>(&points), sizeof(int));

	for (int i = 0; i < rankingContent.size(); i++)
	{
		int rankingNameSize = rankingContent[i].first.size();
		file.write(reinterpret_cast<char*>(&rankingNameSize), sizeof(int));
		file.write(rankingContent[i].first.c_str(), rankingNameSize);
		file.write(reinterpret_cast<char*>(&rankingContent[i].second), sizeof(int));
	}

	file.close();

}

std::vector<std::pair<std::string, int>> getBinaryInfo(SDLState state) {

	std::vector<std::pair<std::string, int>> rankingContent;
	std::fstream file("ranking.bin", std::ios::in | std::ios::binary);
	if (!file.is_open()) SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "ERROR", "Failed to open binary", state.window);

	
	while (file.peek() != EOF) { // Claude is telling me that this loop was reading garbage values and that thats why the release was freaking out
		// When saving the name I dont think thats it but at this point im willing to try anything
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

std::vector<std::pair<std::string, int>> sortRanking(SDLState state) {

	std::vector<std::pair<std::string, int>> sortedRankingContent = getBinaryInfo(state);
	std::vector<std::pair<std::string, int>> top5;

	std::sort(sortedRankingContent.begin(), sortedRankingContent.end(), [](auto& a, auto& b) { return a.second > b.second;}); // I asked AI if sorting like that would sort by the int (the second) or by the strinig (the first)
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


void displayRanking(SDLState state, TTF_Font* font) {

	std::vector<std::pair<std::string, int>> top5 = sortRanking(state);
	int gap = 150;

	for (auto x : top5) {

		std::string nameAndScore = x.first + ": " + std::to_string(x.second);
		drawText(state, font, nameAndScore, 32, (width / 2), gap, { 255, 255, 255, 255});
		gap += 80;

	}

}
