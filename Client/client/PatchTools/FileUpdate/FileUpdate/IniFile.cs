using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;
using System.Threading;
using System.Windows;

namespace FileUpdate
{
    public class IniFile
    {
        public string IniPath;
        public IniFile(string InPath)
        {
            IniPath = InPath;
        }

        #region load win32 dll
        [DllImport("kernel32.dll")]
        private static extern long WritePrivateProfileString(string section, string key, string val, string filePath);

        [DllImport("kernel32.dll")]
        private static extern int GetPrivateProfileString(string section, string key, string defVal, StringBuilder retVal, int size, string filePath);

        [DllImport("kernel32.dll")]
        private static extern int GetPrivateProfileString(string section, string key, string defVal, Byte[] RetVal, int size, string filePath);
        #endregion

        public void IniWriteValue(string section, string key, string iValue)
        {
            WritePrivateProfileString(section, key, iValue, IniPath);
        }

        public string IniReadValue(string section, string key)
        {
            StringBuilder sb = new StringBuilder(255);
            int i = GetPrivateProfileString(section, key, "", sb, 255, IniPath);
            return sb.ToString();
        }

        public Byte[] IniReadValues(string section, string key)
        {
            Byte[] bt = new Byte[255];
            int i = GetPrivateProfileString(section, key, "", bt, 255, IniPath);
            return bt;
        }
    }

    public class ZipFile
    {
#if _X64
        [DllImport("zlibwapi64.dll")]
#else
        [DllImport("zlibwapi32.dll")]
#endif
        public static extern int uncompress(Byte[] dest, ref uint destLen, Byte[] source, int sourceLen);
    }
}
