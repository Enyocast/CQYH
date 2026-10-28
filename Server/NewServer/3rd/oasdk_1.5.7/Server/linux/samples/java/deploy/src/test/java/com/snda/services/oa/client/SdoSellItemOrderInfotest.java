
package com.snda.services.oa.client;

import java.util.concurrent.CountDownLatch;
import java.util.concurrent.atomic.AtomicLong;

import com.snda.services.oa.client.impl.OrderServiceProvider;
import com.snda.services.oa.client.impl.SdoSellItemOrderInfo;
/**
 * Item consignment example; see the protocol for parameter values
 * @author chenyifang
 *
 */
public class SdoSellItemOrderInfotest {

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
			new Thread() {
				public void run() {
					try {
						for (int i = 0; i < perThreadNum; i++) {
							OrderService orderProvider = new OrderServiceProvider();
							SdoSellItemOrderInfo order = new SdoSellItemOrderInfo();
							/**
							 * Populate the item consignment order information
							 */
							order.orderId = orderProvider.generateOrderId();
							order.orderIdRelation="223423333333333334";
							order.amount = 1;
							order.payType = 3;
							order.goodsNum = 1;
							order.indication = "test123";
							order.feeDest=1;
							order.feeSrc=1;
							order.goodsInfo="1,1,1";
							order.goodsNum=1;
							order.indication="0";
							order.userIdDest="24234";
							order.userIdSrc="6323423";
							/** Generate an order request URL in the following format:
							 * http://192.168.68.92:8080/billgate/SdoSellItem.do?key=966&callTime=2009-04-29+11%3A17%3A37&userIdSrc=6323423&amount=1&feeDest=1&feeSrc=1&userIdDest=24234&orderIdRelation=223423333333333334&orderId=00000096620090429111737000001996&goodsNum=1&payType=3&indication=0&goodsInfo=1%2C1%2C1&sign=6A13C8488AF480D9E746C70A33135F6E
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
