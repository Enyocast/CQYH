package com.snda.services.oa.client.impl;

import java.io.UnsupportedEncodingException;

import com.snda.services.oa.client.VerifySignatureService;

public class VerifySignatureServiceProvider implements VerifySignatureService {

	public boolean verify(String source, String verrifiedString) {
		byte[] btys = null;
		try {
			btys = source.getBytes("utf-8");
		} catch (UnsupportedEncodingException e) {
			btys = source.getBytes();
		}
		return OANativeClient.verifyString(btys,verrifiedString);
	}

	public String sign(String source) {
		
		byte[] btys = null;
		try {
			btys = source.getBytes("utf-8");
		} catch (UnsupportedEncodingException e) {
			btys = source.getBytes();
		}
		
		return OANativeClient.sign(btys);
	}
}
