LoadPackage("robot_message_handler.pkg")
LoadPackage("scene_def.pkg")

TestCase.GM = {};

GMList = {
	{ user_name = "GM0101", role_name = "GM0101", group = 1, class  = clsWarrior, sex = cstMale },
	{ user_name = "GM0102", role_name = "GM0102", group = 2, class  = clsMage, sex = cstFemale },
	{ user_name = "GM0103", role_name = "GM0103", group = 3, class  = clsTaoist, sex = cstMale },
};

function TestCase.GM.CreateGMRole()
	for i, v in pairs(GMList) do
		local user, role = startup(v.user_name, v.role_name, v.group, v.class, v.sex);
		wait(5);
		cleanup(user);
		wait(5);
	end
end








