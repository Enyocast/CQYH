#include "stdafx.h"
#include "delete_item.h"

//#include <QInputDialog>
//#include <QMainWindow>
#include <QtWidgets/QMessageBox>



CDeleteItem::CDeleteItem(QWidget *parent, Qt::WindowFlags flags)
: QDialog(parent, flags)
{
    ui.setupUi(this);

    ui.comboBox->addItem("");
    ui.comboBox->addItem(QString::fromLocal8Bit("扣除道具(根据类型ID)"));
    ui.comboBox->addItem(QString::fromLocal8Bit("扣除金币"));
    ui.comboBox->addItem(QString::fromLocal8Bit("清空身上装备"));
    ui.comboBox->addItem(QString::fromLocal8Bit("清空背包"));

    ui.label_3->close();
    ui.label_4->close();
    ui.lineEdit->close();
    ui.lineEdit_2->close();
    ui.comboBox_2->close();

    //connect(ui.loginButton, SIGNAL(clicked()), this, SLOT(Login()));
    //connect(ui.exitButton, SIGNAL(clicked()), this, SLOT(Exit()));
    connect(ui.exeButton, SIGNAL(clicked()), this, SLOT(Execute()));
    connect(ui.exitButton, SIGNAL(clicked()), this, SLOT(Exit()));
    connect(ui.comboBox, SIGNAL(activated(const QString &)), this, SLOT(OnSelectDeleteItemType(const QString &)));


}

CDeleteItem::~CDeleteItem()
{

}

void CDeleteItem::Execute()
{
    accept();
}

void CDeleteItem::Exit()
{
    done(0);
}

void CDeleteItem::OnSelectDeleteItemType(const QString &currentText)
{
    if (currentText == QString::fromLocal8Bit("扣除道具(根据类型ID)"))
    {
        ui.label_3->setText(QString::fromLocal8Bit("道具类型ID"));
        ui.label_3->show();
        ui.lineEdit->show();
        ui.label_4->show();
        ui.lineEdit_2->show();
        ui.comboBox_2->close();
    }
    else if (currentText == QString::fromLocal8Bit("扣除金币"))
    {
        ui.label_3->setText(QString::fromLocal8Bit("金币类型"));
        ui.comboBox_2->addItem("");
        ui.comboBox_2->addItem(QString::fromLocal8Bit("深渊金币"));
        ui.comboBox_2->addItem(QString::fromLocal8Bit("金币"));
        ui.comboBox_2->addItem(QString::fromLocal8Bit("名师值"));
        ui.label_3->show();
        ui.lineEdit->close();
        ui.label_4->show();
        ui.lineEdit_2->show();
        ui.comboBox_2->show();
    }
    else if (currentText == QString::fromLocal8Bit("清空身上装备"))
    {
        ui.label_3->close();
        ui.label_4->close();
        ui.lineEdit->close();
        ui.lineEdit_2->close();
        ui.comboBox_2->close();
    }
    else if (currentText == QString::fromLocal8Bit("清空背包"))
    {
        ui.label_3->close();
        ui.label_4->close();
        ui.lineEdit->close();
        ui.lineEdit_2->close();
        ui.comboBox_2->close();
    }
    else
    {
        ui.label_3->close();
        ui.label_4->close();
        ui.lineEdit->close();
        ui.lineEdit_2->close();
        ui.comboBox_2->close();
    }
}





