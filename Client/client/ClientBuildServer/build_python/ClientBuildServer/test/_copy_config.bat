set srcDir=C:\AutoBuild\Source\08.Prog%1\NewServer\bin\commonconfig\setting\
set destDir=%2CQYH\MMOGame\Config\
rem C:\AutoBuild\edition\Shipping_Bin\CQYH\MMOGame\Config\
set extractExe=C:\AutoBuild\python_client8088\ExtractTable.exe

del /F /Q %destDir%*.xlsx 
del /F /Q %destDir%*.xls
del /F /Q %destDir%*.xlsm

rem goto exit
rem md C:\AutoBuild\edition\Shipping_Bin\CQYH\MMOGame
rem md C:\AutoBuild\edition\Shipping_Bin\CQYH\MMOGame\Config

md %2CQYH\MMOGame
md %2CQYH\MMOGame\Config


copy %srcDir%attribute.txt	%destDir%attribute.txt  /Y
copy %srcDir%attributes1.txt	%destDir%attributes1.txt    /Y
copy %srcDir%attributes2.txt	%destDir%attributes2.txt  /Y
copy %srcDir%set.txt		%destDir%set.txt  /Y
copy %srcDir%spell_var.txt       %destDir%spell_var.txt  /Y
copy %srcDir%transform.txt       %destDir%transform.txt  /Y
copy %srcDir%weapon_rune_id.txt        %destDir%weapon_rune_id.txt  /Y
copy %srcDir%role_relation.txt   	%destDir%role_relation.txt  /Y
copy %srcDir%title.txt   	 	%destDir%title.txt  /Y
copy %srcDir%spell_progress.txt   	 %destDir%spell_progress.txt   /Y
copy %srcDir%refine.txt   	 %destDir%refine.txt    /Y
copy %srcDir%affix.txt   	 %destDir%affix.txt    /Y
copy %srcDir%shop.txt   	 %destDir%shop.txt   /Y
copy %srcDir%soul.txt   	 %destDir%soul.txt   /Y
copy %srcDir%item.txt   	 %destDir%item.txt   /Y
copy %srcDir%item_armor.txt   	 %destDir%item_armor.txt   /Y
copy %srcDir%doodad_drop_data.txt   	 %destDir%doodad_drop_data.txt   /Y
copy %srcDir%drop_group.txt   	 %destDir%drop_group.txt   /Y
copy %srcDir%Compose.txt   	 %destDir%Compose.txt   /Y

copy %srcDir%refine_attribute.txt   	 %destDir%refine_attribute.txt   /Y
copy %srcDir%refine_attr.txt   	 	 %destDir%refine_attr.txt   /Y

copy %srcDir%loadmaptips.txt		%destDir%loadmaptips.txt   /Y
copy %srcDir%spirit_change.txt		%destDir%spirit_change.txt   /Y
copy %srcDir%spirit.txt			%destDir%spirit.txt   /Y
copy %srcDir%air.txt   	 	 	%destDir%air.txt   /Y
copy %srcDir%blood.txt			%destDir%blood.txt   /Y

copy %srcDir%rune.txt		%destDir%rune.txt   /Y


%extractExe% %srcDir%npc.txt %destDir%npc.txt Index TemplateID
%extractExe% %srcDir%spell.txt %destDir%spell.txt Index SpellCommonAttribute.ID SpellCommonAttribute.Class SpellCommonAttribute.RuneSlotID SpellCommonAttribute.CastType
%extractExe% %srcDir%aura.txt %destDir%aura.txt Index TemplateID
%extractExe% %srcDir%missile.txt %destDir%missile.txt Index ID

:exit
