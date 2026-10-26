package com.snda.services.oa.client.impl;

import com.snda.services.oa.client.AbstractOrderInfo;
/**
 * 扣费接口定义
 * @author chenyifang
 *
 */
public class SdoPayOrderInfo extends AbstractOrderInfo {
	public SdoPayOrderInfo(){
		type = ORDER_TYPE_PAY;
	}
	public int amount;
}
