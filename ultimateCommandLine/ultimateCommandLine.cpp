/* Change Log ultimateCommandLine.cpp */
/* YS - 06 / 28 / 2025 - Added Change Log */
/* JR - 06 / 28 / 2025 - Began Main */

#include "helperFunctions.h"
#include "globals.h"
#include "commands.h"

using namespace GLOBALS;

enum COMMANDS {
    LS = 1,
    CD = 2,
    RM = 3,
    RMDIR = 4,
    PWD = 5,
    QUIT = 99,
    UNKNOWN = 100
};

void initCommandLine() {
    
    //set current path to the working path
    std::filesystem::path currentPath = std::filesystem::current_path();
    GLOBALS::set_workingDir(currentPath.generic_string());

    //set running flag
    GLOBALS::isCommandLineActive = true;
}

int main() {

    initCommandLine();

    while (isCommandLineActive) {

        //display current directory
        std::string currWorkingDir = GLOBALS::get_workingDir();
        std::cout << currWorkingDir << "> ";
        
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

        //container to hold switch case
        int cmdNum;

        //do an empty check
        if (parsedInput.size() == 0) {
            cmdNum = UNKNOWN;
        }
        else {
            //decide the action to take
            cmdNum = commandStringToEnum(parsedInput[0]);
        }

        //do processing on command
        switch (cmdNum) {
            case LS:
                listFiles(parsedInput);
                break;
            case CD:
                changeDirectory(parsedInput);
                break;
            case RM:
                removeFile(parsedInput);
                break;
            case RMDIR:
                removeDirectory(parsedInput);
            case PWD:
                printWorkingDir();
                break;
            case UNKNOWN:
                std::cerr << "Command Not Recognized" << std::endl;
                break;
            case QUIT:
                std::cout << "Command Line Terminating" << std::endl;
                isCommandLineActive = false;
                break;
            default:
                std::cerr << "Command Not Recognized" << std::endl;
                break;
        }
    }

    return 0;
}

