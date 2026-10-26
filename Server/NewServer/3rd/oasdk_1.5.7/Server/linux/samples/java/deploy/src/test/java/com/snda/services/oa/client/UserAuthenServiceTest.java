package com.snda.services.oa.client;

import java.util.concurrent.CountDownLatch;
import java.util.concurrent.atomic.AtomicLong;
/**
 * 用户信息认证
 */
import com.snda.services.oa.client.impl.UserAuthenServiceProvider;

public class UserAuthenServiceTest {

	public static void main(String[] args) throws InterruptedException {
		int thread = 10;
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
							UserAuthenService userauthenProvider = new UserAuthenServiceProvider();
							UserAuthenInfo userAuthenInfo = new UserAuthenInfo();
							userAuthenInfo.sessionId = "1E26FA815F3440A884089CFBE0998AEB";
							userAuthenInfo.uniqueId=222222222;
							userAuthenInfo.clientIpAddress = "192.168.68.67";
							UserInfo unserinfo = userauthenProvider
									.getUserInfo(userAuthenInfo);
							System.out.println("UserInfo.result=" + unserinfo.result);
							System.out.println("UserInfo.idCard="+unserinfo.idCard);
							System.out.println("UserInfo.ptId="+unserinfo.ptId);
							System.out.println("UserInfo.sndaId="+unserinfo.sndaId);
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
