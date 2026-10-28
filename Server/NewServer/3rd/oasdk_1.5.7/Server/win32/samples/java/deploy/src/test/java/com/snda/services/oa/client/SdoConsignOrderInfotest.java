package com.snda.services.oa.client;

import java.util.concurrent.CountDownLatch;
import java.util.concurrent.atomic.AtomicLong;

import com.snda.services.oa.client.impl.OrderServiceProvider;
import com.snda.services.oa.client.impl.SdoConsignOrderInfo;
/**
 * Trade order example; see the protocol for parameter values
 * @author chenyifang
 *
 */
public class SdoConsignOrderInfotest {

	public static void main(String[] args) throws InterruptedException {
		int thread = 1;
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
							SdoConsignOrderInfo order = new SdoConsignOrderInfo();
							/**
							 * Populate the trade order information
							 */
							order.orderId = orderProvider.generateOrderId();
							order.amount = 1;
							order.payType = 3;
							order.goodsNum = 1;
							order.indication = "test123";
							order.feeDest=1;
							order.feeSrc=0;
							order.goodsInfo="1,1,1";
							order.goodsNum=1;
							order.userIdDest="234234";
							order.userIdSrc="7675675";
							
							/**
							 * Generate an order request URL in the following format:
							 * http://192.168.68.92:8080/billgate/sdoConsign.do?key=966&callTime=2009-04-29+10%3A55%3A00&userIdSrc=testbbb&amount=1&feeDest=1&feeSrc=0&userIdDest=testaaa&orderId=00000096620090429105500000000100&goodsNum=1&payType=3&indication=test123&goodsInfo=1%2C1%2C1&sign=651A9E9B508E67820B5E410E0F6D73F1
							 * 
							 */
							String orderUrl = orderProvider.buildOrderUrl(order);
							
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
