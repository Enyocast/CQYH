package com.snda.services.oa.client;

public class AbstractOrderType {
	public static int ORDER_TYPE_PAY=1;//Charge
	public static int ORDER_TYPE_SENDITEM=2;//Delivery
	public static int ORDER_TYPE_SELLCURRENCY=3;//Ingot consignment
	public static int ORDER_TYPE_SELLITEM=4;//Item consignment
	public static int ORDER_TYPE_CONSIGN=5;//Trade
/**
 * Identifies the interface to call; see definitions above.
 */
	public int type;
}
