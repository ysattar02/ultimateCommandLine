/* Change Log helperFunctions.h */
/* YS - 06 / 29 / 2025 - Initial Creation */

#include "globals.h"



void GLOBALS::set_isCommandLineActive(bool flag) {
	isCommandLineActive = flag;
}

bool GLOBALS::get_isCommandLineActive() {
	return isCommandLineActive;
}

void GLOBALS::set_workingDir(std::string filePath) {
	workingDir = filePath;
}

std::string GLOBALS::get_workingDir() {
	return workingDir;
}