#ifndef _BT_CONFIG_H_
#define _BT_CONFIG_H_

#include "btnod.h"      //MAX_BT_PARAM
#include "bt_action.h"  //batEnd
#include "bt_event.h"   //evtTotal

struct ACTION_CONFIG
{
    char ActionName[256];
    QString BTEdit;
    QString Param[MAX_BT_PARAM];
    QStringList ParamEnumName[MAX_BT_PARAM];
};

struct EVENT_CONFIG
{
    QString EventName;
    QString BTEdit;
    QString ReferDesc;
};

class BTConfig
{
public:
    BTConfig();
    ~BTConfig();

    static BTConfig& GetInstance(void);

    bool LoadConfigFile(void);

    const ACTION_CONFIG* FindActionConfig( const QString &action ) const; 
    const QStringList &GetActionList() const; 

    const EVENT_CONFIG* MatchEventConfig( const QString &event, int* pnID = NULL ) const; 
    const QStringList &GetEventList() const; 

protected:
    bool LoadActionConfigFile(const QString &filename);
    bool LoadEventConfigFile(const QString &filename);
    int FindBTEventByName( const QString &event ) const;

private:
    static BTConfig       ms_Instance;

    char aEventName[evtTotal][256];

    ACTION_CONFIG aActionConfig[batEnd];
    QStringList ActionList;
    EVENT_CONFIG aEventConfig[evtTotal];
    QStringList EventList;
};

#endif //_BT_CONFIG_H_