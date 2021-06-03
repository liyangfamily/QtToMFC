#include "icxm11202gsetting.h"
#include "ui_icxm11202gsetting.h"
#include <QFile>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>


ICXM11202GSetting::ICXM11202GSetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ICXM11202GSetting)
{
    ui->setupUi(this);



	filename = QCoreApplication::applicationDirPath();
    regpara = Readbin(filename + "/regpara.bin");

    Loadformpara();
}

ICXM11202GSetting::~ICXM11202GSetting()
{
    delete ui;
}

void ICXM11202GSetting::showApp()
{
	this->show();
}

void ICXM11202GSetting::hideApp()
{
	this->hide();
}

int ICXM11202GSetting::execApp()
{
	return 0;
}


/// <summary>
/// 设置对应寄存器的值
/// </summary>
void ICXM11202GSetting::SetRegValue(int Num, int value)
{
    regpara[Num * 6 + 5] = value;
}
unsigned char ICXM11202GSetting::GetRegValue(int Num)
{
    return regpara[Num * 6 + 5];
}

///读取txt文件
QByteArray ICXM11202GSetting::ReadFile(QString filepath)
{
    QFile file(filepath);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"Can't open the file!"<<endl;
    }

    QByteArray array;
    while(!file.atEnd())
    {
        QByteArray line = file.readLine();
        QString str(line);
        int count = str.split(' ').count();

        if (count >= 6 && str.split(' ')[0] != "")
        {
            for (int i = 0;i < 6;i++)
            {
                QString strTemp = str.right(str.length()-3*i).left(2);
                unsigned char tempByte = (unsigned char)(strTemp.toUInt(nullptr,16));
                //qDebug() << tempByte << "------------------";
                array.append(tempByte);

            }
        }

    }

    return array;
}


///写入txt文件
bool ICXM11202GSetting::WriteFile(QString filepath,QByteArray array)
{
    QFile file(filepath);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug()<<"Can't open the file!"<<endl;
    }
    file.write("//XM11202_default_initial_code\n\n");

    int i = 0;
    for (i=0;i<array.length()/6;i++)
    {
        QString str ;
        for (int j=0;j<6;j++)
        {

            str += QString::number(array[i * 6 + j] & 0xFF,16).toUpper().rightJustified(2,QChar('0')) + " ";
        }
        str += "\n";
        file.write(str.toUtf8());
    }


    return true;
}




void ICXM11202GSetting::Loadformpara()
{
    ui->spinBox->setValue(GetRegValue(14) >> 6);
    ui->spinBox_2->setValue(GetRegValue(15) >> 6);
    ui->spinBox_3->setValue(GetRegValue(16) >> 6);

    ui->spinBox_11->setValue(GetRegValue(14) & 0x3F);
    ui->spinBox_10->setValue(GetRegValue(15) & 0x3F);
    ui->spinBox_9->setValue(GetRegValue(16) & 0x3F);

    ui->spinBox_13->setValue(GetRegValue(17));
    ui->spinBox_12->setValue(GetRegValue(18));
    ui->spinBox_14->setValue(GetRegValue(19));

    ui->spinBox_4->setValue(GetRegValue(20));
    ui->spinBox_5->setValue(GetRegValue(21));
    ui->spinBox_6->setValue(GetRegValue(22));

    ui->spinBox_17->setValue(GetRegValue(23));
    ui->spinBox_16->setValue(GetRegValue(24));
    ui->spinBox_15->setValue(GetRegValue(25));

    ui->spinBox_19->setValue(GetRegValue(26));
    ui->spinBox_18->setValue(GetRegValue(27));
    ui->spinBox_20->setValue(GetRegValue(28));

    unsigned char value = GetRegValue(29);
    ui->spinBox_23->setValue(value & 0x0F);
    ui->spinBox_22->setValue(value >> 4);
    ui->spinBox_21->setValue(GetRegValue(30));

    ui->spinBox_26->setValue(GetRegValue(31));
    ui->spinBox_25->setValue(GetRegValue(32));
    ui->spinBox_24->setValue(GetRegValue(33));

    ui->spinBox_29->setValue(GetRegValue(40));
    ui->spinBox_28->setValue(GetRegValue(41));
    ui->spinBox_27->setValue(GetRegValue(42));

    value = GetRegValue(34);
    if (value == 0xF7)
    {
        ui->checkBox->setChecked(true);
    }

    if (regpara[13 * 6 + 4] == (char)0x13)
    {
        ui->checkBox_2->setChecked(true);
    }

    ui->spinBox_8->setValue(GetRegValue(5));
    ui->spinBox_30->setValue(GetRegValue(6));
    ui->spinBox_7->setValue(GetRegValue(4));



    int value1 = GetRegValue(7) + GetRegValue(8) * 256;
    int value2 = value1*GetRegValue(4) * 2;
    if (value2 > 32768)
    {
        ui->lineEdit_4->setText("16Bit");
    }
    else if (value2 > 16384)
    {
        ui->lineEdit_4->setText("15Bit");
    }
    else if (value2 > 8192)
    {
        ui->lineEdit_4->setText("14Bit");
    }
    else
    {

    }


    GetGlobalReg();

}














void ICXM11202GSetting::on_pushButton_clicked()
{
	setCursor(Qt::WaitCursor);

	//电流调节1/2
	unsigned char current = 0;
	//R
	current = ((ui->spinBox->value() << 6) + ui->spinBox_11->value());
	SetRegValue(14, current);
	//G
	current = ((ui->spinBox_2->value() << 6) + ui->spinBox_10->value());
	SetRegValue(15, current);
	//B
	current = ((ui->spinBox_3->value() << 6) + ui->spinBox_9->value());
	SetRegValue(16, current);

	//电流增益
	SetRegValue(17, ui->spinBox_13->value());
	SetRegValue(18, ui->spinBox_12->value());
	SetRegValue(19, ui->spinBox_14->value());

	//消影等级
	SetRegValue(20, ui->spinBox_4->value());
	SetRegValue(21, ui->spinBox_5->value());
	SetRegValue(22, ui->spinBox_6->value());

	//低灰偏色补偿1
	SetRegValue(23, ui->spinBox_17->value());
	SetRegValue(24, ui->spinBox_16->value());
	SetRegValue(25, ui->spinBox_15->value());

	//低灰偏色补偿2
	SetRegValue(26, ui->spinBox_19->value());
	SetRegValue(27, ui->spinBox_18->value());
	SetRegValue(28, ui->spinBox_20->value());

	//渐变过渡优化
	unsigned char value = 0;
	value = ((ui->spinBox_22->value() << 4) + ui->spinBox_23->value());
	SetRegValue(29, value);
	SetRegValue(30, ui->spinBox_21->value());

	//低灰均匀性
	SetRegValue(31, ui->spinBox_26->value());
	SetRegValue(32, ui->spinBox_25->value());
	SetRegValue(33, ui->spinBox_24->value());

	//去坏点侦测等级
	SetRegValue(40, ui->spinBox_29->value());
	SetRegValue(41, ui->spinBox_28->value());
	SetRegValue(42, ui->spinBox_27->value());

	//节能模式
	if (ui->checkBox->isChecked())
	{
		SetRegValue(34, 0xF7);
	}
	else
	{
		SetRegValue(34, 0xF0);
	}

	//去坏点
	if (ui->checkBox_2->isChecked())
	{
		regpara[13 * 6 + 4] = 0x13;
	}
	else
	{
		regpara[13 * 6 + 4] = 0x12;
	}

	//单芯片列行
	SetRegValue(5, ui->spinBox_8->value());
	SetRegValue(6, ui->spinBox_30->value());

	//刷新倍率
	SetRegValue(4, ui->spinBox_7->value());






    SetGlobalReg();
	
	Writebin(filename + "/regpara.bin", regpara);

	setCursor(Qt::ArrowCursor);

	bool result;
	if (m_writeDataFun)
		result = m_writeDataFun(regpara.constData(), regpara.size());

	if (result)
	{
		int ret = QMessageBox::information(this, tr("发送"), tr("发送成功!"), QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok);
	}
	else
	{
		int ret = QMessageBox::information(this, tr("发送"), tr("发送失败!"), QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok);
	}
	
}

void ICXM11202GSetting::SetGlobalReg()
{
     bool ok ;
    regpara[7 * 6 + 0] = QString(ui->lineEdit_5->text()).toInt(&ok,16);
    regpara[7 * 6 + 1] = QString(ui->lineEdit_6->text()).toInt(&ok,16);
    regpara[7 * 6 + 2] = QString(ui->lineEdit_7->text()).toInt(&ok,16);
    regpara[7 * 6 + 3] = QString(ui->lineEdit_8->text()).toInt(&ok,16);
    regpara[7 * 6 + 4] = QString(ui->lineEdit_9->text()).toInt(&ok,16);
    regpara[7 * 6 + 5] = QString(ui->lineEdit_10->text()).toInt(&ok,16);

    regpara[8 * 6 + 0] = QString(ui->lineEdit_11->text()).toInt(&ok,16);
    regpara[8 * 6 + 1] = QString(ui->lineEdit_12->text()).toInt(&ok,16);
    regpara[8 * 6 + 2] = QString(ui->lineEdit_13->text()).toInt(&ok,16);
    regpara[8 * 6 + 3] = QString(ui->lineEdit_14->text()).toInt(&ok,16);
    regpara[8 * 6 + 4] = QString(ui->lineEdit_15->text()).toInt(&ok,16);
    regpara[8 * 6 + 5] = QString(ui->lineEdit_16->text()).toInt(&ok,16);

    regpara[9 * 6 + 0] = QString(ui->lineEdit_17->text()).toInt(&ok,16);
    regpara[9 * 6 + 1] = QString(ui->lineEdit_18->text()).toInt(&ok,16);
    regpara[9 * 6 + 2] = QString(ui->lineEdit_19->text()).toInt(&ok,16);
    regpara[9 * 6 + 3] = QString(ui->lineEdit_20->text()).toInt(&ok,16);
    regpara[9 * 6 + 4] = QString(ui->lineEdit_21->text()).toInt(&ok,16);
    regpara[9 * 6 + 5] = QString(ui->lineEdit_22->text()).toInt(&ok,16);

    regpara[10 * 6 + 0] = QString(ui->lineEdit_23->text()).toInt(&ok,16);
    regpara[10 * 6 + 1] = QString(ui->lineEdit_24->text()).toInt(&ok,16);
    regpara[10 * 6 + 2] = QString(ui->lineEdit_25->text()).toInt(&ok,16);
    regpara[10 * 6 + 3] = QString(ui->lineEdit_26->text()).toInt(&ok,16);
    regpara[10 * 6 + 4] = QString(ui->lineEdit_27->text()).toInt(&ok,16);
    regpara[10 * 6 + 5] = QString(ui->lineEdit_28->text()).toInt(&ok,16);

    regpara[11 * 6 + 0] = QString(ui->lineEdit_29->text()).toInt(&ok,16);
    regpara[11 * 6 + 1] = QString(ui->lineEdit_30->text()).toInt(&ok,16);
    regpara[11 * 6 + 2] = QString(ui->lineEdit_31->text()).toInt(&ok,16);
    regpara[11 * 6 + 3] = QString(ui->lineEdit_32->text()).toInt(&ok,16);
    regpara[11 * 6 + 4] = QString(ui->lineEdit_33->text()).toInt(&ok,16);
    regpara[11 * 6 + 5] = QString(ui->lineEdit_34->text()).toInt(&ok,16);

    regpara[12 * 6 + 0] = QString(ui->lineEdit_35->text()).toInt(&ok,16);
    regpara[12 * 6 + 1] = QString(ui->lineEdit_36->text()).toInt(&ok,16);
    regpara[12 * 6 + 2] = QString(ui->lineEdit_37->text()).toInt(&ok,16);
    regpara[12 * 6 + 3] = QString(ui->lineEdit_38->text()).toInt(&ok,16);
    regpara[12 * 6 + 4] = QString(ui->lineEdit_39->text()).toInt(&ok,16);
    regpara[12 * 6 + 5] = QString(ui->lineEdit_40->text()).toInt(&ok,16);



}

void ICXM11202GSetting::GetGlobalReg()
{
    ui->lineEdit_5->setText(QString::number((unsigned char)regpara[7 * 6 + 0]));
    ui->lineEdit_6->setText(QString::number((unsigned char)regpara[7 * 6 + 1]));
    ui->lineEdit_7->setText(QString::number((unsigned char)regpara[7 * 6 + 2]));
    ui->lineEdit_8->setText(QString::number((unsigned char)regpara[7 * 6 + 3]));
    ui->lineEdit_9->setText(QString::number((unsigned char)regpara[7 * 6 + 4]));
    ui->lineEdit_10->setText(QString::number((unsigned char)regpara[7 * 6 + 5]));

    ui->lineEdit_11->setText(QString::number((unsigned char)regpara[8 * 6 + 0]));
    ui->lineEdit_12->setText(QString::number((unsigned char)regpara[8 * 6 + 1]));
    ui->lineEdit_13->setText(QString::number((unsigned char)regpara[8 * 6 + 2]));
    ui->lineEdit_14->setText(QString::number((unsigned char)regpara[8 * 6 + 3]));
    ui->lineEdit_15->setText(QString::number((unsigned char)regpara[8 * 6 + 4]));
    ui->lineEdit_16->setText(QString::number((unsigned char)regpara[8 * 6 + 5]));

    ui->lineEdit_17->setText(QString::number((unsigned char)regpara[9 * 6 + 0]));
    ui->lineEdit_18->setText(QString::number((unsigned char)regpara[9 * 6 + 1]));
    ui->lineEdit_19->setText(QString::number((unsigned char)regpara[9 * 6 + 2]));
    ui->lineEdit_20->setText(QString::number((unsigned char)regpara[9 * 6 + 3]));
    ui->lineEdit_21->setText(QString::number((unsigned char)regpara[9 * 6 + 4]));
    ui->lineEdit_22->setText(QString::number((unsigned char)regpara[9 * 6 + 5]));

    ui->lineEdit_23->setText(QString::number((unsigned char)regpara[10 * 6 + 0]));
    ui->lineEdit_24->setText(QString::number((unsigned char)regpara[10 * 6 + 1]));
    ui->lineEdit_25->setText(QString::number((unsigned char)regpara[10 * 6 + 2]));
    ui->lineEdit_26->setText(QString::number((unsigned char)regpara[10 * 6 + 3]));
    ui->lineEdit_27->setText(QString::number((unsigned char)regpara[10 * 6 + 4]));
    ui->lineEdit_28->setText(QString::number((unsigned char)regpara[10 * 6 + 5]));

    ui->lineEdit_29->setText(QString::number((unsigned char)regpara[11 * 6 + 0]));
    ui->lineEdit_30->setText(QString::number((unsigned char)regpara[11 * 6 + 1]));
    ui->lineEdit_31->setText(QString::number((unsigned char)regpara[11 * 6 + 2]));
    ui->lineEdit_32->setText(QString::number((unsigned char)regpara[11 * 6 + 3]));
    ui->lineEdit_33->setText(QString::number((unsigned char)regpara[11 * 6 + 4]));
    ui->lineEdit_34->setText(QString::number((unsigned char)regpara[11 * 6 + 5]));

    ui->lineEdit_35->setText(QString::number((unsigned char)regpara[12 * 6 + 0]));
    ui->lineEdit_36->setText(QString::number((unsigned char)regpara[12 * 6 + 1]));
    ui->lineEdit_37->setText(QString::number((unsigned char)regpara[12 * 6 + 2]));
    ui->lineEdit_38->setText(QString::number((unsigned char)regpara[12 * 6 + 3]));
    ui->lineEdit_39->setText(QString::number((unsigned char)regpara[12 * 6 + 4]));
    ui->lineEdit_40->setText(QString::number((unsigned char)regpara[12 * 6 + 5]));



}




void ICXM11202GSetting::Writebin(QString path, QByteArray bytes)
{
    QFile f(path);      //定义一个文件
    if (f.open(QIODevice::WriteOnly))       //打开文件
    {
        QDataStream qs(&f);             //定义一个数据流
        int i = 0;
        for(i=0;i<bytes.length();i++)
        {
            qs << (uint8_t)bytes[i];      //把数组中的数据写到数据流，即写入文件中
        }
        f.close();
    }
    else
    {
        qDebug() << "Failed";
    }
}
QByteArray ICXM11202GSetting::Readbin(QString path)
{
    QByteArray ba;
    QFile f(path);      //定义一个文件
    if (f.open(QIODevice::ReadOnly))       //打开文件
    {
        ba = f.readAll();
        f.close();
        //qDebug() << ba;
    }
    else
    {
        qDebug() << "Failed";
    }
    return ba;
}



void ICXM11202GSetting::on_pushButton_2_clicked()
{
	
    QByteArray array1 = ReadGamdat(filename + "/Gamma/XM11202G-GammaA.gamdat");
	bool result;
	if (m_writeGammaDataFun)
		result = m_writeGammaDataFun(array1.constData(), array1.size());
	if (result)
	{
		int ret = QMessageBox::information(this, tr("Gamma"), tr("发送成功!"), QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok);
	}
	else
	{
		int ret = QMessageBox::information(this, tr("Gamma"), tr("发送失败!"), QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok);
	}
	
}

void ICXM11202GSetting::on_pushButton_3_clicked()
{
    QByteArray array1 = ReadGamdat(filename + "/Gamma/XM11202G-GammaB.gamdat");
	bool result;
	if (m_writeGammaDataFun)
		result = m_writeGammaDataFun(array1.constData(), array1.size());
	if (result)
	{
		int ret = QMessageBox::information(this, tr("Gamma"), tr("发送成功!"), QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok);
	}
	else
	{
		int ret = QMessageBox::information(this, tr("Gamma"), tr("发送失败!"), QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok);
	}
}

void ICXM11202GSetting::on_pushButton_4_clicked()
{
    QByteArray array1 = ReadGamdat(filename + "/Gamma/XM11202G-GammaC.gamdat");
	bool result;
	if (m_writeGammaDataFun)
		result = m_writeGammaDataFun(array1.constData(), array1.size());
	if (result)
	{
		int ret = QMessageBox::information(this, tr("Gamma"), tr("发送成功!"), QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok);
	}
	else
	{
		int ret = QMessageBox::information(this, tr("Gamma"), tr("发送失败!"), QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok);
	}
}

void ICXM11202GSetting::on_pushButton_5_clicked()
{
    QByteArray array1 = ReadGamdat(filename + "/Gamma/XM11202G-GammaD.gamdat");
	bool result;
	if (m_writeGammaDataFun)
		result = m_writeGammaDataFun(array1.constData(), array1.size());
	if (result)
	{
		int ret = QMessageBox::information(this, tr("Gamma"), tr("发送成功!"), QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok);
	}
	else
	{
		int ret = QMessageBox::information(this, tr("Gamma"), tr("发送失败!"), QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok);
	}
}

void ICXM11202GSetting::on_pushButton_6_clicked()
{
        //QByteArray array1;
        bool result;
        if (m_removalOfDeadPiexlsFun)
            m_removalOfDeadPiexlsFun();
      /*  if (result)
        {*/
            int ret = QMessageBox::information(this, tr("去坏点"), tr("触发成功!"), QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok);
      /*  }
        else
        {
            int ret = QMessageBox::information(this, tr("去坏点"), tr("触发失败!"), QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok);
        }*/

}




///读取.gamdat文件
QByteArray ICXM11202GSetting::ReadGamdat(QString filepath)
{
    QFile file(filepath);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"Can't open the file!"<<endl;
    }

    QByteArray array;
    QByteArray line = file.readLine();
    QString str(line);
    QString strs = str.split('#')[5];

    QStringList gama = strs.split(',');
    //qDebug() << gama.count() << "----------------------";
    for (int i = 0;i < gama.count();i++)
    {
        unsigned char tempByte = (unsigned char)(gama[i].toUInt(nullptr,10));
        array.append(tempByte);
        //qDebug() << "----------------------" << tempByte;
        tempByte = (unsigned char)(gama[i].toUInt(nullptr,10) >> 8);
        array.append(tempByte);
        //qDebug() << "----------------------" << tempByte;
    }
    return array;
}






void ICXM11202GSetting::on_pushButton_7_clicked()
{
    char* result;
    if (m_readDataFun)
        result = m_readDataFun();

    if (sizeof(result) > 0)
    {
        QByteArray para = result;

        if (para.length() >= (regpara.length() + 2))
        {
            for (int i = 0;i>para.length();i++)
            {
                regpara[i] = para[i];
            }
        }

        Loadformpara();
        int ret = QMessageBox::information(this, tr("回读"), tr("回读成功!"), QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok);
    }
    else
    {
        int ret = QMessageBox::information(this, tr("回读"), tr("回读失败!"), QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok);
        return;
    }

}

void ICXM11202GSetting::on_spinBox_valueChanged(int arg1)
{
    double value = arg1 * (0.16+0.0025*ui->spinBox_11->value()) * ui->spinBox_13->value();
    QString str = QString::number(value,'g',3);
    ui->lineEdit->setText(str);
}

void ICXM11202GSetting::on_spinBox_11_valueChanged(int arg1)
{
    double value = ui->spinBox->value() * (0.16+0.0025*arg1) * ui->spinBox_13->value();
    QString str = QString::number(value,'g',3);
    ui->lineEdit->setText(str);
}

void ICXM11202GSetting::on_spinBox_13_valueChanged(int arg1)
{
    double value = ui->spinBox->value() * (0.16+0.0025*ui->spinBox_11->value()) * arg1;
    QString str = QString::number(value,'g',3);
    ui->lineEdit->setText(str);
}


void ICXM11202GSetting::on_spinBox_2_valueChanged(int arg1)
{
    double value = arg1 * (0.16+0.0025*ui->spinBox_10->value()) * ui->spinBox_12->value();
    QString str = QString::number(value,'g',3);
    ui->lineEdit_2->setText(str);
}

void ICXM11202GSetting::on_spinBox_10_valueChanged(int arg1)
{
    double value = ui->spinBox_2->value() * (0.16+0.0025*arg1) * ui->spinBox_12->value();
    QString str = QString::number(value,'g',3);
    ui->lineEdit_2->setText(str);
}

void ICXM11202GSetting::on_spinBox_12_valueChanged(int arg1)
{
    double value = ui->spinBox_2->value() * (0.16+0.0025*ui->spinBox_10->value()) * arg1;
    QString str = QString::number(value,'g',3);
    ui->lineEdit_2->setText(str);
}


void ICXM11202GSetting::on_spinBox_3_valueChanged(int arg1)
{
    double value = arg1 * (0.16+0.0025*ui->spinBox_9->value()) * ui->spinBox_14->value();
    QString str = QString::number(value,'f',3);
    ui->lineEdit_3->setText(str);
}

void ICXM11202GSetting::on_spinBox_9_valueChanged(int arg1)
{
    double value = ui->spinBox_3->value() * (0.16+0.0025*arg1) * ui->spinBox_14->value();
    QString str = QString::number(value,'f',3);
    ui->lineEdit_3->setText(str);
}

void ICXM11202GSetting::on_spinBox_14_valueChanged(int arg1)
{
    double value = ui->spinBox_3->value() * (0.16+0.0025*ui->spinBox_9->value()) * arg1;
    QString str = QString::number(value,'f',3);
    ui->lineEdit_3->setText(str);
}

void ICXM11202GSetting::on_spinBox_7_valueChanged(int arg1)
{
    int value1 = GetRegValue(7) + GetRegValue(8) * 256;
    int value2 = value1*arg1 * 2;
    if (value2 > 32766)
    {
        ui->lineEdit_4->setText("16Bit");
    }
    else if (value2 > 16384 && value2 <= 32766)
    {
        ui->lineEdit_4->setText("15Bit");
    }
    else if (value2 > 8192 && value2 <= 16384)
    {
        ui->lineEdit_4->setText("14Bit");
    }
    else
    {

    }
}

void ICXM11202GSetting::on_pushButton_9_clicked()
{
    QString fileName;
    fileName = QFileDialog::getSaveFileName(this,tr("Open Config"), "", tr("TXT Files (*.txt);; TXT Files (*.txt)"));
    if (!fileName.isNull())
    {
        WriteFile(fileName,regpara);   //fileName是文件名
    
		int ret = QMessageBox::information(this, tr("保存文件"), tr("文件保存成功!"),QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok);
    }
    else
    {

    }

}
//
//void ICXM11202GSetting::MessageBoxShow(const char title, QString str)
//{
//	//QMessageBox msg(this);//对话框设置父组件
//	//msg.setWindowTitle(title);//对话框标题
//	//msg.setText(str);//对话框提示文本
//	//msg.setIcon(QMessageBox::NoIcon);//设置图标类型
//	//msg.setStandardButtons(QMessageBox::Ok | QMessageBox:: Cancel);//对话框上包含的按钮
//
//	//if(msg.exec() == QMessageBox::Ok)//模态调用
//	//{
//	//    msg.close();
//	//}
//
//
//}


void ICXM11202GSetting::on_pushButton_8_clicked()
{
    QString fileName;
    fileName = QFileDialog::getOpenFileName(this,tr("Open Config"), "", tr("TXT Files (*.txt);; CID Files (*.txt)"));

    if (!fileName.isNull())
    {
        //fileName即是选择的文件名
    }
    else
    {
        return;
    }

    //QString filename = QCoreApplication::applicationDirPath();
    regpara = ReadFile(fileName);
    Loadformpara();
    
	int ret = QMessageBox::information(this, tr("加载文件"), tr("文件加载成功!"), QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok);
}



void ICXM11202GSetting::on_pushButton_10_clicked()
{
    if(ui->pushButton_10->text() == "高级模式")
    {
        ui->groupBox_3->setVisible(true);
        ui->groupBox_2->setVisible(false);
        ui->groupBox->setVisible(false);
        ui->pushButton_10->setText("普通模式");
    }
    else if(ui->pushButton_10->text() == "普通模式")
    {
        ui->groupBox_3->setVisible(false);
        ui->groupBox_2->setVisible(true);
        ui->groupBox->setVisible(true);
        ui->pushButton_10->setText("高级模式");
    }
    else{}
}






















