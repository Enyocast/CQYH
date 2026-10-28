#ifndef _ERROR_DEF_H_
#define _ERROR_DEF_H_

/// @enum ERROR_CODE_DEF
enum ERROR_CODE_DEF
{
    errUnknownError = 0,
	errSuccess = 1,   
    errCritical,
    errDatabase,

    errLoginBegin = 0x100,

    errLoginAuthFailed,             ///< Login authentication failed
    errLoginUnknownError,           ///< Unknown login error
    errLoginServerNotReady,         ///< Server is not ready
    errLoginRepeat,                 ///< Account already logged in
	errLoginRepeatKicked,           ///< Disconnected due to another login to the account
	errLoginErrorUserNameOrPassword,///< Incorrect username or password
	errLoginTooManyOnlineRole,		///< Online player limit exceeded
	errLoginLocked,					///< Player is locked; try again later
	errLoginPrecreate,				///< Game entry is unavailable during pre-creation
	errLoginErrorVersion,			///< Incorrect game version

	errLoginCreateRoleTooMany,      ///< Character creation limit exceeded
    errLoginCreateRoleDupeName,     ///< Duplicate character name (unexpected)
    errLoginCreateRoleCensoredWord, ///< Character name contains restricted words
    errLoginCreateRoleNameLength,   ///< Character name is too long
    errLoginCreateRoleNameServerNotConnected,   ///< Cannot connect to name service
    errLoginCreateRoleNsDupeName,   ///< Duplicate character name
    errLoginCreateRoleNsDbSysErr,   ///< Name database error

    errLoginDeleteRoleNotFound,     ///< Character to delete not found
    errLoginDeleteRoleDeleted,      ///< Character deletion failed: already deleted
    errLoginDeleteRoleMaster,       ///< A mentor cannot delete their character
    errLoginDeleteRoleGuild,        ///< A guild member cannot delete their character
    errLoginDeleteRoleAuction,      ///< Cannot delete a character with an active auction or bid
    errLoginDeleteRoleExchange,     ///< Cannot delete a character with an active exchange order
    errLoginUnDeleteRoleNotFound,   ///< Character to restore not found
    errLoginRoleBusy,               ///< Failed to read character data
    errLoginRoleFrozen,             ///< Character is frozen
    errLoginTimeUnknown,            ///< Game time balance is unknown
    errLogoutNotPermit,				///< Logout is not allowed
	errLoginTooManyUser,			///< Registered user limit reached

    errLoginWrongServer,            ///< Server is not activated; login is not allowed
    errLoginCreateRoleForeverDelete,///< Permanent character deletion is not allowed
    errLoginNeedDynamicPassword,    ///< Dynamic password verification required
    errLoginDynamicPasswordSuccess, ///< Dynamic password verification succeeded
    errLoginDynamicPasswordFailed,  ///< Dynamic password verification failed
    errLoginDynamicPasswordVerified,///< Dynamic password already verified; no need to verify again
    errLoginDynamicPasswordTooOften,///< Dynamic password verification attempted too frequently; try again later

	errLoginEnd,

	errMoveBegin = 0x200,
    errMoveFail,                    ///< Movement failed, usually due to an invalid state
	errMineFail,					///< Mining failed
	errMoveEnd,

	errJumpBegin = 0x300,
    errJumpWrongState,              ///< Cannot change scenes in the current state
    errJumpCasting,                 ///< Cannot change scenes while casting
    errJumpInCombat,                ///< Cannot change scenes during combat
    errJumpStallOpen,               ///< Cannot change scenes while operating a stall
    errJumpTrading,                 ///< Cannot change scenes while trading
	errJumpWrongItem,				///< Failed to use scene transfer scroll
	errJumpWrongPos,				///< Cannot transfer to the specified position
	errJumpSceneFobidden,			///< Scene transfers are prohibited in the current scene
	errJumpDead,					///< Cannot change scenes while dead
	errJumpArrest,					///< Cannot change scenes while imprisoned
	errJumpChangeLineBreak,			///< Line change interrupted
    errJumpEnd,

	errReviveBegin = 0x400,
	errReviveStillAlive,			///< Cannot revive: still alive
	errReviveLackOfItem,			///< Required revival item is missing
	errReviveInProgress,			///< Revival already in progress
	errReviveNoGraveyard,			///< Revival failed: no respawn point data
	errReviveForbidden,				///
	errReviveNotReady,				///
	errReviveUnknown,				///
	errReviveEnd,

	errSpellBegin = 0x500,
	errSpellCasting,		        ///< A spell is already being cast
	errSpellDisabled,		        ///< Spellcasting is disabled
	errSpellWeaponTypeError,        ///< Incorrect weapon type
	errSpellNotExists,		        ///< Spell does not exist
	errSpellNoTarget,		        ///< Target does not exist
	errSpellErrorType,		        ///< Incorrect spell type
	errSpellConditionError,	        ///< Spell conditions are not met
	errSpellCasterCCLimitBitsError,	///< Cannot cast while under crowd control
	errSpellCastNoMove,				///< Cannot cast while moving
	errSpellCastNoMount,			///< Cannot cast while mounted
	errSpellCastNoDead,				///< Cannot cast while dead
	errSpellCastNoLive,				///< Cannot cast while alive
	errSpellCastNoStiff,			///< Cannot cast while in hit stun
	errSpellCasterCheckNodeFailed,	///< Additional casting condition check failed

	errSpellInValidTargetRoleState, ///< Invalid target
	errSpellInValidTargetNodeError, ///< Invalid target
	errSpellInValidTargetDead,		///< Invalid target
	errSpellInValidTargetStance,	///< Invalid target
	errSpellInValidTargetRelationship, ///< Invalid target
	errSpellInValidTargetObjType,   ///< Invalid target
	errSpellInValidTargetNeverBeHit, ///< Invalid target

	errSpellInvalidDirection,		///< Invalid direction
	errSpellOutOfRange,		        ///< Target is out of range
	errSpellObstacled,		        ///< Line of sight is blocked
	errSpellOutOfMana,		        ///< Insufficient resources
	errSpellNotReady,		        ///< Spell is not ready
	errSpellInHardTime,		        ///< Cannot cast during post-attack recovery
	errSpellLackOfItem,		        ///< Required item is missing
	errSpellEquipDisabled,	        ///< Requirements for equipping the spell are not met
	errSpellCannotBeEquipped,	    ///< Spell cannot be equipped
	errSpellEquipBindSlot,	        ///< Spell must be equipped in its bound slot
	errSpellEquipPassiveSlotError,  ///< Passive spell must be equipped in a passive slot
	errSpellSlotError,		        ///< Spell slot does not exist
	errSpellSlotLocked,		        ///< Spell slot is locked
	errSpellSlotNoDuplicate,		///< Spell slots cannot be duplicated
	errSpellLearningClassError,		///< Cannot learn spell: incorrect class
	errSpellLearningLevelError,		///< Cannot learn spell: level requirement not met
	errSpellLearnt,					///< Cannot learn spell: already learned
	errRuneEquipError,		        ///< Error equipping rune
	errRuneEquipClassError,		    ///< Error equipping rune
	errRuneNotExists,		        ///< Rune does not exist
	errRuneNotActivated,	        ///< Rune is not activated
	errPracticeOutOfPts,			///< Spell upgrade: insufficient points
	errPracticeInProgress,			///< Cultivation is in progress
	errPracticeLevelTooLow,			///< Character level is too low for cultivation
	errPracticeAlreadyMax,			///< Spell is already at maximum level
	errSpellEquipNotReady,	        ///< Cannot equip a spell while it is on cooldown
	errSpellSceneLimit,		        ///< Scene difficulty restriction
	errSpellUnknown,		        ///< Unknown spell module error
	errSpellEnd,

	errAuraBegin = 0x600,
	errAuraCannotCancel,
	errAuraResisted,
	errAuraNotExist,
	errAuraConfigError,
	errAuraAppendFailed,
	errAuraEnd,

	errItemBegin = 0x700,
    errItemBagFull,                 ///< Bag is full
    errItemInvalidPos,              ///< Invalid item position (for example, slot 18 in a 16-slot bag); the client should prevent this
    errItemTypeMismatch,            ///< Invalid item type (for example, equipment placed in a material bag); the client should prevent this
    errItemEquipMismatch,           ///< Invalid equipment type (for example, shoes equipped on the head); the client should prevent this
    errItemUnsatisfied,             ///< Item level, class, sex, or other requirements are not met; the client should prevent this
    errItemCannotDestroy,           ///< Cannot destroy item; the client should prevent this
    errItemDropTooMany,             ///< Cannot destroy item because the current grid contains too many items
    errItemCannotUnEquip,           ///< Cannot unequip item; the client should prevent this
    errItemCannotSell,              ///< Cannot sell to NPC; the client should prevent this
    errItemNotFound,                ///< Item does not exist
    errItemNotEnough,               ///< Insufficient item quantity
    errItemBinded,                  ///< Item is bound and cannot be traded or mailed; the client should prevent this
    errItemCannotSplit,             ///< Item cannot be split, or the requested amount exceeds the stack; the client should prevent this
    errItemCannotUse,               ///< Item cannot be used; the client should prevent this
    errItemFull,                    ///< Stored-value item is full
    errItemNotFull,                 ///< Stored-value item is not full and cannot be used
    errItemExpBottleMaxTimes,       ///< Experience bottle use limit reached
    errItemWrongCombatState,        ///< Item combat-state requirement is not met
    errItemCannotUseInArena,        ///< Item cannot be used in the arena
    errItemNoNeedRepair,            ///< Item does not need repair
    errItemCannotRepair,            ///< Item cannot be repaired
    errItemMaxRefineLevel,          ///< Maximum enhancement level reached; the client should prevent this
    errItemRefineError,             ///< Insufficient enhancement materials; the client should prevent this
    errItemStall,                   ///< Cannot perform this item operation while running a stall; the client should prevent this
    errItemTrading,                 ///< Cannot perform this item operation while trading; the client should prevent this
    errItemNotEnoughExp,            ///< Insufficient experience
    errItemNotEnoughMoneytype01,    ///< Insufficient bound gold
    errItemNotEnoughMoneytype02,    ///< Insufficient gold
    errItemNotEnoughMoney,          ///< Insufficient currency
    errItemNotEnoughReputation,     ///< Insufficient reputation
    errItemNotEnoughBuildingLevel,  ///< Building level is too low
    errItemNotReady,                ///< Item is not ready
    errItemScriptUseFail,           ///< Script use failed
    errItemCannotFindScript,        ///< Specified script not found
    errItemCannotUpgradeSoul,       ///< Item cannot undergo soul upgrade
    errItemUpgradeSoulLimit,        ///< Soul is already at maximum level
    errItemCannotAddSoul,           ///< Item cannot receive a soul
    errItemAlreadySocketed,         ///< Socket already contains a soul
    errItemSocketNotMatch,          ///< Soul socket color does not match
    errItemNotSocketed,             ///< No soul to remove
    errItemRuneError,               ///< Item does not support inscription functions
    errItemRuneNotEnoughMaterial,   ///< Insufficient inscription stones
    errItemComposeError,            ///< Insufficient equipment crafting materials
    errItemRoleDead,                ///< Character is dead
    errItemRoleCombat,              ///< Character is in combat
    errItemEquipped,                ///< Cannot perform this operation on equipped items; the client should prevent this
    errItemDailyMoneyExceeded,      ///< Currency exceeds the daily limit
    errItemWeekMoneyExceeded,       ///< Currency exceeds the weekly limit
    errItemTotalMoneyExceeded,      ///< Currency exceeds the carrying limit
    errItemMaxLuck,                 ///< Blessing oil used on a weapon at maximum luck; the client should preferably prevent this
    errItemNotIdentified,           ///< Item is unidentified
    errItemAlreadyIdentified,       ///< Item is already identified
    errItemCannotSign,              ///< Item cannot be signed; the client should prevent this
    errItemNotSigned,               ///< Item is unsigned; the client should prevent this
    errItemAlreadySigned,           ///< Item is already signed; the client should prevent this
    errItemOthersSigned,            ///< Cannot equip an item signed by someone else; the client should prevent this
    errItemSelfSigned,              ///< Cannot auction an item signed by yourself; the client should prevent this
    errItemCannotAuction,           ///< Item cannot be auctioned; the client should prevent this
    errItemNotEnoughPkValue,        ///< Atonement charm error: insufficient PvP points
    errItemCannotLevelup,           ///< Cannot upgrade
    errItemLevelUpInProcess,        ///< Weapon upgrade in progress
    errItemLevelUpNotFinished,      ///< Weapon upgrade has not finished
    errItemDurLow,                  ///< Durability is too low
    errItemWeaponNotTried,          ///< Weapon has not been tested
    errItemNotEnoughBlackIron,      ///< Missing black iron
    errItemLevelupError,            ///< Invalid equipment upgrade material
    errItemNoLevelUp,               ///< No weapon upgrade in progress
    errItemWeaponTooHeavy,          ///< Weapon weight limit exceeded
    errItemArmorTooHeavy,           ///< Armor weight limit exceeded
    errItemBagTooHeavy,             ///< Bag weight limit exceeded
    errItemOpenPackageEarly,        ///< Gift pack opened before the allowed time
    errItemOpenPackageTooMany,      ///< Gift pack opening limit exceeded
    errItemRoleNotFound,			///< Unknown character name
    errItemNotSabacGuild,			///< Not a member of the Sabac guild
    errItemBlackMarketItemNotFound, ///< Black market item not found
    errItemBlackMarketNotFound,     ///< Black market shop not found
    errItemBlackMarketSold,         ///< Black market item sold out
    errItemBlackMarketCooldown,     ///< Black market item is on cooldown
    errItemMaterialWeaopn,          ///< Mining-refinement weapon not equipped or insufficient durability
    errItemNoExerciseTime,          ///< No forging experience available to claim
    errItemExerciseTimeNotEmpty,    ///< Remaining forging experience is not zero
    errItemCannotDecompose,         ///< Cannot decompose item; the client should prevent this
    errItemUnknown,                 ///< Unknown item module error
    errItemWeaponLevelUpTakeoutImmediatelyTooLate,///< Immediate weapon retrieval expired; normal retrieval is available
	errItemTooLowLevel,				///< Level too low to use
	errItemNoConsumeUse,			///< Not consumed on use
    errItemNotDoubleRune,           ///< Advanced inscription refinement requires a double inscription
    errItemNewbieRune,              ///< Advanced inscription refinement cannot be used on a beginner inscription
	errItemEnd,

	errMountBegin = 0x800,
	errMountOutOfItem,				///< Insufficient materials to activate the mount
	errMountAlreadyExists,			///< Mount already exists
	errMountLevelLimited,			///< Level is too low to activate the mount
	errMountNotExist,				///< Mount is not activated
	errMountAuraError,				///< Mount buff error
	errMountEnd,

	errDropBegin = 0x900,
    errDropNotFound,                ///< Drop does not exist
    errDropFaraway,                 ///< Too far away to reach
    errDropProtected,               ///< Another player’s drop; pickup is not permitted
	errDropOtherStand,				///< Cannot pick up the item while another player stands on it
    errDropFast,                    ///< Required time since the last successful pickup has not elapsed
    errDropBindied,                 ///< Cannot pick up an item bound to another player
    errDropIsBidding,               ///< Previous item auction has not ended
    errDropFcm,                     ///< Anti-addiction restriction is active
	errDropEnd,

	errShopBegin = 0xA00,
    errNotEnoughMoney,              ///< Insufficient currency
    errShopNotFound,                ///< Shop not found
    errShopItemNotFound,            ///< Shop item not found
    errShopTooMany,                 ///< Purchase quantity exceeds one stack; the client should prevent this
    errShopTypeSell,                ///< This shop does not buy the item; the client should prevent this
    errVipShopNotFound,             ///< VIP shop not found
	errShopEnd,

	errStallBegin = 0xB00,
    errStallWrongState,             ///< Invalid stall state
    errStallForbid,                 ///< Stalls are not allowed here
    errStallOthersOpen,             ///< Another player already has a stall here
    errStallWrongMoveState,         ///< Must stand still to open a stall
    errStallTrading,                ///< Cannot open a stall while trading
    errStallInvalidSlot,            ///< Invalid slot
    errStallSlotExist,              ///< Slot already contains an item
    errStallSlotNotExist,           ///< Slot contains no item
    errStallAlreadyInStall,         ///< Item is already listed
    errStallItemCountError,         ///< Listing quantity exceeds owned quantity
    errStallMoneyExceeded,          ///< Listing the item would exceed the currency limit
    errStallNotFound,               ///< Stall not found
    errStallFaraway,                ///< Stall is too far away
    errStallNotEnoughItems,         ///< Requested quantity exceeds the seller’s available quantity
    errStallItemExpired,            ///< Item to purchase has changed
	errStallEnd,
	
	errQuestBegin = 0xC00,
    errQuestAlreadyAccepted,        ///<  Quest is already accepted
    errQuestAlreadyCompleted,       ///<  Quest is already complete
    errQuestLogFull,                ///<  Quest log is full
    errQuestNotCompletePreQuest,    ///<  Prerequisite quest is incomplete
	errQuestTalkNpcTooFar,			///<  Too far from the dialogue NPC
	errQuestTalkNotCompleted,		///<  Dialogue is incomplete
    errQuestNpcTooFar,              ///<  Too far from the quest NPC
    errQuestSex,                    ///<  Quest acceptance sex requirement not met
    errQuestClass,                  ///<  Quest acceptance class requirement not met
    errQuestBuffNotFound,           ///<  Required buff not found
    errQuestLowReputation,          ///<  Reputation is too low
    errQuestHighReputation,         ///<  Reputation is too high
    errQuestTime,                   ///<  Quest cannot be accepted at this time
    errQuestLevel,                  ///<  Level requirement not met
    errQuestNotEnoughItem,          ///<  Insufficient quest items
    errQuestLimitVar,               ///<  Quest acceptance variable check failed
    errQuestNotEnoughMoney,         ///<  Insufficient money to accept the quest
    errQuestMaxCompleted,           ///<  Quest completion limit reached
    errQuestNotEnoughKill,          ///<  Required monster kill count not reached
    errQuestTooMuchMoney,           ///<  Wallet is full
    errQuestCanNotAbandon,          ///<  Quest cannot be abandoned
	errQuestShareUnavailable,		///<  Quest sharing failed
	errQuestNoShareTeam,			///<  Sharing team not found
	errQuestNoSharer,				///<  Quest sharer not found
	errQuestShareNotSameScene,		///<  Sharer and recipient are not on the same map
	errQuestCannotShare,			///<  Quest cannot be shared
	errQuestCannotFindScript,		///<  Quest script not found
    errQuestScriptUseFail,          ///<  Script use failed
	errQuestItemBagFull,			///<  Failed to add quest item because the bag is full
	errQuestTimeLimit,				///<  Timed quest expired
	errQuestZone,					///<  No quest is bound to the zone
	errQuestGrid,					///<  No quest is bound to the grid
	errQuestExplore,				///<  Exploration is incomplete
	errQuestVarIndex,				///<  Quest index configuration error
	errQuestSelectItemClass,		///<  Selected reward is unsuitable for the class
	errQuestCheckLevel,				///<  Level requirement for quest completion not met
	errQuestDailyCompleteFull,		///<  Daily quest completion limit reached
	errQuestDailyBrushCDTime,		///<  Daily quest cooldown has not elapsed
	errQuestDailyCompleteTimeOut,	///<  No daily quest attempts remain
	errQuestCircleDailyComplete,	///<  Cycle quest already completed today
	errQuestRewardQuestComplete,	///<  Daily bounty quest completion limit reached
	errQuestRewardBoughtTimeUp,		///<  Daily limit on bounty completion-limit purchases reached
	errQuestRecycle,				///<  Item recycling failed: no matching recycling quest
	errQuestNoMaster,				///<  Cannot accept quest without a mentor
	errQuestTeamMaster,				///<  Cannot accept quest: some team members do not have a mentor-student relationship
	errQuestCoolDown,				///<  Cannot accept quest: map cooldown has not elapsed
	errQuestKillPlayer,				///<  Cannot complete quest: insufficient player kills
	errQuestInCombat,				///<  Cannot accept or complete quest during combat
	errQuestKillBufPlayer,			///<  Cannot complete quest: required buffed player was not killed
	errQuestDoodad,					///<  Cannot complete quest: insufficient doodads collected
	errQuestCheckItem,				///<  Cannot complete quest: insufficient items
	errAcceptQuestScriptUseFail,	///<  Quest cannot be accepted
	errCompleteQuestScriptUseFail,	///<  Quest cannot be completed
	errQuestUnknownError,			///<  Unknown quest error
	errQuestEnd,

	errNpcBegin = 0xD00,
    errNpcNotFound,                 ///<  NPC not found
    errNpcTooFar,                   ///<  Player is too far from the NPC
    errNpcOpponentTarget,           ///<  Cannot interact with an enemy
    errNpcDataNil,                  ///<  Invalid NPC at this position
    errNpcDialogTimeout,            ///<  NPC dialogue timed out
    errNpcNoSuchFunction,           ///<  NPC does not provide this function
    errNpcInCombat,                 ///<  Cannot talk to the NPC during combat
	errNpcEnd,

	errDoodadBegin = 0xE00,
    errDoodadNotExist,              ///<  Doodad does not exist
    errDoodadOutOfRange,            ///<  Doodad is too far away
    errDoodadCannotOperate,         ///<  Doodad interaction requirements are not met
    errDoodadSpellCasting,          ///<  Cannot interact with the doodad while casting a spell
	errDoodadEnd,

	errTeamBegin = 0xF00,
	errTeamInvitationSent,			///<  Invitation sent to the target player
	errTeamApplicationSent,			///<  Application sent to the target player
	errTeamFailed,					///<  Failed to form team
    errTeamOffLine,					///<  Team is offline
	errTeamInBattleQueue,			///<  Team is in the battlefield queue
	errTeamInArenaQueue,			///<  Team is in the arena queue
    errTeamAlreadyInTeam,			///<  Already in a team
    errTeamFull,					///<  Team is full
    errTeamRefuse,					///<  Declined to join team
    errTeamNotLeader,				///<  You are not the team leader
    errTeamNameError,				///<  Invalid team name
    errTeamNotPermit,				///<  No permission for this team operation
    errTeamNotInTeam,				///<  Not in a team
    errTeamNotExist,				///<  Team does not exist
    errTeamRefusedInvitation,   	///<  Invitation declined
    errTeamInvitationRefused,       ///<  Invitation was declined
    errTeamRefusedApplication,		///<  Application declined
    errTeamApplicationRefused,      ///<  Application was declined
	errTeamAssignedTypeError,		///<  Invalid allocation mode
    errTeamRequestNotAvailable,     ///<  Application is no longer valid
	errTeamAuctionBidTooLow,		///<  Bid is too low
	errTeamAuctionNotEnoughMoney,	///<  Insufficient money
	errTeamAuctionNotBegin,			///<  Auction has not started
	errAdjacentDataTimeLimit,
	errTeamNoKickInAuction,			///<  Cannot remove team members during an auction
	errTeamSceneForbidden,			///<  Teams are prohibited in this scene
    errTeamEnd,

	errArenaBegin = 0x1000,
    errArenaGetRewardSucc,          ///< Arena chest claimed successfully
    errArenaNotInRewardTime,        ///< Not within the reward claim period
    errArenaNoReward,               ///< No rewards are available to claim
    errArenaNotLucky,               ///< No prize was won
    errArenaCannotUseItem,          ///< You do not have permission to use the item
    errArenaUseItemLimit,           ///< Item use limit exceeded
    errArenaMatchTimeout,           ///< Arena queue timed out without a match
    errArenaLucky,                  ///< Congratulations, you won a prize
    errArenaMatchFailed,            ///< Matchmaking failed
	errArenaEnd,

	errBattleBegin = 0x1100,
	errBattleQueueNow,				///< Already in the battlefield queue
	errBattleNotQueue,				///< Not in the battlefield queue
	errBattleConfirmTimeout,		///< Confirmation timed out
	errBattleEnd,

	errSceneBegin = 0x1200,
    errSceneTooFarFromTeleport,     ///< Too far from the teleport point
	errSceneTooFarFromTeleportPlatform,///< Too far from the teleport platform
    errSceneNotTeamLeader,          ///< Only the team leader can teleport
    errSceneNotTeamMember,          ///< Too many team members to teleport
    errSceneErrorDungeonLevel,      ///< Invalid dungeon level
    errSceneErrorDungeonDifficulty, ///< Invalid dungeon difficulty
    errSceneNoEnterRight,           ///< No permission to enter the dungeon
    errSceneNoEnterMaxRole,         ///< Scene player limit exceeded
    errSceneNotExist,               ///< Dungeon does not exist
    errSceneCreateSceneFailed,      ///< Failed to create dungeon
    errSceneDestroySceneFailed,     ///< Failed to destroy dungeon
    errScenePreEnterFailed,         ///< Failed to prepare scene entry
    errSceneNoFatigue,              ///< Insufficient activity points to enter the scene
    errSceneEnterCountLimit,        ///< Daily entry limit reached
    errSceneNoLevel,                ///< Scene entry level requirement not met
	errSceneTooLowLevel,			///< Level too low to enter the scene
	errSceneTooHighLevel,			///< Level too high to enter the scene
	errSceneEnd,

	errChatBegin = 0x1300,
	errChatCountOut,			///< Server-wide chat limit reached
	errChatTooFrequent,			///< Chat messages sent too quickly
	errChatServiceUnavaible,	///< Chat service error
	errChatTargetNotFound,		///< Chat recipient not found
	errGroupChatWithItem,		///< Long-distance message item not found
    errChatForbidden,           ///< You are muted
	errChatSceneForbidden,		///< This chat function is prohibited in the current scene
	errChatLevelTooLow,		    ///< Chat level requirement not met
	errChatMoneyNotEnough,	    ///< Insufficient gold for chat
	errChatSafeAreaForbidden,	///< Nearby chat is prohibited in safe areas
	errChatEnd,

	errFriendBegin = 0x1400,
    errFriendNotFound,          ///< Friend not found
    errFriendAlreadyExists,     ///< Already friends
    errFriendNotMutual,         ///< Friendship is not mutual
    errFriendNotOnline,         ///< Friend is offline
	errFriendFull,              ///< Friends list is full
    errEnemyNotFind,            ///< Enemy not found
	errFriendEnd,

	errTitleBegin = 0x1500,
    errTitleNotFind,            ///< Title does not exist
    errTitleCondNotSatisfy,     ///< Title equip requirements not met
	errTitleEnd,

	errTradeBegin = 0x1600,
	errTradeAskSent,			///< Trade request sent to target player
	errTradeWrongState,         ///< Invalid trade state
    errTradeTargetNotFound,     ///< Trade partner not found
    errTradeTargetFaraway,      ///< Trade partner is too far away
    errTradeTargetBusy,         ///< Trade partner is busy
    errTradeDifferentGroup,     ///< Trade partner is in a different server group (for example, a cross-server battlefield)
    errTradeBagFull,            ///< Bag is full
    errTradeUnknown,            ///< Unknown trade module error
	errTradeSceneFobidden,		///< Trading is prohibited in the current scene
    errTradeChangeNotAllowed,   ///< Submitted items and money cannot be withdrawn or changed
    errTradeNeedIntimacy,       ///< Insufficient friendship level to trade
    errTradeOverWeight,         ///< Bag is overweight
	errTradeEnd,

    // master
	errMasterBegin = 0x1700,
    errMstFailed,
    errMasterNotMaster,         ///<  Not a mentor
    errMasterStudFull,          ///<  Student limit reached
    errMasterTeacherNotOnline,  ///<  Mentor is offline
    errMasterStudentNotOnline,  ///<
    errMasterStudHighLevel,     ///<  Student level is too high
    errMasterStudhasMasterAlready, ///<  Student already has a mentor
    errMasterStudAppFull,
    errMasterTargetStudAppFull,
    errMasterNoStudApp,         ///<  
    errMasterNoTeacherApp,
    errMstApplyFull,            ///<  Application limit reached
    errMstApplyerFull,          ///<  Applicant limit reached
    errMasterAlreadyApply,      ///<  Already applied to this mentor
    errMstRefuseApply,          ///<  Application declined
    errMasterStudNotOnline,     ///<  Student is offline
    errMasterApplayMstCD,       ///<  Cannot choose a new mentor immediately after leaving one
    errMasterFireStudentCD,     ///<  Student dismissal cooldown
    errMasterTargetFireStudCD,  ///<  Target has a student dismissal cooldown
    errMasterNoMaster,          ///<  No mentor
    errMasterAlreadyGrad,       ///<  Already graduated
    errMstCannotCZ,             ///<  Only a mentor can congratulate
	errMstHaveNoStu,			///<  No students
    errMstMissApplication,      ///<  Application record not found
    errMasterRoleNotExist,      ///<  Character not found
    errMasterAddExpFailed,
    errMasterHighLevel,         ///< Level exceeds the mentorship application limit
    errMasterOpFast,            ///< Operation performed too frequently
    errMasterNotCZLevel,        ///< Level is not eligible for congratulations
    errMasterNeedGetRewardExp,  ///< Unclaimed mentorship reward experience remains
	errMasterEnd,

	errMailBegin = 0x1800,
    errMailUnknown,
    errMailReceiverNotFound,    ///< Recipient not found
    errMailReceiverFull,        ///< Recipient mailbox is full
    errMailNotFound,            ///< Specified mail not found
    errMailCostNotEnough,       ///< Insufficient postage
    errMailAttachNotFound,      ///< Mail has no attachment
    errMailSendTooFast,         ///< Mail sent too frequently
    errMailAttachCDTime,        ///< Attachment cannot be claimed during cooldown
	errMailSceneForbidden,		///< Mail is prohibited in the current scene
	errMailEnd,

	errAchievementBegin = 0x1900,
	errAchievementLevel,									///<  Achievement incomplete: required level not reached
	errAchievementExperience,								///<  Achievement incomplete: required total experience not reached
	errAchievementPkValue,									///<  Achievement incomplete: required good/evil value not reached
	errAchievementForceReputation,							///<  Achievement incomplete: required faction reputation not reached
	errAchievementVariousForceCount,						///<  Achievement incomplete: required number of factions not unlocked
	errAchievementEquip,									///<  Achievement incomplete: required equipment not obtained
	errAchievementEquipColor,								///<  Achievement incomplete: equipment of the required quality not obtained
	errAchievementEquipBodyColor,							///<  Achievement incomplete: required equipment quality not obtained for the specified slot
	errAchievementSet,										///<  Achievement incomplete: required outfit not obtained
	errAchievementSetCount,									///<  Achievement incomplete: required outfit count not reached
	errAchievementEquipSet,									///<  Achievement incomplete: required outfit not equipped
	errAchievementBankSlotCount,							///<  Achievement incomplete: required bank slot count not reached
	errAchievementTotalSlotCount,							///<  Achievement incomplete: total slot count reaches the specified count
	errAchievementItemBagSlotCount,							///<  Achievement incomplete: required item bag slot count not reached
	errAchievementEquipBagSlotCount,						///<  Achievement incomplete: required equipment bag slot count not reached
	errAchievementMaterialBagSlotCount,						///<  Achievement incomplete: required material bag slot count not reached
	errAchievementTotalMoneyType,							///<  Achievement incomplete: required number of owned currency types not reached
	errAchievementKillPlayerTotalCount,						///<  Achievement incomplete: required total player kills not reached
	errAchievementEnterScene,								///<  Achievement incomplete: specified map has not been entered
	errAchievementCompleteQuest,							///<  Achievement incomplete: specified quest not completed
	errAchievementCompleteQuestCount,						///<  Achievement incomplete: required total quest completions not reached
	errAchievementCompleteTypeQuest,						///<  Achievement incomplete: required number of quests of the specified type not completed
	errAchievementSpellLevelSpecified,						///<  Achievement incomplete: specified spell has not reached the required level
	errAchievementSpellLevel,								///<  Achievement incomplete: spell level requirement not met
	errAchievementLearnSpell,								///<  Achievement incomplete: specified spell not learned
	errAchievementSpellCount,								///<  Achievement incomplete: required spell count not reached
	errAchievementActiveSpellCount,							///<  Achievement incomplete: required active spell count not reached
	errAchievementRuneCount,								///<  Achievement incomplete: required spell rune infusion count not reached
	errAchievementEquipPassiveSpellCount,					///<  Achievement incomplete: required number of passive spells not equipped
	errAchievementEquipPassiveSpellIDCount,					///<  Achievement incomplete: specified passive spell not equipped
	errAchievementAchievement,								///<  Achievement incomplete: prerequisite achievement not obtained
	errAchievementAchievementCount,							///<  Achievement incomplete: required achievement count not reached
	errAchievementGetItem,									///<  Achievement incomplete: required item not obtained
	errAchievementItemLuck,									///<  Achievement incomplete: no item has reached the required luck value
	errAchievementItemRefine,								///<  Achievement incomplete: no item has reached the required enhancement level
	errAchievementTitle,									///<  Achievement incomplete: required title not obtained
	errAchievementTitleCount,								///<  Achievement incomplete: required title count not reached
	errAchievementFriendCount,								///<  Achievement incomplete: required friend count not reached
	errAchievementLeaveStudentCount,						///<  Achievement incomplete: required number of students have not graduated
	errAchievementLeaveMaster,								///<  Achievement incomplete: student graduation not completed
	errAchievementCreateTime,								///<  Achievement incomplete: required character age not reached
	errAchievementDailyCompleteQuestCount,					///<  Achievement incomplete: required daily quest completions not reached
	errAchievementMainCompleteQuestCount,					///<  Achievement incomplete: required main quest completions not reached
	errAchievementSubCompleteQuestCount,					///<  Achievement incomplete: required side quest completions not reached
	errAchievementHiddenCompleteQuestCount,					///<  Achievement incomplete: required hidden quest completions not reached
	errAchievementUseTypeItemCount,							///<  Achievement incomplete: required uses of the specified item type (spellbook) not reached
	errAchievementUseItem101Count,							///<  Achievement incomplete: required uses of item ID 101 not reached
	errAchievementKillWithNoGuilty,							///<  Achievement incomplete: PvP without gaining PK points not completed
	errAchievementVariableCheckError,						///<  Achievement incomplete: character variable check failed
	errAchievementSpiritLevel,								///<  Achievement incomplete: required spirit level not reached
	errAchievementPlayerNotFound,							///<  Achievement incomplete: player to compare not found
	errAchievementPlayerNotInSameScene,						///<  Achievement incomplete: comparison player is not on the same map
	errAchievementPlayerTooFar,								///<  Comparison player is too far away
	errAchievementRewarded,									///<  Reward already claimed
    errAchievementNotCompleted,								///<  Cannot claim reward: achievement incomplete
	errAchievementAlreadyCompleted,							///<  Achievement already completed
	errAchievementMount,									///<  Required mount count not reached
	errAchievementHero,										///<  Hero is not the specified class or has not reached the required level
	errAchievementRewardBagFull,							///<  Cannot claim reward: bag is full
	errAchievementSpiritBuyAirBagSlotCount,					///<  Required unlocked qi bag slots not obtained
	errAchievementSpiritBuyAirStallSlotCount,				///<  Required unlocked qi storage slots not obtained
	errAchievementSpiritBuyAirEquipSlotCount,				///<  Required unlocked qi equipment slots not obtained
	errAchievementSpiritBloodPageCount,						///<  Required number of spirit pages not unlocked
	errAchievementSpiritBloodPageCompleteCount,				///<  Required spirit completion percentage not reached
	errAchievementSpiritBloodPageLevel,						///<  No spirit ring has reached the required level
	errAchievementTotalRefineTime,							///<  Required number of physique enhancements not reached
	errAchievementTeamAuctionCount,							///<  Required number of item auctions not reached
	errAchievementVip,										///<  Achievement incomplete: not VIP
	errAchievementColorItemComposeCount,					///<  Achievement incomplete: required number of items of the specified quality not crafted
	errAchievementItemComposeCount,							///<  Achievement incomplete: required equipment crafting count not reached
	errAchievementColorItemDeComposeCount,					///<  Achievement incomplete: required number of items of the specified quality not decomposed
	errAchievementItemDeComposeCount,						///<  Achievement incomplete: required equipment decomposition count not reached
	errAchievementRuneWeaponCount,							///<  Achievement incomplete: required number of inscribed weapons not obtained
	errAchievementExplore,									///<  Achievement incomplete: specified map not entered

	errAchievementEnd,

    // guild
	errGuildBegin = 0x1A00,
    errGuildFailed,
    errGuildInternalError,
    errGuildMsgError,
    errGuildSqlError,
    errGuildClientParamError,
    errGuildNumLimit,                       ///<  Guild creation limit reached
    errGuildQueryFailed,
    errGuildCreateFailed,                   ///<  Failed to create guild
    errGuildSendTVMsgError,                 ///<  Failed to send screen announcement
    errGuildSendMailFailed,                 ///<  Failed to send mail
    errGuildViewGuildFailed,                ///<  Query failed; could not fetch guild list
    errGuildNoGuild,                        ///<  Not a guild member
    errGuildNotFind,                        ///<  Guild not found
    errGuildLeaderNotExist,                 ///<  Guild leader does not exist
    errGuildNotMember,                      ///<  You are not a guild member
    errGuildCannotFindMember,               ///<  Guild member not found
    errGuildAddMemberFailed,                ///<  Failed to add guild member
    errGuildAddEventFailed,                 ///<  Failed to record guild event
    errGuildAddChestEventFailed,            ///<  Failed to add fund record
    errGuildDeleteGuildAppFailed,           ///<  Failed to delete guild application record
    errGuildDestoryFailed,                  ///<  Failed to delete guild
    errGuildNoticeSizeError,                ///<  Guild message length
    errGuildAnnounceSizeError,              ///<
    errGuildSetChatFlagError,               ///<  Failed to set chat permission flag
    errGuildCannotSetSelfPosition,          ///<  Cannot set your own position
    errGuildSetPositionFailed,              ///<  Failed to set position
    errGuildSubRoleMoneyFailed,             ///<  Failed to deduct character gold
    errGuildSubMoneyFailed,                 ///<  Failed to deduct guild funds
    errGuildAddMoneyFailed,                 ///<  Failed to add guild funds
    errGuildDonateLimit,                    ///<  Donation limit reached
    errGuildAddWoodFailed,                  ///<  Failed to add wood
    errGuildAddHerbFailed,                  ///<  Failed to add herbs
    errGuildAddCrystalFailed,               ///<  Failed to add crystals
    errGuildAddSilverFailed,                ///<  Failed to add mithril
    errGuildSubResFailed,                   ///<  Failed to deduct resources
    errGuildAddAllianceAppFailed,           ///<  Failed to add guild alliance application
    errGuildAddEnemyFailed,                 ///<  Failed to add enemy guild
    errGuildCannotAddYourself,              ///<  Cannot add your own guild
    errGuildAllianceAppNotExist,            ///<  Guild alliance application does not exist
    errGuildAllianceAppTimeTypeError,       ///<  Invalid event type for guild alliance application
    errGuildSameName,                       ///<  Duplicate name
    errGuildCensoredWord,                   ///<  Guild name contains restricted words
    errGuildLowerLevel,                     ///<  Level is too low
    errGuildNotEnoughMoney,                 ///<  Insufficient money
    errGuildNotEnoughContribution,          ///<  Insufficient guild contribution
    errGuildNoItem,                         ///<  Required item is missing
    errGuildApplyGuildFailed,               ///<  Guild application failed
    errGuildPositionError,                  ///<  Invalid guild position
    errGuildAppFull,                        ///<  Guild application limit reached
    errGuildCannotDemiseMyself,             ///<  Cannot transfer leadership to yourself
    errGuildAlreadyJoin,                    ///<  Already in a guild
    errGuildAlreadyApply,                   ///<  Already applied
    errGuildNoRight,                        ///<  No permission for this operation
    errGuildMemberCountFull,                ///<  Member limit reached
    errGuildTargetNotOnline,                ///<  Target is offline
    errGuildGuildHighLevel,                 ///<  Guild level is too high
    errGuildInviteSuccessfully,             ///<  Recruitment message sent; awaiting response
    errGuildJoinGuildLevelLimit,            ///<  Level too low to join guild
    
    errGuildSamePosition,                   ///<  Same position
    errGuildPositionLow,                    ///<  Cannot act on a player with a higher position
    errGuildPosHumanFull,                   ///<  Position is full
    errGuildPosLeader,                      ///<  Guild leader cannot step down
    errGuildNotLeader,                      ///<  Not the guild leader
    errGuildDrawSalaryFailed,               ///<  Failed to claim salary
    errGuildNoSalary,                       ///<  No salary available
    errGuildDrawSalaryAlready,              ///<  Salary already claimed
    errGuildDiplomatTimeError,              ///<  Invalid diplomacy duration type
    errGuildMoneyLack,                      ///<  Insufficient guild funds
    errGuildAllianceFull,                   ///<  Alliance limit reached
    errGuildIsEnemy,                        ///<  Guild is an enemy
    errGuildIsAlliance,                     ///<  Guild is an ally
    errGuildNotAlliance,                    ///< 
	errGuildAllianceAppAlreadyDel,          ///<  Alliance application record was deleted
    errGuildAllianceAppAlready,             ///<  Alliance application already submitted
    errGuildAppNotExist,                    ///<  Guild application does not exist
    errGuildRoleNotExist,                   ///<  Character does not exist
    errGuildJoinCD,                         ///<  Guild join cooldown
    errGuildTargetJoinCD,                   ///<  Target has a guild join cooldown
    errGuildStorageTargetSlotError,         ///<  Invalid target slot
    errGuildStorageSlotUsed,                ///<  Slot is already occupied
    errGuildStorageItemNotExist,            ///<  No item in target slot
    errGuildStorageSlotUsing,               ///<  Slot is in use
    errGuildDelHaveAlliance,                ///<  Cannot delete guild while it has allies
    errGuildDelHaveEnemy,                   ///<  Cannot delete guild while it has enemies
    errGuildLeaderCannotDelRole,            ///<  Guild leader cannot delete character
    errGuildNoMoreHistory,                  ///<  No more guild events
    errGuildNoMoreChest,                    ///<  No more fund records
    errGuildConfigError,                    ///<  Configuration error
    errGuildContributionLimit,              ///<  Contribution gain limit reached

    errGuildStorageCD,                      ///<  Guild operation cooldown
    errGuildChangeAnnounceSucc,             ///<  Guild announcement changed successfully

    // guild welfare
    errGuildWarTime,                        ///<  Cannot upgrade during a guild war
    errGuildWelfareNeedUpgrade,             ///<  Welfare buff has not been upgraded
    errGuildWelfareAuraIDError,             ///<  Invalid welfare ID
    errGuildBuildingLevelLower,             ///<  Building level too low
    errGuildNoMoreGuildMoney,               ///<  Insufficient guild gold
    errGuildNoMoreWood,                     ///<  Insufficient wood
    errGuildNoMoreHerb,                     ///<  Insufficient herbs
    errGuildNoMoreCrystal,                  ///<  Insufficient crystals
    errGuildNoMoreSilver,                   ///<  Insufficient silver
    errGuildMaxLevel,                       ///<  Already at maximum level
    errGuildWelfareBufferNotExist,          ///<  Welfare buff does not exist
    errGuildBuyAuraFailed,                  ///<  Failed to redeem buff
    errGuildAuraPurchaseLimit,              ///<  Purchase limit reached
    errGuildWelfareUpgrading,               ///<  Welfare upgrade is in progress
    errGuildUpgradingCountLimit,            ///<  Maximum number of simultaneous upgrades reached

    errGuildBuildingIDError,                ///<  Invalid building ID
    errGuildBuildingNpcIDError,             ///<  Invalid base NPC ID
    errGuildBuildingConfigError,            ///<  Invalid building configuration
    errGuildBuildingAlreadyExist,           ///<  Another building already exists
    errGuildBuildingNotExist,               ///<  No building at this position to upgrade
    errGuildBuildingUpgrading,              ///<  Building upgrade is in progress
    errGuildBuildingUpgradeError,           ///<  Building upgrade error
    errGuildBuildingDead,                   ///<  Building is destroyed
    errGuildErrorBuildingTypeForNpc,        ///<  NPC does not support this building type
    errGuildBuildingMaxLevel,               ///<  Building has reached maximum level
    errGuildBTypeNotMatch,                  ///<  Building type does not match
    errGuildBMaxNum,                        ///<  Building count limit reached
    errGuildCannotDel,                      ///<  Building cannot be demolished
    errGuildCannotCreate,                   ///<  Building cannot be constructed
    errGuildBaseBuildingFailed,             ///<  Prerequisite building requirements not met
    errGuildUpgradeDataNotExist,            ///<  Building upgrade data does not exist

    errGuildEnterSceneFailed,               ///<  Failed to enter the territory map
    errGuildWeatherAlreadyBeChanged,        ///<  Weather has already changed
    errGuildWrongMap,                       ///<  Invalid map; weather cannot be changed on this map
    errGuildWelfareBeFrozen,                ///<  Welfare is frozen
    errGuildAlreadyOpenDungeon,             ///<  Dungeon is already open
    errGuildOpenDungeonFailed,              ///<  Failed to open dungeon
    errGuildEnterDungeonFailed,             ///<  Failed to enter dungeon
    errGuildCannotFindDungeon,              ///<  Open dungeon not found
    errGuildNotDungeonLeader,               ///<  Not the team leader designated by the owner
    errGuildDeclareFailed,                  ///<  Failed to declare war
    errGuildCannotDeclaredYourself,         ///<  Cannot declare war on your own guild
    errGuildWarLevelLimit,                  ///<  Guild level too low to declare war
    errGuildInProtectionTime,               ///<  Cannot declare war on a guild under war protection
    errGuildAttackCD,                       ///<  Guild war declaration cooldown
    errGuildAllianceCannotBeDeclared,       ///<  Cannot declare war on an allied guild
    errGuildInDeclareTime,                  ///<  Outside the war declaration period
    errGuildDungeonMapClosing,              ///<  Dungeon is closing
    errGuildMatchGuildFailed,               ///<  Guild matchmaking failed
    errGuildMatchWarCountLimit,             ///<  Guild war matchmaking limit reached
    errGuildInWar,                          ///<  Guild war in progress...
    errGuildNotWarTime,                     ///<  Outside the guild war period
    errGuildBeFightingToday,                ///<  Cannot declare war on a guild already fighting today

    // guild achievement
    errGuildAchiAlreadyReward,              ///< Guild achievement reward already claimed
    errGuildAchiNotComplete,                ///< Guild achievement incomplete
    errGuildAchiRewardSucc,                 ///< Guild achievement reward claimed

    // guild activity
    errGuildActivityConfigError,            ///< Invalid guild activity configuration
    errGuildAcAlreadyOpen,                  ///< Guild activity already started

	// guild escort
	errGuildTodayAlreadyAcceptEscort,		///<  Escort already completed today
	errGuildTodayNotOpenEscort,             ///<  Guild escort has not started
	errGuildEscortCarBeenKilled,            ///<  Escort cart was destroyed
	errGuildEscortCarTimeOut,               ///<  Escort cart expired

    // alliance
    errGuildDelAllianceSuccess,             ///< Guild alliance removed successfully
    
    errGuildDeclearWarMustEnemy,            ///< Can only declare war on an enemy guild
    errGuildCannotLeaveGuildInCombat,       ///< Cannot leave guild during combat
    errGuildCannotBanishTargetInCombat,     ///< Cannot expel a player who is in combat
	errGuildEscortLevelNotEnough,			///< Level too low for the escort quest

    errGuildPageEnd,                        ///< Last page reached
    errGuildCannotLeaveInWar,               ///< Cannot leave guild during a guild war
    errGuildCannotDisbandInWar,             ///< Cannot disband guild during a guild war
    errGuildNotActivityTime,                ///< Outside the activity period
    errGuildWarTargetLevelLimit,            ///< Target guild level is too low
    errGuildWarTargetAlreadyBeDeclared,     ///< War has already been declared on the target
    errGuildWarClose,                       ///< Guild wars are not enabled on this server

	errGuildEnd,

	errSpiritBegin = 0x1B00,
	errSpiritNotOpen,						///<  Spirit progression is not unlocked
	errSpiritDailyChangeCount,				///<  Conversion count limit reached
	errSpiritMoneyNotEnough,				///<  Insufficient soul for conversion
	errSpiritPtsNotEnough,					///<  Insufficient cultivation points
	errSpiritChangeCDTime,					///<  Conversion cooldown has not elapsed
	errSpiritLevel,							///<  Level is too low
	errSpiritProductLevel,					///<  Qi cultivation level is too low
	errSpiritUpExpNotEnough,				///<  Insufficient experience to level up
	errSpiritUpLevelMax,					///<  Maximum level reached
	errSpiritAirSeaBagFull,					///<  Air sea bag is full
	errSpiritExchangeMoney,					///<  Insufficient money to exchange for arcane qi
	errSpiritAirSlotNotEmpty,				///<  Qi slot is not empty
	errSpiritAirSlotEmpty,					///<  Qi slot is empty
	errSpiritAirEquipSameGroup,				///<  A qi of the same group is already equipped
	errSpiritDailyExp2PtsOut,				///<  Daily gold limit for one-click soul-to-cultivation conversion reached
	errSpiritExp2PtsMoneyOut,				///<  Insufficient gold for one-click soul-to-cultivation conversion today
	errSpiritBloodAlreadyOpen,				///<  Page is already unlocked
	errSpiritRoleLevelLimit,				///<  Spirit unlock level not reached
	errSpiritBloodSlotNumber,				///<  Slot value has reached its maximum
	errSpiritBloodNotOpen,					///<  Page is not unlocked
	errSpiritBloodSlotLevel,				///<  Required spirit level for this slot not reached
	errSpiritSpellPts,						///<  Insufficient cultivation points
	errSpiritExp2PtsMaxCount,				///<  Daily soul-to-cultivation conversion limit reached
	errSpiritEnd,

	errHeroBegin = 0x1C00,
	errHeroInvalid,							///<  Invalid hero
	errHeroAlreadyExist,					///<  Hero already exists
	errHeroNotExist,						///<  Hero does not exist
	errHeroSummonFailed,					///<  Failed to summon hero
	errHeroNotReady,						///<  Hero is on cooldown
	errHeroContainerNotEmpty,				///<  Hero bag is not empty
	errHeroAiInvalid,    				    ///<  Invalid hero AI type
	errHeroAlreadyHaveName,    			    ///<  Hero already has a name
	errHeroAlreadySummoned,					///<  Hero has already been summoned
	errHeroAlreadyRecalled,					///<  Hero has already been recalled
	errHeroEnd,

    // shield list
	errShieldBegin = 0x1D00,
    errNotFindTargetRole,                   ///<  Target character not found
    errAlreadyShield,                       ///<  Already on the block list
    errNotFindInShieldList,                 ///<  Not found on the block list
    errShieldedListFull,                    ///<  Block list is full
    errCannotShieldYourself,                ///<  Cannot block yourself
	errShieldEnd,

    // auction
	errAuctionBegin = 0x1E00,
    errAuctionItemNotFound,                 ///<  Auction item not found
    errAuctionSellingFull,                  ///<  Sale listing limit reached
    errAuctionBuyingFull,                   ///<  Bid limit reached
    errAuctionQuerying,                     ///<  Auction server is busy
    errAuctionSellingPriceLow,              ///<  Starting price is too low
    errAuctionBuyingPriceLow,               ///<  Bid is too low
    errAuctionSellerCannotBuy,              ///<  Seller cannot bid on their own item
    errAuctionBuyerCannotBuy,               ///<  Current highest bidder cannot bid again
    errAuctionOnBid,                        ///<  Auction item has an active bid
    errAuctionNotOpen,                      ///<  Auction house is not available
    errAuctionUnknown,
	errAuctionEnd,

    // exchange
	errExchangeBegin = 0x1F00,
    errExchangeOrderFull,                   ///<  Order count limit exceeded
    errExchangeOrderNotFound,               ///<  Order not found
    errExchangeQuerying,                    ///<  Exchange server is busy
    errExchangeSceneForbidden,				///<  Gold exchange is prohibited in the current scene
	errExchangeEnd,

	// activity
	errActivityBegin = 0x2000,
	errLackofActivity,						///<  Insufficient activity points
	errActivityRewardAccepted,				///<  Activity gift pack already claimed
	errActivityEnd,

    // real money shop
	errRMShopBegin = 0x2100,
    errRealMoneyShopNotOpen,                ///<  Cash shop is not available
    errCannotConnectSndaServer,             ///<  Failed to communicate with the Shanda billing platform
    errRealMoneyBuyNotEnoughMoney,          ///<  Insufficient ingots
    errRealMoneyShopItemNotFound,           ///<  Shop item not found
    errRealMoneyShopFriendNotFound,         ///<  Gift recipient not found
    errRealMoneyShopCrcFailed,              ///<  Cash shop CRC check failed
    errBillingSystemError,                  ///<  Billing platform returned an unknown failure
    errTimeBillingNotOpen,                  ///<  Game time card billing is not available
    errTimeBillingNotEnough,                ///<  Insufficient game time remaining
    errTimeBillBusy,                        ///<  Game time balance query in progress
	errRMShopEnd,

	// ranklist
	errRankListBegin = 0x2200,
	errRoleNotOnline,						///< Player is offline
	errRankListEnd,

	// sabac
	errSabacBegin = 0x2300,
	errSabacNotGuildLeader,					///<  Not the guild leader
	errSabacNotEnoughMoney,					///<  Insufficient registration fee
	errSabacNotEnoughItem,					///<  Insufficient registration items
	errSabacEnrolled,						///<  Already registered
	errSabacOccupied,						///<  Already occupied
	errSabacFighting,						///<  Cannot register during battle
	errSabacErectStatue,					///<  Only the leader of the guild occupying Sabac can erect a statue
	errSabacErectNotEnoughMoney,			///<  Insufficient money to erect a statue
	errSabacEnd,

	// reputation award
	errReputationBegin = 0x2400,
	errRepReceiveAwardSuccess,				///<  Reward claimed successfully
	errRepAlreadyReceived,					///<  Reward already claimed
	errRepNotEnoughReputation,				///<  Insufficient reputation
	errReputationEnd,

    // pet
	errPetBegin = 0x2500,
    errPetChangeStateSuccess,               ///<  Pet state changed successfully
    errPetStateSame,                        ///<  Already in that state
	errPetEnd,

	// checkin
	errCheckInBegin = 0x2600,
	errCheckInNotExist,
	errCheckInAlreadyDid,
	errCheckInLevelLimit,
	errCheckInClosed,
	errCheckInEnd,

    // award
	errAwardBegin = 0x2700,
    errAwardNotEnabled,
    errAwardReqSentFailed,
    errAwardFailed,
	errAwardFailed_1,
	errAwardFailed_2,
	errAwardFailed_3,
	errAwardFailed_4,
	errAwardFailed_5,
	errAwardFailed_6,
	errAwardFailed_7,
	errAwardFailed_8,
	errAwardFailed_9,
	errAwardEnd,


	// anti-cheat
	errAntiCheatBegin = 0x2800,
	errAntiCheatSuccess,
	errAntiCheatError,
	errAntiCheatErrorKick,
	errAntiCheatErrorTimeoutReturn,
	errAntiCheatExit,
	errAntiCheatNotReady,
	errAntiCheatEnd,

    // gm
	errGMBegin = 0x2900,
	errGMNoRight,
	errGMGSExecute,
	errGMNotExecute,
	errGMNoCommand,
    errGMExecuteFailed,
    errGMCannotConnectGMSvr,
    errGMKickYou,

    // GM: for internal server use only; the client need not parse these
    errGMUnknownError,
    errGMVersionError,
    errGMConnectERROR,
    errGMPwdError,
    errGMRelogin,
    errGMCannotExecuteNewCmd,
    errGMNotExecutePermission,
    errGMGetPermissionError,
    errGMUserNotFind,
    errGMDBError,
    errGMTimeout,
    errGMSendMsgToMSError,
    errGMLostTLUser,
    errGMCannotFindRole,
    errGMLostCmd,
    errGMMSNotOnline,
    errGMMSExecuteCmdFailed,
    errGMSaveRoleDataFailed,
    errGMModifyRoleTypeError,
    errGMRoleOnline,
    errGMQueryZeroRoleData,
    errGMRoleNotFreeze,
    errGMRoleFreezeLessOneHour,
    errGMAnnounceNotExist,
    errGMRoleBeOp,
    errGMRoleLockedByOther,

    errGMStrCommandFailed,
    errGMStrCmdExeFailed,					///< Command execution failed
    errGMCmdExecuting,

	errGMEnd,

	// NOTE: ADD NEW SECTION BEFORE THIS LINE

	errMiscBegin = 0x10000,

	errDisconnectTimeOut,
	errFreeMode,							///< Trial mode: some game features are disabled
	errRoleLowLevel,						///< Character level is too low; some game features are disabled
	errArrestRoleOffline,					///< Target to arrest is offline
	errArrestClosed,						///< Prison population requirements are not met; arrests are temporarily disabled
	errArrestSceneNoPunish,					///< GPK arrests are not enabled in the current scene
	errGpkAuthKick,							///< Disconnect player after GPK authentication failure

	errMiscEnd,
};

enum NS_ERROR_CODE_DEF
{
    errNsUnknownError = 0,
	errNsSuccess = 1,   

    errNsNameDuplicated,					///< Duplicate name
    errNsNameDBSysErr,						///< Name database error
    errNsNameUnknown,				        ///< Unknown error
	errNsTooManyUser,						///< User limit reached
};

#endif // _ERROR_DEF_H_
