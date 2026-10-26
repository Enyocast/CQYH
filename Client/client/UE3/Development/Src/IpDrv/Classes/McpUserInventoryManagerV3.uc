/**
 * Copyright 1998-2013 Epic Games, Inc. All Rights Reserved.
 *
 * This is the MCP3 version of the inventory manager
 */
class McpUserInventoryManagerV3 extends McpUserInventoryBase
	config(Engine);

/** The URL to send game commands to */
var config String ProcessCommandUrl;
var config String ProfileResourcePath;

/** Id used on the backend to create your default profile data */
var config String ProfileTemplateId;

/** Holds the context for the create */
struct UserRequest
{
	var HttpRequestInterface Request;
	var String McpId;
	var String SaveSlotId;
};

/** Holds the context for the create */
struct SaveSlotRequest extends UserRequest
{
	var String SaveSlotId;
};

/** The set of requests that are pending */
var array<SaveSlotRequest> SaveSlotRequests;

/**
 * Builds the path to a user's profile
 *
 * @param McpId the user manipulating their profile
 * @param ProfileId the profile being manipulated
 *
 * @return the path to the profile resource
 */
function String BuildProfileResourcePath(String McpId, optional String ProfileId)
{
	local String Path;

	Path = Repl(ProfileResourcePath, "{epicId}", McpId);
	Path = Repl(Path, "{profileId}", ProfileId);
	return GetBaseURL() $ Path;
}

/**
 * Creates a new save slot for the user
 * 
 * @param McpId the id of the user that made the request
 * @param SaveSlotId the save slot that is being created
 * @param ParentSaveSlotId ignored
 */
function CreateSaveSlot(string McpId, string SaveSlotId, optional string ParentSaveSlotId)
{
	local String Url;
	local HttpRequestInterface Request;
	local int AddAt;
	local String Json;

	Request = CreateHttpRequest(McpId);
	if (Request != none)
	{
		Url = GetBaseURL() $ ProcessCommandUrl;

		Json = "[ { \"action\": \"createProfile\", " $
			"\"epicId\": \"" $ McpId $ "\", " $
			"\"profileId\": \"" $ SaveSlotId $ "\", " $
			"\"templateId\": \"" $ ProfileTemplateId $ "\" } ]";

		`Logd("CreateSaveSlot JSON is " $ Json);
		`Logd("CreateSaveSlot URL is POST " $ Url);
		// Build our web request with the above URL
		Request.SetURL(Url);
		Request.SetVerb("POST");
		Request.SetContentAsString(Json);
		Request.OnProcessRequestComplete = OnCreateSaveSlotRequestComplete;

		// Store off the data for reporting later
		AddAt = SaveSlotRequests.Length;
		SaveSlotRequests.Length = AddAt + 1;
		SaveSlotRequests[AddAt].Request = Request;
		SaveSlotRequests[AddAt].McpId = McpId;

		// Now kick off the request
		if (!Request.ProcessRequest())
		{
			`Log("Failed to start CreateSaveSlot web request for URL(" $ Url $ ")");
		}
	}
}

/**
 * Called once the request/response has completed
 * 
 * @param Request the request object that was used
 * @param Response the response object that was generated
 * @param bWasSuccessful whether or not the request completed successfully
 */
function OnCreateSaveSlotRequestComplete(HttpRequestInterface Request, HttpResponseInterface Response, bool bWasSuccessful)
{
	local int Index;
	local int ResponseCode;
	local string ErrorString;
	local String ResponseString;

	Index = SaveSlotRequests.Find('Request', Request);
	if (Index != INDEX_NONE)
	{
		ResponseCode = 500;
		if (Response != none)
		{
			ResponseCode = Response.GetResponseCode();
			ResponseString = Response.GetContentAsString();
		}
		// Both of these need to be true for the request to be a success
		bWasSuccessful = bWasSuccessful && IsSuccessCode(ResponseCode);
		if (!bWasSuccessful)
		{
			ErrorString = "CreateSaveSlot failed with response code (" $ ResponseCode $ ") and payload:\n" $ ResponseString;
			`Logd("");
			`Logd("ResponseCode = " $ ResponseCode);
			`Logd("ResponseString = " $ ResponseString);
			`Logd("");
		}
		// Notify anyone waiting on this
		OnCreateSaveSlotComplete(SaveSlotRequests[Index].McpId, SaveSlotRequests[Index].SaveSlotId, bWasSuccessful, ErrorString);
		SaveSlotRequests.Remove(Index,1);
	}
}

/**
 * Deletes an existing user save slot and all the inventory items that belong to it
 * 
 * @param McpId the id of the user that made the request
 * @param SaveSlotId the save slot that is being deleted
 */
function DeleteSaveSlot(string McpId, string SaveSlotId)
{
	local String Url;
	local HttpRequestInterface Request;
	local int AddAt;
	local String Json;

	Request = CreateHttpRequest(McpId);
	if (Request != none)
	{
		Url = GetBaseURL() $ ProcessCommandUrl;

		Json = "[ { \"action\": \"deleteProfile\", " $
			"\"epicId\": \"" $ McpId $ "\", " $
			"\"profileId\": \"" $ SaveSlotId $ "\" } ]";

		`Logd("DeleteSaveSlot JSON is " $ Json);
		`Logd("DeleteSaveSlot URL is POST " $ Url);
		// Build our web request with the above URL
		Request.SetURL(Url);
		Request.SetVerb("POST");
		Request.SetContentAsString(Json);
		Request.OnProcessRequestComplete = OnDeleteSaveSlotRequestComplete;

		// Store off the data for reporting later
		AddAt = SaveSlotRequests.Length;
		SaveSlotRequests.Length = AddAt + 1;
		SaveSlotRequests[AddAt].Request = Request;
		SaveSlotRequests[AddAt].McpId = McpId;

		// Now kick off the request
		if (!Request.ProcessRequest())
		{
			`Log("Failed to start DeleteSaveSlot web request for URL(" $ Url $ ")");
		}
	}
}

/**
 * Called once the request/response has completed
 * 
 * @param Request the request object that was used
 * @param Response the response object that was generated
 * @param bWasSuccessful whether or not the request completed successfully
 */
function OnDeleteSaveSlotRequestComplete(HttpRequestInterface Request, HttpResponseInterface Response, bool bWasSuccessful)
{
	local int Index;
	local int ResponseCode;
	local string ErrorString;
	local String ResponseString;

	Index = SaveSlotRequests.Find('Request', Request);
	if (Index != INDEX_NONE)
	{
		ResponseCode = 500;
		if (Response != none)
		{
			ResponseCode = Response.GetResponseCode();
			ResponseString = Response.GetContentAsString();
		}
		// Both of these need to be true for the request to be a success
		bWasSuccessful = bWasSuccessful && IsSuccessCode(ResponseCode);
		if (!bWasSuccessful)
		{
			ErrorString = "DeleteSaveSlot failed with response code (" $ ResponseCode $ ") and payload:\n" $ ResponseString;
			`Logd("");
			`Logd("ResponseCode = " $ ResponseCode);
			`Logd("ResponseString = " $ ResponseString);
			`Logd("");
		}
		// Notify anyone waiting on this
		OnDeleteSaveSlotComplete(SaveSlotRequests[Index].McpId, SaveSlotRequests[Index].SaveSlotId, bWasSuccessful, ErrorString);
		SaveSlotRequests.Remove(Index,1);
	}
}

/**
 * Record an IAP (In App Purchase) by sending receipt to server for validation
 * Results in list of items being added to inventory if successful
 * 
 * @param McpId the id of the user that made the request
 * @param SaveSlotId the save slot that the item(s) will be placed in once validated
 * @param Vendor the provider of the purchasing system (Apple, Xbox Live, etc.)
 * @param Receipt IAP receipt to validate the purchase on the server
 */
function RecordIap(String McpId, String SaveSlotId, String Vendor, String Receipt)
{
	local String Url;
	local HttpRequestInterface Request;
	local int AddAt;
	local String Json;

	Request = CreateHttpRequest(McpId);
	if (Request != none)
	{
		Url = GetBaseURL() $ ProcessCommandUrl;

		Json = "[ { \"action\": \"iapPurchase\", " $
			"\"epicId\": \"" $ McpId $ "\", " $
			"\"profileId\": \"" $ SaveSlotId $ "\", " $
			"\"vendor\": \"" $ Vendor $ "\", " $
			"\"vendorReceipt\": \"" $ Receipt $ "\" } ]";

		`Logd("RecordIap JSON is " $ Json);
		`Logd("RecordIap URL is POST " $ Url);
		// Build our web request with the above URL
		Request.SetURL(Url);
		Request.SetVerb("POST");
		Request.SetContentAsString(Json);
		Request.OnProcessRequestComplete = OnRecordIapRequestComplete;

		// Store off the data for reporting later
		AddAt = SaveSlotRequests.Length;
		SaveSlotRequests.Length = AddAt + 1;
		SaveSlotRequests[AddAt].Request = Request;
		SaveSlotRequests[AddAt].McpId = McpId;
		SaveSlotRequests[AddAt].SaveSlotId = SaveSlotId;

		// Now kick off the request
		if (!Request.ProcessRequest())
		{
			`Log("Failed to start RecordIap web request for URL(" $ Url $ ")");
		}
	}
}

/**
 * Called once the request/response has completed
 * 
 * @param Request the request object that was used
 * @param Response the response object that was generated
 * @param bWasSuccessful whether or not the request completed successfully
 */
function OnRecordIapRequestComplete(HttpRequestInterface Request, HttpResponseInterface Response, bool bWasSuccessful)
{
	local int Index;
	local int ResponseCode;
	local string ErrorString;
	local String ResponseString;
	local array<string> UpdatedItemIds;
	local JsonObject ParsedJson, JsonElement;
	local int JsonIndex;

	Index = SaveSlotRequests.Find('Request', Request);
	if (Index != INDEX_NONE)
	{
		ResponseCode = 500;
		if (Response != none)
		{
			ResponseCode = Response.GetResponseCode();
			ResponseString = Response.GetContentAsString();
		}
		// Both of these need to be true for the request to be a success
		bWasSuccessful = bWasSuccessful && IsSuccessCode(ResponseCode);
		if (bWasSuccessful)
		{
//@todo -- Needs to report quantity too

			// Parse the JSON into the array of updated ids
			//[{"epicId":"e5734fbc4aab40809fb2201e60919042","profileId":"SaveSlot1","item":{"id":"ad225a196a264119a3b1dcb4f2ec7b6c","templateId":"chips1200","attributes":{},"quantity":1200}}]
			ParsedJson = class'JsonObject'.static.DecodeJson(ResponseString);
			// Parse each user, adding them if needed
			for (JsonIndex = 0; JsonIndex < ParsedJson.ObjectArray.Length; JsonIndex++)
			{
				JsonElement = ParsedJson.ObjectArray[JsonIndex];
				JsonElement = JsonElement.GetObject("item");
				if (JsonElement.HasKey("templateId"))
				{
					UpdatedItemIds.AddItem(JsonElement.GetStringValue("templateId"));
				}
			}
		}
		else
		{
			ErrorString = "RecordIap failed with response code (" $ ResponseCode $ ") and payload:\n" $ ResponseString;
		}
		// Notify anyone waiting on this
		OnRecordIapComplete(SaveSlotRequests[Index].McpId, SaveSlotRequests[Index].SaveSlotId, UpdatedItemIds, bWasSuccessful, ErrorString);
		SaveSlotRequests.Remove(Index,1);
	}
}

/**
 * Query for the list of save slots that exist for the user
 * 
 * @param McpId the id of the user that made the request
 */
function QuerySaveSlotList(string McpId)
{
	local String Url;
	local HttpRequestInterface Request;
	local int AddAt;

	Request = CreateHttpRequest(McpId);
	if (Request != none)
	{
		Url = BuildProfileResourcePath(McpId);
		`Logd("QuerySaveSlotList URL is GET " $ Url);
		// Build our web request with the above URL
		Request.SetURL(Url);
		Request.SetVerb("GET");
		Request.OnProcessRequestComplete = OnQuerySaveSlotsRequestComplete;

		// Store off the data for reporting later
		AddAt = SaveSlotRequests.Length;
		SaveSlotRequests.Length = AddAt + 1;
		SaveSlotRequests[AddAt].Request = Request;
		SaveSlotRequests[AddAt].McpId = McpId;

		// Now kick off the request
		if (!Request.ProcessRequest())
		{
			`Log("Failed to start QuerySaveSlotList web request for URL(" $ Url $ ")");
		}
	}
}

/**
 * Called once the request/response has completed
 * 
 * @param Request the request object that was used
 * @param Response the response object that was generated
 * @param bWasSuccessful whether or not the request completed successfully
 */
function OnQuerySaveSlotsRequestComplete(HttpRequestInterface Request, HttpResponseInterface Response, bool bWasSuccessful)
{
	local int Index;
	local int ResponseCode;
	local string ErrorString;
	local String ResponseString;

	Index = SaveSlotRequests.Find('Request', Request);
	if (Index != INDEX_NONE)
	{
		ResponseCode = 500;
		if (Response != none)
		{
			ResponseCode = Response.GetResponseCode();
			ResponseString = Response.GetContentAsString();
`Logd("");
`Logd("ResponseCode = " $ ResponseCode);
`Logd("ResponseString = " $ ResponseString);
`Logd("");
		}
		// Both of these need to be true for the request to be a success
		bWasSuccessful = bWasSuccessful && IsSuccessCode(ResponseCode);
		if (!bWasSuccessful)
		{
			ErrorString = "QuerySaveSlotList failed with response code (" $ ResponseCode $ ") and payload:\n" $ ResponseString;
		}
		// Notify anyone waiting on this
		OnQuerySaveSlotListComplete(SaveSlotRequests[Index].McpId, bWasSuccessful, ErrorString);
		SaveSlotRequests.Remove(Index,1);
	}
}

/**
 * Get the cached list of save slot ids for a user
 * 
 * @param McpId the id of the user that made the request
 *
 * @return the list of save slot ids for the user
 */
function array<string> GetSaveSlotList(string McpId);
