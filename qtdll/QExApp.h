#pragma once
#include <QMutex>

#include <windows.h>
#include <string>
#include <functional>

class QExApp
{
public:
	virtual ~QExApp();
	static QExApp* attachInstance(HWND hParentWnd);
	static QExApp* attachInstance();
	static bool detachInstance();

	virtual void showApp() = 0;
	virtual void hideApp() = 0;
	virtual int execApp() = 0;
	virtual void moveApp(int, int) = 0;
	virtual void setGeometryApp(int, int, int, int) = 0;


	inline bool registerWriteFun(std::function<void(std::string)> cb) {
		m_writeFun = cb;
		return true;
	}
	inline bool registerReadFun(std::function<void(std::string)> cb) {
		m_readFun = cb;
		return true;
	}

	inline bool registerWriteDataFun(std::function<void(const char *str, int len)> cb) {
		m_writeDataFun = cb;
		return true;
	}

	inline bool registerReadDataFun(std::function<void(char *str, int len)> cb) {
		m_readDataFun = cb;
		return true;
	}

protected:
	QExApp();
	QExApp(const QExApp&) = delete;
	QExApp& operator=(const QExApp&) = delete;

	static QMutex m_mutex_protect;
	static QExApp* m_Instance;

	std::function<void(std::string)> m_writeFun;
	std::function<void(std::string)> m_readFun;

	std::function<void(const char *str, int len)> m_writeDataFun;
	std::function<void(char *str, int len)> m_readDataFun;
};

