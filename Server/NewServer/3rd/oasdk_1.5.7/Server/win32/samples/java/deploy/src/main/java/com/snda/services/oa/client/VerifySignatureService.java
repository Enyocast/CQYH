package com.snda.services.oa.client;

/**
 * 验证签名服务
 * @author StructChen
 *
 */
public interface VerifySignatureService {
	
	/**
	 * 验证签名是否一致
	 * @param source 未签名的字符串
	 * @param verrifiedString 已经签名的字符串
	 * @return boolean  验证签名一致则返回true
	 */
	public boolean verify(String source,String verrifiedString);
	
	/**
	 * 对字符串进行签名
	 * 
	 * @param source 需要进行签名的字符串
	 * @return String 返回签名
	 */
	public String sign(String source);
}
