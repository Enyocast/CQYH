class MMOAnimBlendByState extends AnimNodeBlendList;

var MMOAnimNodeDummy    CurrentAnimTree;
var array< MMOAnimNodeDummy >   AnimTreeArray;

function OnStateChange( name nextStateName, optional float fBlendTime = 0.2f )
{
	local MMOAnimNodeDummy nextAnimTree;
	local int idx;
	idx = 0;
	foreach AnimTreeArray( nextAnimTree )
	{
		if( nextAnimTree.StateName == nextStateName )
		{
			if( CurrentAnimTree != nextAnimTree )
			{
				SetActiveChild( idx, fBlendTime );
				CurrentAnimTree = nextAnimTree;
			}
			break;
		}
		++idx;
	}
}

DefaultProperties
{
}
