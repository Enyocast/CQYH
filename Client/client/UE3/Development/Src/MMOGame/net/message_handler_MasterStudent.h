#ifndef __MESSAGE_HANDLER_MasterStudent_H__
#define __MESSAGE_HANDLER_MasterStudent_H__
public:
	/*
		请求可以当师傅的人员列表
		请求可以做徒弟的人员列表
		师傅请求进入招募徒弟状态
		师傅请求退出招募徒弟状态
	*/
	void Send_MasterListAck();
	void Send_SoloStudentListAck();
	void Send_ApplyRecruitStudent();
	void Send_CancelRecruitStudent();

	/*
		徒弟请求拜师 
		师傅同意  
		师傅拒绝
		徒弟自己取消拜师
	*/
	void Send_SubmitApplyToMaster( INT RoleId  ); 
	void Send_AgreeStudentdApply( INT RoleId  ); 
	void Send_RefuseStudentApply( INT RoleId  ); 
	void Send_CancelStudentApplyBySelf( INT RoleId  ); 
	
	/*
		师傅请求招收该徒弟   
		徒弟同意  
		徒弟拒绝
		师傅自己取消招收该徒弟
	*/
	void Send_SubmitApplyToStudent( INT RoleId ,UINT8 twitter = 0 ); 
	void Send_AgreeMasterdApply( INT RoleId  ); 
	void Send_RefuseMasterApply( INT RoleId  ); 
	void Send_CancelMasterApplyBySelf( INT RoleId  ); 
	
	/*
		背叛师门
		开除徒弟
		请求师傅信息
		发出祝贺信息
	*/
	void Send_LeaveMaster(); 
	void Send_FireStudent( INT RoleId  ); 
	void Send_GetMasterInfo();
	void Send_Congratulation(INT nRoleID,INT nTargetID,INT nConType,FString strCon,INT level);


	void Send_DesireGrad();
	void Send_AgreeGrad(INT nRoleID);
	void Send_ForceGrad();
	

	//推送相关
	void Send_Ignore(UINT32 nRoleId);
	void Send_Twitter(UINT8 twitter);

	//师徒经验
	void Send_QueryMasterExp();
	void Send_ReciveMasterExp(UINT32 roleId);

private:
	M_DECL_PARSE_FUN(g2c_sync_master);
	M_DECL_PARSE_FUN(m2c_master_sync_lvl);
	M_DECL_PARSE_FUN(m2c_master_recruit_list);
	M_DECL_PARSE_FUN(m2c_master_get_solo_list_ack);
	//M_DECL_PARSE_FUN(m2c_master_recruit_ack);

	/* 徒弟请求拜师系列消息回应*/
	M_DECL_PARSE_FUN(m2c_master_stud_submit_app_ack);
	M_DECL_PARSE_FUN(m2c_master_stud_submit_app_ntf);
	M_DECL_PARSE_FUN(m2c_master_agree_stud_app_ack); 
	M_DECL_PARSE_FUN(m2c_master_refuse_stud_app_ack);
	M_DECL_PARSE_FUN(m2c_master_refuse_stud_app_ntf);
	M_DECL_PARSE_FUN(m2c_master_cancel_stud_app_ack);
	M_DECL_PARSE_FUN(m2c_master_cancel_stud_app_ntf);

	/* 师傅请求收徒系列消息回应*/
	M_DECL_PARSE_FUN(m2c_master_teacher_submit_app_ack);
	M_DECL_PARSE_FUN(m2c_master_teacher_submit_app_ntf);
	M_DECL_PARSE_FUN(m2c_master_agree_teacher_app_ack);
	M_DECL_PARSE_FUN(m2c_master_refuse_teacher_app_ack);
	M_DECL_PARSE_FUN(m2c_master_refuse_teacher_app_ntf);
	M_DECL_PARSE_FUN(m2c_master_cancel_teacher_app_ack);
	M_DECL_PARSE_FUN(m2c_master_cancel_teacher_app_ntf);

	/*师门内部操作消息回应*/
	M_DECL_PARSE_FUN(m2c_master_leave_teacher_ack);
	M_DECL_PARSE_FUN(m2c_master_leave_teacher_ntf);
	M_DECL_PARSE_FUN(m2c_master_fire_student_ack);
	M_DECL_PARSE_FUN(m2c_master_fire_student_ntf);
	M_DECL_PARSE_FUN(m2c_master_add_student_ntf);
	M_DECL_PARSE_FUN(m2c_master_del_student_ntf);
	M_DECL_PARSE_FUN(m2c_master_clear_info);
	M_DECL_PARSE_FUN(m2c_master_info);
	M_DECL_PARSE_FUN(m2c_master_cz_level);
	M_DECL_PARSE_FUN(m2c_master_cz_ack);
	//M_DECL_PARSE_FUN(m2c_master_desire_grad_ack);
	//M_DECL_PARSE_FUN(m2c_master_desire_grad_ntf);
	M_DECL_PARSE_FUN(m2c_master_grad);

	M_DECL_PARSE_FUN(m2c_master_hello_teacher);
	M_DECL_PARSE_FUN(g2c_sync_master_reward_exp);
	M_DECL_PARSE_FUN(g2c_receive_master_reward_exp_ack);
	M_DECL_PARSE_FUN(m2c_master_twitter_ack);

#define M_INIT_MSGHANDLER_MASTER\
	MREG_PARSE_FUN(g2c_sync_master);\
	MREG_PARSE_FUN(m2c_master_sync_lvl);\
	MREG_PARSE_FUN(m2c_master_recruit_list);\
	MREG_PARSE_FUN(m2c_master_get_solo_list_ack);\
	MREG_PARSE_FUN(m2c_master_stud_submit_app_ack);\
	MREG_PARSE_FUN(m2c_master_stud_submit_app_ntf);\
	MREG_PARSE_FUN(m2c_master_agree_stud_app_ack);\
	MREG_PARSE_FUN(m2c_master_refuse_stud_app_ack);\
	MREG_PARSE_FUN(m2c_master_refuse_stud_app_ntf);\
	MREG_PARSE_FUN(m2c_master_cancel_stud_app_ack);\
	MREG_PARSE_FUN(m2c_master_cancel_stud_app_ntf);\
	MREG_PARSE_FUN(m2c_master_teacher_submit_app_ack);\
	MREG_PARSE_FUN(m2c_master_teacher_submit_app_ntf);\
	MREG_PARSE_FUN(m2c_master_agree_teacher_app_ack);\
	MREG_PARSE_FUN(m2c_master_refuse_teacher_app_ack);\
	MREG_PARSE_FUN(m2c_master_refuse_teacher_app_ntf);\
	MREG_PARSE_FUN(m2c_master_cancel_teacher_app_ack);\
	MREG_PARSE_FUN(m2c_master_cancel_teacher_app_ntf);\
	MREG_PARSE_FUN(m2c_master_leave_teacher_ack);\
	MREG_PARSE_FUN(m2c_master_leave_teacher_ntf);\
	MREG_PARSE_FUN(m2c_master_fire_student_ack);\
	MREG_PARSE_FUN(m2c_master_fire_student_ntf);\
	MREG_PARSE_FUN(m2c_master_add_student_ntf);\
	MREG_PARSE_FUN(m2c_master_del_student_ntf);\
	MREG_PARSE_FUN(m2c_master_clear_info);\
	MREG_PARSE_FUN(m2c_master_info);\
	MREG_PARSE_FUN(m2c_master_cz_ack);\
	MREG_PARSE_FUN(m2c_master_grad);\
	MREG_PARSE_FUN(m2c_master_cz_level);\
	MREG_PARSE_FUN(m2c_master_hello_teacher);\
	MREG_PARSE_FUN(g2c_sync_master_reward_exp);\
	MREG_PARSE_FUN(g2c_receive_master_reward_exp_ack);\
	MREG_PARSE_FUN(m2c_master_twitter_ack);
#endif
 