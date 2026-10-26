NewRoleConfig = {
    nSceneTempID = 186,
    nX = 8800,
    nY = 10600,
    nZ = 4748,
    wFaceDirection = 5120,

    MaleNewEquip = {
	-- 战士 --
        [0] = {
            nMainHand = 99900001,
      --      nHead = 0,
      --      nShoulder = 0,
            nBody = 99980113,
      --      nArm = 0,
      --      nWaist = 0,
      --      nFoot = 0,
	  --      nBack = 0
        },
	-- 法师 --
        [1] = {
            nMainHand = 99900001,
      --       nHead = 0,
      --       nShoulder = 0,
            nBody = 99980113,
      --       nArm = 0,
      --       nWaist = 0,
      --       nFoot = 0,
      --       nBack = 0
        },
	-- 刺客 --
        [2] = {
             nMainHand = 99900001,
      --       nHead = 0,
      --       nShoulder = 0,
            nBody = 99980113,
      --       nArm =0 ,
      --       nWaist =0 ,
      --       nFoot =0 ,
      --       nBack = 0
        },
	-- 弓手 --
        [3] = {
            nMainHand = 99900001,
	  --       nHead = 0,
      --       nShoulder = 0,
            nBody = 99980113,
      --       nArm = 0,
      --       nWaist = 0,
      --       nFoot = 0,
      --       nBack = 0
        },
	-- 道士 --
        [4] = {
            nMainHand = 99900001,
      --       nHead = 0,
      --       nShoulder = 0,
            nBody = 89980113,
      --       nArm = 0,
      --       nWaist = 0,
      --       nFoot = ,
      --       nBack = 0
        },
	},
    FemaleNewEquip = {
 	-- 战士 --
        [0] = {
            nMainHand = 99900001,
      --       nHead = 0,
      --       nShoulder = 0,
            nBody = 99990113,
      --       nArm = 0,
      --       nWaist = 0,
      --       nFoot = 0,
      --       nBack = 0
        },
	-- 法师 --
        [1] = {
            nMainHand = 99900001,
      --       nHead = 0,
      --       nShoulder = 0,
            nBody = 99990113,
      --       nArm = 0,
      --       nWaist = 0,
      --       nFoot = 0,
      --       nBack = 0
        },
 	-- 刺客 --
       [2] = {
             nMainHand = 99900001,
      --       nHead = 0,
      --        nShoulder = 0,
            nBody = 99990113,
      --       nArm = 0,
      --       nWaist = 0,
      --       nFoot = 0,
      --       nBack = 0
        },
 	-- 弓手 --
       [3] = {
            nMainHand = 99900001,
      --       nHead = 0,
      --       nShoulder = 0,
            nBody = 99990113,
      --       nArm = 0,
      --       nWaist = 0,
      --       nFoot = 0,
      --       nBack = 0
        },
	-- 道士 --
        [4] = {
            nMainHand = 99900001,
      --       nHead = 0,
      --       nShoulder = 0,
            nBody = 99990113,
      --       nArm = 0,
      --       nWaist = 0,
      --       nFoot = 0,
      --       nBack = 0
        },
	}
};

NewRoleConfig.nX, NewRoleConfig.nY, NewRoleConfig.nZ =
	ConvertCoordO2N(NewRoleConfig.nX, NewRoleConfig.nY, NewRoleConfig.nZ);
