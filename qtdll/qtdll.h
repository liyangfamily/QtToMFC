#pragma once

#include "qtdll_global.h"

#include <windows.h>

#include <string>
#include <functional>
namespace qtm
{
	extern "C" BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID /*lpvReserved*/);

	extern "C" QTDLL_EXPORT void showDialog(HWND parent);
	extern "C" QTDLL_EXPORT void destroyDialog();
	extern "C" QTDLL_EXPORT void hideAppDialog();
	extern "C" QTDLL_EXPORT void moveAppDialog(int x, int y);
	extern "C" QTDLL_EXPORT void setDialogGeometry(int x, int y, int w, int h);

	extern "C" QTDLL_EXPORT bool registerWriteFun(std::function<void(std::string)> cb);
	extern "C" QTDLL_EXPORT bool registerReadFun(std::function<void(std::string)> cb);

	extern "C" QTDLL_EXPORT bool registerWriteDataFun(std::function<void(const char *str, int len)> cb);
	extern "C" QTDLL_EXPORT bool registerReadDataFun(std::function<void(char *str, int len)> cb);
}