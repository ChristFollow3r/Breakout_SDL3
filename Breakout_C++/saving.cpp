#include "saving.hpp"
#include <algorithm>
#include <SDL3/SDL.h>

	

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



