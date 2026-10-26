public:

	virtual INT Main(const FString& Params);

	void StartChildren(INT NumFiles);
	void StartChildJob(const TArray<FString>& Job);
	void StopChildren();

	UBOOL ChildIsIdle(INT ProcessIndex);
	void CheckForCrashedChildren();

	void SendChildCommand(INT ProcessIndex, const TArray<FString>& Command);
	UBOOL SendStopCommands();

	TArray<FString> GetMyNextJob();
	void JobCompleted();

	void MergeLogs(FString* CriticalReason = NULL);

	void RobustSaveStringToFile(const TArray<FString>& String, const TCHAR *Filename);
	void WaitToDeleteFile(const TCHAR *Filename);

	void ProcessPkgs(const TArray<FString>& upkList, const TArray<FString>& udkList, TSet<FString>& resources);

	FString GetChildProcessWorkDir(INT processIdx) const;
	FString GetCurrentChildProcessWorkDir() const;
