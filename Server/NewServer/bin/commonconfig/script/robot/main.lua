LoadPackage("asimov_user.pkg")
LoadPackage("asimov_user_mgr.pkg")
LoadPackage("role.pkg")
LoadPackage("msg.pkg")
LoadPackage("ai.pkg")
LoadPackage("score_def.pkg")
LoadPackage("char_def.pkg")
LoadPackage("teleport.pkg")
LoadPackage("scene.pkg")
LoadPackage("gameworld.pkg")
LoadPackage("spell.pkg")
LoadPackage("spell_book.pkg")
LoadPackage("robot_message_handler.pkg")
LoadPackage("asimov_message_handler.pkg")
LoadPackage("variable.pkg")

gameworld = CGameWorld:GetInstance();
g_RobotMessageHandler = CRobotMessageHandler:GetInstance();
g_AsimovMessageHandler = CAsimovMessageHandler:GetInstance();
g_user_mgr = CUserMgr:GetInstance();


--SERVER_IP_ADDR = "172.30.66.22"
SERVER_IP_ADDR = "127.0.0.1"
--SERVER_IP_ADDR = "172.30.66.32"
SERVER_PORT = 8701
GROUP_ID = g_user_mgr:GetDefaultGroupID();

Include("script/robot/coroutine.lua")
Include("script/robot/show.lua")
Include("script/robot/util.lua")
Include("script/test_case/test_case.lua")
