#pragma once

#ifndef BUILD_STATIC
# if defined(QTDLL_LIB)
#  define QTDLL_EXPORT __declspec(dllexport)
# else
#  define QTDLL_EXPORT __declspec(dllimport)
# endif
#else
# define QTDLL_EXPORT
#endif
