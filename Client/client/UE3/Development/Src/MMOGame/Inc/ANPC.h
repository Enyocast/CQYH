
//Start 用于SingleNPCSpawnPoint
virtual INT GetServerID(){ return AutoServerID; }
virtual INT GetObjectServerType() const { return (INT)kotSingleNpc; }
//End 用于SingleNPCSpawnPoint
virtual void TickSpecial( FLOAT DeltaSeconds );
virtual INT32 CalGridBlockRadius();	// zhaojun@snda


virtual FString GetDetailedDescription( INT InIndex );

virtual void PlayRandomSound(const TArray<class USoundCue*>& soundList);

bool CanPlayOpenSoundNow() const;
bool CanPlayCloseSoundNow() const;
bool CanPlayAnimSoundNow() const;

void StartOpenSoundPlayCD();
void StartCloseSoundPlayCD();
void StartAnimSoundPlayCD();

// add by zhangrui05@snda
void PlayTalkSound();
void PlayEventSound(USoundCue* sound);

virtual FString GetUserDefinedName() const
{
	return Template->GetName();
}

virtual FString GetDebugDescription()
{
	FString resName;
	if( Mesh && Mesh->SkeletalMesh )
	{
		if( Mesh->SkeletalMesh->GetOuter() )
		{
			resName = Mesh->SkeletalMesh->GetOuter()->GetName();
		}
		resName += FString(TEXT(".")) + Mesh->SkeletalMesh->GetName();
	}
	return FString::Printf( TEXT("%s[%s]"), *Template->GetName(), *resName );
}