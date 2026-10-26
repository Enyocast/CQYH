TestCase.Scene = {};

function TestCase.Scene.Weather()
	local msg, ret;
    local user_name = "weat"..os.date("%H%M%S");
    local user, role = startup(user_name, user_name);

	ret = user:GMCommand('weather '..swtFog);
	check(ret, 'failed to run gm command');
   
	msg = recv_msg(40, user:GetSessionID(), protocol.g2c_update_weather);
	check(msg, 'failed to recv g2c_update_weather');
	check(msg.byWeather == swtFog, 'error weather id');
	
    cleanup(user);
end