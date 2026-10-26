#ifndef _CIRCLE_LIST_H_
#define _CIRCLE_LIST_H_

// This circle list is thread-safe for SISO
class CCircleList
{
public:
    CCircleList();
    ~CCircleList();

    BOOL Init(UINT32 dwSize);
    BOOL UnInit(void);

    BOOL Push(void* pData);
    void* Pop(void);
    void* Check(void);
    BOOL IsEmpty(void);

private:
    UINT32  m_dwSize;
    UINT32  m_dwHead;
    UINT32  m_dwRear;
    void**  m_ppData;
};

#endif  // _CIRCLE_LIST_H_