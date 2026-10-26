using System;
using System.Collections;
using System.Text;
using System.Diagnostics;
using System.Windows;
using System.Net;
using System.IO;
using System.Data;
using System.Threading;
using System.Security.Cryptography;



namespace FileUpdate
{
    public enum FileStateType
    {
        FST_WaitToProfile,
        FST_WaitToLoadFromLocalDisk,
        FST_WaitToDownLoadFromServer,
        FST_WaitToComputeMD5,
        FST_WaitToDecode,
        FST_WaitToWriteToDisk,
        FST_WaitToDeleteLocalFile,
        FST_Finished,
    }

    public enum SubTaskState
    {
        STS_ToDo,
        STS_Doing,
        STS_Done,
    }

    public enum MessageType
    {
        MT_Download,
        MT_ComputeMD5,
        MT_Uncompress,
        MT_ReadDisk,
        MT_WriteDisk,
        MT_Max,
    }


    public class FileNode
    {
        // common info
        public string RelativeName;
        public FileStateType StateType;

        public SubTaskState SubState;

        public Thread SubThread;

        // server info
        public string ServerMD5Value;
        public int ZipSize;

        public Byte[] ServerContent;

        public Byte[] UncompressedContext;

        // client info
        public string ClientMD5Value;
        public FileNode(string InRelativeName, string InMD5, string InZipSize)
        {
            RelativeName = InRelativeName;
            StateType = FileStateType.FST_WaitToProfile;
            SubState = SubTaskState.STS_ToDo;
            ServerMD5Value = InMD5;
            ZipSize = Convert.ToInt32(InZipSize);
            ServerContent = null;
            UncompressedContext = null;
            ClientMD5Value = "";
        }

        public FileNode(string InRelativeName)
        {
            RelativeName = InRelativeName;
            StateType = FileStateType.FST_WaitToProfile;
            SubState = SubTaskState.STS_ToDo;
            ServerMD5Value = "";
            ZipSize = 0;
            ServerContent = null;
            UncompressedContext = null;
            ClientMD5Value = "";
        }

        public void StopTask()
        {
            ServerContent = null;
            UncompressedContext = null;
            StateType = FileStateType.FST_Finished;
            SubState = SubTaskState.STS_Done;
        }

        public string GetFolderString()
        {
            int i = RelativeName.LastIndexOf("/");
            if (i != -1)
            {
                return RelativeName.Substring(0, i);
            }
            else
            {
                return "";
            }
        }
    }


    public class UpdateProcess
    {
        MainWindow ViewWindow;
        // ini file
        protected IniFile PatchConfig;

        protected Hashtable FileHashTable;

        private bool bMultThreadReadWrite = false;

        public bool bLastTaskFinished;
        public bool bTaskFinished;
        protected string CurrentSectionName;
        protected string CurrentServerVer;
        protected string CurrentServerVi;

        protected string ApplicationPath;
        protected string ServerRootPath;

        protected bool bForceUpdate;

        protected bool bDownloadThreadExit;
        protected bool bMD5ComputeThreadExit;
        protected bool bLocalDiskStreamThreadExit;
        protected bool bDecodeThreadExit;

        protected string Log;

        public string[] MessageList = new string[(int)MessageType.MT_Max];

        public int[] TaskState = new int[(int)MessageType.MT_Max];
        public int TotalTaskCount;
        public int ProcessedTaskCount;

        Thread DownloadThread;

        Thread LocalDiskThread;

        Thread MD5ComputeThread;

        Thread DecodeThread;

        public bool bDownloading;
        public bool bReadingDisk;
        public bool bWritingDisk;
        public bool bComputingMD5;
        public bool bUncompressing;

        protected int ThreadTimeOutTime = 1000;

        protected int TastStartTickCount;
        public double TaskTotalTime;
        public double TaskDownloadTime;
        public double TaskUncompressTime;
        public double TaskWriteDiskTime;
        public double TaskReadDiskTime;
        public double TaskComputeMD5Time;

        // version info
        public string QAGameServerVer;
        public string QAGameClientVer;

        public string QAEditorServerVer;
        public string QAEditorClientVer;

        public string DevGameServerVer;
        public string DevGameClientVer;

        public string DevEditorServerVer;
        public string DevEditorClientVer;

        public string FinalGameServerVer;
        public string FinalGameClientVer;

        public string CurrentGameLocalVer;
        public string CurrentEditorLocalVer;
        

        protected int ToProcessTaskCount;

        public UpdateProcess(MainWindow InView)
        {
            ViewWindow = InView;

            ApplicationPath = System.AppDomain.CurrentDomain.SetupInformation.ApplicationBase;

            // init ini file
            PatchConfig = new IniFile(ApplicationPath + "PatchConfigV2.ini");

            FileHashTable = new Hashtable();

            bForceUpdate = false;

            bLastTaskFinished = false;
            bTaskFinished = true;

            bDownloadThreadExit = false;
            bMD5ComputeThreadExit = false;
            bLocalDiskStreamThreadExit = false;
            bDecodeThreadExit = false;

            TastStartTickCount = 0;
            ToProcessTaskCount = 0;  

            bDownloading = false;
            bReadingDisk = false;
            bWritingDisk = false;
            bComputingMD5 = false;
            bUncompressing = false;
        }

        public void ClearAllData()
        {
            bTaskFinished = true;
            CurrentSectionName = "";
            CurrentServerVer = "";
            CurrentServerVi = "";

            ServerRootPath = "";

            bForceUpdate = true;
            Log = "";

            for (int i = 0; i < (int)MessageType.MT_Max; ++i)
            {
                MessageList[i] = "";
                TaskState[i] = 0;
            }

            TastStartTickCount = 0;

            ToProcessTaskCount = 0;

            TaskDownloadTime = 0;
            TaskComputeMD5Time = 0;
            TaskReadDiskTime = 0;
            TaskUncompressTime = 0;
            TaskWriteDiskTime = 0;

            foreach (DictionaryEntry i in FileHashTable)
            {
                FileNode fn = (FileNode)i.Value;
                fn.ServerContent = null;
                fn.UncompressedContext = null;
            }
            FileHashTable.Clear();
        }

        public void StopAllThread()
        {
            if (DownloadThread != null)
            {
                DownloadThread.Abort();
                DownloadThread.Join(ThreadTimeOutTime);
            }

            if (LocalDiskThread != null)
            {
                LocalDiskThread.Abort();
                LocalDiskThread.Join(ThreadTimeOutTime);

            }


            if (MD5ComputeThread != null)
            {
                MD5ComputeThread.Abort();
                MD5ComputeThread.Join(ThreadTimeOutTime);
            }


            if (DecodeThread != null)
            {
                DecodeThread.Abort();
                DecodeThread.Join(ThreadTimeOutTime);
            }

            foreach (DictionaryEntry i in FileHashTable)
            {
                FileNode fn = (FileNode)i.Value;
                if (fn.SubThread != null)
                {
                    fn.SubThread.Abort();
                    fn.SubThread.Join(ThreadTimeOutTime);
                }
            }

        }

        public void AddTaskCount(int InValue)
        {
            lock(this)
            {
                ToProcessTaskCount += InValue;
                WriteLog("AddedTaskCount = " + ToProcessTaskCount);
            }
        }

        public void AddMD5ComputeCostTime(int InDelta)
        {
            lock (this)
            {
                TaskComputeMD5Time += (double)(InDelta / 1000.0);
            }
        }

        public void AddWriteDiskCostTime(int InDelta)
        {
            lock (this)
            {
                TaskWriteDiskTime += (double)(InDelta / 1000.0);
            }
        }

        public void AddUncompressCostTime(int InDelta)
        {
            lock (this)
            {
                TaskUncompressTime += (double)(InDelta/1000.0);
            }
        }

        public bool CanAddTask()
        {
            return ToProcessTaskCount <= 10;
        }

        public void WriteLog(string InStr)
        {
            Console.WriteLine(InStr);
        }

        public void WriteLog(MessageType InType, string InStr)
        {
            int idx = (int)InType;
            MessageList[idx] += (InStr + "\r\n");
        }

        public bool IsAllTaskFinished()
        {
            if (bTaskFinished)
            {
                return true;
            }

            foreach (DictionaryEntry i in FileHashTable)
            {
                FileNode fn = (FileNode)i.Value;
                if (fn.StateType != FileStateType.FST_Finished)
                {
                    return false;
                }
            }

            return true;
        }

        // if there is no task, return true
        public bool AnalyseTask()
        {
            for (int i = 0; i < (int)MessageType.MT_Max; ++i)
            {
                TaskState[i] = 0;
            }

            TotalTaskCount = FileHashTable.Count;
            int tempProcessTaskCount = 0;


            foreach (DictionaryEntry i in FileHashTable)
            {
                FileNode fn = (FileNode)i.Value;
                if (fn.StateType == FileStateType.FST_Finished)
                {
                    tempProcessTaskCount++;
                }
                else if (fn.StateType == FileStateType.FST_WaitToComputeMD5)
                {
                    TaskState[(int)MessageType.MT_ComputeMD5] += 1;
                }
                else if (fn.StateType == FileStateType.FST_WaitToDecode)
                {
                    TaskState[(int)MessageType.MT_Uncompress] += 1;
                }
                else if (fn.StateType == FileStateType.FST_WaitToDownLoadFromServer)
                {
                    TaskState[(int)MessageType.MT_Download] += 1;
                }
                else if (fn.StateType == FileStateType.FST_WaitToLoadFromLocalDisk)
                {
                    TaskState[(int)MessageType.MT_ReadDisk] += 1;
                }
                else if (fn.StateType == FileStateType.FST_WaitToWriteToDisk)
                {
                    TaskState[(int)MessageType.MT_WriteDisk] += 1;
                }
            }

            if (TaskState[(int)MessageType.MT_ComputeMD5] > 0)
            {
                bComputingMD5 = true;
            }
            else
            {
                bComputingMD5 = false;
            }
               
            if (TaskState[(int)MessageType.MT_Uncompress] > 0)
            {
                bUncompressing = true;
            }
            else
            {
                bUncompressing = false;
            }

            if (TaskState[(int)MessageType.MT_Download] > 0)
            {
                bDownloading = true;
            }
            else
            {
                bDownloading = false;
            }

            if (TaskState[(int)MessageType.MT_ReadDisk] > 0)
            {
                bReadingDisk = true;
            }
            else
            {
                bReadingDisk = false;
            }

            if (TaskState[(int)MessageType.MT_WriteDisk] > 0)
            {
                bWritingDisk = true;
            }
            else
            {
                bWritingDisk = false;
            }

            ProcessedTaskCount = tempProcessTaskCount;

            if (ProcessedTaskCount == TotalTaskCount)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        public bool ProcessCheck()
        {
            Process[] CurrentProcess = Process.GetProcessesByName("mmogame.exe");
            if (CurrentProcess.Length > 0)
            {
                MessageBox.Show("请退出游戏//编辑器,再进行更新");
                return false;
            }

            return true;
        }

        public bool ServerCheck()
        {
            string url = PatchConfig.IniReadValue("Server", "Server1");
            HttpWebRequest myReq = (HttpWebRequest)WebRequest.Create(url);
            try
            {
                HttpWebResponse myRes = (HttpWebResponse)myReq.GetResponse();
            }

            catch (Exception e)
            {
                MessageBox.Show("无法连接上服务器:" + e.Message);
                return false;
            }

            return true;
        }

        public bool DownLoadFileFromServer(string url, string InLocalPath)
        {
            WebClient wc = new WebClient();
            try
            {
                wc.DownloadFile(url, InLocalPath);
            }
            catch (Exception e)
            {
                MessageBox.Show("DownLoad File error:" + e.Message);
                return false;
            }
            return true;
        }

        public string DownLoadStringFromServer(string url)
        {
            WebClient wc = new WebClient();
            try
            {
                return wc.DownloadString(url);
            }
            catch (System.Exception ex)
            {
                MessageBox.Show("从服务器下载版本号出错:" + ex.Message + " url=" + url);
                return "";
            }
        }

        public byte[] DownLoadByteFromServer(string url)
        {
            WebClient wc = new WebClient();
            try
            {
                return wc.DownloadData(url);
            }
            catch(Exception e)
            {                       
                MessageBox.Show("从服务器下载版本号出错:" + e.Message);
                return null;
            }
        }

        public bool ParseViString(string InValue, bool bServer)
        {
            int i1 = 0;
            int i2 = 0;
            while (true)
            {
                i2 = InValue.IndexOf(',', i1);
                if (i2 == -1)
                {
                    break;
                }
                string RelativeName = InValue.Substring(i1, i2 - i1);
                i1 = (++i2);

                RelativeName = RelativeName.Replace("\\", "/");


                i2 = InValue.IndexOf(',', i1);
                if (i2 == -1)
                {
                    break;
                }
                string FileTypeString = InValue.Substring(i1, i2 - i1);
                i1 = (++i2);


                i2 = InValue.IndexOf(',', i1);
                if (i2 == -1)
                {
                    break;
                }
                string MD5String = InValue.Substring(i1, i2 - i1);
                i1 = (++i2);

                i2 = InValue.IndexOf("\r\n", i1);
                if (i2 == -1)
                {
                    break;
                }
                string SizeString = InValue.Substring(i1, i2 - i1);
                i2 += 2;
                i1 = i2;

                if (FileTypeString == "Dir")
                {
                    continue;
                }


                if (bServer)
                {
                    FileNode fn = new FileNode(RelativeName, MD5String, SizeString);
                    if (FileHashTable.Contains(RelativeName))
                    {
                        MessageBox.Show("error 245");
                        return false;
                    }

                    FileHashTable.Add(RelativeName, fn);
                }
                else
                {
                    if (FileHashTable.Contains(RelativeName))
                    {
                        FileNode nd = (FileNode)FileHashTable[RelativeName];
                        nd.ClientMD5Value = MD5String;
                    }
                    else
                    {
                        FileNode fn = new FileNode(RelativeName);
                        FileHashTable.Add(RelativeName, fn);
                    }
                }
            }

            return true;
        }

        public bool LoadServerFileInfo()
        {

            ServerRootPath = PatchConfig.IniReadValue(CurrentSectionName, "Server1");

            // download server vi and ver file
            string VerFileName = PatchConfig.IniReadValue(CurrentSectionName, "VerFile");
            string ServerVer = DownLoadStringFromServer(ServerRootPath + VerFileName);
            if (ServerVer == "")
            {
                MessageBox.Show("服务器版本数据损坏,无法更新");
                return false;
            }
            CurrentServerVer = ServerVer;


            // read vi file
            string PatchFile = PatchConfig.IniReadValue(CurrentSectionName, "ViFile");
            string DownLoadedViFile = ApplicationPath + PatchFile + ".temp";
            string ViStrin = DownLoadStringFromServer(ServerRootPath + PatchFile);
            if (ViStrin.Length == 0)
            {
                return false;
            }

            CurrentServerVi = ViStrin;

            ParseViString(ViStrin, true);

            return true;
        }

        public void LoadClientFileInfo()
        {
            string PatchFileName = ApplicationPath + PatchConfig.IniReadValue(CurrentSectionName, "ViFile");
            if (File.Exists(PatchFileName) == false)
            {
                bForceUpdate = true;
            }

            string VerFileName = ApplicationPath + PatchConfig.IniReadValue(CurrentSectionName, "VerFile");
            if (File.Exists(VerFileName) == false)
            {
                bForceUpdate = true;
            }

            if (bForceUpdate == false)
            {
                string ClienViFileString = File.ReadAllText(PatchFileName);
                bool bOk = ParseViString(ClienViFileString, false);
            }
        }

        public void GenerateTaskData()
        {
            foreach (DictionaryEntry i in FileHashTable)
            {
                FileNode fn = (FileNode)(i.Value);
                if (fn.ServerMD5Value == "")
                {
                    fn.StateType = FileStateType.FST_WaitToDeleteLocalFile;
                }
                else
                {
                    if (fn.ClientMD5Value == "")
                    {
                        if (File.Exists(ApplicationPath + fn.RelativeName))
                        {
                            fn.StateType = FileStateType.FST_WaitToLoadFromLocalDisk;
                        }
                        else
                        {
                            fn.StateType = FileStateType.FST_WaitToDownLoadFromServer;
                        }
                    }
                    else
                    {
                        if (fn.ServerMD5Value == fn.ClientMD5Value)
                        {
                            fn.StateType = FileStateType.FST_Finished;
                        }
                        else
                        {
                            fn.StateType = FileStateType.FST_WaitToDownLoadFromServer;
                        }
                    }
                }
            }
        }

        public void UpdateLocalConfig()
        {
            string PatchFileName = ApplicationPath + PatchConfig.IniReadValue(CurrentSectionName, "ViFile");
            File.WriteAllText(PatchFileName, CurrentServerVi);

            string VerFileName = ApplicationPath + PatchConfig.IniReadValue(CurrentSectionName, "VerFile");
            File.WriteAllText(VerFileName, CurrentServerVer);

            if (CurrentSectionName == "Server" || CurrentSectionName =="QAGameServer")
            {
                CurrentGameLocalVer = CurrentServerVer;
            }
            else if (CurrentSectionName == "EditorServer" || CurrentSectionName == "QAEditorServer")
            {
                CurrentEditorLocalVer = CurrentServerVer;
            }
        }

        public void UpdateVersionInfo(string branchName)
        {
            string[] SectionList = new string[5];
            SectionList[0] = "Server" + branchName;
            SectionList[1] = "EditorServer" + branchName;
            SectionList[2] = "QAGameServer" + branchName;
            SectionList[3] = "QAEditorServer" + branchName;
            SectionList[4] = "ShippingGameServer" + branchName;

            string[] ServerVerList = new string[5];
            string[] ClientVerList = new string[5];

            for (int i = 0; i < 5; ++i)
            {
                string ServerPath = PatchConfig.IniReadValue(SectionList[i], "Server1");
                string VerFileName = PatchConfig.IniReadValue(SectionList[i], "VerFile");
                string ServerVer = DownLoadStringFromServer(ServerPath + VerFileName);
                if (ServerVer == "")
                {
                    ServerVerList[i] = "Unknown";
                }
                else
                {
                    ServerVerList[i] = ServerVer;
                }

                if (File.Exists(ApplicationPath + VerFileName))
                {
                    string ClientVer = File.ReadAllText(ApplicationPath + VerFileName);
                    ClientVerList[i] = ClientVer;
                }
                else
                {
                    ClientVerList[i] = "Unknown";
                }

                if (i == 0 || i == 2)
                {
                    CurrentGameLocalVer = ClientVerList[i];
                }
                else if (i == 1 || i == 3)
                {
                    CurrentEditorLocalVer = ClientVerList[i];
                }
            }

            DevGameServerVer = ServerVerList[0];
            DevGameClientVer = ClientVerList[0];

            DevEditorServerVer = ServerVerList[1];
            DevEditorClientVer = ClientVerList[1];

            QAGameServerVer = ServerVerList[2];
            QAGameClientVer = ClientVerList[2];

            QAEditorServerVer = ServerVerList[3];
            QAEditorClientVer = ClientVerList[3];

            FinalGameServerVer = ServerVerList[4];
            FinalGameClientVer = ClientVerList[4];
        }

        public void DeleteLocalFile()
        {
            foreach (DictionaryEntry i in FileHashTable)
            {
                if (bTaskFinished) return;

                FileNode fn = (FileNode)i.Value;
                if (fn.StateType == FileStateType.FST_WaitToDeleteLocalFile)
                {
                    File.Delete(ApplicationPath + fn.RelativeName);
                    fn.StateType = FileStateType.FST_Finished;
                }
            }
        }

        public void DownloadFromServerWorker()
        {
            while (true)
            {
                if (bTaskFinished) return;

                int DownloadFileCount = 0;     

                foreach (DictionaryEntry i in FileHashTable)
                {
                    if (bTaskFinished) return;

                    FileNode fn = (FileNode)i.Value;
                    if (fn.StateType == FileStateType.FST_WaitToDownLoadFromServer)
                    {
                        if (!CanAddTask())
                        {
                            Thread.Sleep(1);
                            break;
                        }
                        AddTaskCount(1);

                        int tempTime = Environment.TickCount;

                        ++DownloadFileCount;

                        string ToDownloadFileFullName = ServerRootPath + fn.RelativeName;
                        if (fn.ZipSize != 0)
                        {
                            ToDownloadFileFullName += ".zfp";
                        }
                            
                        WebClient wc = new WebClient();
                        try
                        {
                            if (fn.ZipSize == 0)
                            {
                                fn.UncompressedContext = wc.DownloadData(ToDownloadFileFullName);
                                fn.StateType = FileStateType.FST_WaitToWriteToDisk;
                            }
                            else
                            {
                                fn.ServerContent = wc.DownloadData(ToDownloadFileFullName);
                                fn.StateType = FileStateType.FST_WaitToDecode;
                            }
                            WriteLog(MessageType.MT_Download, "Downloaded file= " + fn.RelativeName);
                        }
                        catch (Exception e)
                        {
                            fn.StateType = FileStateType.FST_Finished;
                            WriteLog("download err file= " + ToDownloadFileFullName + " message= " + e.Message);
                            continue;
                        }

                        TaskDownloadTime += (double)((Environment.TickCount - tempTime) / 1000.0);
                    }
                }

                if (DownloadFileCount == 0)
                {
                    Thread.Sleep(1);
                }
            }
        }

        public void WriteDiskWorker(object key)
        {
            if (bTaskFinished)
            {
                return;
            }

            int tempTime = Environment.TickCount;

            FileNode fn = (FileNode)FileHashTable[key];

            string FolderPath = ApplicationPath + fn.GetFolderString();
            if (Directory.Exists(FolderPath) == false)
            {
                Directory.CreateDirectory(FolderPath);
            }

            File.WriteAllBytes(ApplicationPath + fn.RelativeName, fn.UncompressedContext);
            WriteLog(MessageType.MT_WriteDisk, "WriteFileToDisk : " + fn.RelativeName + " size= " + fn.UncompressedContext.Length);
            fn.StopTask();
            AddTaskCount(-1);
            fn.SubThread = null;
            AddWriteDiskCostTime(Environment.TickCount - tempTime);
            fn.SubState = SubTaskState.STS_Done;
            fn.StateType = FileStateType.FST_Finished;
            
        }

        public void LocalDiskStreamWorker()
        {
            while (true)
            {
                if (bTaskFinished) return;

                int ProcessedCount = 0;

                foreach (DictionaryEntry i in FileHashTable)
                {
                    if (bTaskFinished) return;

                    FileNode fn = (FileNode)i.Value;
                    if (fn.StateType == FileStateType.FST_WaitToWriteToDisk && fn.SubState == SubTaskState.STS_ToDo)
                    {
                        ++ProcessedCount;

                        if (bMultThreadReadWrite)
                        {
                            fn.SubState = SubTaskState.STS_Doing;
                            fn.SubThread = new Thread(WriteDiskWorker);
                            fn.SubThread.Start(fn.RelativeName);
                        }
                        else
                        {
                            int tempTime = Environment.TickCount;

                            string FolderPath = ApplicationPath + fn.GetFolderString();
                            if (Directory.Exists(FolderPath) == false)
                            {
                                Directory.CreateDirectory(FolderPath);
                            }

                            File.WriteAllBytes(ApplicationPath + fn.RelativeName, fn.UncompressedContext);
                            WriteLog(MessageType.MT_WriteDisk, "WriteFileToDisk : " + fn.RelativeName + " size= " + fn.UncompressedContext.Length);
                            fn.StopTask();
                            AddTaskCount(-1);

                            TaskWriteDiskTime += (double)((Environment.TickCount - tempTime) / 1000.0);
                        }
                    }
                }


                foreach (DictionaryEntry i in FileHashTable)
                {
                    if (bTaskFinished) return;

                    FileNode fn = (FileNode)i.Value;
                    if (fn.StateType == FileStateType.FST_WaitToLoadFromLocalDisk)
                    {
                        if (!CanAddTask())
                        {
                            Thread.Sleep(1);
                            break;
                        }

                        AddTaskCount(1);

                        int tempTime = Environment.TickCount;

                        ++ProcessedCount;
                        if (File.Exists(ApplicationPath + fn.RelativeName) == false)
                        {
                            MessageBox.Show("error 449 check!!!");
                            continue;
                        }

                        try
                        {
                            fn.UncompressedContext = File.ReadAllBytes(ApplicationPath + fn.RelativeName);
                        }
                        catch (Exception e)
                        {
                            TaskReadDiskTime += (double)((Environment.TickCount - tempTime)/1000.0);

                            fn.UncompressedContext = null;
                            Thread.Sleep(20);
                            break;
                        }

                        TaskReadDiskTime += (double)((Environment.TickCount - tempTime)/1000.0);

                        WriteLog(MessageType.MT_ReadDisk, "ReadFileFromDisk " + fn.RelativeName + " size = " + fn.UncompressedContext.Length);
                        fn.StateType = FileStateType.FST_WaitToComputeMD5;
                        break;
                    }
                }

                if (ProcessedCount == 0)
                {
                    Thread.Sleep(1);
                }
            }

        }

        public void SubMD5ComputerWorker(object InKey)
        {
            if (bTaskFinished)
            {
                return;
            }
            int tempTime = Environment.TickCount;
            FileNode fn = (FileNode)(FileHashTable[(object)InKey]);
            System.Security.Cryptography.MD5 md5 = new System.Security.Cryptography.MD5CryptoServiceProvider();
            byte[] ret = md5.ComputeHash(fn.UncompressedContext);
            StringBuilder sb = new StringBuilder();
            for (int j = 0; j < ret.Length; ++j)
            {
                sb.Append(ret[j].ToString("x2"));
            }

            fn.ClientMD5Value = sb.ToString();
            if (fn.ClientMD5Value == fn.ServerMD5Value)
            {
                fn.StopTask();
                AddTaskCount(-1);
                WriteLog(MessageType.MT_ComputeMD5, " Computed Hash : ServerMD5 == ClientMD5 " + fn.RelativeName + "  " + fn.ClientMD5Value);
            }
            else
            {
                fn.UncompressedContext = null;
                fn.StateType = FileStateType.FST_WaitToDownLoadFromServer;
                fn.SubState = SubTaskState.STS_ToDo;
                AddTaskCount(-1);
                WriteLog(MessageType.MT_ComputeMD5, "Hash Computed not the same. " + fn.RelativeName + " server=" + fn.ServerMD5Value + " Client=" + fn.ClientMD5Value);
            }

            fn.SubThread = null;
            AddMD5ComputeCostTime(Environment.TickCount - tempTime);
        }

        public void MD5ComputeWorker()
        {
            while (true)
            {
                if (bTaskFinished) return;

                int ProcessedCount = 0;
                foreach (DictionaryEntry i in FileHashTable)
                {
                    if (bTaskFinished) break;

                    FileNode fn = (FileNode)i.Value;
                    if (fn.StateType == FileStateType.FST_WaitToComputeMD5)
                    {
                        if (fn.SubState == SubTaskState.STS_ToDo)
                        {
                            ++ProcessedCount;

                            fn.SubState = SubTaskState.STS_Doing;
                            Thread MD5SubThread = new Thread(SubMD5ComputerWorker);
                            fn.SubThread = MD5SubThread;
                            MD5SubThread.Start(fn.RelativeName);
                        }
                    }
                }

                if (ProcessedCount == 0)
                {
                    Thread.Sleep(1);
                }
            }

        }

        public void UncompressWorker(object InKey)
        {
            int tempTime = Environment.TickCount;

            FileNode fn = (FileNode)FileHashTable[(string)InKey];

            uint size = (uint)fn.ZipSize;
            try
            {
                fn.UncompressedContext = new Byte[fn.ZipSize];
            }
            catch (Exception e)
            {
                fn.SubState = SubTaskState.STS_ToDo;
                fn.SubThread = null;
                return;
            }

            try
            {
                int ret = ZipFile.uncompress(fn.UncompressedContext, ref size, fn.ServerContent, fn.ServerContent.Length);
                if (ret == 0)
                {
                    WriteLog(MessageType.MT_Uncompress, "uncompressed OK " + fn.RelativeName + " size=" + size);
                }
                else
                {
                    WriteLog(MessageType.MT_Uncompress, "uncompressed error " + fn.RelativeName + " error=" + ret);
                }

            }
            catch (Exception e)
            {
                MessageBox.Show("Uncompressed error" + fn.RelativeName +"  " + e.Message);
            }


            fn.SubThread = null;
            fn.StateType = FileStateType.FST_WaitToWriteToDisk;
            fn.SubState = SubTaskState.STS_ToDo;

            AddUncompressCostTime(Environment.TickCount - tempTime);
        }

        public void DecodeWorker()
        {
            while (true)
            {
                if (bTaskFinished) return;

                int ProcessedCount = 0;
                foreach (DictionaryEntry i in FileHashTable)
                {
                    if (bTaskFinished) return;

                    FileNode fn = (FileNode)i.Value;
                    if (fn.StateType == FileStateType.FST_WaitToDecode)
                    {
                        ++ProcessedCount;

                        if (fn.SubState == SubTaskState.STS_ToDo)
                        {
                            fn.SubState = SubTaskState.STS_Doing;
                            Thread UncompressThread = new Thread(UncompressWorker);
                            fn.SubThread = UncompressThread;
                            UncompressThread.Start(fn.RelativeName);
                        }
                    }
                }

                if (ProcessedCount == 0)
                {
                    Thread.Sleep(1);
                }
            }
        }

        public string UpdateThread()
        {
            bool bOK = LoadServerFileInfo();

            if (!bOK)
            {
                bTaskFinished = true;
                return "error";
            }

            LoadClientFileInfo();

            GenerateTaskData();

            AnalyseTask();

            DeleteLocalFile();

            // setup sub thread
            DownloadThread = new Thread(DownloadFromServerWorker);
            DownloadThread.Start();

            LocalDiskThread = new Thread(LocalDiskStreamWorker);
            LocalDiskThread.Start();

            MD5ComputeThread = new Thread(MD5ComputeWorker);
            MD5ComputeThread.Start();

            DecodeThread = new Thread(DecodeWorker);
            DecodeThread.Start();

            while (!AnalyseTask())
            {
                Thread.Sleep(1);
            }

            bLastTaskFinished = true;
            bTaskFinished = true;

            UpdateLocalConfig();

            FileHashTable.Clear();

            return "OK";
        }

        public delegate string AnsycDelegate();

        public void TaskAllFinished(IAsyncResult ias)
        {
            AnsycDelegate ad = (AnsycDelegate)ias.AsyncState;
            ad.EndInvoke(ias);
            int LastTime = Environment.TickCount - TastStartTickCount;
            TaskTotalTime = (double)(LastTime / 1000.0);

            UpdateVersionInfo(MainWindow.getBranchName());
           // ViewWindow.UpdateVersionText();
            //MessageBox.Show("Task Finished. UseTime=" + (double)(LastTime / 1000.0) + " DownloadUseTime="+(float)(DownloadUseTime / 1000.0) + " ReadFromDiskTime="+ (double)(ReadFromDiskUseTime/1000.0) + " WriteToDisktime="+(double)(WriteToDiskUseTime/1000.0)+"  ComputeMD5Time="+(float)(ComputeMD5UseTime/1000.0)+"  DecodeTime="+(float)(DecodeUseTime/1000.0));
        }

        public void Update(string InSection, bool bForce)
        {
            if (!bTaskFinished)
            {
                MessageBox.Show("更新任务正在进行中");
                return;
            }

            ClearAllData();

            TastStartTickCount = Environment.TickCount;


            bTaskFinished = false;
            CurrentSectionName = InSection;
            bForceUpdate = bForce;

            AnsycDelegate TaskDelegate = new AnsycDelegate(UpdateThread);
            AsyncCallback Callback = new AsyncCallback(TaskAllFinished);
            TaskDelegate.BeginInvoke(Callback, TaskDelegate);
        }




    }
}

