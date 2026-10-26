#include "stdafx.h"

#include "bt_manager.h"

#include "bt_config.h"

BTConfig BTConfig::ms_Instance;

BTConfig::BTConfig()
{
}

BTConfig::~BTConfig()
{
}

BTConfig& BTConfig::GetInstance(void)
{
    return ms_Instance;
}

const ACTION_CONFIG* BTConfig::FindActionConfig( const QString &action ) const
{
    //int ActionID = CBTManager::GetInstance().FindBTActionByName( arr.constData() );
    //return &aActionConfig[ActionID];
    for ( int i=0; i<sizeof(aActionConfig)/sizeof(aActionConfig[0]); ++i )
    {
        if ( action == aActionConfig[i].ActionName )
        {
            return &aActionConfig[i];
        }
    }
    return NULL;
}

const QStringList &BTConfig::GetActionList() const
{
    return ActionList;
}

const EVENT_CONFIG* BTConfig::MatchEventConfig( const QString &event, int* pnID ) const
{
    const EVENT_CONFIG* pConfig = NULL;
    for ( int i=0; i<sizeof(aEventConfig)/sizeof(aEventConfig[0]); ++i )
    {
        //if ( aEventConfig[i].EventName == event )
        if ( !aEventConfig[i].EventName.isEmpty() && 
             event.startsWith(aEventConfig[i].EventName) )
        {
            pConfig = &aEventConfig[i];
            if ( pnID )
            {
                QString str = event.mid( aEventConfig[i].EventName.length() + 1 ); // +1 skip "_"
                (*pnID) = str.toInt();
            }
            break;
        }
    }
    return pConfig;
}

const QStringList &BTConfig::GetEventList() const
{
    return EventList;
}

#define REG_EVENT(array, action) strxcpy(array[action], #action, sizeof(array[action]))

bool BTConfig::LoadConfigFile(void)
{
    BOOL nRetCode = CBTManager::GetInstance().Init();
    if ( !nRetCode )
    {
        return false;
    }

    REG_EVENT(aEventName, evtAIBegin);
    REG_EVENT(aEventName, evtAIInit);
    REG_EVENT(aEventName, evtAIIdle);
    REG_EVENT(aEventName, evtAIFight);
    REG_EVENT(aEventName, evtAIDie);
    REG_EVENT(aEventName, evtAIInteract);
    REG_EVENT(aEventName, evtAIEnd);

    REG_EVENT(aEventName, evtSceneBegin);
    REG_EVENT(aEventName, evtSceneInit);
    REG_EVENT(aEventName, evtEnterScene); 
    REG_EVENT(aEventName, evtLeaveScene);     
    REG_EVENT(aEventName, evtTouchVolume);     
    REG_EVENT(aEventName, evtSingleNpcDie);                        
    REG_EVENT(aEventName, evtMediumGroupDie);                         
    REG_EVENT(aEventName, evtLargeGroupDie);                         
    REG_EVENT(aEventName, evtRoleInteract);  
    REG_EVENT(aEventName, evtRoleDie);   
    REG_EVENT(aEventName, evtSceneEnd);

    const char* pActionFile = "bteditor/MMOBTNode.ini";
    nRetCode = BTConfig::GetInstance().LoadActionConfigFile( pActionFile );
    LOG_PROCESS_ERROR(nRetCode);

    const char* pEventFile = "bteditor/MMOBTEvent.ini";
    nRetCode = BTConfig::GetInstance().LoadEventConfigFile( pEventFile );
    LOG_PROCESS_ERROR(nRetCode);

Exit0:
    return nRetCode;
}
bool BTConfig::LoadActionConfigFile(const QString &filename)
{
    Q_ASSERT( ! filename.isEmpty());

    QSettings *settings = new QSettings(filename, QSettings::IniFormat);
    if ( NULL == settings )
    {
        return false;
    }

    //QString action = settings->value("/batRandom/BTEdit").toString();

    QStringList groups = settings->childGroups();
    for ( int i=0; i<groups.count(); ++i )
    {
        QString action = groups[i];

        QByteArray arr = action.toLatin1();
        int ActionID = CBTManager::GetInstance().FindBTActionByName( arr.constData() );
        if( ActionID > 0 )
            //if ( action.indexOf( QRegExp("^bat\\w*$")) >= 0 )
        {
            if (aActionConfig[ActionID].ActionName[0] != '\0' )
            {
                // duplicated config!
                return false;
            }

            strxcpy(aActionConfig[ActionID].ActionName, action.toAscii(), sizeof(aActionConfig[ActionID].ActionName) );
            aActionConfig[ActionID].BTEdit = settings->value( groups[i] + "/BTEdit" ).toString();
            aActionConfig[ActionID].Param[0] = settings->value( groups[i] + "/p0" ).toString();
            aActionConfig[ActionID].Param[1] = settings->value( groups[i] + "/p1" ).toString();
            aActionConfig[ActionID].Param[2] = settings->value( groups[i] + "/p2" ).toString();
            aActionConfig[ActionID].Param[3] = settings->value( groups[i] + "/p3" ).toString();
        }
    }

    for ( int i=0; i<sizeof(aActionConfig)/sizeof(aActionConfig[0]); ++i )
    {
        if ( aActionConfig[i].ActionName[0] != '\0' )
        {
            ActionList << aActionConfig[i].ActionName;
        }
    }

    return true;
}

int BTConfig::FindBTEventByName( const QString &event ) const
{
    for (int i=0; i<sizeof(aEventName)/sizeof(aEventName[0]); ++i)
    {
        if (event == aEventName[i])
        {
            return i;
        }
    }
    return -1;
}

bool BTConfig::LoadEventConfigFile(const QString &filename)
{
    Q_ASSERT( ! filename.isEmpty());

    QSettings *settings = new QSettings(filename, QSettings::IniFormat);
    if ( NULL == settings )
    {
        return false;
    }

    QStringList groups = settings->childGroups();
    for ( int i=0; i<groups.count(); ++i )
    {
        QString event = groups[i];

        QByteArray arr = event.toLatin1();
        int EventID = FindBTEventByName( arr.constData() );
        if( EventID > 0 )
            //if ( action.indexOf( QRegExp("^evt\\w*$")) >= 0 )
        {
            if (!aEventConfig[EventID].EventName.isEmpty() )
            {
                // duplicated config!
                return false;
            }

            aEventConfig[EventID].EventName = event;
            aEventConfig[EventID].BTEdit = settings->value( groups[i] + "/BTEdit" ).toString();
            aEventConfig[EventID].ReferDesc = settings->value( groups[i] + "/Refer" ).toString();
        }
    }

    for ( int i=0; i<sizeof(aEventConfig)/sizeof(aEventConfig[0]); ++i )
    {
        if ( aEventConfig[i].EventName[0] != '\0' )
        {
            EventList << aEventConfig[i].EventName;
        }
    }

    return true;
}
