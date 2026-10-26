/**
 * Copyright 1998-2012 Epic Games, Inc. All Rights Reserved.
 */

// Implementation of Steam SDK to Online Subsystem bridges (nothing interesting here)

#include "OnlineSubsystemSteamworks.h"
#include "OnlineSubsystemSteamworksBridge.h"

#if WITH_UE3_NETWORKING && WITH_STEAMWORKS


/**
 * UOnlineSubsystemSteamworks bridge
 */

void SteamCallbackBridge::OnGSClientAchievementStatus(GSClientAchievementStatus_t* CallbackData)
{
	Subsystem->OnGSClientAchievementStatus(CallbackData);
}

void SteamCallbackBridge::OnGameServerChangeRequested(GameServerChangeRequested_t* CallbackData)
{
	Subsystem->OnGameServerChangeRequested(CallbackData);
}

void SteamCallbackBridge::OnGameJoinRequested(GameRichPresenceJoinRequested_t* CallbackData)
{
	Subsystem->OnGameJoinRequested(CallbackData);
}

void SteamCallbackBridge::OnSteamShutdown(SteamShutdown_t* CallbackData)
{
	Subsystem->OnSteamShutdown(CallbackData);
}

void SteamCallbackBridge::OnGameOverlayActivated(GameOverlayActivated_t* CallbackData)
{
	Subsystem->OnGameOverlayActivated(CallbackData);
}

void SteamCallbackBridge::OnGSPolicyResponse(GSPolicyResponse_t* CallbackData)
{
	Subsystem->OnGSPolicyResponse(CallbackData);
}

void SteamCallbackBridge::OnSteamServersConnected(SteamServersConnected_t* CallbackData)
{
	Subsystem->OnSteamServersConnected(CallbackData);
}

void SteamCallbackBridge::OnSteamServersDisconnected(SteamServersDisconnected_t* CallbackData)
{
	Subsystem->OnSteamServersDisconnected(CallbackData);
}

void SteamCallbackBridge::OnGSSteamServersConnected(SteamServersConnected_t* CallbackData)
{
	Subsystem->OnGSSteamServersConnected(CallbackData);
}

void SteamCallbackBridge::OnGSSteamServersDisconnected(SteamServersDisconnected_t* CallbackData)
{
	Subsystem->OnGSSteamServersDisconnected(CallbackData);
}

void SteamCallbackBridge::OnUserStatsReceived(UserStatsReceived_t* CallbackData)
{
	Subsystem->OnUserStatsReceived(CallbackData);
}

void SteamCallbackBridge::OnUserStatsStored(UserStatsStored_t* CallbackData)
{
	Subsystem->OnUserStatsStored(CallbackData);
}

void SteamCallbackBridge::OnSpecificUserStatsReceived(UserStatsReceived_t* CallbackData, bool bIOFailure)
{
	Subsystem->OnSpecificUserStatsReceived(CallbackData, bIOFailure);
}

void SteamCallbackBridge::OnSpecificGSStatsReceived(GSStatsReceived_t* CallbackData, bool bIOFailure)
{
	Subsystem->OnSpecificGSStatsReceived(CallbackData, bIOFailure);
}

void SteamCallbackBridge::OnSpecificGSStatsStored(GSStatsStored_t* CallbackData, bool bIOFailure)
{
	Subsystem->OnSpecificGSStatsStored(CallbackData, bIOFailure);
}

void SteamCallbackBridge::OnNumberOfCurrentPlayers(NumberOfCurrentPlayers_t *CallbackData, bool bIOFailure)
{
	Subsystem->OnNumberOfCurrentPlayers(CallbackData, bIOFailure);
}

void SteamCallbackBridge::OnUserFindLeaderboard(LeaderboardFindResult_t* CallbackData, bool bIOFailure)
{
	Subsystem->OnUserFindLeaderboard(CallbackData, bIOFailure);
}

void SteamCallbackBridge::OnUserDownloadedLeaderboardEntries(LeaderboardScoresDownloaded_t* CallbackData, bool bIOFailure)
{
	Subsystem->OnUserDownloadedLeaderboardEntries(CallbackData, bIOFailure);
}

void SteamCallbackBridge::OnUserUploadedLeaderboardScore(LeaderboardScoreUploaded_t* CallbackData, bool bIOFailure)
{
	Subsystem->OnUserUploadedLeaderboardScore(CallbackData, bIOFailure);
}

void SteamCallbackBridge::OnAvatarImageLoaded(AvatarImageLoaded_t* CallbackData)
{
	Subsystem->OnAvatarImageLoaded(CallbackData);
}

/** Steam callback: remote shared data has been posted. */
void SteamCallbackBridge::OnRemoteStorageFileShareResult(RemoteStorageFileShareResult_t* CallbackResult, const FString& UserId, const FString& Filename, bool bIOFailure)
{
	Subsystem->OnRemoteStorageFileShareResult(CallbackResult, UserId, Filename, bIOFailure);
}

/** Steam callback: remote shared data has been downloaded */
void SteamCallbackBridge::OnRemoteStorageFileShareDownload(RemoteStorageDownloadUGCResult_t* CallbackResult, bool bIOFailure)
{
	Subsystem->OnRemoteStorageFileShareDownload(CallbackResult, bIOFailure);
}


/**
 * UOnlineAuthInterfaceSteamworks bridge
 */

void SteamAuthCallbackBridge::OnClientGameServerDeny(ClientGameServerDeny_t* CallbackData)
{
	AuthInterface->OnClientGameServerDeny(CallbackData);
}

void SteamAuthCallbackBridge::OnGSClientApprove(GSClientApprove_t* CallbackData)
{
	AuthInterface->OnGSClientApprove(CallbackData);
}

void SteamAuthCallbackBridge::OnGSClientDeny(GSClientDeny_t* CallbackData)
{
	AuthInterface->OnGSClientDeny(CallbackData);
}

void SteamAuthCallbackBridge::OnClientValidateAuth(ValidateAuthTicketResponse_t* CallbackData)
{
	AuthInterface->OnClientValidateAuth(CallbackData);
}

void SteamAuthCallbackBridge::OnGSClientValidateAuth(ValidateAuthTicketResponse_t* CallbackData)
{
	AuthInterface->OnGSClientValidateAuth(CallbackData);
}

void SteamAuthCallbackBridge::OnGSClientKick(GSClientKick_t* CallbackData)
{
	AuthInterface->OnGSClientKick(CallbackData);
}


/**
 * UOnlineLobbyInterfaceSteamworks bridge
 */

#if STEAM_MATCHMAKING_LOBBY

void SteamLobbyCallbackBridge::OnSteamLobbyCreated(LobbyCreated_t* CallbackData)
{
	LobbyInterface->OnSteamLobbyCreated(CallbackData);
}

void SteamLobbyCallbackBridge::OnSteamLobbyEnter(LobbyEnter_t* CallbackData)
{
	LobbyInterface->OnSteamLobbyEnter(CallbackData);
}

void SteamLobbyCallbackBridge::OnSteamLobbyDataUpdate(LobbyDataUpdate_t* CallbackData)
{
	LobbyInterface->OnSteamLobbyDataUpdate(CallbackData);
}

void SteamLobbyCallbackBridge::OnSteamLobbyChatUpdate(LobbyChatUpdate_t* CallbackData)
{
	LobbyInterface->OnSteamLobbyChatUpdate(CallbackData);
}

void SteamLobbyCallbackBridge::OnSteamLobbyGameCreated(LobbyGameCreated_t* CallbackData)
{
	LobbyInterface->OnSteamLobbyGameCreated(CallbackData);
}

void SteamLobbyCallbackBridge::OnSteamLobbyChatMessage(LobbyChatMsg_t* CallbackData)
{
	LobbyInterface->OnSteamLobbyChatMessage(CallbackData);
}

void SteamLobbyCallbackBridge::OnSteamLobbyMatchList(LobbyMatchList_t* CallbackData)
{
	LobbyInterface->OnSteamLobbyMatchList(CallbackData);
}

void SteamLobbyCallbackBridge::OnSteamLobbyInvite(LobbyInvite_t* CallbackData)
{
	LobbyInterface->OnSteamLobbyInvite(CallbackData);
}

void SteamLobbyCallbackBridge::OnSteamAcceptLobbyInvite(GameLobbyJoinRequested_t* CallbackData)
{
	LobbyInterface->OnSteamAcceptLobbyInvite(CallbackData);
}

#endif	// STEAM_MATCHMAKING_LOBBY


#endif // WITH_UE3_NETWORKING && WITH_STEAMWORKS

