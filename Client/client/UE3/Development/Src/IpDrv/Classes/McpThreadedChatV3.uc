/**
 * Copyright 1998-2013 Epic Games, Inc. All Rights Reserved.
 *
 * Provides the interface for posting to and creating chat threads with the server
 */
class McpThreadedChatV3 extends McpThreadedChatBase;

var config String ChatThreadResource;

/** Cached list of system chat threads */
var array<McpSystemChatThread> SystemChatThreads;

/** Cached list of user owned chat threads */
var array<McpUserChatThread> UserChatThreads;

/** Holds the set of cached chat posts */
var array<McpChatPost> ChatPosts;

/** Holds the state information for an outstanding user request */
struct UserRequest
{
	/** The MCP id that was returned by the backend */
	var string McpId;
	/** The request object for this request */
	var HttpRequestInterface Request;
};

var array<UserRequest> UserRequests;

/** Holds the state information for an outstanding user/thread request */
struct UserThreadNameRequest extends UserRequest
{
	/** The name of the thread being acted upon */
	var string ThreadName;
};

var array<UserThreadNameRequest> UserThreadNameRequests;

/** Holds the state information for an outstanding thread request */
struct ThreadRequest
{
	/** The ThreadId that was returned by the backend */
	var string ThreadId;
	/** The request object for this request */
	var HttpRequestInterface Request;
};
var array<ThreadRequest> ThreadRequests;


/** Holds the state information for an outstanding thread request */
struct UserThreadRequest extends ThreadRequest
{
	/** The McpId that was returned by the backend */
	var string McpId;
};
var array<UserThreadRequest> UserThreadRequests;

/** Holds the state information for an outstanding thread request */
struct PostRequest
{
	/** The PostId that was returned by the backend */
	var string PostId;
	/** The request object for this request */
	var HttpRequestInterface Request;
};
var array<PostRequest> PostRequests;

/**
 * Initiates a query with the backend to get the list of system chat threads
 */
function ReadSystemChatThreads()
{
	local String Url;
	local HttpRequestInterface Request;

	Request = CreateHttpRequestGameAuth();
	if (Request != none)
	{
		Url = GetBaseURL() $ ChatThreadResource;
		`Logd("ReadSystemChatThreads URL is GET " $ Url);

		// Build our web request with the above URL
		Request.SetURL(Url);
		Request.SetVerb("GET");
		Request.OnProcessRequestComplete = OnReadSystemChatThreadsRequestComplete;

		// Now kick off the request
		if (!Request.ProcessRequest())
		{
			`Log("Failed to start ReadSystemChatThreads web request for URL(" $ Url $ ")");
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
function OnReadSystemChatThreadsRequestComplete(HttpRequestInterface Request, HttpResponseInterface Response, bool bWasSuccessful)
{
	local int ResponseCode;
	local string ErrorString;
	local String ResponseString;

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
		ParseThreads(ResponseString, true);
	}
	else
	{
		ErrorString = "ReadSystemChatThreads failed with response code (" $ ResponseCode $ ") and payload:\n" $ ResponseString;
	}
	// Notify anyone waiting on this
	OnReadSystemChatThreadsComplete(bWasSuccessful, ErrorString);
}

/**
 * Parses the json which contains an array of chat thread data
 * 
 * @param JsonPayload the json data to parse
 * @param bSystemThread where to place the parsed data (system or user)
 */
protected function ParseThreads(String JsonPayload, bool bSystemThread)
{
	local JsonObject ParsedJson, JsonElement;
	local int JsonIndex;

	ParsedJson = class'JsonObject'.static.DecodeJson(JsonPayload);
	// Parse each user, adding them if needed
	for (JsonIndex = 0; JsonIndex < ParsedJson.ObjectArray.Length; JsonIndex++)
	{
		JsonElement = ParsedJson.ObjectArray[JsonIndex];
		if (bSystemThread)
		{
			ParseSystemChatThread(JsonElement);
		}
		else
		{
			ParseUserChatThread(JsonElement);
		}
	}
}

/**
 * Parses the system chat thread json
 * 
 * @param JsonPayload the json data to parse
 */
protected function ParseSystemChatThread(JsonObject ParsedJson)
{
	local String ThreadId;
	local int ThreadIndex;

	// Example JSON:
	//{
	//	"threadId":"someId",
	//	"name":"someName"
	//}
	// If it doesn't have this field, this is bogus JSON
	if (ParsedJson.HasKey("threadId"))
	{
		// Grab the ThreadId first, since that is our key
		ThreadId = ParsedJson.GetStringValue("threadId");
		// See if we already have a user
		ThreadIndex = SystemChatThreads.Find('ThreadId', ThreadId);
		if (ThreadIndex == INDEX_NONE)
		{
			// Not stored yet, so add one
			ThreadIndex = SystemChatThreads.Length;
			SystemChatThreads.Length = ThreadIndex + 1;
			SystemChatThreads[ThreadIndex].ThreadId = ThreadId;
		}
		SystemChatThreads[ThreadIndex].ThreadName = ParsedJson.GetStringValue("name");
	}
}

/**
 * Parses the user chat thread json
 * 
 * @param JsonPayload the json data to parse
 */
protected function ParseUserChatThread(JsonObject ParsedJson)
{
	local String ThreadId;
	local int ThreadIndex;

	// Example JSON:
	//{
	//	"threadId" : "someId",
	//	"name" : "someName",
	//	"ownerId" : "mcpId"
	//}
	// If it doesn't have this field, this is bogus JSON
	if (ParsedJson.HasKey("threadId"))
	{
		// Grab the ThreadId first, since that is our key
		ThreadId = ParsedJson.GetStringValue("threadId");
		// See if we already have a user
		ThreadIndex = UserChatThreads.Find('ThreadId', ThreadId);
		if (ThreadIndex == INDEX_NONE)
		{
			// Not stored yet, so add one
			ThreadIndex = UserChatThreads.Length;
			UserChatThreads.Length = ThreadIndex + 1;
			UserChatThreads[ThreadIndex].ThreadId = ThreadId;
		}
		UserChatThreads[ThreadIndex].ThreadName = ParsedJson.GetStringValue("name");
		UserChatThreads[ThreadIndex].OwnerId = ParsedJson.GetStringValue("ownerId");
	}
}

/**
 * Returns the set of known system wide chat threads
 */
function GetSystemChatThreads(out array<McpSystemChatThread> OutSystemChatThreads)
{
	OutSystemChatThreads = SystemChatThreads;
}

/**
 * Initiates a query with the backend to get the list of a particular user's chat threads
 */
function ReadUserChatThreads(String McpId)
{
	local String Url;
	local HttpRequestInterface Request;
	local int AddAt;

	Request = CreateHttpRequest(McpId);
	if (Request != none)
	{
		Url = GetBaseURL() $ ChatThreadResource $ "/user/" $ McpId;
		`Logd("ReadUserChatThreads URL is GET " $ Url);

		// Build our web request with the above URL
		Request.SetURL(Url);
		Request.SetVerb("GET");
		Request.OnProcessRequestComplete = OnReadUserChatThreadsRequestComplete;

		AddAt = UserRequests.Length;
		UserRequests.Length = AddAt + 1;
		UserRequests[AddAt].Request = Request;
		UserRequests[AddAt].McpId = McpId;

		// Now kick off the request
		if (!Request.ProcessRequest())
		{
			`Log("Failed to start ReadUserChatThreads web request for URL(" $ Url $ ")");
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
function OnReadUserChatThreadsRequestComplete(HttpRequestInterface Request, HttpResponseInterface Response, bool bWasSuccessful)
{
	local int Index;
	local int ResponseCode;
	local string ErrorString;
	local String ResponseString;

	Index = UserRequests.Find('Request', Request);
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
			ParseThreads(ResponseString, false);
		}
		else
		{
			ErrorString = "ReadUserChatThreads failed with response code (" $ ResponseCode $ ") and payload:\n" $ ResponseString;
		}
		// Notify anyone waiting on this
		OnReadUserChatThreadsComplete(bWasSuccessful, UserRequests[Index].McpId, ErrorString);
		UserRequests.Remove(Index, 1);
	}
}

/**
 * Returns the set of chat threads owned by the specified id
 */
function GetUserChatThreads(String McpId, out array<McpUserChatThread> OutUserChatThreads)
{
	local int Index;

	OutUserChatThreads.Length = 0;
	for (Index = 0; Index < UserChatThreads.Length; Index++)
	{
		if (UserChatThreads[Index].OwnerId == McpId)
		{
			OutUserChatThreads.AddItem(UserChatThreads[Index]);
		}
	}
}

/**
 * Creates a new user chat thread with the specified name
 */
function CreateUserChatThread(String McpId, String ThreadName)
{
	local String Url;
	local HttpRequestInterface Request;
	local int AddAt;

	Request = CreateHttpRequest(McpId);
	if (Request != none)
	{
		// Path is: /user/{epicId}/thread?name=someName
		Url = GetBaseURL() $ ChatThreadResource $ "/user/" $ McpId $ "/thread?name=" $ ThreadName;
		`Logd("CreateUserChatThread URL is POST " $ Url);

		// Build our web request with the above URL
		Request.SetURL(Url);
		Request.SetVerb("POST");
		Request.OnProcessRequestComplete = OnCreateUserChatThreadRequestComplete;

		AddAt = UserThreadNameRequests.Length;
		UserThreadNameRequests.Length = AddAt + 1;
		UserThreadNameRequests[AddAt].Request = Request;
		UserThreadNameRequests[AddAt].McpId = McpId;
		UserThreadNameRequests[AddAt].ThreadName = ThreadName;

		// Now kick off the request
		if (!Request.ProcessRequest())
		{
			`Log("Failed to start CreateUserChatThread web request for URL(" $ Url $ ")");
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
function OnCreateUserChatThreadRequestComplete(HttpRequestInterface Request, HttpResponseInterface Response, bool bWasSuccessful)
{
	local int Index;
	local int ResponseCode;
	local string ErrorString;
	local String ResponseString;
	local JsonObject ParsedJson;

	Index = UserThreadNameRequests.Find('Request', Request);
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
			ParsedJson = class'JsonObject'.static.DecodeJson(ResponseString);
			ParseUserChatThread(ParsedJson);
		}
		else
		{
			ErrorString = "CreateUserChatThread failed with response code (" $ ResponseCode $ ") and payload:\n" $ ResponseString;
		}
		// Notify anyone waiting on this
		OnCreateUserChatThreadComplete(bWasSuccessful, UserThreadNameRequests[Index].McpId, UserThreadNameRequests[Index].ThreadName, ErrorString);
		UserThreadNameRequests.Remove(Index, 1);
	}
}

/**
 * Reads a chunk of posts from a thread based upon time and count
 *
 * @param ThreadId the thread to read the posts for
 * @param Before the time of the last message that you want to read from
 * @param Count the number of posts to read
 */
function ReadChatPostsByTime(String ThreadId, String Before = "", int Count = 20)
{
	local String Url;
	local HttpRequestInterface Request;
	local int AddAt;

	Request = CreateHttpRequestGameAuth();
	if (Request != none)
	{
		Url = GetBaseURL() $ ChatThreadResource $ "/" $ ThreadId $ "?count=" $ Count;
		if (Before != "")
		{
			Url $= "&before=" $ UnrealDateTimeToServerDateTime(Before);
		}
		else
		{
			// Clear for this thread, since they are starting from the top
			ClearChatPosts(ThreadId);
		}
		`Logd("ReadChatPostsByTime URL is GET " $ Url);

		// Build our web request with the above URL
		Request.SetURL(Url);
		Request.SetVerb("GET");
		Request.OnProcessRequestComplete = OnReadChatPostsRequestComplete;

		AddAt = ThreadRequests.Length;
		ThreadRequests.Length = AddAt + 1;
		ThreadRequests[AddAt].Request = Request;
		ThreadRequests[AddAt].ThreadId = ThreadId;

		// Now kick off the request
		if (!Request.ProcessRequest())
		{
			`Log("Failed to start ReadChatPostsByTime web request for URL(" $ Url $ ")");
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
function OnReadChatPostsRequestComplete(HttpRequestInterface Request, HttpResponseInterface Response, bool bWasSuccessful)
{
	local int Index;
	local int ResponseCode;
	local string ErrorString;
	local String ResponseString;

	Index = ThreadRequests.Find('Request', Request);
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
			ParseChatPosts(ResponseString);
		}
		else
		{
			ErrorString = "ReadChatPosts* failed with response code (" $ ResponseCode $ ") and payload:\n" $ ResponseString;
		}
		// Notify anyone waiting on this
		OnReadChatPostsComplete(bWasSuccessful, ThreadRequests[Index].ThreadId, ErrorString);
		ThreadRequests.Remove(Index, 1);
	}
}

/**
 * Reads a chunk of posts from a thread based upon time and count
 *
 * @param ThreadId the thread to read the posts for
 * @param Before the time of the last message that you want to read from
 * @param Count the number of posts to read
 */
function ReadChatPostsByPopularity(String ThreadId, int Start = 0, int Count = 20)
{
	local String Url;
	local HttpRequestInterface Request;
	local int AddAt;

	Request = CreateHttpRequestGameAuth();
	if (Request != none)
	{
		Url = GetBaseURL() $ ChatThreadResource $ "/" $ ThreadId $ "?sortByTime=false&count=" $ Count;
		if (Start != 0)
		{
			Url $= "&start=" $ Start;
		}
		else
		{
			// Clear for this thread, since they are starting from the top
			ClearChatPosts(ThreadId);
		}
		`Logd("ReadChatPostsByPopularity URL is GET " $ Url);

		// Build our web request with the above URL
		Request.SetURL(Url);
		Request.SetVerb("GET");
		Request.OnProcessRequestComplete = OnReadChatPostsRequestComplete;

		AddAt = ThreadRequests.Length;
		ThreadRequests.Length = AddAt + 1;
		ThreadRequests[AddAt].Request = Request;
		ThreadRequests[AddAt].ThreadId = ThreadId;

		// Now kick off the request
		if (!Request.ProcessRequest())
		{
			`Log("Failed to start ReadChatPostsByPopularity web request for URL(" $ Url $ ")");
		}
	}
}

/**
 * Parses a json payload of chat posts
 *
 * @param JsonPayload the json from the server 
 */
function ParseChatPosts(String JsonPayload)
{
	local JsonObject ParsedJson, JsonElement;
	local int JsonIndex;

	ParsedJson = class'JsonObject'.static.DecodeJson(JsonPayload);
	// Parse each user, adding them if needed
	for (JsonIndex = 0; JsonIndex < ParsedJson.ObjectArray.Length; JsonIndex++)
	{
		JsonElement = ParsedJson.ObjectArray[JsonIndex];
		ParseChatPost(JsonElement);
	}
}

/**
 * Parses the chat post json
 * 
 * @param JsonPayload the json data to parse
 */
protected function ParseChatPost(JsonObject ParsedJson)
{
	local String PostId;
	local int PostIndex;

	// Example JSON:
	//{
	//	"postId" : "someId",
	//	"threadId" : "someId",
	//	"ownerId" : "someId",
	//	"ownerName" : "Joe G.",
	//	"ownerRank" : 1.0,
	//	"message" : "Welcome to fun!",
	//	"profanityChecked" : false,
	//	"reported" : false,
	//	"voteUpCount" : 1,
	//	"voteDownCount" : 1,
	//	"popularity" : 0,
	//	"timestamp" : "2013-05-28T21:58:33.605Z"
	//}
	// If it doesn't have this field, this is bogus JSON
	if (ParsedJson.HasKey("postId"))
	{
		// Grab the ThreadId first, since that is our key
		PostId = ParsedJson.GetStringValue("postId");
		// See if we already have a user
		PostIndex = ChatPosts.Find('PostId', PostId);
		if (PostIndex == INDEX_NONE)
		{
			// Not stored yet, so add one
			PostIndex = ChatPosts.Length;
			ChatPosts.Length = PostIndex + 1;
			ChatPosts[PostIndex].PostId = PostId;
		}
		ChatPosts[PostIndex].ThreadId = ParsedJson.GetStringValue("threadId");
		ChatPosts[PostIndex].OwnerId = ParsedJson.GetStringValue("ownerId");
		ChatPosts[PostIndex].OwnerName = ParsedJson.GetStringValue("ownerName");
		ChatPosts[PostIndex].Message = ParsedJson.GetStringValue("message");
		ChatPosts[PostIndex].Timestamp = ServerDateTimeToUnrealDateTime(ParsedJson.GetStringValue("timestamp"));
		ChatPosts[PostIndex].OwnerRank = ParsedJson.GetFloatValue("ownerRank");
		ChatPosts[PostIndex].VoteUpCount = ParsedJson.GetIntValue("voteUpCount");
		ChatPosts[PostIndex].VoteDownCount = ParsedJson.GetIntValue("voteDownCount");
		ChatPosts[PostIndex].Popularity = ParsedJson.GetIntValue("popularity");
		ChatPosts[PostIndex].bReported = ParsedJson.GetBoolValue("reported");
		ChatPosts[PostIndex].bProfanityChecked = ParsedJson.GetBoolValue("profanityChecked");
	}
}

/**
 * Returns the set of chat posts in a given thread
 */
function GetChatPosts(String ThreadId, out array<McpChatPost> OutChatPosts)
{
	local int Index;

	// Do not clear array, assume caller has cleared it if needed.
	for (Index = 0; Index < ChatPosts.Length; Index++)
	{
		if (ChatPosts[Index].ThreadId == ThreadId)
		{
			OutChatPosts.AddItem(ChatPosts[Index]);
		}
	}
}

/**
 * Empties the set of chat posts in a specific thread (save memory)
 */
function ClearChatPosts(String ThreadId)
{
	local int Index;

	for (Index = 0; Index < ChatPosts.Length; Index++)
	{
		if (ChatPosts[Index].ThreadId == ThreadId)
		{
			ChatPosts.Remove(Index, 1);
			Index--;
		}
	}
}

/**
 * Posts a message to a thread
 *
 * @param ThreadId the thread to post to
 * @param McpId the user posting the message
 * @param OwnerName the nickname to use with the message
 * @param Message the message to post
 */
function PostToThread(String ThreadId, String McpId, String OwnerName, String Message)
{
	local String Url;
	local HttpRequestInterface Request;
	local int AddAt;
	local String Json;

	Request = CreateHttpRequest(McpId);
	if (Request != none)
	{
		Url = GetBaseURL() $ ChatThreadResource $ "/" $ ThreadId;
		`Logd("PostToThread URL is POST " $ Url);

		Json = "{ \"ownerId\": \"" $ McpId $ "\", ";
		Json $= " \"ownerName\": \"" $ OwnerName $ "\", ";
		Json $= " \"message\": \"" $ Message $ "\" }";

		// Build our web request with the above URL
		Request.SetURL(Url);
		Request.SetVerb("POST");
		Request.SetContentAsString(Json);
		Request.OnProcessRequestComplete = OnPostToThreadRequestComplete;

		AddAt = UserThreadRequests.Length;
		UserThreadRequests.Length = AddAt + 1;
		UserThreadRequests[AddAt].Request = Request;
		UserThreadRequests[AddAt].ThreadId = ThreadId;
		UserThreadRequests[AddAt].McpId = McpId;

		// Now kick off the request
		if (!Request.ProcessRequest())
		{
			`Log("Failed to start PostToThread web request for URL(" $ Url $ ")");
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
function OnPostToThreadRequestComplete(HttpRequestInterface Request, HttpResponseInterface Response, bool bWasSuccessful)
{
	local int Index;
	local int ResponseCode;
	local string ErrorString;
	local String ResponseString;
	local JsonObject ParsedJson;

	Index = UserThreadRequests.Find('Request', Request);
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
			ParsedJson = class'JsonObject'.static.DecodeJson(ResponseString);
			ParseChatPost(ParsedJson);
		}
		else
		{
			ErrorString = "PostToThread failed with response code (" $ ResponseCode $ ") and payload:\n" $ ResponseString;
		}
		// Notify anyone waiting on this
		OnPostToThreadComplete(bWasSuccessful, UserThreadRequests[Index].ThreadId, UserThreadRequests[Index].McpId, ErrorString);
		UserThreadRequests.Remove(Index, 1);
	}
}

/**
 * Marks a post as being questionable
 *
 * @param ThreadId the thread to post to
 * @param PostId the id of the post being flagged
 * @param McpId the user posting the message
 */
function ReportPost(String ThreadId, String PostId, String McpId)
{
	local String Url;
	local HttpRequestInterface Request;
	local int AddAt;

	Request = CreateHttpRequest(McpId);
	if (Request != none)
	{
		Url = GetBaseURL() $ ChatThreadResource $ "/" $ ThreadId $ "/post/" $ PostId $ "/report?epicId=" $ McpId;
		`Logd("ReportPost URL is POST " $ Url);

		// Build our web request with the above URL
		Request.SetURL(Url);
		Request.SetVerb("POST");
		Request.OnProcessRequestComplete = OnReportPostRequestComplete;

		AddAt = PostRequests.Length;
		PostRequests.Length = AddAt + 1;
		PostRequests[AddAt].Request = Request;
		PostRequests[AddAt].PostId = PostId;

		// Now kick off the request
		if (!Request.ProcessRequest())
		{
			`Log("Failed to start ReportPost web request for URL(" $ Url $ ")");
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
function OnReportPostRequestComplete(HttpRequestInterface Request, HttpResponseInterface Response, bool bWasSuccessful)
{
	local int Index;
	local int ResponseCode;
	local string ErrorString;
	local String ResponseString;

	Index = PostRequests.Find('Request', Request);
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
			ErrorString = "ReportPost failed with response code (" $ ResponseCode $ ") and payload:\n" $ ResponseString;
		}
		// Notify anyone waiting on this
		OnReportPostComplete(bWasSuccessful, PostRequests[Index].PostId, ErrorString);
		PostRequests.Remove(Index, 1);
	}
}

/**
 * Gives a post a thumbs up
 *
 * @param ThreadId the thread to post to
 * @param PostId the id of the post being flagged
 * @param McpId the user posting the message
 */
function VoteUpPost(String ThreadId, String PostId, String McpId)
{
	VoteOnPost(ThreadId, PostId, McpId, true);
}

/**
 * Gives a post a thumbs down
 *
 * @param ThreadId the thread to post to
 * @param PostId the id of the post being flagged
 * @param McpId the user posting the message
 */
function VoteDownPost(String ThreadId, String PostId, String McpId)
{
	VoteOnPost(ThreadId, PostId, McpId, false);
}

/**
 * Votes on a post
 *
 * @param ThreadId the thread to post to
 * @param PostId the id of the post being flagged
 * @param McpId the user posting the message
 * @param bVoteUp true to vote up, false to vote down
 */
function VoteOnPost(String ThreadId, String PostId, String McpId, bool bVoteUp)
{
	local String Url;
	local HttpRequestInterface Request;
	local int AddAt;

	Request = CreateHttpRequest(McpId);
	if (Request != none)
	{
		Url = GetBaseURL() $ ChatThreadResource $ "/" $ ThreadId $ "/post/" $ PostId;
		if (bVoteUp)
		{
			Url $= "/voteUpCount";
		}
		else
		{
			Url $= "/voteDownCount";
		}
		Url $= "?epicId=" $ McpId;
		`Logd("VoteOnPost URL is POST " $ Url);

		// Build our web request with the above URL
		Request.SetURL(Url);
		Request.SetVerb("POST");
		Request.OnProcessRequestComplete = OnVoteOnPostRequestComplete;

		AddAt = PostRequests.Length;
		PostRequests.Length = AddAt + 1;
		PostRequests[AddAt].Request = Request;
		PostRequests[AddAt].PostId = PostId;

		// Now kick off the request
		if (!Request.ProcessRequest())
		{
			`Log("Failed to start VoteOnPost web request for URL(" $ Url $ ")");
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
function OnVoteOnPostRequestComplete(HttpRequestInterface Request, HttpResponseInterface Response, bool bWasSuccessful)
{
	local int Index;
	local int ResponseCode;
	local string ErrorString;
	local String ResponseString;

	Index = PostRequests.Find('Request', Request);
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
			ErrorString = "VoteOnPost failed with response code (" $ ResponseCode $ ") and payload:\n" $ ResponseString;
		}
		// Notify anyone waiting on this
		OnVoteOnPostComplete(bWasSuccessful, PostRequests[Index].PostId, ErrorString);
		PostRequests.Remove(Index, 1);
	}
}
