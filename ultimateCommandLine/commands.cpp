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
	if (!target.is_absolute()) { 
		target = GLOBALS::workingDir.string() + target.string();
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
			std::cin.clear();
			std::cin.ignore();
			return;
		}
		else {
			std::cin.clear();
			std::cin.ignore();
			return;
		}
	}

	return;
}

void touchFile(std::vector <std::string>& fullCmd) {

	//base case
	if (fullCmd.size() > 2) {
		return;
	}

	//filepath to file to touch
	std::filesystem::path target = fullCmd[1];

	//resolve path to absolute
	if (!target.is_absolute()) {
		target = GLOBALS::workingDir.string() + target.string();
	}

	//make sure file doesn't exist
	bool flag = std::filesystem::exists(target);
	if (flag) {
		std::cerr << "File Already Exists" << std::endl;
		return;
	}

	//make the file
	std::ofstream myFile(target);
	myFile.close();

	return;
}

void makeDirectory(std::vector <std::string>& fullCmd) {

	//base case 
	if (fullCmd.size() > 2) {
		return;
	}

	//filepath to directory to make
	std::filesystem::path target = fullCmd[1];

	//resolve path to absolute
	if (!target.is_absolute()) {
		target = GLOBALS::workingDir.string() + target.string();
	}

	//make sure directory doesn't exist
	bool flag = std::filesystem::exists(target);
	if (flag) {
		std::cerr << "Directory Already Exists" << std::endl;
		return;
	}

	//make the directory
	bool wasDirectoryMade = std::filesystem::create_directory(target);
	if (!wasDirectoryMade) {
		std::cerr << "Directory Creation Failed" << std::endl;
		return;
	}

	return;
}

void printWorkingDir(void) {

	std::cout << GLOBALS::get_workingDir().string() << std::endl;
}

void makeDir(std::vector<std::string>& fullCmd) {

	std::filesystem::path path;

	if (!fullCmd[1].find("\\")) {
		path = GLOBALS::get_workingDir();
		path += "\\" + fullCmd[1];
	}
	else {
		path = fullCmd[1];
	}

	try {
		if (std::filesystem::create_directory(path)) {
			std::cout << "Directory created successfully at: " << path << std::endl;
		}
		else {
			std::cout << "Directory already exists or could not be created at: " << path << std::endl;
		}
	}
	catch (const std::filesystem::filesystem_error& e) {
		std::cerr << "Error creating directory: " << e.what() << std::endl;
	}

	return;
}

void displaySystemSpecs() {

#ifdef _WIN32
	// Windows API struct to contain spec info
	SYSTEM_INFO siSysInfo;
	GetSystemInfo(&siSysInfo);

	std::string processorName = "";
	if (siSysInfo.wProcessorArchitecture == 9) {
		processorName = "x64 (AMD || Intel)";
	}
	else if (siSysInfo.wProcessorArchitecture == 5) {
		processorName = "ARM";
	}
	else if (siSysInfo.wProcessorArchitecture == 12) {
		processorName = "ARM64";
	}
	else if (siSysInfo.wProcessorArchitecture == 6) {
		processorName = "Intel Itanium-Based";
	}
	else if (siSysInfo.wProcessorArchitecture == 0) {
		processorName = "x86";
	}
	else {
		processorName = "Unknown Architecture";
	}

	// Calculate total ram installed on the system
	ULONGLONG totalKilobytes = 0;
	GetPhysicallyInstalledSystemMemory(&totalKilobytes);

	// Calculate information about the cache
	DWORD len = 0;

	// This call is to get the size of the buffer using nullptr to ensure failure
	PSYSTEM_LOGICAL_PROCESSOR_INFORMATION logicalProcessorInfo = nullptr;
	GetLogicalProcessorInformation(logicalProcessorInfo, &len);

	// Now malloc the struct with the acquired size
	logicalProcessorInfo = (PSYSTEM_LOGICAL_PROCESSOR_INFORMATION)malloc(len);

	// Make the call again to get the real data
	GetLogicalProcessorInformation(logicalProcessorInfo, &len);

	// Display to the screen
	std::cout << "Processor Architecture: " << processorName << std::endl;
	std::cout << "Page Size: " << siSysInfo.dwPageSize << std::endl;
	std::cout << "Physically Installed Memory (gb): " << totalKilobytes / 1024 / 1024 << std::endl;

	// Calculate number of entries in logicalProcessorInfo struct
	DWORD entryCount = len / sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION);

	// Display logical processor info
	std::cout << std::endl << "Logical Processor Information:" << std::endl;
	
	size_t currEntryCount = 1;
	for (DWORD i = 0; i < entryCount; i++) {

		// Assign the data to a temp container
		PSYSTEM_LOGICAL_PROCESSOR_INFORMATION currInfo = &logicalProcessorInfo[i];

		// Go through the struct using a case statement
		std::string flag = "";
		switch (currInfo->Relationship) {
			case RelationProcessorCore:
				std::cout << "=== Entry #" << currEntryCount << " ===" << std::endl;
				currEntryCount++;
				std::cout << "Relation: Processor Core: " << std::endl;
				(currInfo->ProcessorCore.Flags & 1) ? flag = "Hyperthreading Enabled" : flag = "Hyperthreading Disabled";
				std::cout << "Flag: " << flag << std::endl;
				break;
			case RelationNumaNode:
				std::cout << "Relation: Numa Node" << std::endl;
				std::cout << "Numa Node Number: " << currInfo->NumaNode.NodeNumber << std::endl;
				break;
			case RelationCache:
				std::cout << "Relation: Cache" << std::endl;

				if (currInfo->Cache.Level == 1) {
					std::cout << "Cache Level: " << "L1" << std::endl;
				}
				else if (currInfo->Cache.Level == 2) {
					std::cout << "Cache Level: " << "L2" << std::endl;
				}
				else if (currInfo->Cache.Level == 3) {
					std::cout << "Cache Level: " << "L3" << std::endl;
				}
				else {
					std::cout << "Cache Level: " << "Unknown" << std::endl;
				}

				if (currInfo->Cache.Type == 0) {
					std::cout << "Cache Type: " << "CacheUnified" << std::endl;
				}
				else if (currInfo->Cache.Type == 1) {
					std::cout << "Cache Type: " << "CacheInstruction" << std::endl;
				}
				else if (currInfo->Cache.Type == 2) {
					std::cout << "Cache Type: " << "CacheTrace" << std::endl;
				}
				else {
					std::cout << "Cache Type: " << "CacheUnknown" << std::endl;
				}

				std::cout << "Cache Size (kb): " << currInfo->Cache.Size / 1024 << std::endl;
				break;
			case RelationProcessorPackage:
				std::cout << "Relation: Processor Package" << std::endl;
				break;
			case RelationGroup:
				std::cout << "Relation: Group" << std::endl;
				break;
			default:
				std::cout << "Relation: Unknown" << std::endl;
				break;
		}
		std::cout << std::endl;
	}

	// Free the mallocd memory
	free(logicalProcessorInfo);
	logicalProcessorInfo = nullptr;
#endif //_WIN32

#ifndef _WIN32
	std::cout << "Feature Only Available on WIN32" << std::endl;
#endif //_WIN32

	return;
}

void getIP() {
	return;
}
