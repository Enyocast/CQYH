package com.snda.services.oa.client;

import java.util.concurrent.CountDownLatch;
import java.util.concurrent.atomic.AtomicLong;

import com.snda.services.oa.client.impl.OrderServiceProvider;
import com.snda.services.oa.client.impl.SdoPayOrderInfo;
/**
 * Payment order example; see the protocol for parameter values
 * @author chenyifang
 *
 */
public class SdoPayOrderInfotest {

	public static void main(String[] args) throws InterruptedException {
		int thread = 1;
		int num = 10;
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
							SdoPayOrderInfo order = new SdoPayOrderInfo();
							/**
							 * Populate the payment order information
							 */
							order.orderId = orderProvider.generateOrderId();
							order.amount = 1;
							order.userId = "234234";
							order.payType = 3;
							order.goodsInfo="1,1,1";
							order.goodsNum = 1;
							order.indication = "test123";
							/**
							 * Generate an order request URL in the following format:
							 * http://192.168.68.92:8080/billgate/billGate.do?vendorCode=test&key=966&callTime=2009-04-29+11%3A06%3A11&amount=1&userId=234234&orderId=00000096620090429110611000000005&goodsNum=1&payType=3&indication=test123&goodsInfo=1%2C1%2C1&sign=E0901832344BB1059F997444883BF816
							 * 
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
