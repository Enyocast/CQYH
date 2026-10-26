
virtual void PreOnShow(UBOOL show);
virtual void PostOnShow(UBOOL v);
UBOOL FillUiDataForSkillLearned( INT uniqueSkillID, FString &asTitle, FString &asContent, FString &asIconPath, FString &asExtraString );
UBOOL FillUiDataForSkillLevelUp( INT uniqueSkillID, FString &asTitle, FString &asContent, FString &asIconPath, FString &asExtraString );
UBOOL FillUiDataForSkillSlotUnlock( INT slotIdx, FString &asTitle, FString &asContent, FString &asIconPath, FString &asExtraString );
UBOOL FillUiDataForFBDifficultyUnlock( INT curFbMapID, FString &asTitle, FString &asContent, FString &asIconPath, FString &asExtraString );
UBOOL FillUiDataForFBAchievements( INT fbAchieveID, FString &asTitle, FString &asContent, FString &asIconPath, FString &asExtraString );