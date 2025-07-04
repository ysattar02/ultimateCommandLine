#include "helperFunctions.h"

std::unordered_map <std::string, int> COMMANDMAPPING = {
	{"ls", 1},
	{"cd", 2},
    {"rm", 3},
    {"rmdir", 4},
    {"pwd", 5},
    {"touch", 6},
    {"mkdir", 7},
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

std::vector<std::filesystem::path> listDirInPath(const std::filesystem::path& path) {

    std::vector<std::filesystem::path> directories;

    // To check if the directory exists or not
    if (std::filesystem::exists(path)
        && std::filesystem::is_directory(path)) {

        // Loop through each item (file or subdirectory) in the directory

        for (const auto& entry :
            std::filesystem::directory_iterator(path)) {

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
