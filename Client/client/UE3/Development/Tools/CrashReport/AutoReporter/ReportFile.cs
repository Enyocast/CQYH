/**
 * Copyright 1998-2013 Epic Games, Inc. All Rights Reserved.
 */
using System;
using System.IO;
using System.Text;
using System.Collections.Generic;


namespace AutoReporter
{

    /**
     * ReportFileData - a container representing the data that a crash dump contains and must be sent to the ReportService
     */
    class ReportFileData
    {
        public int Version;
        public string ComputerName;
        public string UserName;
        public string GameName;
        public string PlatformName;
        public string LanguageExt;
        public string TimeOfCrash;
        public string BuildVer;
        public string ChangelistVer;
        public string CommandLine;
        public string BaseDir;
        public string CallStack;
        public string EngineMode;

        /**
         * IsValid - checks if this is valid to be sent to ReportService
         * 
         * @return bool - true if successful
         */
        public bool IsValid(OutputLogFile logFile) 
        {
            if (Version != 0 && !ComputerName.Equals("") && !UserName.Equals("") && !GameName.Equals("") 
                && !LanguageExt.Equals("") && !TimeOfCrash.Equals("") && !BuildVer.Equals("") && !ChangelistVer.Equals("") 
                && !BaseDir.Equals("") && !CallStack.Equals("") && !EngineMode.Equals(""))
            {
                return true;
            }

            logFile.WriteLine("Errors detected reading report dump!");
            return false;
        }
    }

    class ReportFile
    {
        private int lastIndex;

        private static string currentDumpVersion = "3";

        private string GetNextString(string inputString, OutputLogFile logFile)
        {
            if (lastIndex == 0)
            {
                lastIndex = inputString.IndexOf("\0", 0);
            }

            string returnString = "";
            try
            {
                int nextIndex = inputString.IndexOf("\0", lastIndex + 1);
                returnString = inputString.Substring(lastIndex + 1, nextIndex - lastIndex - 1);
                lastIndex = nextIndex;
                logFile.WriteLine(returnString);
            }
            catch (Exception e)
            {
                logFile.WriteLine(e.Message);
                return "";
            }

            return returnString;
        }

        /**
         * ParseReportFile - extracts a ReportFileData from a crash dump file
         * 
         * @param filename - the crash dump
         * @param reportData - the container to fill
         * 
         * @return bool - true if successful
         */
        public bool ParseReportFile(string filename, ReportFileData reportData, OutputLogFile logFile)
        {
            logFile.WriteLine("");
            logFile.WriteLine("Parsing report dump " + filename);
            logFile.WriteLine("\n\n");
            string readText = "";
            try
            {
                //readText = File.ReadAllText(filename, Encoding.Unicode);
                // fangruyi
                if (Program.bNeedDecode)
                {
                    byte[] Ret = File.ReadAllBytes(filename);

                    byte[] dc = new byte[256]{190, 100, 47, 46, 144, 165, 231, 250, 218, 133, 73, 82, 102, 181, 80, 98, 119, 127, 49, 115, 187, 79, 71, 198, 
                        54, 174, 27, 222, 136, 184, 180, 86, 50, 76, 116, 81, 51, 120, 240, 253, 91, 185, 96, 199, 202, 238, 123, 6, 228, 12, 206, 7, 141, 221, 167, 64, 251, 178, 210, 78, 0, 11, 122, 4, 92, 57, 41, 170, 126, 209, 255, 242, 30, 163, 42, 31, 219, 16, 14, 67, 52, 168, 196, 159, 216, 35, 23, 254, 137, 75, 69, 33, 138, 56, 220, 8, 53, 233, 205, 72,
                        118, 60, 230, 192, 77, 145, 99, 83, 237, 195, 84, 18, 20, 197, 45, 107, 87, 65, 48, 155, 103, 160, 129, 213, 147, 93, 252, 182, 5, 97, 109, 215, 225,
                        169, 2, 63, 189, 29, 85, 90, 246, 36, 117, 173, 113, 3, 188, 194, 214, 217, 150, 175, 149, 148, 153, 74, 143, 37, 130, 164, 95, 245, 140, 66, 121, 131, 
                        38, 179, 139, 244, 226, 171, 154, 229, 61, 135, 224, 17, 25, 166, 223, 21, 207, 204, 177, 13, 128, 212, 26, 172, 201, 132, 24, 88, 34, 243, 151, 211,
                        59, 134, 105, 114, 89, 32, 94, 152, 40, 125, 249, 203, 106, 247, 22, 111, 232, 9, 70, 58, 112, 55, 104, 157, 234, 191, 110, 19, 236, 193, 10, 28, 208,
                        186, 101, 176, 241, 146, 44, 1, 142, 162, 200, 156, 15, 108, 43, 68, 239, 183, 248, 39, 124, 235, 161, 158, 227, 62};

                    for (int i = 0; i < Ret.Length; i++)
                    {
                        Ret[i] = dc[Ret[i]];
                    }

                    readText = Encoding.Unicode.GetString(Ret);

                    logFile.WriteLine(readText);

                }
                else
                {
                    readText = File.ReadAllText(filename, Encoding.Unicode);
                }
            }
            catch (Exception e)
            {
                logFile.WriteLine(e.Message);
                logFile.WriteLine("Failed to read report dump!");
                return false;
            }

            int firstIndex = readText.IndexOf("\0");
            string VersionStr = readText.Substring(0, firstIndex);
            logFile.WriteLine("Version = " + VersionStr);

            if (VersionStr.Equals(currentDumpVersion))
            {
                logFile.WriteLine("Dump is current version: " + currentDumpVersion);
                reportData.Version = Int32.Parse(VersionStr);
                reportData.ComputerName = GetNextString(readText, logFile);
                reportData.UserName = GetNextString(readText, logFile);
                reportData.GameName = GetNextString(readText, logFile);
                reportData.PlatformName = GetNextString(readText, logFile);
                reportData.LanguageExt = GetNextString(readText, logFile);
                reportData.TimeOfCrash = GetNextString(readText, logFile);
                reportData.BuildVer = GetNextString(readText, logFile);
                reportData.ChangelistVer = GetNextString(readText, logFile);
                reportData.CommandLine = GetNextString(readText, logFile);
                reportData.BaseDir = GetNextString(readText, logFile);
                reportData.CallStack = GetNextString(readText, logFile);
                reportData.EngineMode = GetNextString(readText, logFile);
            }
            else if (VersionStr.Equals("2"))
            {
                logFile.WriteLine("Dump is old but supported. DumpVer=" + VersionStr + " CurVer=" + currentDumpVersion);
                reportData.Version = Int32.Parse(VersionStr);
                reportData.ComputerName = GetNextString(readText, logFile);
                reportData.UserName = GetNextString(readText, logFile);
                reportData.GameName = GetNextString(readText, logFile);
                reportData.LanguageExt = GetNextString(readText, logFile);
                reportData.TimeOfCrash = GetNextString(readText, logFile);
                reportData.BuildVer = GetNextString(readText, logFile);
                reportData.ChangelistVer = GetNextString(readText, logFile);
                reportData.CommandLine = GetNextString(readText, logFile);
                reportData.BaseDir = GetNextString(readText, logFile);
                reportData.CallStack = GetNextString(readText, logFile);
                reportData.EngineMode = GetNextString(readText, logFile);
            }
            else
            {
                logFile.WriteLine("Outdated dump version " + VersionStr + "! Current Version is " + currentDumpVersion);
                return false;
            }

            logFile.WriteLine("\n\n");

            return reportData.IsValid(logFile);
        }
    }
}
