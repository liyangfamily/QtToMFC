#ifndef ICXM11202GSETTING_H
#define ICXM11202GSETTING_H

#include <QWidget>
#include "QExApp.h"

namespace Ui {
class ICXM11202GSetting;
}

class ICXM11202GSetting : public QWidget, public QExApp
{
    Q_OBJECT

public:
    explicit ICXM11202GSetting(QWidget *parent = nullptr);
    ~ICXM11202GSetting();

public:
	void showApp();
	void hideApp();
	int execApp();
    void SetRegValue(int Num, int value);
    unsigned char GetRegValue(int Num);
    QByteArray ReadFile(QString filepath);
    bool WriteFile(QString filepath,QByteArray array);
    void Writebin(QString path, QByteArray bytes);
    QByteArray Readbin(QString path);
    void Loadformpara();
    QByteArray ReadGamdat(QString filepath);
    //void MessageBoxShow(QString title,QString str);
	QString filename;
    void SetGlobalReg();
    void GetGlobalReg();






public:
    QByteArray regpara;



private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();
	void on_pushButton_6_clicked();
    void on_pushButton_7_clicked();

    void on_spinBox_valueChanged(int arg1);

    void on_spinBox_11_valueChanged(int arg1);

    void on_spinBox_13_valueChanged(int arg1);

    void on_spinBox_2_valueChanged(int arg1);

    void on_spinBox_10_valueChanged(int arg1);

    void on_spinBox_12_valueChanged(int arg1);

    void on_spinBox_3_valueChanged(int arg1);

    void on_spinBox_9_valueChanged(int arg1);

    void on_spinBox_14_valueChanged(int arg1);

    void on_spinBox_7_valueChanged(int arg1);

    void on_pushButton_9_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_10_clicked();

private:
    Ui::ICXM11202GSetting *ui;
};

#endif // ICXM11202GSETTING_H
