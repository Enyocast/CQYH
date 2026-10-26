package com.snda.services.oa.client.impl;

import com.snda.services.oa.client.UserAuthenInfo;
import com.snda.services.oa.client.UserAuthenService;
import com.snda.services.oa.client.UserInfo;

/**
 * 
 * 
 * @author Structchen
 *
 */
public class UserAuthenServiceProvider implements UserAuthenService{
	
	private String configFile;

	public String getConfigFile() {
		return configFile;
	}

	public void setConfigFile(String configFile) {
		this.configFile = configFile;
	}
	
	public void init(){
		
	}

	public UserInfo getUserInfo(UserAuthenInfo userAuthenInfo) {
		return OANativeClient.getUserInfo(userAuthenInfo.sessionId, userAuthenInfo.clientIpAddress, userAuthenInfo.uniqueId);
	}
}
