namespace DevLauncher
{
    partial class MainForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.tabPage2 = new System.Windows.Forms.TabPage();
            this.groupBox7 = new System.Windows.Forms.GroupBox();
            this._radioChn = new System.Windows.Forms.RadioButton();
            this._radioEng = new System.Windows.Forms.RadioButton();
            this.groupBox5 = new System.Windows.Forms.GroupBox();
            this._radioDX11 = new System.Windows.Forms.RadioButton();
            this._radioDX9 = new System.Windows.Forms.RadioButton();
            this.groupBox4 = new System.Windows.Forms.GroupBox();
            this._combCommandlet = new System.Windows.Forms.ComboBox();
            this._btnCommandletRelease = new System.Windows.Forms.Button();
            this._btnCommandletDebug = new System.Windows.Forms.Button();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this._comboMakeScript = new System.Windows.Forms.ComboBox();
            this._btnMakeScriptRelease = new System.Windows.Forms.Button();
            this._btnMakeScriptDebug = new System.Windows.Forms.Button();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this._combGame = new System.Windows.Forms.ComboBox();
            this._btnGameRelease = new System.Windows.Forms.Button();
            this._btnGameDebug = new System.Windows.Forms.Button();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this._comboEditor = new System.Windows.Forms.ComboBox();
            this._btnEditorRelsease = new System.Windows.Forms.Button();
            this._btnEditorDebug = new System.Windows.Forms.Button();
            this.groupBox6 = new System.Windows.Forms.GroupBox();
            this._radioWin64 = new System.Windows.Forms.RadioButton();
            this._radioWin32 = new System.Windows.Forms.RadioButton();
            this.tabControl1.SuspendLayout();
            this.tabPage2.SuspendLayout();
            this.groupBox7.SuspendLayout();
            this.groupBox5.SuspendLayout();
            this.groupBox4.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.groupBox6.SuspendLayout();
            this.SuspendLayout();
            // 
            // tabControl1
            // 
            this.tabControl1.Controls.Add(this.tabPage2);
            this.tabControl1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tabControl1.Location = new System.Drawing.Point(0, 0);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(354, 599);
            this.tabControl1.TabIndex = 0;
            // 
            // tabPage2
            // 
            this.tabPage2.Controls.Add(this.groupBox6);
            this.tabPage2.Controls.Add(this.groupBox7);
            this.tabPage2.Controls.Add(this.groupBox5);
            this.tabPage2.Controls.Add(this.groupBox4);
            this.tabPage2.Controls.Add(this.groupBox3);
            this.tabPage2.Controls.Add(this.groupBox2);
            this.tabPage2.Controls.Add(this.groupBox1);
            this.tabPage2.Location = new System.Drawing.Point(4, 22);
            this.tabPage2.Name = "tabPage2";
            this.tabPage2.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage2.Size = new System.Drawing.Size(346, 573);
            this.tabPage2.TabIndex = 1;
            this.tabPage2.Text = "Prog";
            this.tabPage2.UseVisualStyleBackColor = true;
            // 
            // groupBox7
            // 
            this.groupBox7.Controls.Add(this._radioChn);
            this.groupBox7.Controls.Add(this._radioEng);
            this.groupBox7.Location = new System.Drawing.Point(115, 6);
            this.groupBox7.Name = "groupBox7";
            this.groupBox7.Size = new System.Drawing.Size(107, 72);
            this.groupBox7.TabIndex = 4;
            this.groupBox7.TabStop = false;
            this.groupBox7.Text = "Language";
            // 
            // _radioChn
            // 
            this._radioChn.AutoSize = true;
            this._radioChn.Location = new System.Drawing.Point(6, 43);
            this._radioChn.Name = "_radioChn";
            this._radioChn.Size = new System.Drawing.Size(48, 17);
            this._radioChn.TabIndex = 4;
            this._radioChn.Text = "CHN";
            this._radioChn.UseVisualStyleBackColor = true;
            // 
            // _radioEng
            // 
            this._radioEng.AutoSize = true;
            this._radioEng.Checked = true;
            this._radioEng.Location = new System.Drawing.Point(6, 20);
            this._radioEng.Name = "_radioEng";
            this._radioEng.Size = new System.Drawing.Size(48, 17);
            this._radioEng.TabIndex = 4;
            this._radioEng.TabStop = true;
            this._radioEng.Text = "ENG";
            this._radioEng.UseVisualStyleBackColor = true;
            // 
            // groupBox5
            // 
            this.groupBox5.Controls.Add(this._radioDX11);
            this.groupBox5.Controls.Add(this._radioDX9);
            this.groupBox5.Location = new System.Drawing.Point(6, 6);
            this.groupBox5.Name = "groupBox5";
            this.groupBox5.Size = new System.Drawing.Size(103, 72);
            this.groupBox5.TabIndex = 4;
            this.groupBox5.TabStop = false;
            this.groupBox5.Text = "Rendering API";
            // 
            // _radioDX11
            // 
            this._radioDX11.AutoSize = true;
            this._radioDX11.Location = new System.Drawing.Point(9, 43);
            this._radioDX11.Name = "_radioDX11";
            this._radioDX11.Size = new System.Drawing.Size(52, 17);
            this._radioDX11.TabIndex = 2;
            this._radioDX11.Text = "DX11";
            this._radioDX11.UseVisualStyleBackColor = true;
            // 
            // _radioDX9
            // 
            this._radioDX9.AutoSize = true;
            this._radioDX9.Checked = true;
            this._radioDX9.Location = new System.Drawing.Point(9, 20);
            this._radioDX9.Name = "_radioDX9";
            this._radioDX9.Size = new System.Drawing.Size(46, 17);
            this._radioDX9.TabIndex = 2;
            this._radioDX9.TabStop = true;
            this._radioDX9.Text = "DX9";
            this._radioDX9.UseVisualStyleBackColor = true;
            // 
            // groupBox4
            // 
            this.groupBox4.Controls.Add(this._combCommandlet);
            this.groupBox4.Controls.Add(this._btnCommandletRelease);
            this.groupBox4.Controls.Add(this._btnCommandletDebug);
            this.groupBox4.Location = new System.Drawing.Point(3, 462);
            this.groupBox4.Name = "groupBox4";
            this.groupBox4.Size = new System.Drawing.Size(334, 87);
            this.groupBox4.TabIndex = 3;
            this.groupBox4.TabStop = false;
            this.groupBox4.Text = "Commandlet";
            // 
            // _combCommandlet
            // 
            this._combCommandlet.FormattingEnabled = true;
            this._combCommandlet.Location = new System.Drawing.Point(6, 19);
            this._combCommandlet.Name = "_combCommandlet";
            this._combCommandlet.Size = new System.Drawing.Size(306, 21);
            this._combCommandlet.TabIndex = 1;
            // 
            // _btnCommandletRelease
            // 
            this._btnCommandletRelease.Location = new System.Drawing.Point(172, 46);
            this._btnCommandletRelease.Name = "_btnCommandletRelease";
            this._btnCommandletRelease.Size = new System.Drawing.Size(141, 23);
            this._btnCommandletRelease.TabIndex = 0;
            this._btnCommandletRelease.Tag = ".\\Client\\UE3\\Binaries\\Win32\\MMOGame.exe make -log -auto -full";
            this._btnCommandletRelease.Text = "ReleaseExe";
            this._btnCommandletRelease.UseVisualStyleBackColor = true;
            this._btnCommandletRelease.Click += new System.EventHandler(this._btnCommandletRelease_Click);
            // 
            // _btnCommandletDebug
            // 
            this._btnCommandletDebug.Location = new System.Drawing.Point(7, 46);
            this._btnCommandletDebug.Name = "_btnCommandletDebug";
            this._btnCommandletDebug.Size = new System.Drawing.Size(141, 23);
            this._btnCommandletDebug.TabIndex = 0;
            this._btnCommandletDebug.Tag = "make -log -auto -full";
            this._btnCommandletDebug.Text = "DebugExe";
            this._btnCommandletDebug.UseVisualStyleBackColor = true;
            this._btnCommandletDebug.Click += new System.EventHandler(this._btnCommandletDebug_Click);
            // 
            // groupBox3
            // 
            this.groupBox3.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(224)))), ((int)(((byte)(192)))));
            this.groupBox3.Controls.Add(this._comboMakeScript);
            this.groupBox3.Controls.Add(this._btnMakeScriptRelease);
            this.groupBox3.Controls.Add(this._btnMakeScriptDebug);
            this.groupBox3.Location = new System.Drawing.Point(3, 356);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(334, 92);
            this.groupBox3.TabIndex = 3;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "Make Script";
            // 
            // _comboMakeScript
            // 
            this._comboMakeScript.FormattingEnabled = true;
            this._comboMakeScript.Location = new System.Drawing.Point(6, 21);
            this._comboMakeScript.Name = "_comboMakeScript";
            this._comboMakeScript.Size = new System.Drawing.Size(306, 21);
            this._comboMakeScript.TabIndex = 1;
            // 
            // _btnMakeScriptRelease
            // 
            this._btnMakeScriptRelease.Location = new System.Drawing.Point(171, 48);
            this._btnMakeScriptRelease.Name = "_btnMakeScriptRelease";
            this._btnMakeScriptRelease.Size = new System.Drawing.Size(141, 23);
            this._btnMakeScriptRelease.TabIndex = 0;
            this._btnMakeScriptRelease.Tag = ".\\Client\\UE3\\Binaries\\Win32\\MMOGame.exe make -log -auto -full";
            this._btnMakeScriptRelease.Text = "ReleaseExe_Script";
            this._btnMakeScriptRelease.UseVisualStyleBackColor = true;
            this._btnMakeScriptRelease.Click += new System.EventHandler(this._btnMakeScriptRelease_Click);
            // 
            // _btnMakeScriptDebug
            // 
            this._btnMakeScriptDebug.Location = new System.Drawing.Point(6, 48);
            this._btnMakeScriptDebug.Name = "_btnMakeScriptDebug";
            this._btnMakeScriptDebug.Size = new System.Drawing.Size(141, 23);
            this._btnMakeScriptDebug.TabIndex = 0;
            this._btnMakeScriptDebug.Tag = ".\\Client\\UE3\\Binaries\\Win32\\MMOGame-Win32-Debug.exe make -log -auto -full";
            this._btnMakeScriptDebug.Text = "DebugExe_Script";
            this._btnMakeScriptDebug.UseVisualStyleBackColor = true;
            this._btnMakeScriptDebug.Click += new System.EventHandler(this._btnMakeScriptDebug_Click);
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this._combGame);
            this.groupBox2.Controls.Add(this._btnGameRelease);
            this.groupBox2.Controls.Add(this._btnGameDebug);
            this.groupBox2.Location = new System.Drawing.Point(3, 224);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(334, 104);
            this.groupBox2.TabIndex = 2;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Game";
            // 
            // _combGame
            // 
            this._combGame.FormattingEnabled = true;
            this._combGame.Location = new System.Drawing.Point(7, 19);
            this._combGame.Name = "_combGame";
            this._combGame.Size = new System.Drawing.Size(306, 21);
            this._combGame.TabIndex = 1;
            // 
            // _btnGameRelease
            // 
            this._btnGameRelease.Location = new System.Drawing.Point(171, 57);
            this._btnGameRelease.Name = "_btnGameRelease";
            this._btnGameRelease.Size = new System.Drawing.Size(141, 23);
            this._btnGameRelease.TabIndex = 0;
            this._btnGameRelease.Tag = ".\\Client\\UE3\\Binaries\\Win32\\MMOGame.exe editor -log -NoGADWarning";
            this._btnGameRelease.Text = "Game Release";
            this._btnGameRelease.UseVisualStyleBackColor = true;
            this._btnGameRelease.Click += new System.EventHandler(this._btnGameRelease_Click);
            // 
            // _btnGameDebug
            // 
            this._btnGameDebug.Location = new System.Drawing.Point(6, 57);
            this._btnGameDebug.Name = "_btnGameDebug";
            this._btnGameDebug.Size = new System.Drawing.Size(141, 23);
            this._btnGameDebug.TabIndex = 0;
            this._btnGameDebug.Tag = ".\\Client\\UE3\\Binaries\\Win32\\MMOGame-Win32-Debug.exe editor -log -NoGADWarning";
            this._btnGameDebug.Text = "Game Debug";
            this._btnGameDebug.UseVisualStyleBackColor = true;
            this._btnGameDebug.Click += new System.EventHandler(this._btnGameDebug_Click);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this._comboEditor);
            this.groupBox1.Controls.Add(this._btnEditorRelsease);
            this.groupBox1.Controls.Add(this._btnEditorDebug);
            this.groupBox1.Location = new System.Drawing.Point(6, 105);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(334, 91);
            this.groupBox1.TabIndex = 1;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Editor";
            // 
            // _comboEditor
            // 
            this._comboEditor.FormattingEnabled = true;
            this._comboEditor.Location = new System.Drawing.Point(6, 19);
            this._comboEditor.Name = "_comboEditor";
            this._comboEditor.Size = new System.Drawing.Size(306, 21);
            this._comboEditor.TabIndex = 1;
            // 
            // _btnEditorRelsease
            // 
            this._btnEditorRelsease.Location = new System.Drawing.Point(171, 49);
            this._btnEditorRelsease.Name = "_btnEditorRelsease";
            this._btnEditorRelsease.Size = new System.Drawing.Size(141, 23);
            this._btnEditorRelsease.TabIndex = 0;
            this._btnEditorRelsease.Tag = ".\\Client\\UE3\\Binaries\\Win32\\MMOGame.exe editor -log -NoGADWarning";
            this._btnEditorRelsease.Text = "Editor Release";
            this._btnEditorRelsease.UseVisualStyleBackColor = true;
            this._btnEditorRelsease.Click += new System.EventHandler(this._btnEditorRelsease_Click);
            // 
            // _btnEditorDebug
            // 
            this._btnEditorDebug.Location = new System.Drawing.Point(6, 49);
            this._btnEditorDebug.Name = "_btnEditorDebug";
            this._btnEditorDebug.Size = new System.Drawing.Size(141, 23);
            this._btnEditorDebug.TabIndex = 0;
            this._btnEditorDebug.Tag = ".\\Client\\UE3\\Binaries\\Win32\\MMOGame-Win32-Debug.exe editor -log -NoGADWarning";
            this._btnEditorDebug.Text = "Editor Debug";
            this._btnEditorDebug.UseVisualStyleBackColor = true;
            this._btnEditorDebug.Click += new System.EventHandler(this._btnEditorDebug_Click);
            // 
            // groupBox6
            // 
            this.groupBox6.Controls.Add(this._radioWin64);
            this.groupBox6.Controls.Add(this._radioWin32);
            this.groupBox6.Location = new System.Drawing.Point(228, 6);
            this.groupBox6.Name = "groupBox6";
            this.groupBox6.Size = new System.Drawing.Size(107, 72);
            this.groupBox6.TabIndex = 6;
            this.groupBox6.TabStop = false;
            this.groupBox6.Text = "Language";
            // 
            // _radioWin64
            // 
            this._radioWin64.AutoSize = true;
            this._radioWin64.Location = new System.Drawing.Point(6, 43);
            this._radioWin64.Name = "_radioWin64";
            this._radioWin64.Size = new System.Drawing.Size(56, 17);
            this._radioWin64.TabIndex = 5;
            this._radioWin64.Text = "Win64";
            this._radioWin64.UseVisualStyleBackColor = true;
            // 
            // _radioWin32
            // 
            this._radioWin32.AutoSize = true;
            this._radioWin32.Checked = true;
            this._radioWin32.Location = new System.Drawing.Point(6, 20);
            this._radioWin32.Name = "_radioWin32";
            this._radioWin32.Size = new System.Drawing.Size(56, 17);
            this._radioWin32.TabIndex = 4;
            this._radioWin32.TabStop = true;
            this._radioWin32.Text = "Win32";
            this._radioWin32.UseVisualStyleBackColor = true;
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(354, 599);
            this.Controls.Add(this.tabControl1);
            this.Name = "MainForm";
            this.Text = "AOD DevLauncher";
            this.tabControl1.ResumeLayout(false);
            this.tabPage2.ResumeLayout(false);
            this.groupBox7.ResumeLayout(false);
            this.groupBox7.PerformLayout();
            this.groupBox5.ResumeLayout(false);
            this.groupBox5.PerformLayout();
            this.groupBox4.ResumeLayout(false);
            this.groupBox3.ResumeLayout(false);
            this.groupBox2.ResumeLayout(false);
            this.groupBox1.ResumeLayout(false);
            this.groupBox6.ResumeLayout(false);
            this.groupBox6.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage tabPage2;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.Button _btnMakeScriptRelease;
        private System.Windows.Forms.Button _btnMakeScriptDebug;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.GroupBox groupBox4;
        private System.Windows.Forms.ComboBox _combCommandlet;
        private System.Windows.Forms.Button _btnCommandletRelease;
        private System.Windows.Forms.Button _btnCommandletDebug;
        private System.Windows.Forms.Button _btnEditorRelsease;
        private System.Windows.Forms.Button _btnEditorDebug;
        private System.Windows.Forms.ComboBox _combGame;
        private System.Windows.Forms.Button _btnGameRelease;
        private System.Windows.Forms.Button _btnGameDebug;
        private System.Windows.Forms.ComboBox _comboMakeScript;
        private System.Windows.Forms.ComboBox _comboEditor;
        private System.Windows.Forms.GroupBox groupBox5;
        private System.Windows.Forms.RadioButton _radioDX11;
        private System.Windows.Forms.RadioButton _radioDX9;
        private System.Windows.Forms.GroupBox groupBox7;
        private System.Windows.Forms.RadioButton _radioChn;
        private System.Windows.Forms.RadioButton _radioEng;
        private System.Windows.Forms.GroupBox groupBox6;
        private System.Windows.Forms.RadioButton _radioWin64;
        private System.Windows.Forms.RadioButton _radioWin32;

    }
}

