/* Change Log ultimateCommandLine.cpp */
/* YS - 06 / 28 / 2025 - Added Change Log */
/* JR - 06 / 28 / 2025 - Began Main */

#include "helperFunctions.h"

#include <iostream>
#include<string>
#include<sstream>
#include<vector>

enum COMMANDS {
    LS = 1,
    CD = 2,
    UNKNOWN = 100
};

int main() {

    while (true) {

        //display current directory
        displayCurrentDirectory();
        
        //grab the full line from console
        std::string input;
        std::getline(std::cin, input);

        //create an ss object to split into a vector
        std::stringstream ss(input);
        std::vector <std::string> parsedInput;

        //creating a token to store the words
        std::string token;
        while (ss >> token) {
            parsedInput.push_back(token);
        }
        
        //decide the action to take
        int cmdNum = commandStringToEnum(parsedInput[0]);
        switch (cmdNum) {
            case LS:
                //add function call here
                break;
            case CD:
                //add function call here
                break;
            case UNKNOWN:
                std::cerr << "Command Not Recognized" << std::endl;
                break;
            default:
                std::cerr << "Command Not Recognized" << std::endl;
                break;
        }
    }

    return 0;
}

