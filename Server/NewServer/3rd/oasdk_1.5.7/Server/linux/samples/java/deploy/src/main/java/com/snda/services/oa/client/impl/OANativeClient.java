package com.snda.services.oa.client.impl;

import java.io.File;

import com.snda.services.oa.client.UserInfo;
import com.snda.services.util.NativeClassLoader;

public class OANativeClient {
	public static boolean initializeStatus = true;
	static {
		String projectHome = System.getProperty("project.home",".");// 动态库文件放置的路径
		File filePath = new File(projectHome);
		NativeClassLoader.loadLibrary("OANativeClient");// OANativeClient为动态库名字，载入dll,不需要后缀的

		String confFileName = "sdoa4server.ini";// 初始化文件名字
		String configFile = new File(new File(filePath, "conf"),confFileName).getAbsolutePath();
		int inted = init(configFile);
		if (inted != 0) {
			initializeStatus = false;
		}
	}

	private OANativeClient() {
	};

	/**
	 * 
	 * @param config
	 *            配置文件的路径 ，包括名称
	 * @return
	 */
	public native static int init(String config);

	/**
	 * 
	 * @param keys
	 *            订单信息中的变量
	 * @param values
	 *            对应订单信息中的变量的值
	 *   @param         orderType
	 *            订单类型：
	 * @return
	 */
	public native static String buildOrderUrl(String[] keys, String[] values,int orderType);

	/**
	 * 生成唯一的订单号
	 * 
	 * @return
	 */
	public native static String generateOrderId();

	/**
	 * 认证用户信息
	 * 
	 * @param sessionId
	 *            需要验证的Token或者SessionId
	 * @param clientIpAddress
	 *            客户端IP
	 * @param uniqueId
	 *            token唯一id
	 * @return
	 */
	public native static UserInfo getUserInfo(String sessionId,
			String clientIpAddress, long uniqueId);

	/**
	 * 验证签名
	 * 
	 * @param source
	 *            待验证源数据
	 * @param length
	 *            待验证源数据长度
	 * @param signedString
	 *            待验证签名
	 * @return
	 */

	public native static boolean verifyString(byte[] source,String signedString);
	
	
	public native static String sign(byte[] source);
}
