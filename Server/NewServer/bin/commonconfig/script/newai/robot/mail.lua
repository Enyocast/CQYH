

function write_mail(owner)
    local role = tolua.cast(owner, 'CRole');
    local user = CUserMgr:GetInstance():FindUser(role:GetSessionID());
    local target_user = rand_another_user(user);
    
    if target_user then
        local target_role = target_user:GetPlayingRole();
        if target_role then
            user:SendMail(target_role:GetName(), "Robot Test Mail", "Robot Test Mail");
        end
    end
    
    return brvSuccess;
end

function list_mail(owner)
    local role = tolua.cast(owner, 'CRole');
    local user = CUserMgr:GetInstance():FindUser(role:GetSessionID());
    
    user:ListMail();
    
    return brvSuccess;
end

function read_mail(owner)
    local role = tolua.cast(owner, 'CRole');
    local mailid = role:GetFirstMail();
    
    if (mailid ~= 0) then
        local user = CUserMgr:GetInstance():FindUser(role:GetSessionID());
        user:ReadMail(mailid);
    end
    
    return brvSuccess;
end

function delete_mail(owner)
    local role = tolua.cast(owner, 'CRole');
    local mailid = role:GetFirstMail();
    
    if (mailid ~= 0) then
        local user = CUserMgr:GetInstance():FindUser(role:GetSessionID());
        user:DeleteMail(mailid);
    end
    
    return brvSuccess;
end

function get_mail_attach(owner)
    local role = tolua.cast(owner, 'CRole');
    local mailid = role:GetFirstAttach();
    
    if (mailid ~= 0) then
        local user = CUserMgr:GetInstance():FindUser(role:GetSessionID());
        user:GetMailAttach(mailid);
    end
    
    return brvSuccess;
end

function do_mail_action(owner)
    local rand_value = math.random(5);

    if  rand_value == 1 then
        write_mail(owner);
    elseif rand_value == 2 then
        list_mail(owner);
    elseif rand_value == 3 then
        read_mail(owner);
    elseif rand_value == 4 then
        delete_mail(owner);
    elseif rand_value == 5 then
        get_mail_attach(owner);
    end
end