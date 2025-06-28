/* Change Log ultimateCommandLine.cpp */
/* YS - 06 / 28 / 2025 - Added Change Log */

#include <iostream>
#include <filesystem>
#include<string>
#include<sstream>
#include<vector>

int main() {

    while (true) {

        std::string input;
        std::filesystem::path currentPath = std::filesystem::current_path();

        std::cout << currentPath << "> ";
        std::cin >> input;

        std::stringstream ss(input);
        std::vector<std::string> parsedInput;
        std::string token;

        while (ss >> token) {
            parsedInput.push_back(token);
        }

        std::cout << "Hello World!\n";

    }


    std::cout << "Hello World!\n";
    return 0;
}

