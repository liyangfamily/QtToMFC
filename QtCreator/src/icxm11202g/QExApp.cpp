#include "QExApp.h"

#include "icxm11202gsetting.h"

#include <QDebug>

QExApp* QExApp::m_Instance = nullptr;
QMutex QExApp::m_mutex_protect;

QExApp::QExApp()
{
}


QExApp::~QExApp()
{
}

QExApp* QExApp::attachInstance()
{
	if (nullptr == m_Instance)
	{
		m_mutex_protect.lock();
		if (nullptr == m_Instance)
		{
			m_Instance = new ICXM11202GSetting();
		}
		m_mutex_protect.unlock();
	}
	return m_Instance;
}

bool QExApp::detachInstance()
{
	if (m_Instance)
	{
		delete m_Instance;
		m_Instance = nullptr;
	}
	return true;
}

//void QExApp::showApp()
//{
//	qDebug() << "QExApp::you need to implement showApp() into Subclass.";
//}
//
//void QExApp::hideApp()
//{
//	qDebug() << "QExApp::you need to implement hideApp() into Subclass.";
//}
//
//int QExApp::execApp()
//{
//	qDebug() << "QExApp::you need to implement execApp() into Subclass.";
//	return 0;
//}
