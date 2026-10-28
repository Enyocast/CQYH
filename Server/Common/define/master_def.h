/********************************************************************
	created:	28:2:2013   15:55
	file:		master_ms_def.h
	author:		Allan Tao
	
	purpose:	Mentorship system
*********************************************************************/


#ifndef _H_MASTER_DEF_H_
#define _H_MASTER_DEF_H_

#include "string_def.h"
#define MAX_STUDENT_NUM (5)                   // Maximum number of students
//#define MAX_STUD_APP_NUM    (8)         
//#define MAX_TEACHER_APP_NUM     (8)
#define GRADUATE_LEVEL (30)                     // Graduation level; congratulate the student on graduating when advancing from level 39 to 40
#define STUD_LEVEL_LOWER_LIMIT  (1)

//#define FIRE_STUDENT_CD (86400)                 // Cooldown before dismissing another student
#define REGET_MASTER_CD (86400)                 // Cooldown before choosing another mentor
#define APPLY_VALID_TIME (86400)                // Application validity period
#define SEND_MASTER_INFO_NUM (30)               // msg use
#define SEND_SOLO_INFO_NUM  (30)                // msg use
#define MAX_CZ_TEXT_LENGTH  (150 + 1)


#define MAX_MASTER_SEND_APP_NUM     (3)
#define MAX_MASTER_RECV_APP_NUM     (8)

enum MASTER_STATE
{
    MASTER_NONE = 0,
    MASTER_STUDENT = 1,
    MASTER_TEACHER = 2,

    MASTER_BECOME_TEACHER = 3,
};

// Additional level-up congratulation type
enum MASTER_CONG_TYPE
{
    MASTER_CONG_BEGIN       = 0,
    MASTER_CONG_BY_FREE     = 1,
    MASTER_CONG_BY_MONEY    = 2,
    MASTER_CONG_BY_GOLD     = 3,
    MASTER_CONG_END         = 4,
};

enum MASTER_TEACHER_APP_TYPE
{
    MTAT_FROM_COMMON,
    MTAT_FROM_TWITTER,      
};

// server use
enum MST_SUCCESS_RSP_TYPE
{
    MST_APPLY_RECRUIT_SUCC = 1,
    MST_CANCEL_RECRUIT_SUCC = 2,
};

enum MST_SYNC_GS_DATA_TYPE
{
    MST_SYNC_GS_CD      = 1,
    MST_SYNC_GS_TWITTER_CD ,
    MST_SYNC_PUNISH_EXP,
    MST_SYNC_MASTER_EXP_DEC,
};

#endif //_H_MASTER_DEF_H_



