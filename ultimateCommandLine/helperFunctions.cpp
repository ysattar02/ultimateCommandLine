/* Change Log helperFunctions.cpp */
/* YS - 06 / 28 / 2025 - Initial Creation */

#include "helperFunctions.h"

std::unordered_map <std::string, int> COMMANDMAPPING = {
	{"ls", 1},
	{"cd", 2}
};

void displayCurrentDirectory() {
	std::filesystem::path currentPath = std::filesystem::current_path();
	std::cout << currentPath << "> ";
	return;
}

int commandStringToEnum(const std::string &command) {
	auto it = COMMANDMAPPING.find(command);
	if (it != COMMANDMAPPING.end()) {
		return it->second;
	}
	else {
		return 100;
	}
}