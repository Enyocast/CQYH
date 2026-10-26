using System;
using System.Collections.Generic;
using System.Configuration;
using System.IO;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Windows.Forms;
using CrashReport.Models;
using System.IO.Compression;

namespace AutoReportWebService
{
	public partial class UploadReportFiles : System.Web.UI.Page
	{
		/**
		 * Uploads files and places them in the folder specified by the NewFolderName key
		 * in the HTTP header.
		 */
		protected void Page_Load(object sender, EventArgs e)
		{
			string ErrorLogFileName = ConfigurationManager.AppSettings["LogFileName"];
			int newID = -1;

			StreamWriter errorLogFile = null;
			try
			{
				errorLogFile = new StreamWriter(ErrorLogFileName, true);
			}
			catch (Exception exx)
			{
				// Ignore cases where the log file can't be opened (another instance may be writing to it already)
			}

			string NewFolderName = "";
			string SaveFileName = "";
			string VideoFileKeyword = "CrashVideo";
			//string LogFileName = "Launch.log";
            string CrashDate = DateTime.Now.ToString("yyyy-MM-dd");

			foreach (string headerString in Request.Headers.AllKeys)
			{
				if (headerString.Equals("NewFolderName"))
				{
					NewFolderName = Request.Headers[headerString];
				}
				else if (headerString.Equals("SaveFileName"))
				{
					SaveFileName = Request.Headers[headerString];
				}
				else if (headerString.Equals("LogName"))
				{
					//get the log filename from the header
                    //LogFileName = Request.Headers[headerString];
                    SaveFileName = Request.Headers[headerString];
                }
                else if (headerString.Equals("CrashDate"))
                {
                    CrashDate = Request.Headers[headerString];
                }
			}

			if (NewFolderName.Length > 0)
			{
				string SaveFilesPath = ConfigurationManager.AppSettings["SaveFilesPath"];
                // 根据CrashDate生成日期文件夹
                string DatePath = Path.Combine(SaveFilesPath, DateTime.Now.ToString("yyyyMMdd"));
                if (!Directory.Exists(DatePath))
                    Directory.CreateDirectory(DatePath);
                string NewPath = DatePath + "\\" + NewFolderName;

				foreach (string fileString in Request.Files.AllKeys)
				{
					HttpPostedFile file = Request.Files[fileString];
					if (SaveFileName.Length == 0)
					{
						SaveFileName = file.FileName;
					}
					//if this is the log file, rename it so that it can be identified by the web site
                    //if (file.FileName.Contains(LogFileName))
                    //{
                    //    SaveFileName = "Launch.log";
                    //}

					// If this is the Video file, set the save path to the video save path.
					if (file.FileName.Contains(VideoFileKeyword))
					{
						SaveFilesPath = ConfigurationManager.AppSettings["VideoFilesPath"];
                        NewPath = SaveFilesPath + DatePath + "\\" + NewFolderName;
					}

					try
					{
                        string file_dst = NewPath + "_" + SaveFileName;
                        string zipfile_dst = file_dst + ".zip";
                        errorLogFile.WriteLine("Accept File: " + zipfile_dst);
                        FileInfo fi = new FileInfo(zipfile_dst);
                        DirectoryInfo di = fi.Directory;
                        if (!di.Exists)
                            di.Create();
                        file.SaveAs(zipfile_dst);

                        // 解压文件
                        ExtractFile(zipfile_dst, string.Empty);
                        File.Delete(zipfile_dst);

                        errorLogFile.Flush();

                        // 保存文件路径
                        CrashReportDataContext mCrashDataContext = new CrashReportDataContext();
                        Crash CrashToUpdate = mCrashDataContext.Crashes.Where(c => c.Id == Convert.ToInt32(NewFolderName)).First();

                        if (SaveFileName.EndsWith(".log"))
                            CrashToUpdate.LogFile = file_dst;
                        else if (SaveFileName.EndsWith(".txt"))
                            CrashToUpdate.TxtFile = file_dst;
                        else if (SaveFileName.EndsWith(".dmp"))
                            CrashToUpdate.DmpFile = file_dst;

                        mCrashDataContext.SubmitChanges();
					}
					catch (IOException IOException)
					{
						//TODO Do something here
						if (errorLogFile != null)
						{
							errorLogFile.WriteLine("Could not Save Log File:");
							errorLogFile.WriteLine(IOException.Message);
                            errorLogFile.Flush();
						}
					}
				}
			}
            errorLogFile.Close();
		}

        private bool ExtractFile(string sourceFile, string targetPath)
        {
            if (targetPath.Equals(string.Empty))
                targetPath = Path.GetDirectoryName(sourceFile);

            if (!Directory.Exists(targetPath)) Directory.CreateDirectory(targetPath);
            try
            {
                ZipFile.ExtractToDirectory(sourceFile, targetPath);
                return true;
            }
            catch (Exception ex)
            {
                throw ex;                
            }
        }
	}

}