#include "stdafx.h"

#include "bt_config.h"
#include "bt_item_param_combobox.h"


BTItemParamComboBox::BTItemParamComboBox(QWidget *parent, Qt::WFlags flags)
    : QComboBox( parent )
    , m_siblingRank(-1)
{}

int BTItemParamComboBox::siblingRank()
{
    return m_siblingRank;
}

void BTItemParamComboBox::SetSiblingRank(int rank)
{
    m_siblingRank = rank;
}

void BTItemParamComboBox::InitText(const QString &action, const QString &text)
{
    m_action = action;
    m_initString = text;
}

void BTItemParamComboBox::UpdateEditText(const QString &text)
{
    if ( text == m_action )
    {
        setEditText(m_initString);
        return ;
    }

    clear();

    const ACTION_CONFIG* pConfig = BTConfig::GetInstance().FindActionConfig( text );
    if ( pConfig )
    {
        //assert( m_siblingRank < sizeof(pConfig->Param)/sizeof(pConfig->Param[0]) );
        if ( pConfig->ParamEnumName[ m_siblingRank ].length() > 0 )
        {
            addItems( pConfig->ParamEnumName[ m_siblingRank ] );

            QString text = currentText();
            int index = findText( text );
            if ( index >= 0 )
            {
                setCurrentIndex( index );
            }
        }
        else if( !pConfig->Param[ m_siblingRank ].isEmpty() )
        {
            addItem( pConfig->Param[m_siblingRank] );
        }
    }

    clearEditText();

    return ;
}
