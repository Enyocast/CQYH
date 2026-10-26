package com.snda.services.oa.client;

/**
 * 订单相关的服务,包括产生订单号,订单签名
 * @author Structchen
 *
 */
public interface OrderService {
	
	/**
	 * 自动产生一个订单ID
	 * @return 
	 */
	public String generateOrderId();
	
	/**
	 * 
	 * 对订单进行签名返回签名以后的字符串.
	 * 
	 * @param orderInfo
	 * 
	 * @return String 返回包含订单签名字符串Url
	 */
	public String buildOrderUrl(AbstractOrderInfo orderInfo);
}
