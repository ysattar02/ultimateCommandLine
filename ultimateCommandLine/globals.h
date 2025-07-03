#pragma once

#include <iostream>
#include <filesystem>
#include <atomic>
#include <string>
#include <sstream>
#include <vector>


namespace GLOBALS {

/*************************************************************
	Function Name - set_isCommandLineActive(bool flag)
	@brief Setter for the isCommandLineActive data member
	@param Bool to set isCommandLineActive to 
*************************************************************/
	void set_isCommandLineActive(bool flag);

/*************************************************************
	Function Name - get_isCommandLineActive()
	@brief Getter for the isCommandLineActive data member
	@param N/A
*************************************************************/
	bool get_isCommandLineActive();

/*************************************************************
	Function Name - set_workingDir(std::string filePath)
	@brief Setter for the workingDir data member
	@param Filepath to set the data member to
*************************************************************/
	void set_workingDir(std::filesystem::path filePath);

/*************************************************************
	Function Name - set_workingDir()
	@brief Getter for the workingDir data member
	@param N/A
*************************************************************/
	std::filesystem::path get_workingDir();

	// Data Members
	static std::atomic<bool> isCommandLineActive = true;
	static std::filesystem::path workingDir;
}