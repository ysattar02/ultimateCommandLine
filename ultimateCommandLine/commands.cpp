/* Change Log helperFunctions.cpp */
/* YS - 06 / 29 / 2025 - Initial Creation */

#include "commands.h"
#include "globals.h"

using namespace GLOBALS;

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

	//check if only "cd" so base case or too many arguments
	if (fullCmd.size() != 2) {
		//only "cd or too many commands so exit early to save processing
		return;
	}
	else {
		if (!std::filesystem::exists(fullCmd[1]) || !std::filesystem::is_directory(fullCmd[1])) {
			//path doesn't exist or is not a directory
			return;
		}
		else {
			if (fullCmd[1] == "..") {
				// go back a directory and set to workingDir
				return;
			}
			else if (fullCmd[1] == ".") {
				// go back to parent directory
				return;
			}
			else {
				GLOBALS::set_workingDir(fullCmd[1]);
				return;
			}
		}
	}

	return;
}