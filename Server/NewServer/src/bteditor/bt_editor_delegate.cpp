#include "stdafx.h"
#include "bt_editor_delegate.h"

#include "bt_model.h"
#include "btree_file.h"
#include "bt_config.h"

BTEditorDelegate::BTEditorDelegate(QObject *parent)
    : QItemDelegate(parent)
{
}

QWidget *BTEditorDelegate::createEditor(QWidget *parent,
    const QStyleOptionViewItem & option ,
    const QModelIndex & index ) const
{
	QComboBox* pResult = NULL;

	BTModel* pModel = (BTModel*)index.model();
	LOG_PROCESS_ERROR(pModel);

	BT_EDIT_NOD* pNode = (BT_EDIT_NOD*)index.internalPointer();
	LOG_PROCESS_ERROR(pNode);

	pResult = new QComboBox(parent);
	LOG_PROCESS_ERROR(pResult);

	pResult->setEditable(true);

	if (index.column() == 0)
	{
		if (index.parent().isValid())
		{
            QStringList values = BTConfig::GetInstance().GetActionList();
            values.sort();
			pResult->addItems(values);
			pResult->setCurrentIndex(pResult->findText(pNode->szType));
		}
		else
        {
            QStringList values = BTConfig::GetInstance().GetEventList();
            values.sort();
            pResult->addItems(values);
            pResult->setCurrentIndex(pResult->findText(pNode->szType));
		}
        pResult->setMaxVisibleItems(96);
	}
	else
	{
        if (index.parent().isValid())
        {
            INT32 nParamIndex = index.column() - 1;
            const ACTION_CONFIG* pConfig = BTConfig::GetInstance().FindActionConfig(pNode->szType);
            if (pConfig)
            {
                if (pConfig->Param[nParamIndex].indexOf('#') == 0 )
                {
                    QStringList values = pModel->GetBTreeFile()->GetEnumValues(pConfig->Param[nParamIndex].toAscii().data() + 1);
                    values.sort();
                    pResult->addItems(values);
                    pResult->setCurrentIndex(pResult->findText(pNode->szParam[nParamIndex]));
                }
                pResult->setToolTip(pConfig->Param[nParamIndex]);
            }
        }
        else
        {
            INT32 nParamIndex = index.column() - 1;
            const EVENT_CONFIG* pConfig = BTConfig::GetInstance().MatchEventConfig(pNode->szType);
            if (pConfig)
            {
                pResult->setToolTip(pConfig->ReferDesc);
            }
        }
        pResult->setMaxVisibleItems(32);
	}

	return pResult;
Exit0:
	SAFE_DELETE(pResult);

	return NULL;
}

void BTEditorDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{    
    QString str = index.model()->data(index, Qt::EditRole).toString();

    QComboBox* pComboBox = static_cast<QComboBox*>(editor);
	LOG_PROCESS_ERROR(pComboBox);

    pComboBox->setEditText(str);

Exit0:
	return;
}

void BTEditorDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QComboBox* pComboBox = static_cast<QComboBox*>(editor);
	LOG_PROCESS_ERROR(pComboBox);

	//if (!pComboBox->currentText().isEmpty())
	    model->setData(index, pComboBox->currentText(), Qt::EditRole);

Exit0:
	return;
}
