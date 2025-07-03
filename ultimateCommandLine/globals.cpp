#include "globals.h"



void GLOBALS::set_isCommandLineActive(bool flag) {
	isCommandLineActive = flag;
}

bool GLOBALS::get_isCommandLineActive() {
	return isCommandLineActive;
}

void GLOBALS::set_workingDir(std::filesystem::path filePath) {
	workingDir = filePath;
}

std::filesystem::path GLOBALS::get_workingDir() {
	return workingDir;
}