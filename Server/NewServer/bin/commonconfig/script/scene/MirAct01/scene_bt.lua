
evtEnterScene = 
{ batSequencer,
	{ batRoleCheckRoleVariable  , param = { boNEQ , 182 , 1 } }, 
	{ batRoleCheckMoney , param = { boGTE , 1 , 10000 } },
	{ batRoleSubMoney , param = { tarRole , 1 , 10000, MONEYLOG_BT_02 } },
	{ batRoleSetRoleVariable , param = { 182 , 1 } },
	{ batRoleSetRoleVariable, param = { 220, 'CGameWorld:GetInstance():GetGameTime()', 0 } },
    { batRoleCheckDailyVariable, param = { 222 } },
	{ batRoleAddActivityPts , param = { 40 , aprWuDouChang } },
	{ batRoleUpdateDailyVariable, param = { 222 } },    												
};

evtRoleDie  =  
{ batSequencer,
	{ send_kill_info },
};
