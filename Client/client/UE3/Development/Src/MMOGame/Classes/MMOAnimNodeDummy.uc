class MMOAnimNodeDummy extends AnimNodeSequence;

var()   name        StateName;
var()   AnimTree    StateAnimTree;

function ReplaceByAnimNodes()
{
	local AnimNodeBlendBase node;
	foreach ParentNodes( node )
	{
		if( node.Children.Length != 1 )
		{
			`log( "Error: wrong animation node dummy." );
		}
		// copy the anim nodes ot StateAnimTree to replace the dummy node
		node.Children[0] = StateAnimTree.Children[0];
	}
}

DefaultProperties
{
}
