g_CoroutineList = {};
g_RunningList = {};
g_RunningCount = 0;
g_RunningCoName = nil;

MAX_CO_PER_LOOP = 4;
MAX_RUNNING_CO = 4096;

-----------------------------------------------------------
-- Create protocol table
g_ProtocolTable = {};
protocol = {};

function _InitProtocolTable()
    for k,v in pairs(ExternalMessage) do
		if string.sub(k,2,2) == '2' then
			if type(v) == 'number' then
				if string.sub(k,5,17) ~= 'message_begin' and string.sub(k,5,15) ~= 'message_end' then
					local msg_id = ExternalMessage[string.lower(k)];
					local msg_prefix = string.sub(k,1,3);
					g_ProtocolTable[msg_id] = 'ExternalMessage::'..string.upper(k)
--					print("id:"..msg_id.." value:"..g_ProtocolTable[msg_id]);
				end
			end
			protocol[k] = v;
		end
    end

end

_InitProtocolTable();

-----------------------------------------------------------
-- Tool functions for test case lua codes

function _resume(cname, ...)

    if g_RunningList[cname].msgCount ~= nil then
	    local i = 1;
	    while i <= g_RunningList[cname].msgCount do
		un_register_msg(g_RunningList[cname].msgInfo[i].sessionID);
		i = i + 1;
	    end
    end

    g_RunningCoName = cname;
    local ret, errormsg = coroutine.resume(g_RunningList[cname].co, ...);
	g_RunningCoName = nil;

    if (not ret) then
        print("["..cname.."] "..errormsg);
        detach_coroutine(cname);
        setstatus(cname, errormsg);
        setresult(cname, "failed");
		g_RunningList[cname].msgCount = 0;
		g_RunningList[cname].msgInfo = nil;
        g_RunningList[cname] = nil;
        g_RunningCount = g_RunningCount - 1;
 	
    elseif (coroutine.status(g_RunningList[cname].co) == "dead") then	 
		print("coroutine.lua _resume found ["..cname.."] dead, so detach_coroutine");
        detach_coroutine(cname);
        setresult(cname, "passed");
		g_RunningList[cname].msgCount = 0;
		g_RunningList[cname].msgInfo = nil;
        g_RunningList[cname] = nil;
        g_RunningCount = g_RunningCount - 1;			
    end
end

function check(condition, error_msg)
    local ar = debug.getinfo(2, "lS");
    if (condition == nil or not condition) then
        setstatus(g_RunningCoName, "error : "..error_msg..", at line "..ar.currentline.." in "..ar.source);
        error("["..g_RunningCoName.."] error : "..error_msg..", at line "..ar.currentline.." in "..ar.source);
    else
        print("["..g_RunningCoName.."] pass : at line "..ar.currentline.." in "..ar.source);
        setstatus(g_RunningCoName, "pass : at line "..ar.currentline.." in "..ar.source);
    end
end

function recv_msg(overtime, ...)
	local param = {...};
	
	local CParam = {};
	local msgInfo = {};

    local index = 0;
    for k,v in pairs(param) do
		if(k % 2 == 1) then
			index = index + 1;
			msgInfo[index] = {};
			msgInfo[index].sessionID = v;
		else
			msgInfo[index].msgID = v;
		end
		CParam[k] = v;
    end

    local i = 1;
	local status = "receiving msg ";
	while i <= index do
		if i > 1 then
			status = status.."or"..g_ProtocolTable[msgInfo[i].msgID];
		else
			status = status..g_ProtocolTable[msgInfo[i].msgID];
		end
		i = i + 1;
	end
	--status = status.."... now received msg:"
    
	setstatus(g_RunningCoName, status.." in "..overtime.." sce");
	
    g_RunningList[g_RunningCoName] = {};
    g_RunningList[g_RunningCoName].type = "recv_msg";
    g_RunningList[g_RunningCoName].co = coroutine.running();
    g_RunningList[g_RunningCoName].endTime = os.clock() + overtime;

    g_RunningList[g_RunningCoName].strstatus = status;
    g_RunningList[g_RunningCoName].msgCount = index;
    g_RunningList[g_RunningCoName].flag = "or";
    g_RunningList[g_RunningCoName].receiveCount = 0;
    g_RunningList[g_RunningCoName].msgInfo = nil;
    g_RunningList[g_RunningCoName].msgInfo = msgInfo;


    register_msg(g_RunningCoName, CParam);
    return coroutine.yield();
end

function wait(duration)
    setstatus(g_RunningCoName, "waiting "..duration.." sec");

    g_RunningList[g_RunningCoName] = {};
    g_RunningList[g_RunningCoName].type = "wait";
    g_RunningList[g_RunningCoName].co = coroutine.running();
    g_RunningList[g_RunningCoName].endTime = os.clock() + duration;

    return coroutine.yield();
end

-----------------------------------------------------------
-- event handler functions for C codes
function addco(cname, f, ...)
    if (g_CoroutineList[cname] ~= nil) then
        print("duplicated coroutine name "..cname);
        return
    end
    g_CoroutineList[cname] = {};
    g_CoroutineList[cname].f = f;
    g_CoroutineList[cname].param = {...};
end

function MainLoop()
    local currentTime = os.clock();

    -- check overtime msg
    local k,v = next(g_RunningList, nil);
    while (k ~= nil) do
        local nk,nv = next(g_RunningList, k);
        if (v.type == "recv_msg") then
            if currentTime >= v.endTime then
				local i = 1;	
				while i <= v.msgCount do
					if(v.msgInfo[i].msg == nil) then
						OnRecvMsg(k, v.msgInfo[i].sessionID, v.msgInfo[i].msgID, nil);
					end
					i = i + 1;
				end
			else
				--receiving msg
				setstatus(k, v.strstatus.." in "..(v.endTime - currentTime).." sec");
            end
        elseif (v.type == "wait") then
            if currentTime >= v.endTime then
				--print("wait resume");
                _resume(k, nil);
            else
                setstatus(k, "waiting "..(v.endTime - currentTime).." sec");
            end
        end
        k = nk;
        v = nv;
    end

    local counter = 0;
    k, v = next(g_CoroutineList, nil);
    while (k ~= nil) and (counter < MAX_CO_PER_LOOP) and
        (g_RunningCount < MAX_RUNNING_CO) do
        nk, nv = next(g_CoroutineList, k);

        setstatus(k, "start to run...");

        local co = coroutine.create(v.f);
        g_RunningCoName = k;
        local ret, errormsg = coroutine.resume(co, unpack(v.param));
        g_RunningCoName = nil;

        if (not ret) then
            print("["..k.."] "..errormsg);
            detach_coroutine(k);
            setstatus(k, errormsg);
            setresult(k, "failed");
        elseif (coroutine.status(co) == "dead") then
			print("coroutine.lua MainLoop found ["..k.."] dead, so detach_coroutine");
            detach_coroutine(k);
            setresult(k, "passed");
        elseif (coroutine.status(co) == "suspended") then
            g_RunningCount = g_RunningCount + 1;
        end

        counter = counter + 1;
        g_CoroutineList[k] = nil;
        k = nk;
        v = nv;	
    end
end

function OnRecvMsg(cname, session_id, msg_id, msg)
    local i = 1;
	

    if(g_RunningList[cname] == nil) then
		print("nil");
		return;
    end

    while( i <= g_RunningList[cname].msgCount) do

		if(g_RunningList[cname].msgInfo[i].sessionID == session_id and g_RunningList[cname].msgInfo[i].msgID == msg_id) then
						
			local szPacketName = g_ProtocolTable[msg_id];
			msg = Cast(msg, szPacketName);

			g_RunningList[cname].msgInfo[i].msg = nil;
			g_RunningList[cname].msgInfo[i].msg = msg;
			g_RunningList[cname].receiveCount = g_RunningList[cname].receiveCount + 1;
			g_RunningList[cname].strstatus = g_RunningList[cname].strstatus.." "..g_ProtocolTable[msg_id];

			
			if(g_RunningList[cname].flag == "or") then
				_resume(cname, msg, msg_id, session_id);
			
			elseif(g_RunningList[cname].flag == "and" and g_RunningList[cname].receiveCount == g_RunningList[cname].msgCount) then
				
				--print("receive count:"..g_RunningList[cname].receiveCount);
				--print("msgCount:"..g_RunningList[cname].msgCount);

				if(g_RunningList[cname].msgCount == 1) then
					--print("receive resume");
					_resume(cname, msg, msg_id, session_id);
				
				elseif(g_RunningList[cname].msgCount >= 2) then
					--print("receive resume:"..g_RunningList[cname].msgCount);
					local msgInfo = g_RunningList[cname].msgInfo;
					_resume(cname, msgInfo);
				end			
			end

		break;
		end

	i = i + 1;
	end
end


function recv_msg_and(overtime, ...)
	local param = {...};
	
	local CParam = {};
	local msgInfo = {};

    local index = 0;
    for k,v in pairs(param) do
		if(k % 2 == 1) then
			index = index + 1;
			msgInfo[index] = {};
			msgInfo[index].sessionID = v;
		else
			msgInfo[index].msgID = v;
		end
	CParam[k] = v;
    end

    local i = 1;
    local status = "receiving msg ";
    while i <= index do
	if i > 1 then
		status = status.." or "..g_ProtocolTable[msgInfo[i].msgID];
	else
		status = status..g_ProtocolTable[msgInfo[i].msgID];
	end
	i = i + 1;
    end
    status = status.."... now received msg:"
    
    setstatus(g_RunningCoName, status.." in "..overtime.." sce");
	
    g_RunningList[g_RunningCoName] = {};
    g_RunningList[g_RunningCoName].type = "recv_msg";
    g_RunningList[g_RunningCoName].co = coroutine.running();
    g_RunningList[g_RunningCoName].endTime = os.clock() + overtime;

    g_RunningList[g_RunningCoName].strstatus = status;
    g_RunningList[g_RunningCoName].msgCount = index;
    g_RunningList[g_RunningCoName].flag = "and";
    g_RunningList[g_RunningCoName].receiveCount = 0;
    g_RunningList[g_RunningCoName].msgInfo = nil;
    g_RunningList[g_RunningCoName].msgInfo = msgInfo;

    register_msg(g_RunningCoName, CParam);
    return coroutine.yield();
end