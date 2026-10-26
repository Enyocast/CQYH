package com.snda.services.oa.client;

public class AbstractOrderType {
	public static int ORDER_TYPE_PAY=1;//扣费
	public static int ORDER_TYPE_SENDITEM=2;//发货
	public static int ORDER_TYPE_SELLCURRENCY=3;//寄售元宝
	public static int ORDER_TYPE_SELLITEM=4;//寄售道具
	public static int ORDER_TYPE_CONSIGN=5;//交易
/**
 * 表示调用哪个接口 ，定义见上。
 */
	public int type;
}
