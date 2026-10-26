

#ifndef _H_UI_EXCHANGE_HISTORY_H_
#define _H_UI_EXCHANGE_HISTORY_H_

#include <QtWidgets/QLabel>
#include "gm_def.h"

class CExchangeHistoryUI : public QLabel
{
public:
    CExchangeHistoryUI(QWidget *parent = 0, Qt::WindowFlags flags = 0);
    ~CExchangeHistoryUI();

    BOOL    UnInit();
    BOOL    SetData(INT32 nCount, const char *pcBuffer);

    void paintEvent(QPaintEvent *event);
    void wheelEvent(QWheelEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    INT32       m_nKWidth;
    INT32       m_nKInterval;

    INT32       m_nShowIndex;
    INT32       m_nMouseX;
    INT32       m_nMouseY;

    INT32       m_nVolumeMin;
    INT32       m_nVolumeMax;
    double      m_lfVolumeUnit;

    INT32       m_nBaseLowY;
    INT32       m_nBaseHighY;

    double      m_lfUnit;

    INT32                       m_nCount;
    GM_EXCHANGE_PRICE_HISTORY   m_Data[MAX_EXCHANGE_HISTORY_NUM];
};










#endif //_H_UI_EXCHANGE_HISTORY_H_
