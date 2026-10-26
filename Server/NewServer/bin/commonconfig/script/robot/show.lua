LoadPackage("asimov_common.pkg")
LoadPackage("asimov_user.pkg")
LoadPackage("role.pkg")
LoadPackage("ai.pkg")
LoadPackage("common.pkg")
LoadPackage("scene.pkg")

g_user = nil
g_role = nil

g_param = {}
g_routine = {}

function update_role()
    if not g_user then
        print("Global user Nil.")
        return false
    end

    g_role = g_user:GetPlayingRole()

    if not g_role then
        print("Role is Nil.")
        return false
    end

    return true
end

function bind_ex_ai()
    if not update_role() then
        return false
    end

    ai = g_role:GetAIProcessor()
    if not ai then
        print("AI Nil.")
	return
    end
    ai:SetWanderScript('script/ai/main.lua')
end

function release_ai()
    if not update_role() then
        return false
    end

    if g_role:GetAIProcessor() == Nil then
        return false
    end

    g_role:RemoveAIProcessor()
    print("Release AI done.")
end

function create_ai()
    if not update_role() then
        return false
    end

    if g_role:GetAIProcessor() ~= Nil then
        return false
    end

    ai = g_role:CreateAIProcessor()
    if ai == Nil then
        print("Create AI fail.")
    end

    print("Create AI done.")
end

function get_pos()
    if not update_role() then
        return false
    end

    print(string.format("[%s] POS [X: %d Y: %d Z: %d]",
        g_role:GetName(), g_role:GetX(), g_role:GetY(), g_role:GetZ()))
end

function random_move()
    if not update_role() then
        return false
    end

    direction = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}}

    local role = g_role

    way = direction[math.random(4)];
    local x = role:GetX() + math.random(POINT_PER_METER * 10) * way[1];
    local y = role:GetY() + math.random(POINT_PER_METER * 10) * way[2];

    print("AI role[" .. role:GetName() .. "] random move to " .. x .. " , " .. y);


    ai = role:GetAIProcessor()
    if ai then
        ai:MoveTo(x, y)
    else
        print("AI Nil, create temp ai.")
        ai = role:CreateAIProcessor()
        if ai then
            ai:MoveTo(x, y)
        end
    end

    return true
end


-- Set the params need to be displayed here.
function get_data()
    print('call get_data')
    if not update_role() then
        return false
    end

    -- Here we start to set value.

    g_param.UserName = g_user:GetUserName()
    -- g_param.UserType = g_user:GetUserType()
    g_param.RoleName = g_role:GetName()
    g_param.SceneName = tostring(g_role:GetSceneID())

    -- Set routine param.
    g_routine.GetPos = "get_pos()"
    g_routine.RandMov = "random_move()"
    g_routine.ReleaseAI = "release_ai()"
    -- g_routine.CreateAI = "create_ai()"
    -- g_routine.BindEXAI = "bind_ex_ai()"

    -- End of k/v setting.
    return true
end
