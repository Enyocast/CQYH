#ifndef anti_cheat_h__
#define anti_cheat_h__

#include "dds_def.h"

struct JigsawImage
{
	INT32 nImageIndex;
	UINT64 qwBlock[JIGSAW_PIC_WIDTH_IN_BLOCK][JIGSAW_PIC_WIDTH_IN_BLOCK];	// 32 x 32 blocks
};

struct JigsawSingleAnswer
{
	UINT64 qwBlock[JIGSAW_ANSWER_WIDTH_IN_BLOCK][JIGSAW_ANSWER_WIDTH_IN_BLOCK];
};

struct JigsawAnswer
{
	INT32 nAnswerIdx;
	INT32 nBlockX;
	INT32 nBlockY;

	JigsawSingleAnswer Answer[JIGSAW_ANSWER_COUNT];
};

class CAntiCheatMgr
{
public:
	CAntiCheatMgr(void);
	virtual ~CAntiCheatMgr(void);

	static CAntiCheatMgr& GetInstance(void);

	BOOL Init(void);
	void UnInit(void);

	BOOL GenerateJigsaw(JigsawImage* poImg, JigsawAnswer* poAnswer);

protected:
	BOOL _ProcessDDS(const char* szFileName);

private:
	static CAntiCheatMgr ms_Instance;

	typedef std::vector<JigsawImage*> TPicDataList;
	TPicDataList m_List;
};


#endif // anti_cheat_h__
