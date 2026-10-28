package com.snda.services.oa.client;

/**
 * User authentication service
 * 
 * @author StructChen
 */
public interface UserAuthenService {
	
	/**
	 * Check whether the user is valid
	 * @param userAuthenInfo
	 * @return int 0 if user information is valid; otherwise an error code
	 */
	public UserInfo getUserInfo(UserAuthenInfo userAuthenInfo);
}
