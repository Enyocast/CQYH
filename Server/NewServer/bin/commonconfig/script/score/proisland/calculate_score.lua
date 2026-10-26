LoadPackage("common.pkg")
LoadPackage("gameworld.pkg")
LoadPackage("role.pkg")
LoadPackage("scene.pkg")
LoadPackage("score_def.pkg")


function CalculateScore(oRole)
	oRole:SetVariable(ervtFinishTimeScore, edsSSS);
	oRole:SetVariable(ervtFinishTimeScore, edsSSS);
    oRole:SetVariable(ervtKillAndAttackScore, edsSSS);    
    oRole:SetVariable(ervtAchievementScore, edsSSS);
	oRole:SetVariable(ervtTotalScore, edsSSS);
    oRole:SetVariable(ervtTotalExp, 0);
    oRole:SetVariable(ervtExpOfActivity, 0);
    oRole:SetVariable(ervtExpOfFirst, 0);
    oRole:SetVariable(ervtExpOfGuild, 0);
    oRole:SetVariable(ervtExpOfTeam, 0);
    oRole:SetVariable(ervtExpOfVip, 0);
    oRole:SetVariable(ervtMoneyType, 1);
    oRole:SetVariable(ervtMoneyCount, 0);
end