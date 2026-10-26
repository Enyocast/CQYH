

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

static TSet<FString> ReadResList(const FString& fileName);
static bool WriteResList(const FString& fileName, const TSet<FString>& resList);

FString GetChildProcessWorkDir(INT processIdx) const;
FString GetCurrentChildProcessWorkDir() const;

void CollectResRefFromConfig();
void CollectForDiffuseTexture(const FString& diffuseTexPath, TSet<FString>& tmpRes);
