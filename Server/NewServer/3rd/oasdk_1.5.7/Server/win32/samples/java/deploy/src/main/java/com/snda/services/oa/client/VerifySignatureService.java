package com.snda.services.oa.client;

/**
 * Signature verification service
 * @author StructChen
 *
 */
public interface VerifySignatureService {
	
	/**
	 * Check whether signatures match
	 * @param source unsigned string
	 * @param verrifiedString signed string
	 * @return boolean true if the signature matches
	 */
	public boolean verify(String source,String verrifiedString);
	
	/**
	 * Sign a string
	 * 
	 * @param source string to sign
	 * @return String signature
	 */
	public String sign(String source);
}
