/**
 * Copyright 1998-2012 Epic Games, Inc. All Rights Reserved.
 */

#ifndef INCLUDED_ONLINESUBSYSTEMSTEAMWORKSBRIDGE_H
#define INCLUDED_ONLINESUBSYSTEMSTEAMWORKSBRIDGE_H 1

#if WITH_UE3_NETWORKING && WITH_STEAMWORKS

/**
 * The callback bridge classes in this file are tied to callbacks from Steam, and are used to relay those callbacks/events to the native
 * UScript-linked classes; this is done using non-UScript classes to both keep the code tidy, and to prevent issues with native/UScript class
 * size mismatches (due to the properties used for handling callbacks)
 *
 *
 * Steam Callback Types:
 *	1: 'Static' events/callbacks:
 *		These correspond to a single general event, e.g. a friend invite, and are only registered (i.e. hooked up) once;
 *		they are handled in the Steam SDK through the CCallback class, and are setup within UE3 using the 'STATIC_STEAM_CALLBACK' and
 *		'STATIC_STEAM_GAMESERVER_CALLBACK' macros
 *
 *	2: 'Dynamic' events/callbacks:
 *		These represent asynchronous data requests with Steam (e.g. requesting multiple players stats data),
 *		and there is a unique callback for each request; each request, represented by a 'SteamAPICall_t' reference, must be
 *		'registered'/tracked individually.
 *
 *		These are handled in the Steam SDK through the CCallResult class, however, this class should not be used, as callbacks tracked
 *		using this class sometimes trigger untraceable Steam SDK crashes (in cases where a lot of consecutive results are pending).
 *
 *		To avoid crashes, dynamic callbacks >MUST< be handled manually, instead of through CCallResult; this is done in UE3 using the
 *		'DYNAMIC_STEAM_CALLBACK' and 'DYNAMIC_STEAM_GAMESERVER_CALLBACK' macros
 *
 *	3: Game server callbacks:
 *		These are static or dynamic callbacks, which are linked to the Steam game server interfaces, instead of the regular Steam Client
 *		interfaces. In UE3, these are setup using the 'STATIC_STEAM_GAMESERVER_CALLBACK' and 'DYNAMIC_STEAM_GAMESERVER_CALLBACK' macros
 *
 *
 * Callback components:
 *	- Data struct:
 *		This is the struct in the Steam SDK that defines the data a callback will return, e.g:
 * 		struct UserStatsReceived_t
 * 		{
 * 			enum { k_iCallback = k_iSteamUserStatsCallbacks + 1 };
 * 			uint64		m_nGameID;	// Game these stats are for
 * 			EResult		m_eResult;	// Success / error fetching the stats
 * 			CSteamID	m_steamIDUser;	// The user for whom the stats are retrieved for
 * 		};
 *
 *	- Callback manager: 
 *		For static callbacks, this is the 'CCallback' instance/wrapper that handles registering and passing on a callback, usually specified
 *		using the 'STATIC_STEAM_CALLBACK' macro, e.g:
 *		STATIC_STEAM_CALLBACK(SteamCallbackBridge, OnUserStatsReceived, UserStatsReceived_t);
 *
 *		For dynamic callbacks, this is the internal 'Poll*Requests()' function, implemented by the 'DYNAMIC_STEAM_CALLBACK' macro, which
 *		handles checking if the asynchronous call has completed, e.g:
 *		DYNAMIC_STEAM_CALLBACK(OnSpecificUserStatsReceived, AddSpecificUserStatsRequest, UserStatsReceived_t);
 *		...
 *		void PollCallbacks()
 *		{
 *			...
 *			POLL_DYNAMIC_STEAM_CALLBACK(OnSpecificUserStatsReceived);
 *			...
 *		}
 *
 *	- Callback interface:
 *		This is a reference to the UScript-linked class that will be receiving the callbacks; the reference must be placed in the callback
 *		bridge, and must be named 'CallbackInterface', e.g:
 *		UOnlineSubsystemSteamworks* CallbackInterface;
 *
 *		All callbacks must be implemented in the callback interface, in the following format:
 *		void CallbackInterface::CallbackName(DataStruct* CallbackData)
 *
 *		For example:
 *		void UOnlineSubsystemSteamworks::OnUserStatsReceived(UserStatsReceived_t* CallbackData)
 *
 *
 * Registering callbacks:
 *	1: Automatic:
 *		All static callbacks are registered in the callback bridge constructor, using the 'CONSTRUCT_STATIC_STEAM_CALLBACK' macro
 *		(this macro is used in the constructor instantiation list; see callback bridge code below for examples)
 *
 *	2: Manual:
 *		This applies to dynamic callbacks; these are not 'registered' like static callbacks are, but instead each 'request' is stored
 *		and individually tracked, until the request completes. The function used to add requests is defined by the 'DYNAMIC_STEAM_CALLBACK'
 *		macro, e.g: (in this case, 'AddSpecificUserStatsRequest')
 *		DYNAMIC_STEAM_CALLBACK(OnSpecificUserStatsReceived, AddSpecificUserStatsRequest, UserStatsReceived_t);
 *
 *
 * Triggering callbacks:
 *	1: Automatic:
 *		Static callbacks are triggered automatically, through SteamAPI_RunCallbacks() in UOnlineSubsystemSteamworks::TickSteamworksTasks
 *
 *	2: Manual:
 *		This is only applicable to dynamic callbacks which use the 'DYNAMIC_STEAM_CALLBACK' macros (as opposed to CCallResult, which should
 *		not be used due to stability issues); dynamic callbacks are polled and triggered through the internal 'Poll*Callbacks()' function
 *		implemented by the 'DYNAMIC_STEAM_CALLBACK' macro.
 *
 *		This internal 'Poll*Callbacks()' function is triggered using the 'POLL_DYNAMIC_STEAM_CALLBACK' macro, which is placed within the
 *		callback bridges primary 'PollCallbacks' function. In turn, the primary 'PollCallbacks' function for the bridge must be triggered
 *		every Tick (usually by the UScript-linked class which owns the callback bridge).
 */


/**
 * Static callbacks
 */

/**
 * Implements a static Steam callback (specified by the input struct)
 * NOTE: This must go within the body of the bridge class
 * NOTE: Do not put this into a UScript-linked class, it will cause a mismatch between script/native class sizes
 *
 * @param BridgeClass		The class that will be used to relay this callback from the Steam SDK to UE3
 * @param CallbackName		The name of the function (in the UE3 script class) that will receive the callback
 * @param DataStruct		The Steam SDK data struct that represents the callback and the data it returns
 */
#define STATIC_STEAM_CALLBACK(BridgeClass, CallbackName, DataStruct) \
private: \
	STEAM_CALLBACK(BridgeClass, CallbackName, DataStruct, CallbackName##Callback) \
	{ \
		CallbackInterface->CallbackName(pParam); \
	} \
public:

/**
 * Implements a static Steam callback (specified by the input struct), that uses the Steam game server interface
 * NOTE: This must go within the body of the bridge class
 * NOTE: Do not put this into a UScript-linked class, it will cause a mismatch between script/native class sizes
 *
 * @param BridgeClass		The class that will be used to relay this callback from the Steam SDK to UE3
 * @param CallbackName		The name of the function (in the UE3 script class) that will receive the callback
 * @param DataStruct		The Steam SDK data struct that represents the callback and the data it returns
 */
#define STATIC_STEAM_GAMESERVER_CALLBACK(BridgeClass, CallbackName, DataStruct) \
private: \
	STEAM_GAMESERVER_CALLBACK(BridgeClass, CallbackName, DataStruct, CallbackName##Callback) \
	{ \
		CallbackInterface->CallbackName(pParam); \
	} \
public:

/**
 * Constructs the member variables for the specified static Steam callback
 * NOTE: This must be put in the instantiation list for the bridge class's constructor
 *
 * @param BridgeClass		The class that will be used to relay this callback from the Steam SDK to UE3
 * @param CallbackName		The name of the function (in the UE3 script class) that will receive the callback
 */
#define CONSTRUCT_STATIC_STEAM_CALLBACK(BridgeClass, CallbackName) \
	CallbackName##Callback(this, &##BridgeClass##::##CallbackName)


/**
 * Dynamic callbacks
 */

/**
 * Implements a dynamic Steam callback (specified by the input struct), and methods required for adding/polling callback requests
 * NOTE: This must go within the body of the bridge class
 * NOTE: Do not put this into a UScript-linked class, it will cause a mismatch between script/native class sizes
 *
 * @param CallbackName		The name of the function (in the UE3 script class) that will receive the callback
 * @param AddCallbackFunc	The name of the function (within the bridge class) that will be used to add callback requests for polling
 * @param DataStruct		The Steam SDK data struct that represents the callback and the data it returns
 */
#define DYNAMIC_STEAM_CALLBACK(CallbackName, AddCallbackFunc, DataStruct) \
	BASE_DYNAMIC_STEAM_CALLBACK(CallbackName, AddCallbackFunc, DataStruct, GSteamUtils)

/**
 * Implements a dynamic Steam callback (that uses the Steam game server interface), and methods required for adding/polling callback requests
 * NOTE: This must go within the body of the bridge class
 * NOTE: Do not put this into a UScript-linked class, it will cause a mismatch between script/native class sizes
 *
 * @param CallbackName		The name of the function (in the UE3 script class) that will receive the callback
 * @param AddCallbackFunc	The name of the function (within the bridge class) that will be used to add callback requests for polling
 * @param DataStruct		The Steam SDK data struct that represents the callback and the data it returns
 */
#define DYNAMIC_STEAM_GAMESERVER_CALLBACK(CallbackName, AddCallbackFunc, DataStruct) \
	BASE_DYNAMIC_STEAM_CALLBACK(CallbackName, AddCallbackFunc, DataStruct, GSteamGameServerUtils)


/**
 * Internal implementation of the above dynamic Steam callback macros
 */
#define BASE_DYNAMIC_STEAM_CALLBACK(CallbackName, AddCallbackFunc, DataStruct, SteamInterface) \
public: \
	void AddCallbackFunc(SteamAPICall_t ApiCall) \
	{ \
		CallbackName##Callbacks.AddItem(ApiCall); \
	} \
	\
	FORCEINLINE void Poll##CallbackName##Requests() \
	{ \
		for (INT i=0; i<CallbackName##Callbacks.Num(); i++) \
		{ \
			SteamAPICall_t CurCallback = CallbackName##Callbacks(i); \
			bool bFailed = FALSE; \
			\
			if (SteamInterface->IsAPICallCompleted(CurCallback, &bFailed)) \
			{ \
				DataStruct Result; \
				UBOOL bSuccess = SteamInterface->GetAPICallResult(CurCallback, &Result, sizeof(Result), Result.k_iCallback, &bFailed); \
				\
				CallbackInterface->CallbackName(&Result, !bSuccess || bFailed); \
				\
				/* Remove the current entry */ \
				CallbackName##Callbacks.Remove(i, 1); \
				i--; \
			} \
		} \
	} \
	\
private: \
	TArray<SteamAPICall_t> CallbackName##Callbacks; \
public:


/**
 * Custom dynamic callbacks - allows you to track extra data alongside each callback
 */

/**
 * Implements a special dynamic Steam callback, where each callback has data stored alongside it for tracking
 * NOTE: This must go within the body of the bridge class
 * NOTE: Do not put this into a UScript-linked class, it will cause a mismatch between script/native class sizes
 *
 * @param CallbackName		The name of the function (in the UE3 script class) that will receive the callback
 * @param AddCallbackFunc	The name of the function (within the bridge class) that will be used to add callback requests for polling
 * @param DataStruct		The Steam SDK data struct that represents the callback and the data it returns
 * @param CustomDataType	The data type that is stored alongside each callback
 */
#define CUSTOM_DYNAMIC_STEAM_CALLBACK(CallbackName, AddCallbackFunc, DataStruct, CustomDataType) \
	BASE_CUSTOM_DYNAMIC_STEAM_CALLBACK(CallbackName, AddCallbackFunc, DataStruct, CustomDataType, GSteamUtils)

/**
 * Implements a special dynamic Steam callback, where each callback has data stored alongside it for tracking
 * NOTE: This must go within the body of the bridge class
 * NOTE: Do not put this into a UScript-linked class, it will cause a mismatch between script/native class sizes
 *
 * @param CallbackName		The name of the function (in the UE3 script class) that will receive the callback
 * @param AddCallbackFunc	The name of the function (within the bridge class) that will be used to add callback requests for polling
 * @param DataStruct		The Steam SDK data struct that represents the callback and the data it returns
 * @param CustomDataType	The data type that is stored alongside each callback
 */
#define CUSTOM_DYNAMIC_STEAM_GAMESERVER_CALLBACK(CallbackName, AddCallbackFunc, DataStruct, CustomDataType) \
	BASE_CUSTOM_DYNAMIC_STEAM_CALLBACK(CallbackName, AddCallbackFunc, DataStruct, CustomDataType GSteamGameServerUtils)

/**
 * Internal implementation of the above dynamic Steam callback macros
 */
#define BASE_CUSTOM_DYNAMIC_STEAM_CALLBACK(CallbackName, AddCallbackFunc, DataStruct, CustomDataType, SteamInterface) \
public: \
	void AddCallbackFunc(SteamAPICall_t ApiCall, CustomDataType CustomData) \
	{ \
		CallbackName##Callbacks.Set(ApiCall, CustomData); \
	} \
	\
	FORCEINLINE void Poll##CallbackName##Requests() \
	{ \
		for (TMap<SteamAPICall_t, CustomDataType>::TIterator It(CallbackName##Callbacks); It; ++It) \
		{ \
			SteamAPICall_t CurCallback = It.Key(); \
			bool bFailed = FALSE; \
			\
			if (SteamInterface->IsAPICallCompleted(CurCallback, &bFailed)) \
			{ \
				DataStruct Result; \
				UBOOL bSuccess = SteamInterface->GetAPICallResult(CurCallback, &Result, sizeof(Result), Result.k_iCallback, &bFailed); \
				\
				CallbackInterface->CallbackName(&Result, It.Value(), !bSuccess || bFailed); \
				\
				/* Remove the current entry */ \
				It.RemoveCurrent(); \
			} \
		} \
	} \
	\
private: \
	TMap<SteamAPICall_t, CustomDataType> CallbackName##Callbacks; \
public:



/**
 * Polls any pending requests for the specified dynamic Steam callback, to see if they have completed, and triggers the callback if so
 *
 * @param CallbackName		The name of the function (in the UE3 script class) that will receive the callback
 */
#define POLL_DYNAMIC_STEAM_CALLBACK(CallbackName) \
	Poll##CallbackName##Requests()


/**
 * UOnlineSubsystemSteamworks bridge
 */
class SteamCallbackBridge
{
public:
	SteamCallbackBridge(UOnlineSubsystemSteamworks* Subsystem)
		: CallbackInterface(Subsystem)
		, CONSTRUCT_STATIC_STEAM_CALLBACK(SteamCallbackBridge, OnUserStatsReceived)
		, CONSTRUCT_STATIC_STEAM_CALLBACK(SteamCallbackBridge, OnUserStatsStored)
		, CONSTRUCT_STATIC_STEAM_CALLBACK(SteamCallbackBridge, OnGameOverlayActivated)
		, CONSTRUCT_STATIC_STEAM_CALLBACK(SteamCallbackBridge, OnSteamShutdown)
		, CONSTRUCT_STATIC_STEAM_CALLBACK(SteamCallbackBridge, OnGameServerChangeRequested)
		, CONSTRUCT_STATIC_STEAM_CALLBACK(SteamCallbackBridge, OnGameJoinRequested)
		, CONSTRUCT_STATIC_STEAM_CALLBACK(SteamCallbackBridge, OnSteamServersConnected)
		, CONSTRUCT_STATIC_STEAM_CALLBACK(SteamCallbackBridge, OnSteamServersDisconnected)
		, CONSTRUCT_STATIC_STEAM_CALLBACK(SteamCallbackBridge, OnAvatarImageLoaded)
		, CONSTRUCT_STATIC_STEAM_CALLBACK(SteamCallbackBridge, OnGSPolicyResponse)
		, CONSTRUCT_STATIC_STEAM_CALLBACK(SteamCallbackBridge, OnGSClientAchievementStatus)
		, CONSTRUCT_STATIC_STEAM_CALLBACK(SteamCallbackBridge, OnGSSteamServersConnected)
		, CONSTRUCT_STATIC_STEAM_CALLBACK(SteamCallbackBridge, OnGSSteamServersDisconnected)
	{
	}

	STATIC_STEAM_CALLBACK(SteamCallbackBridge, OnUserStatsReceived, UserStatsReceived_t);
	STATIC_STEAM_CALLBACK(SteamCallbackBridge, OnUserStatsStored, UserStatsStored_t);
	STATIC_STEAM_CALLBACK(SteamCallbackBridge, OnGameOverlayActivated, GameOverlayActivated_t);
	STATIC_STEAM_CALLBACK(SteamCallbackBridge, OnSteamShutdown, SteamShutdown_t);
	STATIC_STEAM_CALLBACK(SteamCallbackBridge, OnGameServerChangeRequested, GameServerChangeRequested_t);
	STATIC_STEAM_CALLBACK(SteamCallbackBridge, OnGameJoinRequested, GameRichPresenceJoinRequested_t);
	STATIC_STEAM_CALLBACK(SteamCallbackBridge, OnSteamServersConnected, SteamServersConnected_t);
	STATIC_STEAM_CALLBACK(SteamCallbackBridge, OnSteamServersDisconnected, SteamServersDisconnected_t);
	STATIC_STEAM_CALLBACK(SteamCallbackBridge, OnAvatarImageLoaded, AvatarImageLoaded_t);

	STATIC_STEAM_GAMESERVER_CALLBACK(SteamCallbackBridge, OnGSPolicyResponse, GSPolicyResponse_t);
	STATIC_STEAM_GAMESERVER_CALLBACK(SteamCallbackBridge, OnGSClientAchievementStatus, GSClientAchievementStatus_t);
	STATIC_STEAM_GAMESERVER_CALLBACK(SteamCallbackBridge, OnGSSteamServersConnected, SteamServersConnected_t);
	STATIC_STEAM_GAMESERVER_CALLBACK(SteamCallbackBridge, OnGSSteamServersDisconnected, SteamServersDisconnected_t);


	DYNAMIC_STEAM_CALLBACK(OnGlobalStatsReceived, AddGlobalStatsRequest, GlobalStatsReceived_t);
	DYNAMIC_STEAM_CALLBACK(OnSpecificUserStatsReceived, AddSpecificUserStatsRequest, UserStatsReceived_t);
	DYNAMIC_STEAM_CALLBACK(OnNumberOfCurrentPlayers, AddNumberOfCurrentPlayersRequest, NumberOfCurrentPlayers_t);
	DYNAMIC_STEAM_CALLBACK(OnUserFindLeaderboard, AddUserFindLeaderboard, LeaderboardFindResult_t);
	DYNAMIC_STEAM_CALLBACK(OnUserDownloadedLeaderboardEntries, AddUserDownloadedLeaderboardEntries, LeaderboardScoresDownloaded_t);
	DYNAMIC_STEAM_CALLBACK(OnUserUploadedLeaderboardScore, AddUserUploadedLeaderboardScore, LeaderboardScoreUploaded_t);
	CUSTOM_DYNAMIC_STEAM_CALLBACK(OnRemoteStorageFileShareResult, AddRemoteStorageFileShareCallback, RemoteStorageFileShareResult_t,
					RemoteStorageCallbackData);
	DYNAMIC_STEAM_CALLBACK(OnRemoteStorageFileShareDownload, AddRemoteStorageDownloadCallback, RemoteStorageDownloadUGCResult_t);

	DYNAMIC_STEAM_GAMESERVER_CALLBACK(OnSpecificGSStatsReceived, AddSpecificGSStatsRequest, GSStatsReceived_t);
	DYNAMIC_STEAM_GAMESERVER_CALLBACK(OnSpecificGSStatsStored, AddSpecificGSStatsStore, GSStatsStored_t);


	void PollCallbacks()
	{
		POLL_DYNAMIC_STEAM_CALLBACK(OnGlobalStatsReceived);
		POLL_DYNAMIC_STEAM_CALLBACK(OnSpecificUserStatsReceived);
		POLL_DYNAMIC_STEAM_CALLBACK(OnNumberOfCurrentPlayers);
		POLL_DYNAMIC_STEAM_CALLBACK(OnUserFindLeaderboard);
		POLL_DYNAMIC_STEAM_CALLBACK(OnUserDownloadedLeaderboardEntries);
		POLL_DYNAMIC_STEAM_CALLBACK(OnUserUploadedLeaderboardScore);
		POLL_DYNAMIC_STEAM_CALLBACK(OnRemoteStorageFileShareResult);
		POLL_DYNAMIC_STEAM_CALLBACK(OnRemoteStorageFileShareDownload);

		POLL_DYNAMIC_STEAM_CALLBACK(OnSpecificGSStatsReceived);
		POLL_DYNAMIC_STEAM_CALLBACK(OnSpecificGSStatsStored);
	}

private:
	UOnlineSubsystemSteamworks* CallbackInterface;
};



/**
 * UOnlineAuthInterfaceSteamworks bridge
 */

// Bridge between Steamworks auth callbacks, and UOnlineAuthInterfaceSteamworks
class SteamAuthCallbackBridge
{
public:
	SteamAuthCallbackBridge(UOnlineAuthInterfaceSteamworks* AuthInterface)
		: CallbackInterface(AuthInterface)
		, CONSTRUCT_STATIC_STEAM_CALLBACK(SteamAuthCallbackBridge, OnClientGameServerDeny)
		, CONSTRUCT_STATIC_STEAM_CALLBACK(SteamAuthCallbackBridge, OnClientValidateAuth)
		, CONSTRUCT_STATIC_STEAM_CALLBACK(SteamAuthCallbackBridge, OnGSClientApprove)
		, CONSTRUCT_STATIC_STEAM_CALLBACK(SteamAuthCallbackBridge, OnGSClientDeny)
		, CONSTRUCT_STATIC_STEAM_CALLBACK(SteamAuthCallbackBridge, OnGSClientValidateAuth)
		, CONSTRUCT_STATIC_STEAM_CALLBACK(SteamAuthCallbackBridge, OnGSClientKick)
	{
	}

	STATIC_STEAM_CALLBACK(SteamAuthCallbackBridge, OnClientGameServerDeny, ClientGameServerDeny_t);
	STATIC_STEAM_CALLBACK(SteamAuthCallbackBridge, OnClientValidateAuth, ValidateAuthTicketResponse_t);

	STATIC_STEAM_GAMESERVER_CALLBACK(SteamAuthCallbackBridge, OnGSClientApprove, GSClientApprove_t);
	STATIC_STEAM_GAMESERVER_CALLBACK(SteamAuthCallbackBridge, OnGSClientDeny, GSClientDeny_t);
	STATIC_STEAM_GAMESERVER_CALLBACK(SteamAuthCallbackBridge, OnGSClientValidateAuth, ValidateAuthTicketResponse_t);
	STATIC_STEAM_GAMESERVER_CALLBACK(SteamAuthCallbackBridge, OnGSClientKick, GSClientKick_t);

private:
	UOnlineAuthInterfaceSteamworks* CallbackInterface;
};


/**
 * UOnlineGameInterfaceSteamworks bridges
 */

// Glue to bridge between Steamworks callback class and Unreal class;
//	multiple inheritance from arbitrary C++ classes in unrealscript is complicated
class SteamServerListResponse : public ISteamMatchmakingServerListResponse
{
public:
	SteamServerListResponse(UOnlineGameInterfaceSteamworks* _GameInterface)
		: GameInterface(_GameInterface)
	{
	}

	virtual void ServerResponded(HServerListRequest Request, int iServer)
	{
		GameInterface->ServerResponded(iServer);
	}

	virtual void ServerFailedToRespond(HServerListRequest Request, int iServer)
	{
		GameInterface->ServerFailedToRespond(iServer);
	}

	virtual void RefreshComplete(HServerListRequest Request, EMatchMakingServerResponse Response)
	{
		GameInterface->RefreshComplete(Response);
	}

private:
	UOnlineGameInterfaceSteamworks* GameInterface;
};


class SteamRulesResponse : public ISteamMatchmakingRulesResponse
{
public:
	SteamRulesResponse(UOnlineGameInterfaceSteamworks* _GameInterface, UOnlineGameSettings* _Settings,
				const DWORD _IpAddr, const INT _Port, const uint64 _ServerSteamId)
		: GameInterface(_GameInterface)
		, Settings(_Settings)
		, IpAddr(_IpAddr)
		, Port(_Port)
		, ServerSteamId(_ServerSteamId)
		, bDeleteMe(FALSE)
		{
		}

	virtual void RulesResponded(const char* pchRule, const char* pchValue)
	{
		GameInterface->RulesResponded(this, pchRule, pchValue);
	}

	virtual void RulesFailedToRespond()
	{
		GameInterface->RulesFailedToRespond(this);
	}

	virtual void RulesRefreshComplete()
	{
		GameInterface->RulesRefreshComplete(this);
	}


	UOnlineGameSettings* GetOnlineGameSettings() const
	{
		return Settings;
	}

	SteamRulesMap& GetRules()
	{
		return Rules;
	}

	DWORD GetIpAddr() const
	{
		return IpAddr;
	}

	DWORD GetPort() const
	{
		return Port;
	}

	QWORD GetServerSteamId() const
	{
		return ServerSteamId;
	}

private:
	UOnlineGameInterfaceSteamworks* GameInterface;
	UOnlineGameSettings* Settings;
	SteamRulesMap Rules;
	const DWORD IpAddr;
	const INT Port;
	const uint64 ServerSteamId;

public:
	// Flag for deletion, since we can't delete it during the callback
	UBOOL bDeleteMe;
};


class SteamPingResponse : public ISteamMatchmakingPingResponse
{
public:
	SteamPingResponse(UOnlineGameInterfaceSteamworks* _GameInterface, UOnlineGameSettings* _Settings)
		: GameInterface(_GameInterface)
		, Settings(_Settings)
		, bDeleteMe(FALSE)
	{
	}

	virtual void ServerResponded(gameserveritem_t& server)
	{
		GameInterface->PingServerResponded(this, server);
	}

	virtual void ServerFailedToRespond()
	{
		GameInterface->PingServerFailedToRespond(this);
	}


	UOnlineGameSettings* GetOnlineGameSettings() const
	{
		return Settings;
	}

private:
	UOnlineGameInterfaceSteamworks* GameInterface;
	UOnlineGameSettings* Settings;

public:
	// Flag for deletion, since we can't delete it during the callback
	UBOOL bDeleteMe;
};


#if STEAM_MATCHMAKING_LOBBY

/**
 * UOnlineLobbyInterfaceSteamworks bridge
 */

// Bridge between ISteamMatchmaking and UOnlineLobbyInterfaceSteamworks
class SteamLobbyCallbackBridge
{
public:
	SteamLobbyCallbackBridge(UOnlineLobbyInterfaceSteamworks* LobbyInterface)
		: CallbackInterface(LobbyInterface)
		, CONSTRUCT_STATIC_STEAM_CALLBACK(SteamLobbyCallbackBridge, OnSteamLobbyCreated)
		, CONSTRUCT_STATIC_STEAM_CALLBACK(SteamLobbyCallbackBridge, OnSteamLobbyEnter)
		, CONSTRUCT_STATIC_STEAM_CALLBACK(SteamLobbyCallbackBridge, OnSteamLobbyDataUpdate)
		, CONSTRUCT_STATIC_STEAM_CALLBACK(SteamLobbyCallbackBridge, OnSteamLobbyChatUpdate)
		, CONSTRUCT_STATIC_STEAM_CALLBACK(SteamLobbyCallbackBridge, OnSteamLobbyGameCreated)
		, CONSTRUCT_STATIC_STEAM_CALLBACK(SteamLobbyCallbackBridge, OnSteamLobbyChatMessage)
		, CONSTRUCT_STATIC_STEAM_CALLBACK(SteamLobbyCallbackBridge, OnSteamLobbyMatchList)
		, CONSTRUCT_STATIC_STEAM_CALLBACK(SteamLobbyCallbackBridge, OnSteamLobbyInvite)
		, CONSTRUCT_STATIC_STEAM_CALLBACK(SteamLobbyCallbackBridge, OnSteamAcceptLobbyInvite)
	{
	}

	STATIC_STEAM_CALLBACK(SteamLobbyCallbackBridge, OnSteamLobbyCreated, LobbyCreated_t);
	STATIC_STEAM_CALLBACK(SteamLobbyCallbackBridge, OnSteamLobbyEnter, LobbyEnter_t);
	STATIC_STEAM_CALLBACK(SteamLobbyCallbackBridge, OnSteamLobbyDataUpdate, LobbyDataUpdate_t);
	STATIC_STEAM_CALLBACK(SteamLobbyCallbackBridge, OnSteamLobbyChatUpdate, LobbyChatUpdate_t);
	STATIC_STEAM_CALLBACK(SteamLobbyCallbackBridge, OnSteamLobbyGameCreated, LobbyGameCreated_t);
	STATIC_STEAM_CALLBACK(SteamLobbyCallbackBridge, OnSteamLobbyChatMessage, LobbyChatMsg_t);
	STATIC_STEAM_CALLBACK(SteamLobbyCallbackBridge, OnSteamLobbyMatchList, LobbyMatchList_t);
	STATIC_STEAM_CALLBACK(SteamLobbyCallbackBridge, OnSteamLobbyInvite, LobbyInvite_t);
	STATIC_STEAM_CALLBACK(SteamLobbyCallbackBridge, OnSteamAcceptLobbyInvite, GameLobbyJoinRequested_t);

private:
	UOnlineLobbyInterfaceSteamworks* CallbackInterface;
};

#endif	// STEAM_MATCHMAKING_LOBBY


#endif	// WITH_UE3_NETWORKING && WITH_STEAMWORKS

#endif  // !INCLUDED_ONLINESUBSYSTEMSTEAMWORKSBRIDGE_H


