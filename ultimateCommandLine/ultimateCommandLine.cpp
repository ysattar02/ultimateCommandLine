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
    TOUCH = 6,
    MKDIR = 7,
    MK = 8,
    IP = 9,
    WHOAMI = 10,
    SYS_SPEC = 98,
    QUIT = 99,
    UNKNOWN = 100
};

void initCommandLine() {

    // Set log level (static so exists)
    SingletonLogger::getInstance()->setLoglevel(SingletonLogger::LOG_LEVEL::TRACE);

    //set current path to the working path
    std::filesystem::path currentPath = std::filesystem::current_path();
    GLOBALS::set_workingDir(currentPath);

    //set running flag
    GLOBALS::isCommandLineActive = true;
}

int main() {

    initCommandLine();

    while (isCommandLineActive) {

        //display current directory
        std::filesystem::path currWorkingDir = GLOBALS::get_workingDir();
        std::cout << currWorkingDir.string() << "> ";
        
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

        //container to hold switch case choice
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
                break;
            case PWD:
                printWorkingDir();
                break;
            case TOUCH:
                touchFile(parsedInput);
                break;
            case MKDIR:
                makeDirectory(parsedInput);
                break;
            case MK:
                makeDir(parsedInput);
                break;
            case IP:
                getIP();
                break;
            case WHOAMI:
                whoami(parsedInput);
                break;
            case SYS_SPEC:
                displaySystemSpecs();
                break;
            case UNKNOWN:
                LOG_WARNING("Command Not Recognized");
                break;
            case QUIT:
                LOG_WARNING("Command Line Terminating");
                isCommandLineActive = false;

                // Allow the user time to read the message
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                break;
            default:
                LOG_WARNING("Command Not Recognized");
                break;
        }
    }

    return 0;
}

