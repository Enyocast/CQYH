#include "stdafx.h"
#include "ui_exchange_history.h"

#define VOLUME_HEIGHT       (115)
#define KVOLUMEDISTANCE     (10)
#define VOLUME_TEXT_HEIGHT  (15)
#define KTEXT_WIDTH         (30)
#define KTEXT_HEIGHT        (12)
#define HEIGHT_TOP_OFFSET   (10)

#define K_WIDTH         (6)
#define K_INTERVAL      (2)



CExchangeHistoryUI::CExchangeHistoryUI(QWidget *parent, Qt::WindowFlags flags)
    : QLabel(parent, flags)
{
    setMouseTracking(true);
    
    m_nShowIndex = -1;

    m_nKInterval = K_INTERVAL;
    m_nKWidth = K_WIDTH;
}

CExchangeHistoryUI::~CExchangeHistoryUI()
{
}

BOOL CExchangeHistoryUI::UnInit()
{
    m_nBaseLowY = 0;
    m_nBaseHighY = 0;

    m_lfUnit = 0.0;

    m_nCount = 0;
    memset(m_Data, 0, sizeof(m_Data));

    return TRUE;
}

BOOL CExchangeHistoryUI::SetData(INT32 nCount, const char *pcBuffer)
{
    GM_EXCHANGE_PRICE_HISTORY   *pHistory = NULL;
    LOG_PROCESS_ERROR(pcBuffer);

    pHistory = (GM_EXCHANGE_PRICE_HISTORY *)pcBuffer;

    memset(m_Data, 0, sizeof(m_Data));

    m_nBaseLowY = 0x7FFFFFFF;
    m_nBaseHighY = 0;
    m_nVolumeMin = 0x7FFFFFFF;
    m_nVolumeMax = 0;
    m_lfUnit = 0.0;

    m_nCount = nCount;

    for (INT32 i = 0; i < nCount; ++i)
    {
        m_Data[i] = pHistory[i];
    }

    repaint();

    return TRUE;
Exit0:
    return FALSE;
}

INT32 GetInterval(INT32 nWidth, INT32 nOldValue)
{
    switch (nWidth)
    {
    case 3:
        return 1;
    case 6:
        return 2;
    case 12:
        return 3;
    case 18:
        return 6;
    case 24:
        return 8;
    case 30:
        return 10;
    case 36:
        return 14;
    case 42:
        return 18;
    default:
        return nOldValue;
    }
}

void CExchangeHistoryUI::wheelEvent(QWheelEvent*event)
{
    QPoint qAD = event->angleDelta();

    if (qAD.y() > 0)
    {
        ++m_nKWidth;

        if (m_nKWidth > 48)
            m_nKWidth = 48;

        m_nKInterval = GetInterval(m_nKWidth, m_nKInterval);
    }
    else if (qAD.y() < 0)
    {
        --m_nKWidth;

        if (m_nKWidth < 1)
            m_nKWidth = 1;

        m_nKInterval = GetInterval(m_nKWidth, m_nKInterval);
    }

    repaint();
    return;
}


void CExchangeHistoryUI::mouseMoveEvent(QMouseEvent *event)
{
    INT32       HEIGHT_LIMIT = height() - VOLUME_HEIGHT;
    INT32       WIDTH_LIMIT = width() - KTEXT_WIDTH;
    INT32       K_NUM = WIDTH_LIMIT / (m_nKWidth + m_nKInterval);
    INT32       nX = 1;
    INT32   nHeight = height() ;

    m_nShowIndex = -1;
    m_nMouseX = event->x();
    m_nMouseY = event->y();

    if (m_nMouseX > WIDTH_LIMIT)
    {
        m_nMouseX = 0;
        m_nMouseY = 0;
    }

    //if (event->y() > HEIGHT_LIMIT && event->y() < (nHeight - VOLUME_TEXT_HEIGHT))
    {
        INT32       nIndex = 0;
        if (m_nCount > K_NUM)
            nIndex = m_nCount - K_NUM;
        else
            nIndex = 0;
        for (INT32 i = 0; nIndex < m_nCount; ++i, ++nIndex)
        {
            GM_EXCHANGE_PRICE_HISTORY   &rd = m_Data[nIndex];

            if (m_nMouseX >= nX && m_nMouseX < (nX + m_nKWidth + m_nKInterval))
            {
                m_nShowIndex = nIndex;   
            }

            //
            nX += m_nKInterval;
            nX += m_nKWidth;
        }
    }
        
    if (m_nCount > 0)
        repaint();

    return;
}

void CExchangeHistoryUI::paintEvent(QPaintEvent *event)
{
    INT32       HEIGHT_LIMIT = height() - KVOLUMEDISTANCE  - VOLUME_HEIGHT;
    INT32       WIDTH_LIMIT = width() - KTEXT_WIDTH;
    
    INT32       K_NUM = WIDTH_LIMIT / (m_nKWidth + m_nKInterval);

    INT32       K_LINE_NUM = 12;
    INT32       K_LINE_DISTANCE = 50;
    QPainter    painter(this);
    QPen        dash_pen;
    QPen        red_full_pen;
    QPen        white_full_pen;

    dash_pen.setWidth(1);
    dash_pen.setColor(QColor(176, 0, 0));
    red_full_pen.setColor(QColor(176, 0, 0));
    white_full_pen.setColor(QColor(255, 255, 255));

    double lfPriceUnit = (m_nBaseHighY - m_nBaseLowY) / (HEIGHT_LIMIT - HEIGHT_TOP_OFFSET);

    INT32       nMax = 0;
    INT32       nMin = 0x7FFFFFFF;

    INT32       nTempIndex = 0;
    if (m_nCount > K_NUM)
        nTempIndex = m_nCount - K_NUM;
    else
        nTempIndex = 0;
    for (; nTempIndex < m_nCount; ++nTempIndex)
    {
        if (nMax < m_Data[nTempIndex].nHigh)
            nMax = m_Data[nTempIndex].nHigh;
        if (nMin > m_Data[nTempIndex].nLow)
            nMin = m_Data[nTempIndex].nLow;

        if (m_nVolumeMax < m_Data[nTempIndex].nVolume)
            m_nVolumeMax = m_Data[nTempIndex].nVolume;
        if (m_nVolumeMin > m_Data[nTempIndex].nVolume)
            m_nVolumeMin = m_Data[nTempIndex].nVolume;
    }


    m_nBaseLowY = ((nMin / 10) - 1) * 10;
    m_nBaseHighY = ((nMax / 10) + 1) * 10;

    m_nBaseLowY = m_nBaseLowY > 0 ? m_nBaseLowY : 0;
    m_nBaseHighY = m_nBaseHighY > 0 ? m_nBaseHighY : 0;



    if (m_nBaseHighY - m_nBaseLowY)
        m_lfUnit = (double)(HEIGHT_LIMIT - HEIGHT_TOP_OFFSET) / (m_nBaseHighY - m_nBaseLowY);
    else
        m_lfUnit = 1;

    if (m_nVolumeMax - m_nVolumeMin)
        m_lfVolumeUnit = (double)(VOLUME_HEIGHT - VOLUME_TEXT_HEIGHT - HEIGHT_TOP_OFFSET) / (m_nVolumeMax - m_nVolumeMin);
    else
        m_lfVolumeUnit = 1.0;

    K_LINE_NUM = (HEIGHT_LIMIT - HEIGHT_TOP_OFFSET) / K_LINE_DISTANCE;
    --K_LINE_NUM;
    K_LINE_DISTANCE = (HEIGHT_LIMIT - HEIGHT_TOP_OFFSET) / K_LINE_NUM;

    // init widget
    QPalette    palette;
    palette.setColor(QPalette::Background, QColor(0, 0, 0));
    setPalette(palette);
    setAutoFillBackground(true);

    QVector<qreal>  dashes;
    qreal   space = 3;
    dashes << 1 << space;
    dash_pen.setDashPattern(dashes);

    painter.setPen(dash_pen);

    for (INT32 i = 0; i < K_LINE_NUM + 1; ++i)
    {
        INT32   nHeight = K_LINE_DISTANCE * i + HEIGHT_TOP_OFFSET;
        painter.drawLine(QLine(0, nHeight, WIDTH_LIMIT, nHeight));
    }
    
    // volume
    INT32   VOLUME_LINE_NUM = 5;
    INT32   VOLUME_LINE_DISTANCE = (VOLUME_HEIGHT - VOLUME_TEXT_HEIGHT - HEIGHT_TOP_OFFSET) / VOLUME_LINE_NUM;
    for (INT32 i = 0; i < VOLUME_LINE_NUM; ++i)
    {
        INT32   nHeight = height() - VOLUME_TEXT_HEIGHT - VOLUME_LINE_DISTANCE * (i + 1);
        painter.drawLine(QLine(0, nHeight, WIDTH_LIMIT, nHeight));
    }

    painter.setPen(red_full_pen);
    painter.drawLine(QLine(0, height() - VOLUME_HEIGHT, width(), height() - VOLUME_HEIGHT));
    painter.drawLine(QLine(0, height() - VOLUME_TEXT_HEIGHT, width(), height() - VOLUME_TEXT_HEIGHT));
    painter.drawLine(QLine(width() - KTEXT_WIDTH, 0, width() - KTEXT_WIDTH, height()));


    // draw text
    if (m_nBaseHighY > 0)
    {
        double lfInterval = (double)((m_nBaseHighY - m_nBaseLowY) * 100 / K_LINE_NUM) / 100;
        QString qstr;
        painter.drawText(WIDTH_LIMIT, HEIGHT_LIMIT - HEIGHT_TOP_OFFSET, KTEXT_WIDTH, KTEXT_HEIGHT, Qt::AlignLeft, qstr.setNum((double)m_nBaseLowY / 100));

        for (INT32 i = 1; i < K_LINE_NUM + 1; ++i)
        {
            painter.drawText(WIDTH_LIMIT, HEIGHT_LIMIT - K_LINE_DISTANCE * i - HEIGHT_TOP_OFFSET, KTEXT_WIDTH, KTEXT_HEIGHT, Qt::AlignLeft, qstr.setNum((double)(m_nBaseLowY + lfInterval * i) / 100));
        }
    }

    if (m_nVolumeMax > 0)
    {
        double lfVolumeInterval = (double)(m_nVolumeMax - m_nVolumeMin) / K_LINE_NUM;

        for (INT32 i = 0; i < VOLUME_LINE_NUM; ++i)
        {
            double   lfNum = m_nVolumeMin + lfVolumeInterval * (i + 1);
            QString qstr;
            INT32   nHeight = height() - VOLUME_TEXT_HEIGHT - VOLUME_LINE_DISTANCE * (i + 1) - KTEXT_HEIGHT / 2;

            painter.drawText(WIDTH_LIMIT, nHeight, KTEXT_WIDTH, KTEXT_HEIGHT, Qt::AlignLeft, qstr.setNum(lfNum));
        }
    }
 
    // draw k lines
    QPen        pen;
    QColor      blackColor(0, 0, 0);
    QColor      greenColor(84, 255, 255);
    QColor      *pRc = &blackColor;
    pen.setWidth(1);

    const INT32     K_HEIGHT_LIMIT = K_LINE_NUM * K_LINE_DISTANCE + HEIGHT_TOP_OFFSET;

    INT32   nX = 1;
    INT32   nY = 0;
    INT32   nH = 0;

    INT32   n1;
    INT32   n2;
    INT32   n3;
    INT32   n4;

    INT32       nIndex = 0;
    if (m_nCount > K_NUM)
        nIndex = m_nCount - K_NUM;
    else
        nIndex = 0;

    for (INT32 i = 0; nIndex < m_nCount; ++i, ++nIndex)
    {
        GM_EXCHANGE_PRICE_HISTORY   &rd = m_Data[nIndex];

        n1 = rd.nLow;
        n4 = rd.nHigh;

        if (rd.nClose > rd.nOpen)       // 涨,红色
        {
            pen.setColor(QColor(255, 50, 50));
            pRc = &blackColor;

            n2 = rd.nOpen;
            n3 = rd.nClose;
        }
        else if (rd.nClose < rd.nOpen)      // 跌, 绿色
        {
            pen.setColor(QColor(84, 255, 255));
            pRc = &greenColor;

            n2 = rd.nClose;
            n3 = rd.nOpen;
        }
        else
        {
            pen.setColor(QColor(255, 255, 255));
            n1 = rd.nOpen;
            n2 = n1;
            n3 = rd.nLow;
        }

        painter.setPen(pen);


        // translate coordinate

        // draw volume
        INT32   nVolumeHeight = rd.nVolume * m_lfVolumeUnit;
        painter.drawRect(QRect(nX, height() - VOLUME_TEXT_HEIGHT - nVolumeHeight, m_nKWidth, nVolumeHeight));
        painter.fillRect(QRect(nX + 1, height() - VOLUME_TEXT_HEIGHT - nVolumeHeight + 1, m_nKWidth - 1, nVolumeHeight - 1), *pRc);

        if (m_nShowIndex  >= 0 && m_nShowIndex == nIndex)
        {
            const QPen    &old_pen = painter.pen();
            painter.setPen(white_full_pen);

            if (m_nMouseX > WIDTH_LIMIT - 110)
            {
                QString qstr(rd.szHistoryTime);
                painter.drawText(m_nMouseX - 110, height() - VOLUME_TEXT_HEIGHT, 110, VOLUME_TEXT_HEIGHT, Qt::AlignLeft, qstr);
            }
            else
            {
                QString qstr(rd.szHistoryTime);
                painter.drawText(m_nMouseX, height() - VOLUME_TEXT_HEIGHT, 110, VOLUME_TEXT_HEIGHT, Qt::AlignLeft, qstr);
            }
            
            if (m_nMouseY > height() - VOLUME_HEIGHT)
            {
                QString volumeStr;
                painter.drawText(WIDTH_LIMIT, m_nMouseY - KTEXT_HEIGHT, KTEXT_WIDTH, KTEXT_HEIGHT, Qt::AlignLeft, volumeStr.setNum(rd.nVolume));
            }
            else if (m_nMouseY < HEIGHT_LIMIT)
            {
                //QString volumeStr;
                //painter.drawText(WIDTH_LIMIT, m_nMouseY - KTEXT_HEIGHT, KTEXT_WIDTH, KTEXT_HEIGHT, Qt::AlignLeft, volumeStr.setNum((HEIGHT_LIMIT - m_nMouseY) * lfPriceUnit + m_nBaseLowY));
            }

            painter.setPen(old_pen);
        }

        // step 1.
        if (n1 < n2)
        {
            nY = (n1 - m_nBaseLowY) * m_lfUnit;
            nH = (n2 - m_nBaseLowY) * m_lfUnit - nY;
            nY = K_HEIGHT_LIMIT - nY;
            
            painter.drawLine(QLine(nX + m_nKWidth / 2, nY, nX + m_nKWidth / 2, nY - nH));
        }

        // step 2.
        if (rd.nClose != rd.nOpen)
        {
            nY = (n2 - m_nBaseLowY) * m_lfUnit;
            nH = (n3 - m_nBaseLowY) * m_lfUnit - nY;
            nY = K_HEIGHT_LIMIT - nY;

            painter.drawRect(QRect(nX, nY - nH, m_nKWidth, nH));
            painter.fillRect(QRect(nX + 1, nY - nH + 1, m_nKWidth - 1, nH - 1), *pRc);
        }
        else
        {
            nY = (n2 - m_nBaseLowY) * m_lfUnit;
            nY = K_HEIGHT_LIMIT - nY;

            painter.drawLine(QLine(nX, nY, nX + m_nKWidth, nY));
        }

        // step 3.
        if (n3 < n4)
        {
            nY = (n3 - m_nBaseLowY) * m_lfUnit;
            nH = (n4 - m_nBaseLowY) * m_lfUnit - nY;
            nY = K_HEIGHT_LIMIT - nY;

            painter.drawLine(QLine(nX + m_nKWidth / 2, nY, nX + m_nKWidth / 2, nY - nH));
        }

        //
        nX += m_nKInterval;
        nX += m_nKWidth;
    }
    
    if (m_nMouseX > 0 && m_nMouseY > 0 && m_nCount > 0)
    {
        painter.setPen(white_full_pen);

        painter.drawLine(QLine(m_nMouseX, 0, m_nMouseX, height()));
        painter.drawLine(QLine(0, m_nMouseY, width(), m_nMouseY));
    }



    painter.end();

}

