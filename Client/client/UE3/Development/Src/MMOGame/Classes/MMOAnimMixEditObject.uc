//
// 音效材质编辑器
//

class MMOAnimMixEditObject extends Object
	dependson(GamePlayDataManager)
	hidecategories(Object)
	native;

//struct AnimMixNode;
//新建这个只是为了 编辑器中使用
var() AnimMixNode AnimMixInfo;
/*
//源动画
var() editconst EAnimMixSource   SourceAnim;
//目标动画
var() editconst EAnimMixTarget    TargetAnim;
//对应的混合动画
var() AnimationNode                     Anim;*/
