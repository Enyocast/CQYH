using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Diagnostics;

namespace DevLauncher
{
    public partial class MainForm : Form
    {
        public MainForm()
        {
            InitializeComponent();


            //System.IO.Directory.SetCurrentDirectory(System.IO.Directory.GetCurrentDirectory() + _workingDir);
        }

        string _debugExe = @"MMOGame-Win32-Debug.exe";
        string _releaseExe = @"MMOGame.exe";
        string _workingDir = @"\Client\UE3\Binaries\";
        string _rootDir = System.IO.Directory.GetCurrentDirectory();

        string GetWorkingDir()
        {
            if (_radioWin32.Checked)
            {
                return _workingDir + @"Win32\";
            }

            return _workingDir + @"Win64\";
        }

        string GetDebugExe()
        {
            if (_radioWin32.Checked)
            {
                return @"MMOGame-Win32-Debug.exe";
            }

            return @"MMOGame-Win64-Debug.exe";
        }

        string GetReleaseExe()
        {
            if (_radioWin32.Checked)
            {
                return @"MMOGame.exe";
            }

            return @"MMOGame.exe";
        }

        void StartExe(string exe, string para)
        {
            System.IO.Directory.SetCurrentDirectory(_rootDir + GetWorkingDir());

            ProcessStartInfo StartInfo = new ProcessStartInfo();
            // Prepare a ProcessStart structure 
            StartInfo.FileName = exe;
            StartInfo.WorkingDirectory = System.IO.Directory.GetCurrentDirectory();
            StartInfo.Arguments = para;
            //StartInfo.UseShellExecute = false;
            System.Diagnostics.Process.Start(StartInfo);
        }

        void CacheComboList(ComboBox box)
        {
            string newVal = box.Text;
            foreach (string s in box.Items)
            {
                if (s == newVal)
                {
                    return;
                }
            }

            box.Items.Add(newVal);
        }

        string GetCommonPara()
        {
            string par = "";
            if (_radioDX9.Checked)
            {
                par += " -dx9 ";
            }
            else
            {
                par += " -dx11 ";
            }

            if (_radioEng.Checked)
            {
                par += " -LANGUAGE=ENG ";
            }
            else
            {
                par += " -LANGUAGE=CHN ";
            }

            return par;
        }

        private void _btnEditorDebug_Click(object sender, EventArgs e)
        {
            CacheComboList(_comboEditor);
            StartExe(GetDebugExe(), "editor -log -NoGADWarning " + _comboEditor.Text + GetCommonPara());
        }

        private void _btnEditorRelsease_Click(object sender, EventArgs e)
        {
            CacheComboList(_comboEditor);
            StartExe(GetReleaseExe(), "editor -log -NoGADWarning " + _comboEditor.Text + GetCommonPara());
        }

        private void _btnGameDebug_Click(object sender, EventArgs e)
        {
            CacheComboList(_combGame);
            StartExe(GetDebugExe(), " -log " + _combGame.Text + GetCommonPara());
        }

        private void _btnGameRelease_Click(object sender, EventArgs e)
        {
            CacheComboList(_combGame);
            StartExe(GetReleaseExe(), " -log " + _combGame.Text + GetCommonPara());
        }

        private void _btnMakeScriptDebug_Click(object sender, EventArgs e)
        {
            CacheComboList(_comboMakeScript);
            StartExe(GetDebugExe(), "make -auto -NOPAUSEONSUCCESS -full -DEMOMODE" + _comboMakeScript.Text + GetCommonPara());
        }

        private void _btnMakeScriptRelease_Click(object sender, EventArgs e)
        {
            CacheComboList(_comboMakeScript);
            StartExe(GetReleaseExe(), "make -auto -NOPAUSEONSUCCESS -full -DEMOMODE" + _comboMakeScript.Text + GetCommonPara());
        }

        private void _btnCommandletDebug_Click(object sender, EventArgs e)
        {
            CacheComboList(_combCommandlet);
            StartExe(GetDebugExe(), _combCommandlet.Text + GetCommonPara());
        }

        private void _btnCommandletRelease_Click(object sender, EventArgs e)
        {
            CacheComboList(_combCommandlet);
            StartExe(GetReleaseExe(), _combCommandlet.Text + GetCommonPara());
        }
    }
}
