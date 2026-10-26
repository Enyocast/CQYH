/*
 * 模型定义
 * 
 */

class ModelData extends Object
	hidecategories(Object)
	dependson(AvatarData)
	native;

struct native ModelInfo
{
	var() EPlayerClass  ClassType;
	var() EGenderType   GenderType;
	var() AvatarData     AvatarDataLink;
};

var() array<ModelInfo>  ModelList;

defaultproperties
{

}