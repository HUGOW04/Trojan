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
	std::cout << "0.0.1 ";
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
		<< "|4 | [ls]           - list files and dirs              |\n"
		<< "|5 | [rm]           - delete file                      |\n"
		<< "|6 | [rmdir]        - delete directory                 |\n"
		<< "|7 | [info]         - information (os, cpu, gpu, etc)  |\n"
		<< "|8 | [ps]           - process info                     |\n"
		<< "|9 | [kill]         - kill process                     |\n"
		<< "|10| [keydump]      - dump logs of keylogger           |\n"
		<< "|11| [cryptfile]    - encrypt file      with using XOR |\n"
		<< "|12| [cryptdir]     - encrypt directory with using XOR |\n"
		<< "|13| [download]     - download file                    |\n"
		<< "|14| [shutdown]     - shuting down                     |\n"
		<< "|15| [error]        - print error (english only)       |\n"
		<< "|16| [screencap]    - screenshot the victim's computer |\n"
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

