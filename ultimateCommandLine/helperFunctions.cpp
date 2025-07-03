/* Change Log helperFunctions.cpp */
/* JR - 06 / 29 / 2025 - Added listDirInPath function */

#include "helperFunctions.h"

std::unordered_map <std::string, int> COMMANDMAPPING = {
	{"ls", 1},
	{"cd", 2},
    {"rm", 3},
    {"rmdir", 4},
    {"pwd", 5},
	{"quit", 99}
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

std::vector<std::filesystem::path> listDirInPath(const std::string& path) {

    std::vector<std::filesystem::path> directories;
    std::filesystem::path directorypath = path;

    // To check if the directory exists or not
    if (std::filesystem::exists(directorypath)
        && std::filesystem::is_directory(directorypath)) {

        // Loop through each item (file or subdirectory) in the directory

        for (const auto& entry :
            std::filesystem::directory_iterator(directorypath)) {

            // Store the path of the file or subdirectory to vector
            directories.push_back(entry.path());
        }

        return directories;

    }

    else {
        // Handle the case where the directory doesn't exist
        std::cerr << "Directory not found." << std::endl;
    }

}
