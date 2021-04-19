#pragma once

#include <QtWidgets/QWidget>
#include <QStandardItem>
#include <QSharedPointer>
#include "ui_ICEditor.h"
#include "framelesswindow.h"
#include "qwinwidget.h"
#include "QExApp.h"

class ICEditor : public QWinWidget, public QExApp
{
	Q_OBJECT

public:
	ICEditor(HWND hParentWnd, QObject *parent = 0, Qt::WindowFlags f = 0);
	~ICEditor();
public:
	void showApp();
	void hideApp(); 
	int execApp(); 
	void moveApp(int, int);
	void setGeometryApp(int, int, int, int);
public slots:
	void on_pushButton_NewIC_clicked();
	void on_pushButton_NewAttribute_clicked();
	void on_pushButton_Export_clicked();
	void on_pushButton_Import_clicked();
	void on_pushButton_NewOptions_clicked();
	void on_pushButton_NewBitInfo_clicked();
	void on_pushButton_MinSize_clicked();
	void on_pushButton_MaxSize_clicked();
	void on_pushButton_Close_clicked();
	void slotTreeCustomContextMenuRequested(const QPoint &pos);
	void slotItemClicked(QTreeWidgetItem *item, int column);
	void slotItemDelete();
protected:
	void enterEvent(QEvent *e);                      //进入QWidget瞬间事件

private:
	void initFramelessWindow();
	void initTreeTableWidget();
	void initMenu();

private:
	Ui::ICEditorClass ui;

	bool m_bPressed;//鼠标按下标志（不分左右键）  
	QPoint m_ptPress;

	QTreeWidget* m_pTree = nullptr;
};
