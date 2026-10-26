package com.snda.services.oa.client.impl;

import com.snda.services.oa.client.AbstractOrderInfo;
/**
 * 寄售元宝接口定义
 * @author chenyifang
 *
 */
public class SdoSellCurrencyOrderInfo extends AbstractOrderInfo {
	public SdoSellCurrencyOrderInfo() {
		type = ORDER_TYPE_SELLCURRENCY;
	}

	public int amount;

	public int confirm;
}
