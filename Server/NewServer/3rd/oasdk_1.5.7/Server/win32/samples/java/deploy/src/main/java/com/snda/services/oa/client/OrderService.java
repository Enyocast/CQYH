package com.snda.services.oa.client;

/**
 * Order services, including order number generation and signing
 * @author Structchen
 *
 */
public interface OrderService {
	
	/**
	 * Automatically generate an order ID
	 * @return 
	 */
	public String generateOrderId();
	
	/**
	 * 
	 * Sign the order and return the signed string.
	 * 
	 * @param orderInfo
	 * 
	 * @return String URL containing the order signature
	 */
	public String buildOrderUrl(AbstractOrderInfo orderInfo);
}
