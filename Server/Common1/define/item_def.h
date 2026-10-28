#ifndef _ITEM_DEF_H_
#define _ITEM_DEF_H_

/// @file item_def.h 
/// @brief item related definition

#define MAX_ITEM_COUNT		(128)
#define MAX_DROP_COUNT		(128)
#define MAX_REFINE_LEVEL    (300)

///@enum EItemLog
enum EItemLog
{
	ITEMLOG_INVALID = -1,					///< invalid
	ITEMLOG_SHOP,							///< Merchant purchase
	ITEMLOG_LOOT,							///< Loot
	ITEMLOG_GM_COMMAND,						///< GM command
	ITEMLOG_QUEST_PREPAY,					///< Granted on quest acceptance
	ITEMLOG_QUEST_REWARD,					///< Quest completion reward
	ITEMLOG_DUNGEON_REWARD,					///< Dungeon reward
	ITEMLOG_PLAYER_STALL,					///< Player stall
	ITEMLOG_PLAYER_TRADE,					///< Player trade
	ITEMLOG_BUY_BACK,						///< Buyback
	ITEMLOG_CREATE_ROLE,					///< Create character
	ITEMLOG_CREATE_HERO,					///< Create hero
	ITEMLOG_SCRIPT,							///< Script
	ITEMLOG_GET_MAIL_ATTACH,				///< Mail attachment
	ITEMLOG_GUILD_STORAGE,					///< Guild storage transfer
	ITEMLOG_GUILD_DESTORY,                  ///< Guild dissolution
	ITEMLOG_ACHIEVEMENT_REWARD,				///< Achievement reward
	ITEMLOG_UPGRADE_SOUL,					///< Soul stone upgrade
	ITEMLOG_REMOVE_SOUL,					///< Soul stone removal
	ITEMLOG_NPC_DROP,						///< Monster drop
	ITEMLOG_USER_REQUEST,					///< Player discard
	ITEMLOG_SELL,							///< Sell to merchant
	ITEMLOG_CAST_SPELL,						///< Cast spell
	ITEMLOG_REFINE_ITEM,					///< Physique enhancement
	ITEMLOG_COMPLETE_QUEST,					///< Turn in on quest completion
	ITEMLOG_CREATE_GUILD,					///< Create guild
	ITEMLOG_USE_ITEM,						///< Use item
	ITEMLOG_INSERT_SOUL,					///< Soul stone fusion
	ITEMLOG_AUCTION_SELL,					///< Auction house sale
	ITEMLOG_RUNE,							///< Inscription
	ITEMLOG_DECOMPOSE,						///< Item decomposition
	ITEMLOG_COMPOSE,						///< Item crafting
	ITEMLOG_ACTIVITY_REWARD,				///< Event reward
	ITEMLOG_REVIVE,							///< Revival
	ITEMLOG_GM,								///< GM tool
	ITEMLOG_OPEN_DOODAD,					///< Open doodad
	ITEMLOG_REAL_MONEY_SHOP,				///< Cash shop
	ITEMLOG_TEAM_AUCTION,					///< Team auction
	ITEMLOG_TEAM_AUCTION_FAILED,			///< Team auction failed
	ITEMLOG_QUEST_RECYCLE,					///< Cycle quest
	ITEMLOG_EXCHANGE,						///< Exchange
	ITEMLOG_ARENA_COMMON_REWARD,			///< Arena reward
	ITEMLOG_SABAC_AWARD,					///< Sabac reward
	ITEMLOG_REPUTATION_AWARD,				///< Reputation reward
	ITEMLOG_SPLIT,							///< Split item stack
	ITEMLOG_MOVE,							///< Stack items
	ITEMLOG_ORGANIZE_BAG,					///< Organize items
	ITEMLOG_EQUIP_LEVELUP,					///< Equipment upgrade
	ITEMLOG_EQUIP_LEVELUP_FAILED,			///< Equipment upgrade failed
	ITEMLOG_EQUIP_LEVELUP_SUCCEEDED,		///< Equipment upgrade succeeded
	ITEMLOG_RECOVER_USED_UP,				///< Recovery item consumed
	ITEMLOG_MINE,							///< Mining
	ITEMLOG_ENROLL_SABAC,					///< Sabac registration
	ITEMLOG_DEATH,							///< Death
	ITEMLOG_SPELL,							///< Spell effect
	ITEMLOG_ATTACK,							///< Attack
	ITEMLOG_ATTACKED,						///< Attacked
	ITEMLOG_TRUMPET,						///< Trumpet
	ITEMLOG_CHECKIN_AWARD,					///< Check-in reward
	ITEMLOG_AWARD,							///< Platform reward
	ITEMLOG_BLACK_MARKET,					///< Black market
	ITEMLOG_MATERIAL,						///< Ore refinement
	ITEMLOG_GAMBLE,							///< Equipment reforging
	ITEMLOG_PACKAGE,						///< Gift pack
	ITEMLOG_IDENTIFY,						///< Item identification
	ITEMLOG_RANDOMIZE,                      ///< Item refinement
	ITEMLOG_LUCK_OIL,                       ///< Blessing oil
	ITEMLOG_SIGN,                           ///< Equipment signature

	ITEMLOG_TOTAL,							///< total
};

///@enum EMoneyLog
enum EMoneyLog
{
    MONEYLOG_INVALID = -1,					///< invalid
    MONEYLOG_BUY_ITEM,						///< Merchant purchase
	MONEYLOG_REPAIR,						///< Equipment repair
	MONEYLOG_PLAYER_STALL,					///< Player stall
	MONEYLOG_PLAYER_STALL_TAX,				///< Player stall tax
	MONEYLOG_PLAYER_TRADE,					///< Player trade
	MONEYLOG_PLAYER_TRADE_TAX,				///< Player trade tax
	MONEYLOG_BUY_BACK,						///< Buyback
	MONEYLOG_REFINE_ITEM,					///< Physique enhancement
	MONEYLOG_BUY_SLOTS,						///< Expand bag or bank slots
	MONEYLOG_REMOVE_SOUL,					///< Soul stone removal
	MONEYLOG_CREATE_GUILD,					///< Create guild
	MONEYLOG_GUILD_CONTRIBUTE,				///< Guild contribution
	MONEYLOG_GUILD_POP_ITEM,				///< Use guild storage
	MOMEYLOG_GUILD_ENTER_DUNGEON,			///< Enter guild dungeon
	MONEYLOG_TELEPORT_PLATFORM,				///< Teleport
	MONEYLOG_DUNGEON_SELECT_REWARD,			///< Dungeon reward
	MONEYLOG_CAST_SPELL,					///< Cast spell
	MONEYLOG_MAIL_COST,						///< Postage
	MONEYLOG_LOOT,							///< Loot
	MONEYLOG_SELL_ITEM,						///< Sell to merchant
	MONEYLOG_QUEST_PREPAY,					///< Granted on quest acceptance
	MONEYLOG_QUEST_REWARD,					///< Quest completion reward
	MONEYLOG_QUEST_COST,					///< Deducted on quest acceptance
	MONEYLOG_GUILD_SALARY,					///< Guild salary
	MONEYLOG_DUNGEON_REWARD,				///< Dungeon reward
	MONEYLOG_GM_COMMAND,					///< GM command
	MONEYLOG_SCRIPT,						///< Script
	MONEYLOG_IDENTIFY_ITEM,					///< Item identification
	MONEYLOG_RANDOMIZE_ITEM,				///< Item refinement
	MONEYLOG_QUEST_FLY_COST,				///< Teleport to quest area
	MONEYLOG_SIGN_ITEM_COST,				///< Equipment signature
	MONEYLOG_AUCTION_SELL_COST,				///< Auction house sale
	MONEYLOG_AUCTION_BUY_COST,				///< Auction house purchase
	MONEYLOG_CHANGE_WEATHER,				///< Change weather
	MONEYLOG_BUY_VIP,						///< VIP purchase
	MONEYLOG_DAILY_QUEST_BUY_COMPLETE_TIME,	///< Purchase daily quest completions
	MONEYLOG_DAILY_QUEST_BUY_ONESHOT,		///< Refresh daily quests
	MONEYLOG_OPEN_GUILD_DUNGEON,			///< Open guild dungeon
	MONEYLOG_GUILD_DECLARE_WAR,				///< Declare guild war
	MONEYLOG_DECOMPOSE,						///< Item decomposition
	MONEYLOG_COMPOSE,						///< Item crafting
    MONEYLOG_SPIRIT_EXP2PTS,				///< Soul cultivation
	MONEYLOG_SPIRIT_ADDAIR,					///< Qi cultivation
	MONEYLOG_SPIRIT_BUYSLOT,				///< Purchase spirit slots
	MONEYLOG_SPIRIT_BUYEXCHANGEAIR,			///< Equip qi
	MONEYLOG_SPIRIT_BLOOD,					///< Roll bloodline level
	MONEYLOG_REVIVE,						///< Revival
	MONEYLOG_CREATE_ARENA_TEAM,				///< Create arena team
	MONEYLOG_GUILD_BUY_AURA,				///< Purchase guild aura
	MONEYLOG_GET_MAIL_ATTACH,				///< Mail attachment
	MONEYLOG_GM,							///< GM tool
	MONEYLOG_REAL_MONEY_SHOP,				///< Cash shop
	MONEYLOG_TEAM_AUCTION_BONUS,			///< Team auction proceeds
	MONEYLOG_TEAM_AUCTION_RETURN,			///< Team auction refund
	MONEYLOG_TEAM_AUCTION_DEPOSITE,			///< Team auction
	MONEYLOG_EXCHANGE,						///< Exchange
	MONEYLOG_EXCHANGE_FEE,					///< Exchange fee
	MONEYLOG_MASTER_CZ,						///< Mentorship congratulations
	MONEYLOG_ACHIEVEMENT_REWARD,			///< Achievement reward
	MONEYLOG_RUNE,							///< Inscription
	MONEYLOG_ARENA_JOIN_SEASON,				///< Join arena season
	MONEYLOG_ARENA_RANK_REWARD,				///< Arena ranking reward
	MONEYLOG_ENROLL_SABAC,					///< Sabac registration
	MONEYLOG_EQUIP_LEVELUP,					///< Equipment upgrade
	MONEYLOG_REPUTATION_AWARD,				///< Reputation reward
	MONEYLOG_UPGRADE_STALL,					///< Stall upgrade
	MONEYLOG_MINE,							///< Mining
	MONEYLOG_AWARD,							///< Platform reward
	MONEYLOG_ERECT_STATUS,					///< Statue
	MONEYLOG_FCM_LOSS,						///< Anti-addiction deduction
	MONEYLOG_DAILY_LIMIT_LOSS,				///< Deduction for exceeding daily currency limit
	MONEYLOG_WEEKLY_LIMIT_LOSS,				///< Deduction for exceeding weekly currency limit
	MONEYLOG_TOTAL_LIMIT_LOSS,				///< Deduction for exceeding total currency limit
	MONEYLOG_CHAT_COST,						///< Chat
	MONEYLOG_ESCORT,						///< Escort
	MONEYLOG_BLACK_MARKET,					///< Black market
	MONEYLOG_MATERIAL,						///< Ore refinement
	MONEYLOG_BIRTH,							///< Create character
	MONEYLOG_EXP_MORAL,						///< Convert experience to virtue points
	MONEYLOG_TEACHER_REWARD,				///< Mentor reward
	MONEYLOG_STUDENT_REWARD,				///< Student reward

	MONEYLOG_BT_BEGIN = 10000,
	MONEYLOG_BT_01,							///< Designer-defined type 01
	MONEYLOG_BT_02,							///< Designer-defined type 02
	MONEYLOG_BT_03,							///< Designer-defined type 03
	MONEYLOG_BT_04,							///< Designer-defined type 04
	MONEYLOG_BT_05,							///< Designer-defined type 05
	MONEYLOG_BT_06,							///< Designer-defined type 06
	MONEYLOG_BT_07,							///< Designer-defined type 07
	MONEYLOG_BT_08,							///< Designer-defined type 08
	MONEYLOG_BT_09,							///< Designer-defined type 09
	MONEYLOG_BT_10,							///< Designer-defined type 10
	MONEYLOG_BT_11,							///< Designer-defined type 11
    MONEYLOG_BT_12,							///< Designer-defined type 12
    MONEYLOG_BT_13,							///< Designer-defined type 13
    MONEYLOG_BT_14,							///< Designer-defined type 14
    MONEYLOG_BT_15,							///< Designer-defined type 15
    MONEYLOG_BT_16,							///< Designer-defined type 16
    MONEYLOG_BT_17,							///< Designer-defined type 17
    MONEYLOG_BT_18,							///< Designer-defined type 18
    MONEYLOG_BT_19,							///< Designer-defined type 19
    MONEYLOG_BT_20,							///< Designer-defined type 20

    MONEYLOG_TOTAL,							///< 
};

enum EItemActionType
{
    ITEMACTION_ADD,
    ITEMACTION_DEL,
    ITEMACTION_INC,
    ITEMACTION_DEC,
    ITEMACTION_DROP,

    ITEMACTION_TOTAL
};

enum ITEM_TYPE
{
    ITEMTYPE_INVALID,
    ITEMTYPE_USABLE,        ///< Consumable
    ITEMTYPE_EQUIP,         ///< Equipment
    ITEMTYPE_MATERIAL,      ///< Material
    ITEMTYPE_FORMULA,       ///< Recipe
    ITEMTYPE_SPELLBOOK,     ///< Spellbook
    ITEMTYPE_RUNE,          ///< Rune
    ITEMTYPE_DAN,			///< Pill
    ITEMTYPE_SOUL,          ///< Soul
    ITEMTYPE_MISC,          ///< Other
    ITEMTYPE_QUEST,         ///< Quest
    ITEMTYPE_DEPOSIT,       ///< Stored value
    ITEMTYPE_RECOVER,       ///< Automatic recovery
    ITEMTYPE_RMB,           ///< Cash shop
    ITEMTYPE_TOTAL,
};

enum ITEM_SUBTYPE
{
    ITEMSUBTYPE_INVALID,

    ITEMSUBTYPE_USABLE_FOOD = 1,        ///< Food
    ITEMSUBTYPE_USABLE_DRINK,           ///< Drink
    ITEMSUBTYPE_USABLE_POTION,          ///< Potion
    ITEMSUBTYPE_USABLE_FLASK,           ///< Flask
    ITEMSUBTYPE_USABLE_SCROLL,          ///< Scroll
    ITEMSUBTYPE_USABLE_MISC,            ///< Other
    ITEMSUBTYPE_USABLE_GREY_POWDER,     ///< Gray powder
    ITEMSUBTYPE_USABLE_YELLOW_POWDER,   ///< Yellow powder
    ITEMSUBTYPE_USABLE_RUNE,            ///< Amulet

    ITEMSUBTYPE_EQUIP_WEAPON = 1,       ///< Weapon
    ITEMSUBTYPE_EQUIP_HAT,              ///< Hat
    ITEMSUBTYPE_EQUIP_SHOULDER_ARMOR,   ///< Shoulder armor
    ITEMSUBTYPE_EQUIP_CHEST_ARMOR,      ///< Chest armor
    ITEMSUBTYPE_EQUIP_WRIST_ARMOR,      ///< Wrist armor
    ITEMSUBTYPE_EQUIP_BELT,             ///< Belt
    ITEMSUBTYPE_EQUIP_SHOES,            ///< Shoes
    ITEMSUBTYPE_EQUIP_CLOAK,            ///< Cloak
    ITEMSUBTYPE_EQUIP_NECKLACE,         ///< Necklace
    ITEMSUBTYPE_EQUIP_RING,             ///< Ring
    ITEMSUBTYPE_EQUIP_BRACELET,         ///< Bracelet

    ITEMSUBTYPE_MATERIAL_REFINE = 1,    ///< Enhancement material
    ITEMSUBTYPE_MATERIAL_COMPOSE,       ///< Crafting material
    ITEMSUBTYPE_MATERIAL_WEAPON_LEVELUP,///< Weapon upgrade material
    ITEMSUBTYPE_MATERIAL_MISC,          ///< Miscellaneous material

    ITEMSUBTYPE_FORMULA_DEFAULT = 1,

    ITEMSUBTYPE_SPELLBOOK_PLAYER = 1,   ///< Player spellbook
    ITEMSUBTYPE_SPELLBOOK_PET,          ///< Pet spellbook

    ITEMSUBTYPE_RUNE_DEFAULT = 1,
    ITEMSUBTYPE_DAN_DEFAULT = 1,
    ITEMSUBTYPE_SOUL_DEFAULT = 1,

    ITEMSUBTYPE_MISC_DEFAULT = 1,
    ITEMSUBTYPE_MISC_PET,               ///< Pet
    ITEMSUBTYPE_MISC_MOUNT,             ///< Mount

    ITEMSUBTYPE_QUEST_DEFAULT = 1,

    ITEMSUBTYPE_DEPOSIT_SOUL = 1,       ///< Soul bottle
    ITEMSUBTYPE_DEPOSIT_EXP,            ///< Experience bottle

    ITEMSUBTYPE_RECOVER_HP = 1,
    ITEMSUBTYPE_RECOVER_MP,
    ITEMSUBTYPE_RECOVER_HPMP,

    ITEMSUBTYPE_RMB_DEFAULT = 1
};

enum WEAPON_TYPE
{
    WEAPONTYPE_INVALID = -1,
    WEAPONTYPE_HAND,            ///< Unarmed
    WEAPONTYPE_01,              ///< One-handed slashing weapon
    WEAPONTYPE_02,              ///< One-handed blunt weapon
    WEAPONTYPE_03,              ///< Two-handed heavy short weapon
    WEAPONTYPE_04,              ///< Two-handed heavy polearm
    WEAPONTYPE_05,              ///< Dual-wield heavy weapons
    WEAPONTYPE_06,              ///< Two-handed eastern polearm
    WEAPONTYPE_07,              ///< Dual-wield gloves
    WEAPONTYPE_08,              ///< Dual-wield short weapons
    WEAPONTYPE_09,              ///< Dual-wield chain blades
    WEAPONTYPE_10,              ///< Dual-wield hand crossbows
    WEAPONTYPE_11,              ///< Crossbow
    WEAPONTYPE_12,              ///< Bow
    WEAPONTYPE_13,              ///< One-handed short weapon
    WEAPONTYPE_14,              ///< Staff
    WEAPONTYPE_15,              ///< Sword (one-handed eastern short weapon)
    WEAPONTYPE_16,              ///< Fan
    WEAPONTYPE_17,              ///< Rod
    WEAPONTYPE_TOTAL
};

enum ARMOR_TYPE
{
    ARMORTYPE_INVALID = -1,
    ARMORTYPE_NO_ARMOR,         ///< Unarmored
    ARMORTYPE_CLOTH,            ///< Cloth armor
    ARMORTYPE_LEATHER,          ///< Leather armor
    ARMORTYPE_CHAIN,            ///< Mail armor
    ARMORTYPE_PLATE,            ///< Plate armor
    ARMORTYPE_BACK,             ///< Cloak
    ARMORTYPE_JEWELRY,          ///< Jewelry
    ARMORTYPE_AVATAR            ///< Costume
};

enum ITEM_COLOR
{
    ITEMCOLOR_INVALID = -1,
    ITEMCOLOR_WHITE,            ///< White
    ITEMCOLOR_GREEN,            ///< Green
    ITEMCOLOR_BLUE,             ///< Blue
    ITEMCOLOR_PURPLE,           ///< Purple
    ITEMCOLOR_ORANGE,           ///< Orange
    ITEMCOLOR_RESERVED1,        ///< Reserved 1
    ITEMCOLOR_RESERVED2,        ///< Reserved 2
    ITEMCOLOR_TOTAL
};

enum ITEM_COMBAT_TYPE
{
    ITEMCOMBAT_BOTH,    ///< Item can be used regardless of combat state
    ITEMCOMBAT_IN,      ///< Item must be used in combat
    ITEMCOMBAT_OUT      ///< Item must be used out of combat
};

enum DUR_TYPE
{
    DURTYPE_NONE,   ///< No durability
    DURTYPE_EQUIP,  ///< Equipment durability
    DURTYPE_STACK,  ///< Stack items
    DURTYPE_USE,    ///< Number of uses
    DURTYPE_DEPOSIT,///< Stored value
    DURTYPE_RECOVER,///< Automatic recovery
    DURTYPE_PURITY  ///< Purity
};

#define EQUIP_DUR_MULTIPLIER (1000)

enum BIND_TYPE
{
    BINDTYPE_NONE,      ///< Not bound
    BINDTYPE_BOU,       ///< Bind on use
    BINDTYPE_BOE,       ///< Bind on equip
    BINDTYPE_BOP,       ///< Bind on pickup
    BINDTYPE_BOT,       ///< Bind on trade
    BINDTYPE_BINDED = 10///< Bound
};

enum PK_DROP_TYPE
{
    PKDROP_BY_CHANCE,   ///< Random
    PKDROP_NOT_DROP,    ///< Never drops
    PKDROP_MUST_DROP,   ///< Always drops
};

enum IDENTIFY_TYPE
{
    IDENTIFY_TYPE_NO,       ///< Unidentified
    IDENTIFY_TYPE_YES,      ///< Identified
    IDENTIFY_TYPE_LEVEL_UP, ///< Identified; awaiting weapon trial
};

enum CONTAINER_SLOT
{
    CONSLOT_EQUIPPED,       ///< Equipped items
    CONSLOT_DEFAULT,        ///< Default bag
    CONSLOT_BANK,           ///< Bank
    CONSLOT_HERO_EQUIPPED,  ///< Hero equipped items
    CONSLOT_HERO_EQUIPMENT, ///< Hero bag
    CONSLOT_DEPOSIT,        ///< Stored-value slots
    CONSLOT_RECOVER,
    CONSLOT_COUNT,

	///<  client only
	CONSLOT_P2P_MY,         ///< My P2P trade slots
	CONSLOT_P2P_TG,         ///< Other player’s P2P trade slots
	CONSLOT_STALL_SETTING,  ///< 
	CONSLOT_STALL_BUY,      ///< 
    CONSLOT_PROFILE,        ///< View another player’s information
	CONSLOT_GUILD_BANK,		///< Guild storage

    ///<  server only
    CONSLOT_WEAPON_LEVEL_UP = 100,///< Weapon refinement
};

enum NORMAL_EQUIP_SLOT
{
    //Slot                         Equipable item
    //------------------------------------------------------------
    NES_MAIN_HAND,  ///< Hand                         Weapon
    NES_BODY,       ///< Body                         Chest armor
    NES_BACK,       ///< Back                         Cloak
    NES_HEAD,       ///< Head                         Hat
    NES_SHOULDER,   ///< Shoulder                     Shoulder armor
    NES_ARM,        ///< Arm                          Wrist armor
    NES_WAIST,      ///< Waist                        Belt
    NES_FOOT,       ///< Foot                         Shoes
    NES_NECK,       ///< Neck                         Necklace
    NES_FINGER_L,   ///< Left finger                  Ring
    NES_FINGER_R,   ///< Right finger                 Ring
    NES_WRIST_L,    ///< Left wrist                   Bracelet
    NES_WRIST_R,    ///< Right wrist                  Bracelet
    NES_TOTAL,
    NES_VISIBLE_TOTAL = NES_BACK + 1
};

inline bool IsAppearance(UINT16 conslot, UINT16 itemslot)
{
    return ((conslot == CONSLOT_EQUIPPED||conslot == CONSLOT_HERO_EQUIPPED) && itemslot < NES_VISIBLE_TOTAL);
}

enum DEPOSIT_ITEM_SLOT
{
    DEPOSIT_SOUL_SLOT,
    DEPOSIT_EXP_SLOT,
    DEPOSIT_ITEM_SLOT_TOTAL
};

enum SOCKET_TYPE
{
    SOCKET_NONE,
    SOCKET_RED,
    SOCKET_YELLOW,
    SOCKET_BLUE,
    SOCKET_GREEN,
    SOCKET_PURPLE,
    SOCKET_COLORFUL,
    SOCKET_TYPE_COUNT
};

enum EStallState
{
    essNotOpen,
    essPreparing,
    essOpen
};

#define MAX_TRADE_SLOT (6)
enum ETradeState
{
    etsFree,            ///< Not trading
    etsAsking,          ///< Requesting
    etsBeingAsked,      ///< Request received
    etsTrading,         ///< Trading
    etsLocked,          ///< Locked
    etsConfirmed,       ///< Confirmed
    etsSuccess
};

#define MAX_SOLD_ITEMS (10)

#define AUCTION_SEARCH_RESULT_ITEMS_PER_PAGE (50)

enum EAuctionSearchResultSortBy
{
    esbTotalPrice,
    esbSinglePrice,
    esbBuyoutPrice,
    esbBuyoutSinglePrice,
    esbTotal
};

enum EAuctionStatus
{
    easInvalid,
    easBid,
    easNotBid
};

enum EOrderType
{
    eotInvalid,
    eotBuy,
    eotSell
};

enum EOrderStatus
{
    eosInvalid,
    eosEffective,   //Active order
    eosCanceled,    //Canceled by user
    eosExpired,     //Canceled after timeout
    eosFinished,    //Fully filled
    eosTotal,
};

enum EBlackMarketLimitType
{
    ebmltNone,
    ebmltRole,
    ebmltServer
};

#define MAX_RUNE_COUNT          (6)         ///<  Inscription sockets on a weapon, maximum 6

#define MAX_SOCKET_COUNT        (3)         ///<  Soul sockets per equipment item, maximum 3

struct DROP_CHANCE_DATA
{
	INT32 nDropGroupID;
	INT32 nDropChance;
};



static const INT32 EMPTY_SOCKET_SELL_PRICE = 1;
static const INT32 RUNE_SELL_PRICE = 1;

static const UINT8 INVALID_ITEM_SLOT = 255;

static const INT32 TRADE_TAX = 700; ///< In ten-thousandths, i.e. 7%

static const INT8 INIT_CONTAINER_SIZE[CONSLOT_COUNT] = { NES_TOTAL, 32, 16, NES_TOTAL, 16, DEPOSIT_ITEM_SLOT_TOTAL, 1 };
static const INT8 MAX_CONTAINER_SIZE[CONSLOT_COUNT] = { NES_TOTAL, 64, 72, NES_TOTAL, 16, DEPOSIT_ITEM_SLOT_TOTAL, 1 };
static const INT32 GM_MAX_ITEM_COUNT = NES_TOTAL + 64 + 72 + NES_TOTAL + 16 + DEPOSIT_ITEM_SLOT_TOTAL + 1;

static const INT32 MAX_RANDOM_ATTR_COUNT = 4;   ///< Random attributes on an item, maximum 4

static const UINT8 MAX_SOUL_UPGRADE_SRC = 5;    ///< Soul upgrades consume at most 5 other souls

static const UINT8 MAX_REFINE_COST_COUNT = 3;
static const UINT8 MAX_REFINE_ATTR_COUNT = 5;

static const UINT8 MAX_SET_PART_COUNT = 8; ///< Maximum set pieces
static const UINT8 MAX_SET_ATTR_COUNT = 8; ///< Maximum set attributes

static const INT32 RUNE_ITEM_COST = 10000;               ///< Inscription refinement cost
static const INT32 RUNE_ITEMID_WARRIOR_1 = 21001;       ///< Inscription stones consumed by refinement
static const INT32 RUNE_ITEMID_MAGE_1 = 21002;          ///< Inscription stones consumed by refinement
static const INT32 RUNE_ITEMID_TAOIST_1 = 21003;        ///< Inscription stones consumed by refinement
static const INT32 RUNE_ITEMID_WARRIOR_2 = 21011;       ///< Inscription stones consumed by refinement
static const INT32 RUNE_ITEMID_MAGE_2 = 21012;          ///< Inscription stones consumed by refinement
static const INT32 RUNE_ITEMID_TAOIST_2 = 21013;        ///< Inscription stones consumed by refinement

static const UINT8 MAX_DECOMPOSE_ITEM_COUNT = 3; ///< Equipment decomposition produces at most 3 items
static const UINT8 MAX_COMPOSE_ITEM_COUNT = 6;   ///< Equipment crafting requires at most 6 material types

static const INT32 SIGN_ITEM_COST = 100; ///< Gold cost to sign equipment
static const INT32 AUCTION_FEE_RATE = 80;///< Refund 80% of the auction storage fee
static const INT32 AUCTION_TAX = 10;     ///< Auction tax 5%
static const INT32 MAX_AUCTION_SELLING_ITEMS = 10;
static const INT32 MAX_AUCTION_BUYING_ITEMS = 10;

static const INT32 MAX_EXCHANGE_PRICE_COUNT = 5;
static const INT32 MAX_EXCHANGE_SELLING_ORDERS = 5;
static const INT32 MAX_EXCHANGE_BUYING_ORDERS = 5;
static const INT32 EXCHANGE_FEE = 100;
static const INT32 EXCHANGE_TAX = 2;
static const UINT32 EXCHANGE_TIME = 48 * 60 * 60;
static const UINT32 MAX_EXCHANGE_FINISHED_ORDERS = 200;
static const UINT32 MAX_EXCHANGE_LOGS = 200;

static const INT32 WEAPON_LEVEL_UP_COST = 10000;
#ifdef _DEBUG
static const UINT32 WEAPON_LEVEL_UP_TIME = 15;
#else
static const UINT32 WEAPON_LEVEL_UP_TIME = 60 * 60 * 2;
#endif

static const INT32 AUTO_RECOVER_HP_MIN_DIFF = 100;
static const INT32 AUTO_RECOVER_MP_MIN_DIFF = 100;
static const INT32 AUTO_RECOVER_HP_POINT = 100;
static const INT32 AUTO_RECOVER_MP_POINT = 100;

static const INT32 EQUIP_MAX_DUR_RANDOM_MAX = 12000;
static const INT32 EQUIP_MAX_DUR_RANDOM_MIN = 8000;
static const INT32 EQUIP_CUR_DUR_RANDOM = 8000;

static const INT32 STALL_SLOT_COUNT = 10;
static const INT32 STALL_UPGRADE_COST[3][2] = { { 3, 50000 }, { 7, 100000 }, { 15, 200000 } };

static const INT32 MAX_TIMES_EXP_BOTTLE_USE = 5;

static const INT32 USE_MATERIAL_WEAPON_ID = 99900040;

static const INT32 GUILD_RUNE_COST = 1000;

static const INT32 EXERCISE_COST_PER_HOUR = 720;
static const INT32 MAX_EXERCISE_TIME = 9999;

#endif	// _ITEM_DEF_H_
