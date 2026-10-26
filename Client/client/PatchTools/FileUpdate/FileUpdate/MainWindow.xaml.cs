using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Net;
using System.Diagnostics;
using System.Windows.Threading;
using System.Threading;

namespace FileUpdate
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        UpdateProcess FileUpdateProcess;

        DispatcherTimer timer;

        string PointString;
        int LastTickCount;

        bool bWaitFirstTick;

        Color IdleColor = Color.FromRgb(255, 255, 255);
        Color BusyColor = Color.FromRgb(255, 192, 0);


        public MainWindow()
        {
            InitializeComponent();

            LastTickCount = Environment.TickCount;

            PointString = "";

            bWaitFirstTick = true;

            // check the current process
            Process currentPro = Process.GetCurrentProcess();
            Process[] CurrentProcess = Process.GetProcessesByName("FileUpdate");
            if (CurrentProcess.Length > 0 && CurrentProcess[0].Id != currentPro.Id)
            {
                MessageBoxResult mbr = MessageBox.Show("更新程序已运行");
                Process.GetCurrentProcess().Kill();
                return;
            }

            FileUpdateProcess = new UpdateProcess(this);

            this.Title += " - 当前分支:" + getBranchName();
        }

        private void TestDownloadFile(string url, string Des)
        {
            try
            {
                System.Net.WebClient wc = new System.Net.WebClient();
                wc.DownloadFile(url, Des);
            }
            catch (Exception e)
            {
                MessageBox.Show(e.ToString());
            }

        }

        public void UpdateTimeText()
        {
            TimeText1.Content = "Download=" + FileUpdateProcess.TaskDownloadTime + " ReadDisk=" + FileUpdateProcess.TaskReadDiskTime + " WriteDisk=" + FileUpdateProcess.TaskWriteDiskTime;
            TimeText2.Content = "ComputeMD5=" + FileUpdateProcess.TaskComputeMD5Time + " Uncompress=" + FileUpdateProcess.TaskUncompressTime;
        }

        public void UpdateVersionText()
        {
            QAGameLabel.Content = FileUpdateProcess.QAGameServerVer;
            //if (FileUpdateProcess.QAGameServerVer != FileUpdateProcess.QAGameClientVer)
            //{
            //    QAGameLabel.Foreground = new SolidColorBrush(Color.FromRgb(255, 0, 0));
            //}
            //else
            //{
            //    QAGameLabel.Foreground = new SolidColorBrush(Color.FromRgb(0, 198, 0));
            //}

            QAEditorLabel.Content = FileUpdateProcess.QAEditorServerVer;
            //if (FileUpdateProcess.QAEditorClientVer != FileUpdateProcess.QAEditorServerVer)
            //{
            //    QAEditorLabel.Foreground = new SolidColorBrush(Color.FromRgb(255, 0, 0));
            //}
            //else
            //{
            //    QAEditorLabel.Foreground = new SolidColorBrush(Color.FromRgb(0, 198, 0));
            //}

            DevGameLabel.Content = FileUpdateProcess.DevGameServerVer;
            //if (FileUpdateProcess.DevGameClientVer != FileUpdateProcess.DevGameServerVer)
            //{
            //    DevGameLabel.Foreground = new SolidColorBrush(Color.FromRgb(255, 0, 0));
            //}
            //else
            //{
            //    DevGameLabel.Foreground = new SolidColorBrush(Color.FromRgb(0, 198, 0));
            //}

            DevEditorLabel.Content = FileUpdateProcess.DevEditorServerVer;
            //if (FileUpdateProcess.DevEditorClientVer != FileUpdateProcess.DevEditorServerVer)
            //{
            //    DevEditorLabel.Foreground = new SolidColorBrush(Color.FromRgb(255, 0, 0));
            //}
            //else
            //{
            //    DevEditorLabel.Foreground = new SolidColorBrush(Color.FromRgb(0, 198, 0));
            //}

            FinalGameUpdateLabel.Content = FileUpdateProcess.FinalGameServerVer;
            //if (FileUpdateProcess.FinalGameClientVer != FileUpdateProcess.FinalGameServerVer)
            //{
            //    FinalGameUpdateLabel.Foreground = new SolidColorBrush(Color.FromRgb(255, 0, 0));
            //}
            //else
            //{
            //    FinalGameUpdateLabel.Foreground = new SolidColorBrush(Color.FromRgb(0, 198, 0));
            //}

            GameVerLabel.Content = FileUpdateProcess.CurrentGameLocalVer;
            EditorVerLabel.Content = FileUpdateProcess.CurrentEditorLocalVer;
            labelFinalGame.Content = FileUpdateProcess.FinalGameClientVer;
        }

        public void TimerTick(object sender, EventArgs e)
        {
            if (bWaitFirstTick)
            {
                bWaitFirstTick = false;
                FileUpdateProcess.UpdateVersionInfo(getBranchName());
                UpdateVersionText();
            }


            int NewTickCount = Environment.TickCount - LastTickCount;
            if (NewTickCount > 1000)
            {
                LastTickCount = NewTickCount;

                if (PointString.Length <= 4)
                {
                    PointString += ".";
                }
                else
                {
                    PointString = ".";
                }

                UpdateVersionText();
            }

            

            // update task text
            if (FileUpdateProcess.bTaskFinished == false)
            {
                if (DownloadText.Text != FileUpdateProcess.MessageList[(int)MessageType.MT_Download])
                {
                    DownloadText.Text = FileUpdateProcess.MessageList[(int)MessageType.MT_Download];
                    scrollViewer1.ScrollToBottom();
                }

                if (FileUpdateProcess.bDownloading)
                {
                    tabItemDownload.Background = new SolidColorBrush(BusyColor);
                }
                else
                {
                    tabItemDownload.Background = new SolidColorBrush(IdleColor);
                }



                if (ComputeMD5Text.Text != FileUpdateProcess.MessageList[(int)MessageType.MT_ComputeMD5])
                {
                    ComputeMD5Text.Text = FileUpdateProcess.MessageList[(int)MessageType.MT_ComputeMD5];
                    scrollViewer2.ScrollToBottom();
                }

                if (FileUpdateProcess.bComputingMD5)
                {
                    tabItemMD5.Background = new SolidColorBrush(BusyColor);
                }
                else
                {
                    tabItemMD5.Background = new SolidColorBrush(IdleColor);
                }


                if (ReadDiskText.Text != FileUpdateProcess.MessageList[(int)MessageType.MT_ReadDisk])
                {
                    ReadDiskText.Text = FileUpdateProcess.MessageList[(int)MessageType.MT_ReadDisk];
                    scrollViewer4.ScrollToBottom();
                }

                if (FileUpdateProcess.bReadingDisk)
                {
                    tabItemRead.Background = new SolidColorBrush(BusyColor);
                }
                else
                {
                    tabItemRead.Background = new SolidColorBrush(IdleColor);
                }


                if (WriteDiskText.Text != FileUpdateProcess.MessageList[(int)MessageType.MT_WriteDisk])
                {
                    WriteDiskText.Text = FileUpdateProcess.MessageList[(int)MessageType.MT_WriteDisk];
                    scrollViewer5.ScrollToBottom();
                }

                if (FileUpdateProcess.bWritingDisk)
                {
                    tabItemWrite.Background = new SolidColorBrush(BusyColor);
                }
                else
                {
                    tabItemWrite.Background = new SolidColorBrush(IdleColor);
                }


                if (UncompressText.Text != FileUpdateProcess.MessageList[(int)MessageType.MT_Uncompress])
                {
                    UncompressText.Text = FileUpdateProcess.MessageList[(int)MessageType.MT_Uncompress];
                    scrollViewer3.ScrollToBottom();
                }

                if (FileUpdateProcess.bUncompressing)
                {
                    tabItemUncompress.Background = new SolidColorBrush(BusyColor);
                }
                else
                {
                    tabItemUncompress.Background = new SolidColorBrush(IdleColor);
                }
                

                float TaskPercent = 0;
                if (FileUpdateProcess.TotalTaskCount != 0)
                {
                    TaskPercent = (float)((float)(FileUpdateProcess.ProcessedTaskCount) / (float)(FileUpdateProcess.TotalTaskCount));
                }
                MainProgressBar.Value = TaskPercent * 100;

                if (FileUpdateProcess.TotalTaskCount == 0)
                {
                    MainText.Content = "Analyse Data" + PointString;
                }
                else
                {
                    MainText.Content = "Updating... Task : " + FileUpdateProcess.ProcessedTaskCount + "/" + FileUpdateProcess.TotalTaskCount;
                }
            }
            else
            {
                MainProgressBar.Value = 0;
                if (FileUpdateProcess.bLastTaskFinished)
                {
                    MainText.Content = "Task Finished. Cost Time:" + FileUpdateProcess.TaskTotalTime.ToString("F");
                    UpdateTimeText();
                }
                else
                {
                    MainText.Content = "No Task";
                }
                
            }
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            timer = new DispatcherTimer();
            timer.Interval = new TimeSpan(0, 0, 0, 0, 100);
            timer.Tick += new EventHandler(TimerTick);
            timer.Start();

            MainText.Content = "初始化...";
        }

        public static string getBranchName()
        {
            string exePath = AppDomain.CurrentDomain.BaseDirectory;
            string key = "08.Prog";
            int idx = exePath.IndexOf(key);
            int idxEnd = exePath.IndexOf('\\', idx);
            string branchName = exePath.Substring(idx + key.Length, idxEnd - idx - key.Length);
            //MessageBox.Show(branchName);
            return branchName;
        }


        private void button1_Click(object sender, RoutedEventArgs e)
        {
            if (bWaitFirstTick || !FileUpdateProcess.bTaskFinished)
            {
                return;
            }

            string branchName = getBranchName();

            FileUpdateProcess.Update("QAGameServer" + branchName, false);
        }

        private void button2_Click(object sender, RoutedEventArgs e)
        {
            if (bWaitFirstTick || !FileUpdateProcess.bTaskFinished)
            {
                return;
            }

            string branchName = getBranchName();
            FileUpdateProcess.Update("QAEditorServer" + branchName, false);
        }

        private void button3_Click(object sender, RoutedEventArgs e)
        {
            if (bWaitFirstTick || !FileUpdateProcess.bTaskFinished)
            {
                return;
            }

            string branchName = getBranchName();
            FileUpdateProcess.Update("Server" + branchName, (bool)CheckBoxForceUpdate.IsChecked);
        }

        private void button4_Click(object sender, RoutedEventArgs e)
        {
            if (bWaitFirstTick || !FileUpdateProcess.bTaskFinished)
            {
                return;
            }

            string branchName = getBranchName();
            FileUpdateProcess.Update("EditorServer" + branchName, (bool)CheckBoxForceUpdate.IsChecked);
        }

        private void button5_Click(object sender, RoutedEventArgs e)
        {
            if (bWaitFirstTick || !FileUpdateProcess.bTaskFinished)
            {
                return;
            }
            // run dev game
            string platformDir = "Win32";
            string hd = "";
            if (!(bool)CheckBoxHD.IsChecked)
            {
                hd = " -Lite";
            }

            if ((bool)CheckBoxEnglishVersion.IsChecked)
            {
                Process.Start("BinariesDev\\" + platformDir + "\\MMOgame.exe", "-log -DEV_RELEASE -NoGADWarning -LANGUAGE=INT" + hd);
            }
            else
            {
                Process.Start("BinariesDev\\" + platformDir + "\\MMOgame.exe", "-log -DEV_RELEASE -NoGADWarning -LANGUAGE=CHN" + hd);
            }
        }

        private void button6_Click(object sender, RoutedEventArgs e)
        {
            if (bWaitFirstTick || !FileUpdateProcess.bTaskFinished)
            {
                return;
            }
            // run dev editor

            string platformDir = "Win32";
            if ((bool)CheckBox64Bit.IsChecked)
            {
                platformDir = "Win64";
            }

            if ((bool)CheckBoxEnglishVersion.IsChecked)
            {
                Process.Start("BinariesEditor\\" + platformDir + "\\MMOgame.exe", "editor -log -EDITOR_RELEASE -NoGADWarning -LANGUAGE=INT");
            }
            else
            {
                Process.Start("BinariesEditor\\" + platformDir + "\\MMOgame.exe", "editor -log -EDITOR_RELEASE -NoGADWarning -LANGUAGE=CHN");
            }
            
        }

        private void button7_Click(object sender, RoutedEventArgs e)
        {
            if (bWaitFirstTick || !FileUpdateProcess.bTaskFinished)
            {
                return;
            }

            string branchName = getBranchName();
            FileUpdateProcess.Update("ShippingGameServer" + branchName, true);
        }

        private void button8_Click(object sender, RoutedEventArgs e)
        {
            if (bWaitFirstTick || !FileUpdateProcess.bTaskFinished)
            {
                return;
            }
            // run final game
            Process.Start("CQYH\\Binaries\\Win32\\MMOGame-Win32-Shipping.exe", "-log -sdot -seekfreeloading -FINAL_RELEASE -nohomedir");
        }

        private void button9_Click(object sender, RoutedEventArgs e)
        {
            if (bWaitFirstTick || !FileUpdateProcess.bTaskFinished)
            {
                return;
            }
            // update version info
            FileUpdateProcess.UpdateVersionInfo(getBranchName());

            UpdateVersionText();
        }

        private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            FileUpdateProcess.bTaskFinished = true;
            FileUpdateProcess.StopAllThread();
        }

        private void Window_Closed(object sender, EventArgs e)
        {
            FileUpdateProcess.bTaskFinished = true;
            FileUpdateProcess.StopAllThread();
        }

        private void button10_Click(object sender, RoutedEventArgs e)
        {
            if (bWaitFirstTick || !FileUpdateProcess.bTaskFinished)
            {
                return;
            }

            string branchName = getBranchName();
            FileUpdateProcess.Update("ShaderCache" + branchName, true);
        }





    }
}
