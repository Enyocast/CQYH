package com.snda.services.oa.client;

/**
 * 用户认证相关的服务
 * 
 * @author StructChen
 */
public interface UserAuthenService {
	
	/**
	 * 检测用户的合法性
	 * @param userAuthenInfo
	 * @return int : 0 表示用户信息正常, 其他则表示非法错误码
	 */
	public UserInfo getUserInfo(UserAuthenInfo userAuthenInfo);
}
