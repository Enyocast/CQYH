package com.snda.services.oa.client;

import java.util.concurrent.CountDownLatch;
import java.util.concurrent.atomic.AtomicLong;

import com.snda.services.oa.client.impl.OrderServiceProvider;
import com.snda.services.oa.client.impl.SdoSendItemOrderInfo;
/**
 * Item delivery order example; see the protocol for parameter values
 * @author chenyifang
 *
 */
public class SdoSendItemOrderInfotest {

	public static void main(String[] args) throws InterruptedException {
		int thread = 20;
		int num = 100;
		if (args.length >= 2) {
			thread = Integer.valueOf(args[0]);
			num = Integer.valueOf(args[1]);

		}
		final int perThreadNum = num;

		final long timelong = System.currentTimeMillis();
		final CountDownLatch countDown = new CountDownLatch(thread);
		final AtomicLong count = new AtomicLong();
		for (int j = 0; j < thread; j++) {
			final int jj = j;
			new Thread() {
				public void run() {
					try {
						for (int i = 0; i < perThreadNum; i++) {
							OrderService orderProvider = new OrderServiceProvider();
							SdoSendItemOrderInfo order = new SdoSendItemOrderInfo();
							/**
							 * Populate the item delivery order information
							 */
							order.orderId = orderProvider.generateOrderId();
							order.appId=1;
							order.areaId=1;
							order.groupId=1;
							order.goodsInfo="1,1,1";
						    order.spId=1;
							order.userId = "234234";
							order.payType = 3;
							order.goodsNum = 1;
							order.indication = "test123";
							/**
							 *  Generate an order request URL in the following format:
							 *  http://192.168.68.92:8080/billgate/sdoSendItem.do?key=966&callTime=2009-04-29+11%3A18%3A13&groupId=1&userId=234234&appId=1&spId=1&orderId=00000096620090429111813000001997&areaId=1&goodsNum=1&payType=3&indication=test123&goodsInfo=1%2C1%2C1&sign=892BD26B4C489A4DBAB2C01B13C045E6
							 */
							String orderUrl = orderProvider
									.buildOrderUrl(order);
							System.out.println("orderUrl=" + orderUrl);
							long value = count.addAndGet(1);
							if (value % 100 == 0) {
								long current = System.currentTimeMillis();
								System.out.println("cost time="
										+ ((current - timelong) / 1000)
										+ " size=" + value);
							}
						}
					} catch (Exception e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					} finally {
						countDown.countDown();
					}

				}
			}.start();

		}
		countDown.await();
		long costTime = System.currentTimeMillis() - timelong;
		System.out.println("time=" + costTime / 1000);
	}

}
