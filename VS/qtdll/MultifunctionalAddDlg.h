#pragma once

#include <QDialog>
#include "ui_MultifunctionalAddDlg.h"

typedef std::function<void(std::string)> FileOptCallBack;
class MultifunctionalAddDlg : public QDialog
{
	Q_OBJECT

public:
	enum OptMode
	{
		EOM_AddIC,
	};

public:
	MultifunctionalAddDlg(const OptMode& mode, QWidget *parent = Q_NULLPTR);
	~MultifunctionalAddDlg();
public:
    void setCallBack(FileOptCallBack cb1);
public slots:
	void on_pushButton_Cancel_clicked();
	void on_pushButton_Confirm_clicked();

private:
	bool initDlgUIByOptMode(const OptMode&);
	bool updateDataByOptMode(const OptMode&);
private:
	Ui::MultifunctionalAddDlg ui;
    OptMode m_mode = EOM_AddIC;
    void *m_cb;
    FileOptCallBack m_cb1;
};
