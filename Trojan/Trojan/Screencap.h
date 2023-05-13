#pragma once
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <Windows.h>
#include <gdiplus.h>
#pragma comment( lib, "gdiplus" )
#pragma comment(lib, "winmm.lib")
int GetEncoderClsid(const WCHAR* format, CLSID* pClsid);
void CaptureScreenToFile(const wchar_t* filePath, const wchar_t* format);