// vertex local position( before transform )
// ming@snda

class MaterialExpressionVertexPosition extends MaterialExpression
	native( Material )
	collapsecategories
	hidecategories( Object );

cpptext
{
	virtual INT Compile( FMaterialCompiler* Compiler, INT OutputIndex );
	virtual FString GetCaption() const;
}

defaultproperties
{
	MenuCategories(0)="Coordinates"
}