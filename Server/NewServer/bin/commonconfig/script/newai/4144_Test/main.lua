
Include("script/stringtable/stringtable.lh")
LoadPackage("chat_def.pkg")
LoadPackage("scene_def.pkg ")

Include("script/newai/sub_tree/sub_tree.lh");

local distance_limit = 300;

evtAIFight = 
{ btDebug,
	{ btSelector,
		{ btSequencer,
			{ batSetScanEnemyParam, param = { distance_limit, 0, 0, 0 } },
			{ batScanNearby },
			{ batCheckTarget, param = { tarNearestEnemy, 0, 0, 0 } },
			_cast_template_spell(astNormalSpell2, tarNearestEnemy, 3000);
		},
		{ btSequencer,
			{ batCheckTarget, param = { tarAITarget, 0, 0, 0 } },
			_cast_template_spell(astNormalSpell1, tarAITarget, 3000);
		},
	},
};
