package com.snda.services.oa.client.impl;

import java.io.File;

import com.snda.services.oa.client.UserInfo;
import com.snda.services.util.NativeClassLoader;

public class OANativeClient {
	public static boolean initializeStatus = true;
	static {
		String projectHome = System.getProperty("project.home",".");// Directory containing the dynamic library
		File filePath = new File(projectHome);
		NativeClassLoader.loadLibrary("OANativeClient");// OANativeClient is the dynamic library name; load it without the DLL suffix

		String confFileName = "sdoa4server.ini";// Initialization file name
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
	 *            Configuration file path, including its name
	 * @return
	 */
	public native static int init(String config);

	/**
	 * 
	 * @param keys
	 *            Order information field
	 * @param values
	 *            Value of the corresponding order field
	 *   @param         orderType
	 *            Order type:
	 * @return
	 */
	public native static String buildOrderUrl(String[] keys, String[] values,int orderType);

	/**
	 * Generate a unique order number
	 * 
	 * @return
	 */
	public native static String generateOrderId();

	/**
	 * Authenticate user information
	 * 
	 * @param sessionId
	 *            Token or session ID to validate
	 * @param clientIpAddress
	 *            Client IP
	 * @param uniqueId
	 *            Unique token ID
	 * @return
	 */
	public native static UserInfo getUserInfo(String sessionId,
			String clientIpAddress, long uniqueId);

	/**
	 * Verify the signature
	 * 
	 * @param source
	 *            Source data to verify
	 * @param length
	 *            Length of source data to verify
	 * @param signedString
	 *            Signature to verify
	 * @return
	 */

	public native static boolean verifyString(byte[] source,String signedString);
	
	
	public native static String sign(byte[] source);
}
