#pragma once

#include <filesystem>
#include <iostream>
#include <string>
#include <unordered_map>


/*************************************************************
	Function Name - displayCurrentDirectory()
	@brief Print the Current Directory to Console
	@param N/A
*************************************************************/
void displayCurrentDirectory(const std::string& fullCommand);

/*************************************************************
	Function Name - commandStringToEnum(std::string command)
	@brief Convert the Current Command to an Enum Value
	@param std::string - Command to translate to Enum
*************************************************************/
int commandStringToEnum(const std::string& fullCommand);

/*************************************************************
	Function Name - listDirInPath(const std::string& path)
	@brief Return the list of directories in the specified path
	@param std::string - Path to list directories from 
*************************************************************/
std::vector<std::filesystem::path> listDirInPath(const std::filesystem::path& path);