#include "stdafx.h"

#include "bt_config.h"

#include "bt_item_editor.h"

void BTItemEditor::setupUi(QWidget *BTItemEditWidget)
{
    if (BTItemEditWidget->objectName().isEmpty())
        BTItemEditWidget->setObjectName(QString::fromUtf8("BTItemEditWidget"));

    //BTItemEditWidget->resize(401, 24);
    BTItemEditWidget->setAutoFillBackground(true);

    horizontalLayout_NodeAll = new QHBoxLayout(BTItemEditWidget);
    horizontalLayout_NodeAll->setSpacing(0);
    horizontalLayout_NodeAll->setContentsMargins(0, 0, 0, 0);
    horizontalLayout_NodeAll->setObjectName(QString::fromUtf8("horizontalLayout_NodeAll"));

    comboBox_NodeType = new QComboBox(BTItemEditWidget);
    comboBox_NodeType->setObjectName(QString::fromUtf8("comboBox_NodeType"));
    comboBox_NodeType->setEditable(true);

    horizontalLayout_NodeAll->addWidget(comboBox_NodeType);

    const QStringList& list = BTConfig::GetInstance().GetActionList();
    comboBox_NodeType->clear();
    comboBox_NodeType->addItems( list );

    ///
    horizontalLayout_NodeParams = new QHBoxLayout();
    horizontalLayout_NodeParams->setObjectName(QString::fromUtf8("horizontalLayout_NodeParams"));
    horizontalLayout_NodeParams->setContentsMargins(4, -1, -1, -1);

    for ( int i=0; i<MAX_BT_PARAM; ++i )
    {
        BTItemParamLabel* pLabel = new BTItemParamLabel(this); 
        label_Param.insert( label_Param.count(), pLabel );
        label_Param[i]->SetSiblingRank( i );
        label_Param[i]->setObjectName(QString::fromUtf8("label_P%1").arg(i));
        horizontalLayout_NodeParams->addWidget(label_Param[i]);

        BTItemParamComboBox* pComboBox = new BTItemParamComboBox(this);
        comboBox_Param.insert( comboBox_Param.count(), pComboBox );
        comboBox_Param[i]->setObjectName(QString::fromUtf8("comboBox_P%1").arg(i));
        comboBox_Param[i]->setEditable(true);
        comboBox_Param[i]->SetSiblingRank( i );

        horizontalLayout_NodeParams->addWidget(comboBox_Param[i]);
        label_Param[i]->setBuddy(comboBox_Param[i]);

        QObject::connect(comboBox_NodeType, SIGNAL(editTextChanged(QString)), label_Param[i], SLOT(UpdateText(QString)));
        QObject::connect(comboBox_NodeType, SIGNAL(editTextChanged(QString)), comboBox_Param[i], SLOT(UpdateEditText(QString)));
    }
    horizontalLayout_NodeAll->addLayout(horizontalLayout_NodeParams);

    QMetaObject::connectSlotsByName(BTItemEditWidget);
}

BTItemEditor::BTItemEditor(QWidget *parent, Qt::WFlags flags)
    : QWidget(parent, flags)
{
    setupUi(this);
}

BTItemEditor::~BTItemEditor()
{
}

bool BTItemEditor::setText( QString strLine )
{
    QString action;//, p0, p1, p2, p3;
    QString strParam[MAX_BT_PARAM] = {};
    QRegExp rx(".*(\\w*)\\s*(,\\s*param\\s*=\\s*\\{\\s*(\\w*)\\s*,?\\s*(\\w*)\\s*,?\\s*(\\w*)\\s*,?\\s*(\\w*)\\s*,?\\s*\\}\\s*)?.*");
    //QRegExp rx(QRegExp::escape(".*(\w*)\s*(,\s*param\s*=\s*\{\s*(\w*)\s*,?\s*(\w*)\s*,?\s*(\w*)\s*,?\s*(\w*)\s*,?\s*\}\s*)?.*"));
    //QRegExp rx(".*(\w*)\s*(,\s*param\s*=\s*\{\s*(\w*)\s*,?\s*(\w*)\s*,?\s*(\w*)\s*,?\s*(\w*)\s*,?\s*\}\s*)?.*");
    if (rx.indexIn(strLine) != -1) 
    {
        action = rx.cap(1);
        //p0 = rx.cap(3);
        //p1 = rx.cap(4);
        //p2 = rx.cap(5);
        //p3 = rx.cap(6);
        strParam[0] = rx.cap(3);
        strParam[1] = rx.cap(4);
        strParam[2] = rx.cap(5);
        strParam[3] = rx.cap(6);
    }

    if ( action.indexOf(QRegExp("^bt\\w*")) == 0 )
    {
        action.replace( QRegExp("^bt(\\w*)"), "bat\\1" );
    }

    const ACTION_CONFIG* config = BTConfig::GetInstance().FindActionConfig( action );
    if ( NULL == config )
    {
        return false;
    }

/// dynamic set
    //horizontalLayout_NodeParams = new QHBoxLayout();
    //horizontalLayout_NodeParams->setObjectName(QString::fromUtf8("horizontalLayout_NodeParams"));
    //horizontalLayout_NodeParams->setContentsMargins(4, -1, -1, -1);

    //for ( int i=0; i<MAX_BT_PARAM; ++i )
    //{
    //    if ( config->Param[i].isEmpty() )
    //    {
    //        break;
    //    }

    //    BTItemParamLabel* pLabel = new BTItemParamLabel(this); 
    //    label_Param.insert( label_Param.count(), pLabel );
    //    label_Param[i]->SetSiblingRank( i );
    //    label_Param[i]->setObjectName(QString::fromUtf8("label_P%1").arg(i));
    //    horizontalLayout_NodeParams->addWidget(label_Param[i]);

    //    BTItemParamComboBox* pComboBox = new BTItemParamComboBox(this);
    //    comboBox_Param.insert( comboBox_Param.count(), pComboBox );
    //    comboBox_Param[i]->setObjectName(QString::fromUtf8("comboBox_P%1").arg(i));
    //    comboBox_Param[i]->setEditable(true);
    //    comboBox_Param[i]->SetSiblingRank( i );
    //    comboBox_Param[i]->InitText( action, strParam[i] );
    //    label_Param[i]->setBuddy(comboBox_Param[i]);

    //    horizontalLayout_NodeParams->addWidget(comboBox_Param[i]);

    //    QObject::connect(comboBox_NodeType, SIGNAL(currentIndexChanged(QString)), label_Param[i], SLOT(UpdateText(QString)));
    //    QObject::connect(comboBox_NodeType, SIGNAL(currentIndexChanged(QString)), comboBox_Param[i], SLOT(UpdateEditText(QString)));
    //}
    //horizontalLayout_NodeAll->addLayout(horizontalLayout_NodeParams);
/// dynamic set

    for ( int i=0; i<MAX_BT_PARAM; ++i )
    {
        if ( config->Param[i].isEmpty() )
        {
            break;
        }
        comboBox_Param[i]->InitText( action, strParam[i] );
    }
    comboBox_NodeType->setEditText( action );
    //emit comboBox_NodeType->editTextChanged(action);

    return true;
}

QString BTItemEditor::getText()
{
    //return "batCheckCharHp, param = {tarAITarget, boLTE, 50, 100 }";

    QString nodeName = comboBox_NodeType->currentText();

    QString pResult = nodeName;

    const ACTION_CONFIG* pConfig = BTConfig::GetInstance().FindActionConfig(nodeName);
    if ( pConfig )
    {
        if ( !pConfig->Param[0].isEmpty() )
        {
            pResult += ", param={";

            for ( int i=0; i<MAX_BT_PARAM; ++i )
            {
                if ( pConfig->Param[i].isEmpty() )//|| comboBox_Param[i]->currentText().isEmpty() )
                {
                    break;
                }

                if ( i > 0)
                {
                    pResult += ", ";
                }
                if( i < comboBox_Param.count() )
                {
                    pResult += comboBox_Param[i]->currentText();    //comboBox_Param[i]->m_initString
                }
                else // report error
                {
                    pResult += "NEED_SET";
                }
                
            }
            pResult += "}";
        }

    }

    return pResult;
}
