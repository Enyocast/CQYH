/********************************************************************
	Created:	2013/03/27
	Filename: 	StudentDetailManager
	file ext:	h
	Author:		hemu@snda
	Purpose:	师徒系统Model StudentDetailManager 管理当前的徒弟列表
*********************************************************************/
#ifndef _StudentDetailMANAGER_H_
#define _StudentDetailMANAGER_H_

#include "MMOSingleton.h"
#include "m2c_message.h"
#include "MMOUtil.h"

using namespace ExternalMessage;

#define M_DEBUG_StudentDetail 0

namespace MMO
{
	/*
	struct RECRUIT_StudentDetail_INFO
	{
	CHAR        szRoleName[ROLE_NAME_LEN];
	UINT8       byLevel;
	UINT8       byClass;
	UINT32      nStudentDetailID;
	UINT32      nStudentDetailExp;
	};
	*/

	typedef std::map<UINT32, struct ClientBriefStudentDetailInfo*, M_UE3_STL_ALLOC_MAP(UINT32, struct ClientBriefStudentDetailInfo*) > StudentDetailMap;
	typedef  M2C_MASTER_NTF_MST_INFO::MASTER_DATA MASTER_DATA;

	struct ClientBriefStudentDetailInfo : MASTER_DATA
	{
		//bool CanCongraluate;
		bool IsSelected;
	};

	class StudentDetailManager : public SingletonMeyers<StudentDetailManager>
	{
	public:

		StudentDetailManager();
		virtual ~StudentDetailManager();

		void Init();
		void Shutdown();
		void AddStudentDetail(struct M2C_MASTER_NTF_MST_INFO::MASTER_DATA* StudentDetail);
        //需要改动
		ClientBriefStudentDetailInfo* FindStudentDetail(UINT32 StudentDetailID) const;
		void DeleteItem(UINT32 inID);	
		//点击一位师傅
		void MarkStudentDetailSelected(UINT32 StudentDetailID, bool sel);
		//向选中的师傅提出拜师申请
		void ApplySelected();
		const StudentDetailMap& GetAllStudentDetails() const;
		void ClearAll();
		void SetUpdateStudentDetailListDelegate(FScriptDelegate fun);
		void NotifyUpdateStudentDetailList();

	protected:
		StudentDetailMap _StudentDetailMap;
		FScriptDelegate _UpdateStudentDetailListDelegate;
	};

} // MMO
#endif