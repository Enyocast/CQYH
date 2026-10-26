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
	class PS3SymbolParser2 : SymbolParser, IDisplayCallback
	{
		/// <summary> List of all symbols loaded from an elf file. </summary>
		List<FSymbolInfo> SymbolList = new List<FSymbolInfo>( 256000 );

		/// <summary> Path to the PS3 elf file. </summary>
		String ExecutablePath;

		/// <summary> Background thread used to resolving source file and line number for a symbol. </summary>
		private Thread Address2LineThread;

		/// <summary> Event used to signal that new symbols have been added to the lookup queue. </summary>
		private AutoResetEvent Address2LineEvent = new AutoResetEvent( false );

		/// <summary> If True the background thread should be stopped. </summary>
		private bool bQuitAddress2LineThread;

		/// <summary> Array of requests for resolving file name and line number for a symbol. </summary>
		private List<FAddr2LineRequest> Addr2LineRequests = new List<FAddr2LineRequest>();

		/// <summary> Regular expression used to parse the stream produces by PS3Bin which matches symbol information. </summary>
		private Regex PS3BinPattern = new Regex( "^0x([0-9A-Za-z]+) ([A-Za-z]+)[ ]+(Source File|[A-Za-z_]+)[ ]+([A-Za-z0-9_.]+)[ ]+(.*)$", RegexOptions.Compiled );

		/// <summary> Opens a file dialog and asks user to find the elf file for loading symbols. </summary>
		bool OpenFileDialogThreaded()
		{
			Thread DialogThread = new Thread( DialogThreadProc );
			DialogThread.SetApartmentState( ApartmentState.STA );
			DialogThread.Start( this );
			DialogThread.Join();

			return ExecutablePath.Length > 0;
		}

		/// <summary> Helper function needed to open a file dialog on the different thread than main. </summary>
		static void DialogThreadProc( Object Data )
		{
			OpenFileDialog OpenFileDlg = new OpenFileDialog();

			OpenFileDlg.Title = "Find .elf file for the running PS3 game";
			OpenFileDlg.Filter = ".elf Files|*.elf";
			OpenFileDlg.RestoreDirectory = true;
			OpenFileDlg.DefaultExt = "elf";
			OpenFileDlg.AddExtension = true;

			PS3SymbolParser2 Instance = ( PS3SymbolParser2 )Data;

			if( OpenFileDlg.ShowDialog() == DialogResult.OK )
			{
				Instance.ExecutablePath = OpenFileDlg.FileName;
			}
			else
			{
				Instance.ExecutablePath = "";
			}
		}

		/// <summary> Loads symbols for an executable. </summary>
		/// <param name="ExePath"> The path to the executable whose symbols are going to be loaded. </param>
		/// <param name="Modules"> The list of modules loaded by the process. </param>
		public override bool LoadSymbols( string ExePath, ModuleInfo[] modules )
		{
			// Try loading the file containing symbols located in the profiler file folder.
			bool bFileExist = File.Exists( ExePath );
			if( bFileExist == false )
			{
				if( FStreamInfo.bLoadDefaultSymbols == true )
				{
					// Try to look for an exe in the Binaries directory.
					string ExeBinPath = Directory.GetCurrentDirectory();
					ExeBinPath += @"\PS3\";
					ExeBinPath += ExePath;

					// Now ask user to locate the file containing symbols.
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
					return false;
				}
			}
			else
			{
				ExecutablePath = ExePath;
			}

			ExecutablePath = string.Format( "\"{0}\"", ExecutablePath );
			Debug.WriteLine( "Loading elf \"" + ExecutablePath + "\"" );

			string SceRootPath = Environment.GetEnvironmentVariable( "SCE_PS3_ROOT" );
			string PS3BinPath = String.Format( "{0}\\host-win32\\sn\\bin\\ps3bin.exe", SceRootPath );

			if( File.Exists( PS3BinPath ) == false )
			{
				MessageBox.Show( "Failed to create ps3bin process. Check your SCE_PS3_ROOT env variable.", "Process creation error", MessageBoxButtons.OK, MessageBoxIcon.Error );
				return false;
			}

			FManagedCommandLineWrapper PS3BinProcess = new FManagedCommandLineWrapper( PS3BinPath, ExecutablePath + " -dsy" );

			while( true )
			{
				string Line = PS3BinProcess.ReadLine();

				// something went wrong with the ps3bin tool
				// most likely the elf filename was wrong and the file didn't exist or it wasn't an executable
				if( Line == null )
				{
					Console.WriteLine( "Can't read data from ps3bin" );
					return false;
				}

				Match MatchLine = PS3BinPattern.Match( Line );

				if( MatchLine.Success )
				{
					// not all of these are used, but I thought it was a good idea to extract them anyway,
					// to save some future maintainer from trying to decode the regex :)
					ulong Address = ulong.Parse( MatchLine.Groups[ 1 ].Value, NumberStyles.HexNumber );
					string Binding = MatchLine.Groups[ 2 ].Value;
					string Type = MatchLine.Groups[ 3 ].Value;
					string Section = MatchLine.Groups[ 4 ].Value;
					string SymbolName = MatchLine.Groups[ 5 ].Value.TrimEnd();

					if( SymbolName == "_end" )
					{
						break;
					}

					SymbolList.Add( new FSymbolInfo( Address, SymbolName ) );
				}
			}

			SymbolList.TrimExcess();
			PS3BinProcess.Terminate();

			Address2LineThread = new Thread( new ThreadStart( Address2LineThreadMain ) );
			Address2LineThread.Start();

			return true;
		}

		/// <summary> Retrieves the symbol info for an address. </summary>
		/// <param name="Address"> The address to retrieve the symbol information for. </param>
		/// <param name="OutFileName"> The file that the instruction at Address belongs to. Not implemented. </param>
		/// <param name="OutFunction"> The name of the function that owns the instruction pointed to by Address. </param>
		/// <param name="OutLineNumber"> The line number within OutFileName that is represented by Address. Not implemented. </param>
		/// <returns> True if the function succeeds. </returns>
		public override bool ResolveAddressToSymboInfo( ulong Address, ref string OutFileName, ref string OutFunction, ref int OutLineNumber )
		{
			if( Address < SymbolList[ 0 ].Address || Address > SymbolList[ SymbolList.Count - 1 ].Address )
			{
				// Address was too low or too high for the symbol list.
				OutFunction = Address.ToString();
			}
			else
			{
				// Do a binary search for the address.
				int Index = SymbolList.Count / 2;
				int StepSize = Index / 2;

				// loop until the address is between SymbolList[index].address and SymbolList[index + 1].address
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

				OutFunction = SymbolList[ Index ].FunctionName;
			}

			// Don't know filename or line number without using addr2line.
			// addr2line is ridiculously slow, so we only use it for addresses
			// the user is actually looking at.
			OutFileName = "Unknown";
			OutLineNumber = -1;
			return true;
		}

		/// <summary> Nothing to do. </summary>
		public override void UnloadSymbols()
		{
		}

		public void DisplayCallstack( FCallStack Callstack, AddressDataUpdatedDelegate Callback, object UserObject )
		{
			bool bAddedRequests = false;

			lock( Addr2LineRequests )
			{
				foreach( int Index in Callstack.AddressIndices )
				{
					FCallStackAddress CallStackAddress = FStreamInfo.GlobalInstance.CallStackAddressArray[ Index ];
					if( !CallStackAddress.bIsComplete )
					{
						bAddedRequests = true;
						Addr2LineRequests.Add( new FAddr2LineRequest( CallStackAddress, FStreamInfo.GlobalInstance, Callback, UserObject ) );
					}
				}
			}

			if( bAddedRequests )
			{
				Address2LineEvent.Set();
			}
		}

		private void Address2LineThreadMain()
		{
			string SceRootPath = Environment.GetEnvironmentVariable( "SCE_PS3_ROOT" );
			string PS3BinPath = String.Format( "{0}\\host-win32\\sn\\bin\\ps3bin.exe", SceRootPath );
			FManagedCommandLineWrapper Address2LineProcess = new FManagedCommandLineWrapper( PS3BinPath, ExecutablePath + " -a2l" );

			while( !bQuitAddress2LineThread )
			{
				FAddr2LineRequest? Request = null;
				lock( Addr2LineRequests )
				{
					if( Addr2LineRequests.Count > 0 )
					{
						Request = Addr2LineRequests[ 0 ];
						Addr2LineRequests.RemoveAt( 0 );
					}
				}

				if( Request != null )
				{
					FCallStackAddress Address = Request.Value.CallStackAddress;

					Address2LineProcess.Write( string.Format( "0x{0:X}\n", Address.ProgramCounter ) );

					// Throw away "Address:" line
					Address2LineProcess.ReadLine();

					// Throw away "Directory:" line
					Address2LineProcess.ReadLine();

					// Remove "File Name:" and trim spaces
					string Filename = Address2LineProcess.ReadLine();
					Filename = Filename.Substring( Filename.IndexOf( ':' ) + 1 ).Trim();
					Address.FilenameIndex = Request.Value.StreamInfo.GetNameIndex( Filename, true );

					// Remove "Line Number:" and trim spaces
					string LineNumber = Address2LineProcess.ReadLine();
					Address.LineNumber = int.Parse( LineNumber.Substring( LineNumber.IndexOf( ':' ) + 1 ).Trim() );

					// Throw away "Symbol:" line
					Address2LineProcess.ReadLine();
					Address.bIsComplete = true;
					Request.Value.Callback( Request.Value.UserObject );
				}
				else
				{
					Address2LineEvent.WaitOne();
				}
			}

			if( Address2LineProcess != null )
			{
				Address2LineProcess.Terminate();
			}
		}

		public void Shutdown()
		{
			bQuitAddress2LineThread = true;
			Address2LineEvent.Set();

			if( Address2LineThread != null )
			{
				Address2LineThread.Join();
			}
		}
	}

	/// <summary> Encapsulates a request of resolving source file and line number from a symbol. </summary>
	struct FAddr2LineRequest
	{
		public FCallStackAddress CallStackAddress;
		public FStreamInfo StreamInfo;
		public AddressDataUpdatedDelegate Callback;
		public object UserObject;

		public FAddr2LineRequest( FCallStackAddress InCallStackAddress, FStreamInfo InStreamInfo, AddressDataUpdatedDelegate InCallback, object InUserObject )
		{
			CallStackAddress = InCallStackAddress;
			StreamInfo = InStreamInfo;
			Callback = InCallback;
			UserObject = InUserObject;
		}
	}
}
