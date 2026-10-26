#include "stdafx.h"

#include <QLabel>

#include "bt_config.h"
#include "bt_item_param_label.h"


BTItemParamLabel::BTItemParamLabel(QWidget *parent, Qt::WFlags flags)
    : QLabel( parent )
    , m_siblingRank(-1)
{}

int BTItemParamLabel::siblingRank()
{
    return m_siblingRank;
}

void BTItemParamLabel::SetSiblingRank(int rank)
{
    m_siblingRank = rank;
}

void BTItemParamLabel::UpdateText(const QString &text)
{
    clear();

    const ACTION_CONFIG* pConfig = BTConfig::GetInstance().FindActionConfig( text );
    if ( pConfig )
    {
        //assert( m_siblingRank < sizeof(pConfig->Param)/sizeof(pConfig->Param[0]) );
        if( !pConfig->Param[ m_siblingRank ].isEmpty() )
        {
            setText( pConfig->Param[ m_siblingRank ] );
        }
    }

    return ;
}
