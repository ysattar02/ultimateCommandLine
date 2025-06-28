/* Change Log helperFunctions.h */
/* YS - 06 / 28 / 2025 - Initial Creation */

#pragma once

#include <filesystem>
#include <iostream>
#include <unordered_map>



/*************************************************************
	Function Name - displayCurrentDirectory()
	@brief Print the Current Directory to Console
	@param N/A
*************************************************************/
void displayCurrentDirectory();

/*************************************************************
	Function Name - commandStringToEnum(std::string command)
	@brief Convert the Current Command to an Enum Value
	@param std::string - Command to translate to Enum
*************************************************************/
int commandStringToEnum(const std::string &command);