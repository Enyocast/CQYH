/**
 * Copyright 1998-2013 Epic Games, Inc. All Rights Reserved.
 */
using System;
using System.Net;
using System.IO;
using System.IO.Compression;

namespace AutoReporter
{
    class UploadReportFiles
    {

        string StripPath(string PathName)
        {
            int LastBackSlashIndex = PathName.LastIndexOf("\\");
            int LastForwardSlashIndex = PathName.LastIndexOf("/");

            if (LastBackSlashIndex > LastForwardSlashIndex && LastBackSlashIndex >= 0)
            {
                return PathName.Substring(LastBackSlashIndex + 1);
            }
            else if (LastForwardSlashIndex >= 0)
            {
                return PathName.Substring(LastForwardSlashIndex + 1);
            }
            return PathName;
        }

        #region 废弃方法
        /** 
         * UploadFiles - uploads the two files using HTTP POST
         * 
         * @param LogFilename - the local log file
         * @param IniFilename - the local ini file
         * @param uniqueID - the id of the crash report associated with these files. 
         * @return bool - true if successful
         */
        [Obsolete("过期")]
        public bool UploadFiles(string LogFilename, string IniFilename, string MiniDumpFilename, int uniqueID, OutputLogFile logFile)
        {
            logFile.WriteLine("Uploading files " + LogFilename + ", " + IniFilename + " and " + MiniDumpFilename);
			Boolean bWasSuccessful = true;
            try 
            {
                WebClient client = new WebClient();

                //If debugging use local server
#if DEBUG
                string UploadReportURL = Properties.Settings.Default.UploadURL_Debug;
#else
				string UploadReportURL = Properties.Settings.Default.UploadURL;
#endif

                client.Headers.Add("NewFolderName", uniqueID.ToString());

                //copy the log before trying to upload it, since the engine may still have it open for writing
                //in which case a direct upload would fail
                string TempLogFilename = LogFilename + "_AutoReportTemp.log";
            	
                try
                {
                    File.Copy(LogFilename, TempLogFilename, true);
                }
                catch (Exception e)
                {
                    logFile.WriteLine(e.Message);
                    logFile.WriteLine("Couldn't copy log to " + TempLogFilename + ", continuing...");
                }

                client.Headers.Add("LogName", StripPath(TempLogFilename));

                byte[] responseArray;

                try
                {
                    
                    responseArray = client.UploadFile(UploadReportURL, "POST", TempLogFilename);
                }
                catch (WebException webEx)
                {
                    logFile.WriteLine(webEx.Message);
                    logFile.WriteLine(webEx.InnerException.Message);
                    logFile.WriteLine("Couldn't upload log, continuing...");

                    HttpWebResponse res = (HttpWebResponse)webEx.Response;
                    StreamReader sr = new StreamReader(res.GetResponseStream());
                    logFile.WriteLine(sr.ReadToEnd());
                }

                try
                {
                    File.Delete(TempLogFilename);
                }
                catch (Exception)
                {
                }

				client.Headers.Remove( "SaveFileName" );
				client.Headers.Add( "SaveFileName", "UE3AutoReportIniDump.txt" );

				try
                {
                    responseArray = client.UploadFile(UploadReportURL, "POST", IniFilename);
                }
                catch (WebException webEx)
                {
                    logFile.WriteLine(webEx.Message);
                    logFile.WriteLine(webEx.InnerException.Message);
                    logFile.WriteLine("Couldn't upload ini, continuing...");
                	bWasSuccessful = false;
                }

				client.Headers.Remove( "SaveFileName" );
                client.Headers.Add("SaveFileName", "MiniDump.dmp");

                try
                {
                    responseArray = client.UploadFile(UploadReportURL, "POST", MiniDumpFilename);
                }
                catch (WebException webEx)
                {
                    logFile.WriteLine(webEx.Message);
                    logFile.WriteLine(webEx.InnerException.Message);
                    logFile.WriteLine("Couldn't upload mini dump, continuing...");
                	bWasSuccessful = false;
                }

            } catch (WebException webEx) {
                logFile.WriteLine(webEx.Message);
                logFile.WriteLine(webEx.InnerException.Message);
				bWasSuccessful = false;
            }

			return bWasSuccessful;
        }
        #endregion 

        /** 
         * UploadFiles - uploads the two files using HTTP POST throw arg ServerIp ServerPort
         * 
         * @param LogFilename - the local log file
         * @param IniFilename - the local ini file
         * @param uniqueID - the id of the crash report associated with these files. 
         * @return bool - true if successful
         */
        public bool UploadFiles(string LogFilename, string IniFilename, string MiniDumpFilename, int uniqueID, string serverIp, int serverPort, OutputLogFile logFile)
        {
            logFile.WriteLine("Uploading files " + LogFilename + ", " + IniFilename + " and " + MiniDumpFilename);
            Boolean bWasSuccessful = true;
            try
            {
                WebClient client = new WebClient();

                //If debugging use local server
#if DEBUG
                string UploadReportURL = Properties.Settings.Default.UploadURL_Debug;
#else
				string UploadReportURL = Properties.Settings.Default.UploadURL;
#endif

                // 根据返回的服务器地址上传
                Uri uri = new Uri(UploadReportURL);
                if (uri.Port == 80)
                    UploadReportURL = UploadReportURL.Replace(uri.Host, serverIp + ":" + serverPort);
                else
                    UploadReportURL = UploadReportURL.Replace(uri.Host, serverIp).Replace(uri.Port.ToString(), serverPort.ToString());

                client.Headers.Add("NewFolderName", uniqueID.ToString());
                client.Headers.Add("CrashDate", DateTime.Now.ToString("yyyy-MM-dd"));

                //copy the log before trying to upload it, since the engine may still have it open for writing
                //in which case a direct upload would fail
                string TempLogFilename = LogFilename + "_AutoReportTemp.log";

                try
                {
                    File.Copy(LogFilename, TempLogFilename, true);
                }
                catch (Exception e)
                {
                    logFile.WriteLine(e.Message);
                    logFile.WriteLine("Couldn't copy log to " + TempLogFilename + ", continuing...");
                }

                //client.Headers.Add("LogName", StripPath(TempLogFilename));
                client.Headers.Add("LogName", "Launch.log");

                byte[] responseArray;
                string zipFilePath = "";

                try
                {
                    // 添加压缩文件
                    zipFilePath = CreateZipFile(TempLogFilename, uniqueID + "_Launch.log");
                    //responseArray = client.UploadFile(UploadReportURL, "POST", TempLogFilename);
                    responseArray = client.UploadFile(UploadReportURL, "POST", zipFilePath);
                }
                catch (WebException webEx)
                {
                    logFile.WriteLine(webEx.Message);
                    logFile.WriteLine(webEx.InnerException.Message);
                    logFile.WriteLine("Couldn't upload log, continuing...");

                    HttpWebResponse res = (HttpWebResponse)webEx.Response;
                    StreamReader sr = new StreamReader(res.GetResponseStream());
                    logFile.WriteLine(sr.ReadToEnd());
                }
                catch (IOException ioEx)
                {
                    logFile.WriteLine(ioEx.Message);
                    logFile.WriteLine(ioEx.InnerException.Message);
                    logFile.WriteLine("Couldn't zip log, continuing...");
                }

                try
                {
                    File.Delete(TempLogFilename);
                    File.Delete(zipFilePath);
                }
                catch (Exception)
                {
                }

                client.Headers.Remove("SaveFileName");
                client.Headers.Add("SaveFileName", "UE3AutoReportIniDump.txt");

                try
                {
                    // 添加压缩文件
                    zipFilePath = CreateZipFile(IniFilename, uniqueID + "_UE3AutoReportIniDump.txt");
                    //responseArray = client.UploadFile(UploadReportURL, "POST", IniFilename);
                    responseArray = client.UploadFile(UploadReportURL, "POST", zipFilePath);
                }
                catch (WebException webEx)
                {
                    logFile.WriteLine(webEx.Message);
                    logFile.WriteLine(webEx.InnerException.Message);
                    logFile.WriteLine("Couldn't upload ini, continuing...");
                    bWasSuccessful = false;
                }
                catch (IOException ioEx)
                {
                    logFile.WriteLine(ioEx.Message);
                    logFile.WriteLine(ioEx.InnerException.Message);
                    logFile.WriteLine("Couldn't zip ini, continuing...");
                }

                try
                {
                    File.Delete(zipFilePath);
                }
                catch (Exception)
                {
                }

                client.Headers.Remove("SaveFileName");
                client.Headers.Add("SaveFileName", "MiniDump.dmp");

                try
                {
                    // 添加压缩文件
                    zipFilePath = CreateZipFile(MiniDumpFilename, uniqueID + "_MiniDump.dmp");
                    //responseArray = client.UploadFile(UploadReportURL, "POST", MiniDumpFilename);
                    responseArray = client.UploadFile(UploadReportURL, "POST", zipFilePath);
                }
                catch (WebException webEx)
                {
                    logFile.WriteLine(webEx.Message);
                    logFile.WriteLine(webEx.InnerException.Message);
                    logFile.WriteLine("Couldn't upload mini dump, continuing...");
                    bWasSuccessful = false;
                }
                catch (IOException ioEx)
                {
                    logFile.WriteLine(ioEx.Message);
                    logFile.WriteLine(ioEx.InnerException.Message);
                    logFile.WriteLine("Couldn't zip mini dump, continuing...");
                }

                try
                {
                    File.Delete(zipFilePath);
                }
                catch (Exception)
                {
                }

            }
            catch (WebException webEx)
            {
                logFile.WriteLine(webEx.Message);
                logFile.WriteLine(webEx.InnerException.Message);
                bWasSuccessful = false;
            }

            return bWasSuccessful;
        }

        private string CreateZipFile(string sourceFilePath, string zipFileName)
        {
            string zipFilePath = sourceFilePath.Substring(0, sourceFilePath.LastIndexOf(".")) + ".zip";
            File.Delete(zipFilePath);

            if (zipFileName.Equals(string.Empty))
                zipFileName = Path.GetFileName(sourceFilePath);

            using (ZipArchive zip = ZipFile.Open(zipFilePath, ZipArchiveMode.Create))
            {
                zip.CreateEntryFromFile(sourceFilePath, zipFileName);
            }
            return zipFilePath;
        }
    }
}
