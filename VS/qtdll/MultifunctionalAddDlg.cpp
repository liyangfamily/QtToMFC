#include "MultifunctionalAddDlg.h"
#include <QtGlobal>
#include <QRegExpValidator>
#include <QMessageBox>
#include "UTF8Define.h"

MultifunctionalAddDlg::MultifunctionalAddDlg(const OptMode& mode, QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	m_mode = mode;
	initDlgUIByOptMode(m_mode);
}

MultifunctionalAddDlg::~MultifunctionalAddDlg()
{
}

 void MultifunctionalAddDlg::setCallBack(FileOptCallBack cb1)
 {
     m_cb1=cb1;
	 //m_cb = (void*)cb1.;
 }

void MultifunctionalAddDlg::on_pushButton_Cancel_clicked()
{
	this->reject();
}

void MultifunctionalAddDlg::on_pushButton_Confirm_clicked()
{
	if (!updateDataByOptMode(m_mode))
	{
		QMessageBox box(QMessageBox::Warning, "警告", "ICConfiguration icName or icRegCount or icEveryRegByteCount is illegal.");
		box.setStandardButtons(QMessageBox::Yes | QMessageBox::Yes);
		box.setButtonText(QMessageBox::Yes, "确定");
		box.exec();
		return;
	}
    QString path=ui.lineEdit_ICName->text();
    std::string str=path.toLocal8Bit().data();
	if (m_cb1)
	{
		m_cb1(str);
	}
	this->accept();
}

bool MultifunctionalAddDlg::initDlgUIByOptMode(const OptMode& mode)
{
	switch (mode)
	{
	case MultifunctionalAddDlg::EOM_AddIC:
	{
		this->setWindowTitle("添加芯片");
		this->setVisible(true);
		QRegExp regx("[1-9][0-9]+$");
		ui.lineEdit_ICEveryRegByteCount->setValidator(new QRegExpValidator(regx, this));
		ui.lineEdit_ICRegCount->setValidator(new QRegExpValidator(regx, this));
		ui.lineEdit_ICColorCount->setValidator(new QRegExpValidator(regx, this));
	}
	break;
	default:
		break;
	}
	return true;
}

bool MultifunctionalAddDlg::updateDataByOptMode(const OptMode& mode)
{
    return true;
}
