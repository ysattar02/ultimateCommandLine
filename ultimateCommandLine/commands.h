#pragma once

#include <filesystem>
#include <iostream>
#include <unordered_map>
#include <string>
#include "helperFunctions.h"
#include "globals.h"


/*************************************************************
	Function Name - listFiles()
	@brief List all files in current directory "ls"
	@param Vector of std::string containing entire command word by word
*************************************************************/
void listFiles(std::vector <std::string> &fullCmd);

/*************************************************************
	Function Name - changeDirectory()
	@brief Changes current to specified directory "cd"
	@param Vector of std::string containing entire command word by word
*************************************************************/
void changeDirectory(std::vector <std::string>& fullCmd);

/*************************************************************
	Function Name - removeFile()
	@brief Implements functionality of "rm"
	@param Vector of std::string containing entire command word by word
*************************************************************/
void removeFile(std::vector <std::string>& fullCmd);

/*************************************************************
	Function Name - removeDirectory()
	@brief Implements functionality of "rmdir"
	@param Vector of std::string containing entire command word by word
*************************************************************/
void removeDirectory(std::vector <std::string>& fullCmd);

/*************************************************************
	Function Name - makeDirectory()
	@brief Implements functionality of "mkdir"
	@param Vector of std::string containing entire command word by word
*************************************************************/
void makeDirectory(std::vector <std::string>& fullCmd);

/*************************************************************
	Function Name - printWorkingDir()
	@brief Prints the currrent working directory 
	@param none
*************************************************************/
void printWorkingDir(void);
