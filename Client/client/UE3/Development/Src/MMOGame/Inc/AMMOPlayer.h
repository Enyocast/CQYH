
// todo:

virtual void performPhysics(FLOAT DeltaSeconds);
virtual void TickSpecial( FLOAT DeltaSeconds );

virtual void moveDelta(FVector Delta);
bool ValidateMoveDest(const FVector& dest) const;

virtual void OnZoneOrGridChanged(void* pOldZonePter, void* pOldGridPter, void* pNewZonePter, void* pNewGridPter);	// zhaojun@snda

INT GetRealMoney();
void SetRealMoney(INT money);

void PlayOperationMaterialAni();

void BeginOperateMaterial();

#ifdef _DEBUG
virtual void physWalking(FLOAT deltaTime, INT Iterations);
#endif

