set srcDir=C:\AutoBuild\Source\08.Prog%1\NewServer\bin\commonconfig\setting\
set destDir=%2
rem C:\AutoBuild\edition\Shipping_Bin\CQYH\MMOGame\Config\
set extractExe=C:\AutoBuild\python_client8088\ExtractTable.exe

del /F /Q %destDir%*.*
rem pause
rem del /F /Q %destDir%*.xlsx 
rem del /F /Q %destDir%*.xls
rem del /F /Q %destDir%*.xlsm
rem del /F /Q %destDir%*.db

rem goto exit
rem md C:\AutoBuild\edition\Shipping_Bin\CQYH\MMOGame
rem md C:\AutoBuild\edition\Shipping_Bin\CQYH\MMOGame\Config

rem md %2CQYH\MMOGame
rem md %2CQYH\MMOGame\Config

rem %extractExe% %srcDir%affix.txt %destDir%affix.txt

%extractExe% %srcDir%missile.txt %destDir%missile.txt
%extractExe% %srcDir%aura.txt %destDir%aura.txt
%extractExe% %srcDir%attribute.txt %destDir%attribute.txt
%extractExe% %srcDir%spell_var.txt %destDir%spell_var.txt
%extractExe% %srcDir%spell_progress.txt %destDir%spell_progress.txt
%extractExe% %srcDir%spell.txt %destDir%spell.txt
%extractExe% %srcDir%transform.txt %destDir%transform.txt
%extractExe% %srcDir%rune.txt %destDir%rune.txt
%extractExe% %srcDir%item.txt %destDir%item.txt
%extractExe% %srcDir%item_armor.txt %destDir%item_armor.txt
%extractExe% %srcDir%drop_group.txt %destDir%drop_group.txt
%extractExe% %srcDir%doodad_drop_data.txt %destDir%doodad_drop_data.txt
%extractExe% %srcDir%doodad.txt %destDir%doodad.txt
%extractExe% %srcDir%npc.txt %destDir%npc.txt
%extractExe% %srcDir%circle_quest.txt %destDir%circle_quest.txt
%extractExe% %srcDir%quest_reward.txt %destDir%quest_reward.txt
%extractExe% %srcDir%quest_recycle.txt %destDir%quest_recycle.txt
%extractExe% %srcDir%reward_quest_money_cost.txt %destDir%reward_quest_money_cost.txt
%extractExe% %srcDir%set.txt %destDir%set.txt
%extractExe% %srcDir%soul.txt %destDir%soul.txt
%extractExe% %srcDir%level.txt %destDir%level.txt
%extractExe% %srcDir%attributes1.txt %destDir%attributes1.txt
%extractExe% %srcDir%attributes2.txt %destDir%attributes2.txt
%extractExe% %srcDir%role_relation.txt %destDir%role_relation.txt
%extractExe% %srcDir%title.txt %destDir%title.txt
%extractExe% %srcDir%mount.txt %destDir%mount.txt
%extractExe% %srcDir%achievement.txt %destDir%achievement.txt
%extractExe% %srcDir%guild_building.txt %destDir%guild_building.txt
%extractExe% %srcDir%guild_welfare.txt %destDir%guild_welfare.txt
%extractExe% %srcDir%guild_dungeon.txt %destDir%guild_dungeon.txt
%extractExe% %srcDir%spirit_slot.txt %destDir%spirit_slot.txt
%extractExe% %srcDir%spirit.txt %destDir%spirit.txt
%extractExe% %srcDir%air.txt %destDir%air.txt
%extractExe% %srcDir%blood.txt %destDir%blood.txt
%extractExe% %srcDir%spirit_change.txt %destDir%spirit_change.txt
%extractExe% %srcDir%Activity.txt %destDir%Activity.txt
%extractExe% %srcDir%activity_reward.txt %destDir%activity_reward.txt
%extractExe% %srcDir%master_gift.txt %destDir%master_gift.txt
%extractExe% %srcDir%real_money_shop.txt %destDir%real_money_shop.txt
%extractExe% %srcDir%refine_attr.txt %destDir%refine_attr.txt
%extractExe% %srcDir%refine.txt %destDir%refine.txt

:exit
