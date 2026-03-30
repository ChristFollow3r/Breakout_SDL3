	#include "saving.hpp"
	#include <algorithm>
	

	// This is bullshit

	void saveToBinary(std::string playerName, int points) {

		std::fstream file("ranking.bin", std::ios::out | std::ios::binary);
		int playerNameSize = playerName.size();
		file.write(reinterpret_cast<char*>(&playerNameSize), sizeof(int));
		file.write(playerName.c_str(), playerNameSize);
		file.write(reinterpret_cast<char*>(&points), sizeof(int));
		file.close();

	}

	std::vector<std::string> sortInventory() {

		std::vector<std::string> rankingContent;
		std::fstream file("ranking.bin", std::ios::in | std::ios::binary);

		std::string temp;
		int size;
	
		while (!file.eof()) {

			file.read(reinterpret_cast<char*>(&size), sizeof(int));
			file.read(reinterpret_cast<char*>(&temp), size);
			file.read(reinterpret_cast<char*>(&size), sizeof(int));
			static_cast<std::string>(temp);
			temp += " ";
			temp += std::to_string(size);
			rankingContent.push_back(temp);

		}





	}
