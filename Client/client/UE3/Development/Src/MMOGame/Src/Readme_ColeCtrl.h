#if 0
	角色的行为触发，
	1)	FSMState_xxx：虚拟机状态集
		FSMCtrl_xxx ：虚拟机的触发集
		FSMIO_xxx	：虚拟机输入集
	
	2)  FSMCtrl_Behavior：最主要最基础的行为触发集，包括行走，施放技能，交互等。
	
	3)  角色行走机制，向服务器发送SendRequest_MoveTo的同时，本机立刻进行移动eventScriptMoveTo,当收到Parse_g2c_char_move消息，再执行一下eventScriptMoveTo

	4)  角色技能机制，服务器有技能缓存机制，此刻向服务器发送的技能施放请求，如果服务器上技能尚未施放完全，会被缓存下来，等待当前技能施放完成后，自动接着
		施放。

	5)  干扰现象：服务器上是否有缓存的技能，客户端是不知道的，如果客户端在施放完技能的时候立刻发送移动指令，由于有网络延迟，客户端发送移动指令的时候，服
	    务器也在发送技能使用指令。客户端的移动指令是会失败的，但是客户端已经开始eventScriptMoveTo，移动指令失败，当客户端走出一定距离，是会被服务器强行拉回来的。

    6)  新角色行走机制，
		
		第一种：向服务器发送SendRequest_MoveTo的同时，本机立刻进行移动eventScriptMoveTo,当收到Parse_g2c_char_move消息，再执行一下eventScriptMoveTo
				优缺点：反应时间快，手感灵活，但是同步性差。
		第二种：向服务器发送SendRequest_MoveTo的同时，本机不做任何操作,当收到Parse_g2c_char_move消息，再执行eventScriptMoveTo
				优缺点：反应时间慢，手感较差，但是同步性很高。

	7)  角色行走的混合控制
		
		第一种情况，当角色处于位移状态的时候，连续使用第一种行走机制，注重反应时间和手感灵活度，同步也不会有问题。
		第二种情况，当角色处于战斗状态的时候，切换到位移状态的时候，需要先清除服务器上的技能缓存，然后使用第二种行走机制，这一下反应时间慢点关系不大，同步是最重要的问题。
		第三种情况，当角色处于空闲状态的时候，同第一种控制。

	8)  角色行走的混合控制,第二种详解：

		1. UPlayerActionEx_WaitingForClearCache 等待清除技能缓存，阻塞型。用在 UPlayerActionEx_MoveTo 等行为之前，等待返回消息，增加移动指令的成功性。
		2. g_PreMovetoPoint 为true使用第一种行走机制，为false使用第二种行走机制，默认为true，

	


	

#endif