package com.snda.services.oa.client.impl;

import com.snda.services.oa.client.AbstractOrderInfo;
/**
 * 交易接口定义
 * @author chenyifang
 *
 */
public class SdoConsignOrderInfo extends AbstractOrderInfo {

	public SdoConsignOrderInfo() {
		type = ORDER_TYPE_CONSIGN;
	}

	public String userIdDest;
	public int feeDest;
	public String userIdSrc;
	public int feeSrc;
	public int amount;
}
