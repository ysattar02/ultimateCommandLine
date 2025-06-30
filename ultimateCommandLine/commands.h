/* Change Log helperFunctions.h */
/* YS - 06 / 29 / 2025 - Initial Creation */

#pragma once

#include <filesystem>
#include <iostream>
#include <unordered_map>
#include <string>
#include "helperFunctions.h"


/*************************************************************
	Function Name - listFiles()
	@brief List all files in current directory
	@param Vector of std::string containing entire command word by word
*************************************************************/
void listFiles(std::vector <std::string> &fullCmd);

/*************************************************************
	Function Name - changeDirectory()
	@brief Changes current to specified directory
	@param Vector of std::string containing entire command word by word
*************************************************************/
void changeDirectory(std::vector <std::string>& fullCmd);