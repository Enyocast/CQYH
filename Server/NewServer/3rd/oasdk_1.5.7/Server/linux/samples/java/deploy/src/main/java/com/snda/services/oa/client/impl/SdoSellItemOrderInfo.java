package com.snda.services.oa.client.impl;

import com.snda.services.oa.client.AbstractOrderInfo;
/**
 * Item consignment interface definition
 * @author chenyifang
 *
 */
public class SdoSellItemOrderInfo extends AbstractOrderInfo {

	public SdoSellItemOrderInfo() {
		type = ORDER_TYPE_SELLITEM;
	}
    public String orderIdRelation;
	public String userIdDest;
	public int feeDest;
	public String userIdSrc;
	public int feeSrc;
	public int amount;
}
