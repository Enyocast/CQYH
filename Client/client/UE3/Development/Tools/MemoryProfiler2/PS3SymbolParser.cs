/**
 * Copyright 1998-2011 Epic Games, Inc. All Rights Reserved.
 */

using System;
using System.Collections.Generic;
using System.Text;
using StandaloneSymbolParser;
using System.Diagnostics;
using System.Windows.Forms;
using System.Globalization;
using System.Threading;
using System.IO;
using System.Text.RegularExpressions;

namespace MemoryProfiler2
{
	/// <summary> Improved symbol parser for PS3. </summary>
	public class FPS3FastSymbolParser : SymbolParser
	{
		/// <summary> List of all symbols loaded from an elf file. </summary>
		List<FSymbolInfo> SymbolList = new List<FSymbolInfo>( 256000 );

		/// <summary> Path to the PS3 elf file. </summary>
		String ExecutablePath;

		bool OpenFileDialogThreaded()
		{
			Thread DialogThread = new Thread( DialogThreadProc );
			DialogThread.SetApartmentState( ApartmentState.STA );
			DialogThread.Start( this );
			DialogThread.Join();

			return ExecutablePath.Length > 0;
		}

		static void DialogThreadProc( Object Data )
		{
			OpenFileDialog OpenFileDlg = new OpenFileDialog();

			OpenFileDlg.Title = "Find .elf file for the running PS3 game";
			OpenFileDlg.Filter = ".elf Files|*.elf";
			OpenFileDlg.RestoreDirectory = true;
			OpenFileDlg.DefaultExt = "elf";
			OpenFileDlg.AddExtension = true;

			FPS3FastSymbolParser Instance = ( FPS3FastSymbolParser )Data;

			if( OpenFileDlg.ShowDialog() == DialogResult.OK )
			{
				Instance.ExecutablePath = OpenFileDlg.FileName;
			}
			else
			{
				Instance.ExecutablePath = "";
			}
		}


		/**
		 * Loads symbols for an executable.
		 *
		 * @param	ExePath		The path to the executable whose symbols are going to be loaded.
		 * @param	Modules		The list of modules loaded by the process.
		 */
		public override bool LoadSymbols( string ExePath, ModuleInfo[] Modules )
		{
			// Convert .xelf to .elf
			if( ExePath.EndsWith( ".xelf" ) )
			{
				ExePath = ExePath.Replace( ".xelf", ".elf" );
			}

			// Make sure the file exists
			if( File.Exists( ExePath ) == false )
			{
				// Try to look for an exe in the Binaries directory.
				string Filename = System.IO.Path.GetFileName( ExePath );
				string ExeBinPath = System.IO.Path.GetDirectoryName( ExePath );
				ExeBinPath += @"\..\..\..\Binaries\PS3\";
				ExeBinPath += Filename;

				ExeBinPath = System.IO.Path.GetFullPath( ExeBinPath );

				if( File.Exists( ExeBinPath ) == false )
				{
					bool Result = OpenFileDialogThreaded();
					if( Result == false )
					{
						return false;
					}
				}
				else
				{
					ExecutablePath = ExeBinPath;
				}
			}
			else
			{
				ExecutablePath = ExePath;
			}

			string SceRootPath = Environment.GetEnvironmentVariable( "SCE_PS3_ROOT" );
			string PS3BinPath = String.Format( "{0}\\host-win32\\sn\\bin\\ps3bin.exe", SceRootPath );


			if( File.Exists( PS3BinPath ) == false )
			{
				MessageBox.Show( "Failed to create ps3bin process. Check your SCE_PS3_ROOT env variable.", "Process creation error", MessageBoxButtons.OK, MessageBoxIcon.Error );
				return false;
			}

			string Args = string.Format( "{0} -dsy", ExecutablePath );

			/* 
				Data format exported with ps3bin.exe %elf% -dsy
				Value              Binding      Type         Section          Name        
				0x000000000029F680 Global       Function     .text            UMaterialInterface::GetWidth() const

				Value	=  0 - 18
				Binding	= 19 - 31 
				Type	= 32 - 44
				Section	= 45 - 61
				Name	= 62 - endl

				-dsy --dump-symbols                     Dump symbol tables.
			*/

			// Start a PS3Bin process.
			FCommandLineWrapper PS3BinProcess = new FCommandLineWrapper( PS3BinPath, Args );

			bool bShouldQuit = false;
			int SymbolsNum = 0;

			while( bShouldQuit == false )
			{
				string SymbolLine = PS3BinProcess.ReadLine();

				if( SymbolLine.Length < 64 )
				{
					continue;
				}

				// Parse a line.
				string Value = SymbolLine.Substring( 10, 18 - 10 );
				string Binding = SymbolLine.Substring( 19, 31 - 19 );
				string Function = SymbolLine.Substring( 32, 44 - 32 );
				string Section = SymbolLine.Substring( 45, 61 - 45 );
				string Name = SymbolLine.Substring( 62 );

				bool bIsFunction = Function.IndexOf( "Function" ) != -1;

				// @warning This might change in future version of SN compiler.
				// STT_NOTYPE with .rodata are located after Functions, so we can skip rest of list in this case.
				bShouldQuit = SymbolsNum > 0 && Function.IndexOf( "STT_NOTYPE" ) != -1 && Section.IndexOf( ".rodata" ) != -1;

				if( bIsFunction == true )
				{
					UInt64 FunctionAddress = UInt64.Parse( Value, System.Globalization.NumberStyles.HexNumber );

					SymbolList.Add( new FSymbolInfo( FunctionAddress, Name, "(none)", 0 ) );
					SymbolsNum++;
				}

				if( SymbolLine == null )
				{
					bShouldQuit = true;
				}
			}

			SymbolList.TrimExcess();
			PS3BinProcess.Terminate();

			return true;
		}

		public override void UnloadSymbols()
		{
		}


		/**
		 * Retrieves the symbol info for an address.
		 *
		 * @param	Address			The address to retrieve the symbol information for.
		 * @param	OutFileName		The file that the instruction at Address belongs to. Not implemented.
		 * @param	OutFunction		The name of the function that owns the instruction pointed to by Address.
		 * @param	OutLineNumber	The line number within OutFileName that is represented by Address. Not implemented.
		 * @return	True if the function succeeds.
		 */
		public override bool ResolveAddressToSymboInfo( UInt64 Address, ref string outFileName, ref string outFunction, ref int outLineNumber )
		{
			if( Address < SymbolList[ 0 ].Address || Address > SymbolList[ SymbolList.Count - 1 ].Address )
			{
				// Address was too low or too high for the symbol list.
				outFunction = Address.ToString();
				outFileName = "";
				outLineNumber = 0;
			}
			else
			{
				// Do a binary search for the address.
				int Index = SymbolList.Count / 2;
				int StepSize = Index / 2;

				// Loop until the address is between SymbolList[Index].Address and SymbolList[Index + 1].Address
				while( SymbolList[ Index ].Address > Address || Index + 1 >= SymbolList.Count || SymbolList[ Index + 1 ].Address < Address )
				{
					if( SymbolList[ Index ].Address < Address )
					{
						Index += StepSize;
					}
					else
					{
						Index -= StepSize;
					}

					if( StepSize > 1 )
					{
						StepSize /= 2;
					}
				}

				outFunction = SymbolList[ Index ].FunctionName;
				// This is an aproximation only.
				outLineNumber = ( int )( Address - SymbolList[ Index ].Address );
			}

			outFileName = "(Unknown)";

			return true;
		}
	}
}