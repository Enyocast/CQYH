/********************************************************************
	Created:	2013/03/27
	Filename: 	StudentManager
	file ext:	h
	Author:		hemu@snda
	Purpose:	师徒系统Model StudentManager 管理当前的请求拜师的徒弟
*********************************************************************/
#ifndef _StudentMANAGER_H_
#define _StudentMANAGER_H_

#include "MMOSingleton.h"
#include "MMOUtil.h"

#define M_DEBUG_Student 0

namespace MMO
{
	/*
	struct RECRUIT_Student_INFO
	{
	CHAR        szRoleName[ROLE_NAME_LEN];
	UINT8       byLevel;
	UINT8       byClass;
	UINT32      nStudentID;
	UINT32      nStudentExp;
	};
	*/

	struct ClientBriefStudentInfo : M2C_MASTER_ADD_APPLICANT
	{
		bool IsSelected;
	};

	//typedef std::map<UINT32, struct ClientBriefStudentInfo*, M_UE3_STL_ALLOC_MAP(UINT32, struct ClientBriefStudentInfo*) > StudentMap;
    typedef TMap< UINT32, struct ClientBriefStudentInfo* > StudentMap;
    typedef StudentMap::TIterator StudentMapIterator;

    
	class StudentManager : public SingletonMeyers<StudentManager>
	{
	public:
        
        //徒弟排序
        enum MasterSortType
        {
            EMST_NAME = 0,
            EMST_CLASS,
            EMST_LEVEL,
            EMST_EXP,
        };

		StudentManager();
		virtual ~StudentManager();

		void Init();
		void Shutdown();
		void AddStudent(struct M2C_MASTER_ADD_APPLICANT* Student);
		ClientBriefStudentInfo* FindStudent(UINT32 studentID);
		void DeleteItem(UINT32 inID);		
		//点击一位师傅
		void MarkStudentSelected(UINT32 studentID, bool sel);
		//向选中的师傅提出拜师申请
		void ApplySelected();
		const StudentMap& GetAllStudents() const;
		void ClearAll();
		void SetUpdateStudentListDelegate(FScriptDelegate fun);
		void NotifyUpdateStudentList();

        StudentMapIterator BeginIterator();
        void SortMembers(INT type);

	protected:
		StudentMap _StudentMap;
		FScriptDelegate _UpdateStudentListDelegate;
	};

} // MMO
#endif