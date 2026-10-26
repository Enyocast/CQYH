
void Init();

void PlayAnimIdle();
void PlayAnimOpen();
void PlayAnimClose();

void RemoveParticleEffects();
void AddParticleEffects(class UParticleSystem* parTmp, FLOAT effScale);

void DestroyDoodadActor(INT disappearType);

void SetRemainOpenCount(INT newCnt, AMMOActor* instigateActor);
int GetRemainOpenCount() const;
void PlayDestroyAnim(AMMOActor* instigateActor);

bool IsRequireVarOK() const;
bool IsVarRequired() const;

//virtual TickSpecial( FLOAT DeltaSeconds );

virtual FString GetDebugDescription();

virtual void TickSpecial(FLOAT Delta);

void BeginOperate(INT OperatorId, FLOAT InDuration);
void EndOperate(UBOOL bBreak);

void PlayEffect(INT InIndex);

virtual INT32 CalGridBlockRadius() ;	// zhaojun@snda
