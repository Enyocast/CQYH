

function TestCase.Mail()
    local user_name1 = "MA1_" .. os.date("%Y%H%M%S");
    local user_name2 = "MA2_" .. os.date("%Y%H%M%S");
    local user1, user2;
    local role1, role2;
    local ret;
    local msg;
    local session_id1, session_id2;
    local mailid;

    --登录
    user1, role1 = startup(user_name1, user_name1);
    check(user1, "failed to create user1");
    check(role1, "failed to create role1");
    session_id1 = user1:GetSessionID();

    user2, role2 = startup(user_name2, user_name2);
    check(user2, "failed to create user2");
    check(role2, "failed to create role2");
    session_id2 = user2:GetSessionID();

    --user1: 用GM指令加钱，发邮件是要钱的
    ret = user1:GMCommand("AddMoney(1, 10000, MONEYLOG_GM_COMMAND)");
    check(ret, "failed to add money");

    --user1: 给user2发邮件
    ret = user1:SendMail(user_name2, "test mail", "测试邮件正文！！！");
    check(ret, "failed to send mail");

    --user1: 收到邮件发送成功回复
    msg = recv_msg(5, session_id1, protocol.m2c_mail_write_success);
    check(msg, "faield to recv m2c_mail_write_success");

    --user2: 邮件列表
    ret = user2:ListMail();
    check(ret, "failed to send list mail");

    --user2: 收到邮件列表
    msg = recv_msg(5, session_id2, protocol.m2c_mail_list_recv);
    check(msg, "faield to recv m2c_mail_list_recv");
    check(msg.dwMailCount==1, "failed to recv correct mail list msg");
    check(msg.stBriefMailInfo[0].szSenderRoleName==user_name1, "failed to recv correct mail list msg");
    mailid = msg.stBriefMailInfo[0].dwMailID;

    --user2: 读取邮件
    ret = user2:ReadMail(mailid);
    check(ret, "failed to send read mail");

    --user2: 收到读取邮件回复
    msg = recv_msg(5, session_id2, protocol.m2c_mail_read);
    check(msg, "failed to recv m2c_mail_read");
    check(msg.dwMailID==mailid, "failed to recv correct mail read");
    check(msg.szMailContent=="测试邮件正文！！！", "failed to recv correct mail read");

    --user2: 删除邮件
    ret = user2:DeleteMail(mailid);
    check(ret, "failed to send delete mail");

    --user2: 再收一次邮件列表
    ret = user2:ListMail();
    check(ret, "failed to send list mail");

    msg = recv_msg(5, session_id2, protocol.m2c_mail_list_recv);
    check(msg, "faield to recv m2c_mail_list_recv");
    check(msg.dwMailCount==0, "failed to recv correct mail list msg");

    --登出
    cleanup(user1);
    cleanup(user2);
end


function TestCase.MailAttach()
	local user_name = "MT_" .. os.date("%Y%H%M%S");
    local user;
    local role;
    local ret;
    local msg;
    local session_id;
    local mailid;

    --登录
    user, role = startup(user_name, user_name);
    check(user, "failed to create user");
    check(role, "failed to create role");
    session_id = user:GetSessionID();

    --用GM指令给自己发一封邮件，带附件的
    ret = user:GMCommand("SelfRole:TestSendSystemMailToSelf(101, 1)");
    check(ret, "failed to send system mail");

    --等待新邮件消息
    msg = recv_msg(5, session_id, protocol.m2c_mail_new_count);
    check(msg, "failed to recv m2c_mail_new_count");
    check(msg.dwMailNewCount == 1, "failed to recv correct new mail count");

    --请求邮件列表
    ret = user:ListMail();
    check(ret, "failed to send list mail");

    --收到邮件列表
    msg = recv_msg(5, session_id, protocol.m2c_mail_list_recv);
    check(msg, "faield to recv m2c_mail_list_recv");
    check(msg.dwMailCount==1, "failed to recv correct mail list msg");
    mailid = msg.stBriefMailInfo[0].dwMailID;

    --拿附件
    ret = user:GetMailAttach(mailid);
    check(ret, "failed to send get mail attach");

    --收到物品变动消息
    msg = recv_msg(5, session_id, protocol.g2c_item_change);
    check(msg, "failed to recv g2c_item_change");

    --登出
    cleanup(user);
end
