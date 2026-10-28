package com.snda.services.oa.client;

import java.lang.reflect.Field;
import java.lang.reflect.Modifier;
import java.util.Map;

/**
 * 
 * This abstract order interface requires public class fields.
 * When an order is sent to the service layer, its fields are formatted.
 * Formatting excludes transient, static and non-public fields.
 * 
 * Field types include String and all primitive types.
 * 
 * @author Structchen
 *
 */
public abstract class AbstractOrderInfo extends AbstractOrderType{

	public String orderId;
	public String userId;
	public int payType;
	public int goodsNum;
	public String goodsInfo;
	public String sessionId;
	public String indication;
	
	public void readFieldConent(Map<String, String> map) {
		readFieldConent(map,this.getClass(),AbstractOrderType.class);
	}
	
	private void readFieldConent(Map<String, String> map, Class<?> clazz,Class<?> stopClass) {
		if (clazz != stopClass
				&& clazz != null) {
			Field[] fields = clazz.getDeclaredFields();
			for (int i = 0; i < fields.length; i++) {
				String name = fields[i].getName();
				if ((fields[i].getModifiers() & Modifier.STATIC) == 0
						&& (fields[i].getModifiers() & Modifier.TRANSIENT) == 0
						&& (fields[i].getModifiers() & Modifier.PUBLIC) != 0) {
					try {
						Object obj = fields[i].get(this);
						if (obj != null) {
							String value = obj.toString();
							map.put(name, value);
						}
					} catch (Exception e) {
						// ignore
					}
				}
			}
			readFieldConent(map, clazz.getSuperclass(),stopClass);
		}
	}
}
