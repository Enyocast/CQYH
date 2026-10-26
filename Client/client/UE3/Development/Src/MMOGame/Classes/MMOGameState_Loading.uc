class MMOGameState_Loading extends MMOGameState
	native;

var MMOGFXLoadPlayer LoadMovie;
var bool PreLoading;
function CreateLoadMovie()
{
	if(class'Engine'.static.IsEditor())
	{
		return;
	}

	if( LoadMovie != none)
		return;

	LoadMovie = new class'MMOGFXLoadPlayer';
	//LoadMovie.SetTimingMode(TM_Real);
	LoadMovie.MovieInfo = SwfMovie(DynamicLoadObject(LoadMovie.MovieInfoStr, class'SwfMovie', FALSE));
	LoadMovie.Init(class'Engine'.static.GetEngine().GamePlayers[0]);
}

function Init()
{
	super.Init();
	CreateLoadMovie();
}

native function EGameState GetID();
native function OnPreEnter();
native function OnEnter();
native function OnLeave();
native function OnAftLeave();
native function OnUpdate();

DefaultProperties
{
	PreLoading=false
}
