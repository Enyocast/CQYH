#include "stdafx.h"
#include "gm_item_info.h"


CGMItemInfo::CGMItemInfo(QWidget *parent, Qt::WindowFlags flags)
: QDialog(parent, flags)
{
    ui.setupUi(this);

    connect(ui.exitButton, SIGNAL(clicked()), this, SLOT(Exit()));
}

CGMItemInfo::~CGMItemInfo()
{

}


void CGMItemInfo::Exit()
{
    done(0);
}

void CGMItemInfo::ShowInfo(const char *pcszBuffer, BOOL bBiggerFont)
{
    LOG_PROCESS_ERROR(pcszBuffer);

    QTextDocument   *pDoc = new QTextDocument;
    
    LOG_PROCESS_ERROR(pDoc);
    pDoc->setPlainText(QString::fromLocal8Bit(pcszBuffer));
    ui.textEdit->setDocument(pDoc);

    if (bBiggerFont)
    {
        QFont   qft;
        qft.setBold(true);
        qft.setPointSize(12);
        ui.textEdit->setFont(qft);
    }

Exit0:
    return;
}

