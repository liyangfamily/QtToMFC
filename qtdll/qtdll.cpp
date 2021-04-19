#include "qtdll.h"
#include "qmfcapp.h"
#include "qwinwidget.h"
#include "QExApp.h"

#include <QMessageBox>
namespace qtm
{
	BOOL __stdcall DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID)
	{
		static bool ownApplication = FALSE;

		if (dwReason == DLL_PROCESS_ATTACH)
			ownApplication = QMfcApp::pluginInstance(hInstance);
		if (dwReason == DLL_PROCESS_DETACH && ownApplication)
		{
			delete qApp;
		}
		return TRUE;
	}
	QWinWidget *win = nullptr;
	void showDialog(HWND parent)
	{
		//win=new QWinWidget(parent);
		//win->setStyleSheet("background-color:red;");//Qt´°¿Ú±³¾°É« 
		//win->move(0, 0);
		//win->setGeometry(0, 0, 100, 100);
		//win->show();
		QExApp *app = QExApp::attachInstance(parent);
		if (app)
		{
			app->showApp();
		}
		return;
	}

	void destroyDialog()
	{
		QExApp::detachInstance();
		if (win)
		{
			delete win;
		}
		return;
	}

	void hideAppDialog()
	{
		QExApp *app = QExApp::attachInstance();
		if (app)
		{
			app->hideApp();
		}
		return ;
	}

	void moveAppDialog(int x, int y)
	{
		QExApp *app = QExApp::attachInstance();
		if (app)
		{
			app->moveApp(x, y);
		}
		return;
	}

	void setDialogGeometry(int x, int y, int w, int h)
	{
		QExApp *app = QExApp::attachInstance();
		if (app)
		{
			app->setGeometryApp(x, y, w, h);
		}
		return;
	}

	bool registerWriteFun(std::function<void(std::string)> cb)
	{
		QExApp *app = QExApp::attachInstance();
		if (app)
		{
			app->registerWriteFun(cb);
		}
		return true;
	}

	bool registerReadFun(std::function<void(std::string)> cb)
	{
		QExApp *app = QExApp::attachInstance();
		if (app)
		{
			app->registerReadFun(cb);
		}
		return true;
	}
	bool registerWriteDataFun(std::function<void(const char*str, int len)> cb)
	{
		QExApp *app = QExApp::attachInstance();
		if (app)
		{
			app->registerWriteDataFun(cb);
		}
		return true;
	}
	bool registerReadDataFun(std::function<void(char*str, int len)> cb)
	{
		QExApp *app = QExApp::attachInstance();
		if (app)
		{
			app->registerReadDataFun(cb);
		}
		return true;
	}
}