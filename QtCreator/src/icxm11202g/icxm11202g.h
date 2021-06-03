#ifndef ICXM11202G_H
#define ICXM11202G_H
#pragma once

#include "icxm11202g_global.h"

#if defined(Q_OS_WIN)
#include <windows.h>

#include <string>
#include <functional>
namespace qtm
{
    extern "C" BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID /*lpvReserved*/);

    extern "C" ICXM11202G_EXPORT void showDialog();
    extern "C" ICXM11202G_EXPORT void destroyDialog();
    extern "C" ICXM11202G_EXPORT void hideAppDialog();
    /*extern "C" ICXM11202G_EXPORT void moveAppDialog(int x, int y);
    extern "C" ICXM11202G_EXPORT void setDialogGeometry(int x, int y, int w, int h);*/

    extern "C" ICXM11202G_EXPORT bool registerWriteFun(std::function<void(std::string)> cb);
    extern "C" ICXM11202G_EXPORT bool registerReadFun(std::function<void(std::string)> cb);

    extern "C" ICXM11202G_EXPORT bool registerWriteDataFun(std::function<bool(const char *str, int len)> cb);
    extern "C" ICXM11202G_EXPORT bool registerReadDataFun(std::function<char *()> cb);

    extern "C" ICXM11202G_EXPORT bool writeGammaDataFun(std::function<bool(const char *str, int len)> cb);
    extern "C" ICXM11202G_EXPORT bool removalOfDeadPiexlsFun(std::function<void()> cb);
}
#endif // Q_OS_WIN
#endif // ICXM11202G_H
