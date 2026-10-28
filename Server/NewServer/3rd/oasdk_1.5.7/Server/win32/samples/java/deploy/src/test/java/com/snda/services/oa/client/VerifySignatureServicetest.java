package com.snda.services.oa.client;

import java.util.concurrent.CountDownLatch;
import java.util.concurrent.atomic.AtomicLong;

import com.snda.services.oa.client.impl.VerifySignatureServiceProvider;
/**
 * Signature verification and generation service test
 * @author chenyifang
 *
 */
public class VerifySignatureServicetest {

	public static void main(String[] args) throws InterruptedException {
		int thread = 10;
		int num = 1000;
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
							VerifySignatureServiceProvider signProvider = new VerifySignatureServiceProvider();
						   /**
						    * Signature generation example; the parameters to sign are:
						    * orderId|userId|appId|areaId|groupId|depPayType|depValue|callTime|indication
						    */
							String signed = signProvider.sign("00000099520090429102100000000007|40093433|10001|1|1|3|1|2009-04-29 10:21:01|1|appcode:1");
							System.out.println("signed="+signed);
							/**
							 * Signature verification example; the parameters to verify are:
							 * orderId|userId|appId|areaId|groupId|depPayType|depValue|callTime|indication
							 */
							boolean flag = signProvider.verify("00000099520090429102100000000007|40093433|10001|1|1|3|1|2009-04-29 10:21:01|1|appcode:1", signed);
							System.out.println("verify=" + flag);
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
