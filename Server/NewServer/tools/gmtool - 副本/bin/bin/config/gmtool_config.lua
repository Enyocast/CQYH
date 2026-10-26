

TL_CONFIG = {};

TL_CONFIG["ServerList"] ={
	nSvrNum = 2,
	arrGMList = {
		[0] = {
			nSvrID = 1,
			szName = "测试一",
			szAddr = "172.30.68.62",
			dwPort = 9011,
		},
		[1] = {
			nSvrID = 2,
			szName = "内网",
			szAddr = "172.30.66.35",
			dwPort = 9011,
		},
	},
}



function LoadTraverseTable(d, t)
    for k,v in pairs(t) do
		if d[k] == nil then
			print("variable "..k.." is nil")
		else
			if type(v) == "table" then
				LoadTraverseTable(d[k], v)
			else
				d[k] = t[k];
			end
		end
    end
end

function LoadFile()
	LoadTraverseTable(GetTLConfig(), TL_CONFIG);
end


