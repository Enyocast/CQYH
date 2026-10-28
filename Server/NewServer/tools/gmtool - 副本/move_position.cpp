#include "stdafx.h"
#include "move_position.h"

//#include <QInputDialog>
//#include <QMainWindow>
#include <QtWidgets/QMessageBox>



CMovePosition::CMovePosition(QWidget *parent, Qt::WindowFlags flags)
: QDialog(parent, flags)
{
    ui.setupUi(this);

    ui.comboBox->addItem("");
    ui.comboBox->addItem(QString::fromLocal8Bit("xsc-新手村"));
    ui.comboBox->addItem(QString::fromLocal8Bit("hzc-虎爪庄"));
    ui.comboBox->addItem(QString::fromLocal8Bit("hhc-黑虎村"));
    ui.comboBox->addItem(QString::fromLocal8Bit("lgz-龙骨镇"));
    ui.comboBox->addItem(QString::fromLocal8Bit("lgsm-龙骨沙漠"));
    ui.comboBox->addItem(QString::fromLocal8Bit("hmyj-荒漠遗迹"));


    //connect(ui.loginButton, SIGNAL(clicked()), this, SLOT(Login()));
    //connect(ui.exitButton, SIGNAL(clicked()), this, SLOT(Exit()));
    connect(ui.exeButton, SIGNAL(clicked()), this, SLOT(Execute()));
    connect(ui.exitButton, SIGNAL(clicked()), this, SLOT(Exit()));
}

CMovePosition::~CMovePosition()
{

}

void CMovePosition::Execute()
{
    accept();
}

void CMovePosition::Exit()
{
    done(0);
}
