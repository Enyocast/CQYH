

function TestCase.Mail()
    local user_name1 = "MA1_" .. os.date("%Y%H%M%S");
    local user_name2 = "MA2_" .. os.date("%Y%H%M%S");
    local user1, user2;
    local role1, role2;
    local ret;
    local msg;
    local session_id1, session_id2;
    local mailid;

    --Log in
    user1, role1 = startup(user_name1, user_name1);
    check(user1, "failed to create user1");
    check(role1, "failed to create role1");
    session_id1 = user1:GetSessionID();

    user2, role2 = startup(user_name2, user_name2);
    check(user2, "failed to create user2");
    check(role2, "failed to create role2");
    session_id2 = user2:GetSessionID();

    --user1: add money with a GM command; sending mail costs money
    ret = user1:GMCommand("AddMoney(1, 10000, MONEYLOG_GM_COMMAND)");
    check(ret, "failed to add money");

    --user1: send mail to user2
    ret = user1:SendMail(user_name2, "test mail", "测试邮件正文！！！");
    check(ret, "failed to send mail");

    --user1: receive the successful send response
    msg = recv_msg(5, session_id1, protocol.m2c_mail_write_success);
    check(msg, "faield to recv m2c_mail_write_success");

    --user2: request the mail list
    ret = user2:ListMail();
    check(ret, "failed to send list mail");

    --user2: receive the mail list
    msg = recv_msg(5, session_id2, protocol.m2c_mail_list_recv);
    check(msg, "faield to recv m2c_mail_list_recv");
    check(msg.dwMailCount==1, "failed to recv correct mail list msg");
    check(msg.stBriefMailInfo[0].szSenderRoleName==user_name1, "failed to recv correct mail list msg");
    mailid = msg.stBriefMailInfo[0].dwMailID;

    --user2: read the mail
    ret = user2:ReadMail(mailid);
    check(ret, "failed to send read mail");

    --user2: receive the read-mail response
    msg = recv_msg(5, session_id2, protocol.m2c_mail_read);
    check(msg, "failed to recv m2c_mail_read");
    check(msg.dwMailID==mailid, "failed to recv correct mail read");
    check(msg.szMailContent=="测试邮件正文！！！", "failed to recv correct mail read");

    --user2: delete the mail
    ret = user2:DeleteMail(mailid);
    check(ret, "failed to send delete mail");

    --user2: receive the mail list again
    ret = user2:ListMail();
    check(ret, "failed to send list mail");

    msg = recv_msg(5, session_id2, protocol.m2c_mail_list_recv);
    check(msg, "faield to recv m2c_mail_list_recv");
    check(msg.dwMailCount==0, "failed to recv correct mail list msg");

    --Log out
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

    --Log in
    user, role = startup(user_name, user_name);
    check(user, "failed to create user");
    check(role, "failed to create role");
    session_id = user:GetSessionID();

    --Use a GM command to send mail with an attachment to yourself
    ret = user:GMCommand("SelfRole:TestSendSystemMailToSelf(101, 1)");
    check(ret, "failed to send system mail");

    --Wait for the new-mail notification
    msg = recv_msg(5, session_id, protocol.m2c_mail_new_count);
    check(msg, "failed to recv m2c_mail_new_count");
    check(msg.dwMailNewCount == 1, "failed to recv correct new mail count");

    --Request the mail list
    ret = user:ListMail();
    check(ret, "failed to send list mail");

    --Receive the mail list
    msg = recv_msg(5, session_id, protocol.m2c_mail_list_recv);
    check(msg, "faield to recv m2c_mail_list_recv");
    check(msg.dwMailCount==1, "failed to recv correct mail list msg");
    mailid = msg.stBriefMailInfo[0].dwMailID;

    --Collect the attachment
    ret = user:GetMailAttach(mailid);
    check(ret, "failed to send get mail attach");

    --Receive the item-change message
    msg = recv_msg(5, session_id, protocol.g2c_item_change);
    check(msg, "failed to recv g2c_item_change");

    --Log out
    cleanup(user);
end
