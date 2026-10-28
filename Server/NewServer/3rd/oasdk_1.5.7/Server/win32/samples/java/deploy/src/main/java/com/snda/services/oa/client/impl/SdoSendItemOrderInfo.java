package com.snda.services.oa.client.impl;

import com.snda.services.oa.client.AbstractOrderInfo;
/**
 * Item delivery interface definition
 * @author chenyifang
 *
 */
public class SdoSendItemOrderInfo extends AbstractOrderInfo {
	public SdoSendItemOrderInfo() {
		type = ORDER_TYPE_SENDITEM;
	}

	public int spId;
	public int appId;
	public int areaId;
	public int groupId;
}
