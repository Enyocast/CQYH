package com.snda.services.oa.client;

/**
 * User information returned after lookup
 * @author Structchen
 *
 */
public class UserInfo {
	
	/**
	 * ptId may not be provided to the game.
	 */
	public String ptId;
	
	/**
	 * sndaId is present if the user exists
	 */
	public String sndaId;
	
	public String uid;
	
	public String idCard;
	
	/**
	 * Result code returned with user information
	 */
	public int result;
}
