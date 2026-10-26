LoadPackage("gameworld.pkg")
LoadPackage("role.pkg")
LoadPackage("scene.pkg")
LoadPackage("chat_def.pkg")
LoadPackage("item_bag.pkg")

Include("script/include/btnod.lua")

local g_oGameWorld = CGameWorld:GetInstance();

function send_kill_info(owner)
 
  local role =  g_oGameWorld:FindValidRole(get_ctx_role_id());
  local killer = g_oGameWorld:FindValidRole(role:GetLastCasterID());
  if role and killer then
    local ret = role:GetItemBag():DeleteItemId(2800253,1,ITEMLOG_SCRIPT,false,0);
    if ret == 1 then
      return brvSsuccess;
    end
    ret = role:GetItemBag():DeleteItemId(2800254,1,ITEMLOG_SCRIPT,false,0);
    if ret == 1 then
      return brvSsuccess;
    end
    ret = role:GetItemBag():DeleteItemId(2800255,1,ITEMLOG_SCRIPT,false,0);
    if ret == 1 then
      return brvSsuccess;
    end
    ret = role:GetItemBag():DeleteItemId(2800256,1,ITEMLOG_SCRIPT,false,0);
    if ret == 1 then
      return brvSsuccess;
    end
    ret = role:GetItemBag():DeleteItemId(2800257,1,ITEMLOG_SCRIPT,false,0);
    if ret == 1 then
      return brvSsuccess;
    end
    ret = role:GetItemBag():DeleteItemId(2800258,1,ITEMLOG_SCRIPT,false,0);
    if ret == 1 then
      return brvSsuccess;
    end
  end
  print("4");
  return brvFail;
end

Include("script/scene/MirAct11/scene_bt.lua")

