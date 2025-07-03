/* Change Log helperFunctions.cpp */
/* YS - 06 / 29 / 2025 - Initial Creation */

#include "commands.h"
#include "globals.h"

using namespace GLOBALS;

void listFiles(std::vector <std::string>& fullCmd) {

	std::filesystem::path path;

	if (fullCmd.size() < 2)
		path = GLOBALS::get_workingDir();
	else {
		for (int i = 1; i < fullCmd.size(); i++) {
			if (fullCmd[i][0] == '-') {
				continue;
			}
			else
				path += fullCmd[i] + "\\";

		}
	}

	std::vector<std::filesystem::path> directories = listDirInPath(path);

	for (int i = 0; i < directories.size(); i++) {
		std::cout << directories[i].filename().string() << std::endl;
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
			std::filesystem::path new_path;
			if (fullCmd[1] == "..") {
				// go back a directory and set to workingDir
				new_path = GLOBALS::get_workingDir().parent_path();
				GLOBALS::set_workingDir(new_path);
				return;
			}
			else if (fullCmd[1] == "~") {
				// go to home directory
				//new_path = GLOBALS::home_directory;
				//GLOBALS::set_workingDir(new_path);
				return;
			}
			else if (fullCmd[1] == "-") {
				// go back to previous directory
				return;
			}
			else if (fullCmd[1] == "/") {
				// go to root directory
				new_path = GLOBALS::get_workingDir().root_directory();
				GLOBALS::set_workingDir(new_path);
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

void removeFile(std::vector <std::string>& fullCmd) {

	//all rm commands need to be adjusuted to an absolute path
	std::filesystem::path target = fullCmd[1];

	//check if absolute and resolve if it isn't
	if (!target.is_absolute()) {
		target = std::filesystem::absolute(target);
	}
	
	//make sure it exists
	if (!std::filesystem::exists(target)) {
		std::cerr << "File Does Not Exist" << std::endl;
		return;
	}

	//conduct the remove operation
	bool flag = std::filesystem::remove(target);
	if (!flag) {
		std::cerr << "Remove Failed" << std::endl;
		return;
	}
	
	return;
}

void removeDirectory(std::vector <std::string>& fullCmd) {

	//filepath to directory to delete
	std::filesystem::path target = fullCmd[1];

	//check if absolute and resolve if it isn't
	std::string temp;
	if (!target.is_absolute()) { //this is the bug, absolute is taking the path to exe
		target = GLOBALS::workingDir.string() + target.string();
		//std::replace(temp.begin(), temp.end(), '/', '\\');
	}

	//make sure directory exists
	bool flag = std::filesystem::exists(target);
	if (!flag) {
		std::cerr << "Directory Does Not Exist" << std::endl;
		return;
	}

	//make sure it is a directory
	if (!std::filesystem::is_directory(target)) {
		std::cerr << "Target Is Not a Directory" << std::endl;
		return;
	}

	//make sure it is not the path we are currently on
	if (target == GLOBALS::workingDir) {
		std::cerr << "Directory In Use, Cannot Remove" << std::endl;
		return;
	}

	//check if the directory is empty
	if (std::filesystem::is_empty(target)) {
		std::filesystem::remove(target);
	}
	else {
		char decision;
		std::cout << target << "Is Not Empty, Would You Like To Remove? " << std::endl;
		std::cout << "Y = yes, N = no" << std::endl;
		std::cin >> decision;
		if (decision == 'Y' || decision == 'y') {
			std::filesystem::remove_all(target);
		}
		else {
			return;
		}
	}

	return;
}

void printWorkingDir(void) {

	std::cout << GLOBALS::get_workingDir().string() << std::endl;
}