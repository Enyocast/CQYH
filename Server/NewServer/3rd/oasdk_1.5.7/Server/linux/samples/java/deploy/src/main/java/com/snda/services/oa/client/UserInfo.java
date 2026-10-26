package com.snda.services.oa.client;

/**
 * 用户信息,获取用户以后返回的信息,
 * @author Structchen
 *
 */
public class UserInfo {
	
	/**
	 * ptId,这个对游戏来说可能不提供.
	 */
	public String ptId;
	
	/**
	 * sndaId,如果用户存则该值一定有
	 */
	public String sndaId;
	
	public String uid;
	
	public String idCard;
	
	/**
	 * 返回用户信息的结果代码
	 */
	public int result;
}
