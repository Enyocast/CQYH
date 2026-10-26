
virtual FString GetDebugDescription();

virtual void TickSpecial( FLOAT DeltaSeconds );	
virtual void physWalking(FLOAT deltaTime, INT Iterations);
virtual void moveDelta(FVector Delta);
UAnimNodeSequence* GetActiveAnimSequence();
virtual void OnZoneOrGridChanged(void* pOldZonePter, void* pOldGridPter, void* pNewZonePter, void* pNewGridPter);	// zhaojun@snda
virtual INT32 CalGridBlockRadius();	// zhaojun@snda
virtual void ReCalGridBlockRadius();	// zhaojun@snda

//virtual ~AMMOActor();


// add by zhangrui05@snda
void PlayEventSound(USoundCue* sound);

virtual bool ValidateMoveDest(const FVector& dest) const;

