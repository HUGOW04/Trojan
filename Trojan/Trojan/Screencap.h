#pragma once
#include <windows.h>
#include <gdiplus.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#pragma comment( lib, "gdiplus" )
#pragma comment(lib, "winmm.lib")
int GetEncoderClsid(const WCHAR* format, CLSID* pClsid);
void CaptureScreenToFile(const WCHAR* imgpath, const WCHAR* format);