#include "ICEditor.h"
#include <QtGlobal>
#include <QHeaderView>
#include <QMouseEvent>
#include <QDir>
#include <QMenu>
#include <QMessageBox>

#include "ICEditorDefine.h"
#include "UTF8Define.h"
#include "MultifunctionalAddDlg.h"

ICEditor::ICEditor(HWND hParentWnd, QObject *parent, Qt::WindowFlags f)
    : QWinWidget(hParentWnd,parent,f)
{
	ui.setupUi(this);

    initFramelessWindow();
}

void ICEditor::on_pushButton_NewIC_clicked()
{
    MultifunctionalAddDlg adddlg(MultifunctionalAddDlg::EOM_AddIC);
	adddlg.setCallBack(m_writeFun);
    if (QDialog::Rejected == adddlg.exec())
    {
        return;
    }
}

ICEditor::~ICEditor()
{
	int i = 0;
}

void ICEditor::showApp()
{
	this->show();
}

void ICEditor::hideApp()
{
	this->hide();
}

int ICEditor::execApp()
{
	return 0;
}

void ICEditor::moveApp(int x, int y)
{
	this->move(x, y);
}

void ICEditor::setGeometryApp(int x, int y, int w, int h)
{
	this->setGeometry(x, y, w, h);
}

void ICEditor::on_pushButton_NewAttribute_clicked()
{
	int i = 1024;
	QByteArray data;
	std::shared_ptr<char[]> readData(new char[i]());
// 	data.resize(i);
// 	data.clear();
	if (m_readDataFun)
		m_readDataFun(readData.get(), i);
	data.append(readData.get(), i);
	int size = data.size();
	if (m_writeDataFun)
		m_writeDataFun(data.constData(), size);
	int ii = 0;

}

void ICEditor::on_pushButton_Export_clicked()
{

}

void ICEditor::on_pushButton_Import_clicked()
{

}

void ICEditor::on_pushButton_NewOptions_clicked()
{

}

void ICEditor::on_pushButton_NewBitInfo_clicked()
{

}

void ICEditor::enterEvent(QEvent *e)
{
	int i = 0;
	QWidget::enterEvent(e);
}

void ICEditor::initFramelessWindow()
{

   /* this->setWindowFlags(Qt::Window);
    this->setWindowModality(Qt::ApplicationModal);*/

    //this->setAttribute(Qt::WA_StyledBackground, true);
	//this->setAttribute(Qt::WA_TranslucentBackground);//透明不能放在此处，要放在子类中实现

	/*FramelessWindowsManager::addWindow(this);
	FramelessWindowsManager::addIgnoreObject(this, ui.label_Icon);
	FramelessWindowsManager::addIgnoreObject(this, ui.pushButton_MinSize);
	FramelessWindowsManager::addIgnoreObject(this, ui.pushButton_MaxSize);
	FramelessWindowsManager::addIgnoreObject(this, ui.pushButton_Close);*/

    setTitleBar(ui.frame_2);
//    addIgnoreWidget(ui.label_Icon);
//    addIgnoreWidget(ui.pushButton_MinSize);
//    addIgnoreWidget(ui.pushButton_MaxSize);
//    addIgnoreWidget(ui.pushButton_Close);
	//setResizeableAreaWidth(7);
	this->setMouseTracking(true);
}

void ICEditor::initTreeTableWidget()
{

}

void ICEditor::initMenu()
{

}

void ICEditor::on_pushButton_MinSize_clicked()
{
	this->showMinimized();
}

void ICEditor::on_pushButton_MaxSize_clicked()
{
	if (this->isMaximized()) {
		this->showNormal();
	}
	else
		this->showMaximized();
}

void ICEditor::on_pushButton_Close_clicked()
{
	this->close();
}

void ICEditor::slotTreeCustomContextMenuRequested(const QPoint &pos)
{

}

void ICEditor::slotItemClicked(QTreeWidgetItem *item, int column)
{
}

void ICEditor::slotItemDelete()
{

}
