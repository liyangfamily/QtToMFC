#pragma once
#include <QMutex>

#include <windows.h>
#include <string>
#include <functional>

class QExApp
{
public:
	virtual ~QExApp();
	static QExApp* attachInstance();
	static bool detachInstance();

	virtual void showApp() = 0;
	virtual void hideApp() = 0;
	virtual int execApp() = 0;
	/*virtual void moveApp(int, int) = 0;
	virtual void setGeometryApp(int, int, int, int) = 0;*/


	inline bool registerWriteFun(std::function<void(std::string)> cb) {
		m_writeFun = cb;
		return true;
	}
	inline bool registerReadFun(std::function<void(std::string)> cb) {
		m_readFun = cb;
		return true;
	}

	inline bool registerWriteDataFun(std::function<bool(const char *str, int len)> cb) {
		m_writeDataFun = cb;
		return true;
	}

	inline bool registerReadDataFun(std::function<char *()> cb) {
		m_readDataFun = cb;
		return true;
	}

	inline bool writeGammaDataFun(std::function<bool(const char *str, int len)> cb) {
		m_writeGammaDataFun = cb;
		return true;
	}

	inline bool removalOfDeadPiexlsFun(std::function<void()> cb) {
		m_removalOfDeadPiexlsFun = cb;
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

	std::function<bool(const char *str, int len)> m_writeDataFun;
	std::function<char *()> m_readDataFun;

	std::function<bool(const char *str, int len)> m_writeGammaDataFun;	//发送Gamma
	std::function<void()> m_removalOfDeadPiexlsFun;	//发送去坏点

};

