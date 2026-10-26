
/**
 * Add by jimzhang 2012.8.15
 * 
 */
class AnimNodeBlendPerBoneEx extends AnimNodeBlendPerBone
	native(Anim);

cpptext
{
	// AnimNode interface
	virtual	void TickAnim(FLOAT DeltaSeconds);
}

defaultproperties
{
}
