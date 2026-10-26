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
    ui.comboBox->addItem(QString::fromLocal8Bit("xsc-ÐÂÊÖ´å"));
    ui.comboBox->addItem(QString::fromLocal8Bit("hzc-»¢×¦×¯"));
    ui.comboBox->addItem(QString::fromLocal8Bit("hhc-ºÚ»¢´å"));
    ui.comboBox->addItem(QString::fromLocal8Bit("lgz-Áú¹ÇÕò"));
    ui.comboBox->addItem(QString::fromLocal8Bit("lgsm-Áú¹ÇÉ³Ä®"));
    ui.comboBox->addItem(QString::fromLocal8Bit("hmyj-»ÄÄ®ÒÅ¼£"));


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
