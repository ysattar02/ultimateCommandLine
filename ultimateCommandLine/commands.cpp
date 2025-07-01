/* Change Log helperFunctions.cpp */
/* YS - 06 / 29 / 2025 - Initial Creation */

#include "commands.h"

void listFiles(std::vector <std::string>& fullCmd) {

	std::string path = "";

	if (fullCmd.size() < 2)
		path = std::filesystem::current_path().string();
	else {
		for (int i = 1; i < fullCmd.size(); i++) {
			path += fullCmd[i];
		}
	}

	std::vector<std::string> directories = listDirInPath(path);

	for (int i = 0; i < directories.size(); i++) {
		std::cout << directories[i] << std::endl;
	}

	return;
}

void changeDirectory(std::vector <std::string>& fullCmd) {
	return;
}