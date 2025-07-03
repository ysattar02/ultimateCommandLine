/* Change Log helperFunctions.cpp */
/* YS - 06 / 29 / 2025 - Initial Creation */

#include "commands.h"
#include "globals.h"

using namespace GLOBALS;

void listFiles(std::vector <std::string>& fullCmd) {

	std::string path = "";
	int flag = 0;

	if (fullCmd.size() < 2)
		path = GLOBALS::get_workingDir();
	else {
		for (int i = 1; i < fullCmd.size(); i++) {
			if (fullCmd[i][0] == '-') {
				if (fullCmd[i][1] == 'l') {
					flag = 1;
				}
				else if (fullCmd[i][1] == 'a') {
					flag = 2;
				}
				else if (fullCmd[i][1] == 'h') {
					flag = 3;
				}
				else if (fullCmd[i][1] == 't') {
					flag = 4;
				}
				else if (fullCmd[i][1] == 'r') {
					flag = 5;
				}
				else if (fullCmd[i][1] == 'R') {
					flag = 6;
				}
				else if (fullCmd[i][1] == 'S') {
					flag = 7;
				}
				else if (fullCmd[i][1] == '1') {
					flag = 8;
				}
				else if (fullCmd[i][1] == 'l') {
					flag = 9;
				}
				else if (fullCmd[i][1] == 'd') {
					flag = 10;
				}
				else if (fullCmd[i][1] == 'f') {
					flag = 11;
				}
				else {
					std::cout << "Command not recognized";
					return;
				}
			}
			else
				path += fullCmd[i];

		}
	}

	std::vector<std::filesystem::path> directories = listDirInPath(path);

	for (int i = 0; i < directories.size(); i++) {
		if (flag == 0)
			std::cout << directories[i].filename().string() << std::endl;
		else if (flag == 1) {

		}
		else if (flag == 2) {

		}
		else if (flag == 3) {

		}
		else if (flag == 4) {

		}
		else if (flag == 5) {

		}
		else if (flag == 6) {

		}
		else if (flag == 7) {

		}
		else if (flag == 8) {

		}
		else if (flag == 9) {

		}
		else if (flag == 10) {

		}
		else {

		}
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

void printWorkingDir(void) {
	
	std::cout << GLOBALS::get_workingDir() << std::endl;;

}