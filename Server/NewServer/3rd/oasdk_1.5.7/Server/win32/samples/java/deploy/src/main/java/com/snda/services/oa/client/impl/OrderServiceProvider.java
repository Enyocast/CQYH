package com.snda.services.oa.client.impl;

import java.util.HashMap;
import java.util.Map;

import com.snda.services.oa.client.AbstractOrderInfo;
import com.snda.services.oa.client.OrderService;

/**
 * 
 * ¶©µ¥·þÎñ
 * 
 * @author Structchen
 * 
 */
public class OrderServiceProvider implements OrderService {

	public OrderServiceProvider() {
	};

	public String buildOrderUrl(AbstractOrderInfo orderInfo) {
		Map<String, String> map = new HashMap<String, String>();
		orderInfo.readFieldConent(map);

		String[] keys = map.keySet().toArray(new String[] {});
		String[] values = map.values().toArray(new String[] {});
		return OANativeClient.buildOrderUrl(keys, values,orderInfo.type);
	}

	public String generateOrderId() {
		return OANativeClient.generateOrderId();
	}

	public static void main(String[] args){
		SdoPayOrderInfo order = new SdoPayOrderInfo();
		order.amount = 1000;
		order.indication = "asd";
		OrderServiceProvider provider = new OrderServiceProvider();
		System.out.println(provider.buildOrderUrl(order));
	}
}