package com.snda.services.oa.client;

import java.lang.reflect.Field;
import java.lang.reflect.Modifier;
import java.util.Map;

/**
 * 
 * 该抽象订单接口,类变量必须得公开,
 * 订单对象发送到订单服务层的时候,将订单内部的字段进行数据格式化,
 * 格式化数据的时候将会过滤修饰符为 transient static 非public 的字段.
 * 
 * 字段类型支持包括String在内的所有基础类型数据
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
