/**
 * Copyright 1998-2012 Epic Games, Inc. All Rights Reserved.
 */
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Drawing;
using System.Globalization;
using System.IO;
using System.Reflection;
using System.Text;
using System.Xml;
using System.Xml.XPath;
using System.Xml.Serialization;

using ConsoleInterface;

namespace Controller
{
	public partial class GameConfig
	{
		public PlatformType GetPlatformType()
		{
			PlatformType PlatformType = PlatformType.None;
			switch( Platform.ToLower() )
			{
			case "pc":
			case "win32":
			case "win64":
				PlatformType = PlatformType.PC;
				break;

			case "pcconsole":
			case "win32console":
			case "win64console":
				PlatformType = PlatformType.PCConsole;
				break;

			case "pcserver":
			case "win32server":
			case "win64server":
				PlatformType = PlatformType.PCServer;
				break;

			case "xbox360":
				PlatformType = PlatformType.Xbox360;
				break;

			case "ps3":
				PlatformType = PlatformType.PS3;
				break;

			case "mac":
				PlatformType = PlatformType.MacOSX;
				break;

			case "iphone":
				PlatformType = PlatformType.IPhone;
				break;

			case "android":
				PlatformType = PlatformType.Android;
				break;
			}

			return PlatformType;
		}
	}

	public partial class BuildState
	{
		public bool CheckTargetState()
		{
			// Extract the desired state
			TargetState State = TargetState.Unconnected;
			try
			{
				State = ( TargetState )Enum.Parse( typeof( TargetState ), CurrentCommand.CommandLine, true );
			}
			catch
			{
				Parent.Log( "ERROR: Unknown target state: " + CurrentCommand.CommandLine, Color.Red );
				return true;
			}

			// Find all the available targets of this platform type
			foreach( Platform Platform in DLLInterface.Platforms )
			{
				if( Platform != null )
				{
					// Get the state of the default target
					Parent.Log( "Target state '" + Platform.DefaultTarget.State.ToString() + "'", Color.Magenta );

					return Platform.DefaultTarget.State == State;
				}
			}

			return false;
		}
	}

	public partial class SandboxedAction
	{
		private void PrepareForSync()
		{
			DLLInterface.UnloadPlatforms( PlatformType.All );
		}

		public MODES LaunchGame()
		{
			try
			{
				string LogFileName = Builder.GetLogFileName( COMMANDS.LaunchGame );
				Builder.OpenLog( LogFileName, false );

				if( Builder.AFTTestMap.Length == 0 )
				{
					Builder.Write( "Error: No test map set to launch." );
					State = COMMANDS.LaunchGame;
				}
				else
				{
					// Delete any existing screenshots
					GameConfig Config = Builder.CreateGameConfig();
					if( !DeletePatternFromFolder( Builder.LabelInfo.Game + "Game\\Screenshots\\" + Config.GetCookedFolderPlatform(), "*.bmp", false ) )
					{
						State = COMMANDS.SimpleDelete;
					}
					else
					{
						List<string> Executables = Config.GetExecutableNames( Builder.BranchDef.Version );
						string CommandLine = Builder.AFTTestMap + " " + CommonCommandLine;

						CurrentBuild = new BuildProcess( Parent, Builder, Executables[0], CommandLine, "", true );

						State = CurrentBuild.GetErrorLevel();
					}
				}

				StartTime = DateTime.UtcNow;
			}
			catch
			{
				State = COMMANDS.LaunchGame;
				Builder.Write( "Error: exception while starting to launch game." );
				Builder.CloseLog();
			}

			return MODES.Monitor;
		}

		public MODES LaunchConsole()
		{
			try
			{
				string LogFileName = Builder.GetLogFileName( COMMANDS.LaunchConsole );
				Builder.OpenLog( LogFileName, false );

				if( Builder.AFTTestMap.Length == 0 )
				{
					Builder.Write( "Error: No test map set to launch." );
					State = COMMANDS.LaunchConsole;
				}
				else
				{
					// Delete any existing screenshots
					GameConfig Config = Builder.CreateGameConfig();
					if( !DeletePatternFromFolder( Config.GetScreenShotFolderName(), "*.bmp", false ) )
					{
						State = COMMANDS.SimpleDelete;
					}
					else
					{
						// Load in the platform support dll for the current platform
						Environment.CurrentDirectory = Builder.BranchDef.ClientRoot + "\\" + Builder.BranchDef.Branch + "\\Binaries";

						Builder.Write( " ... loading platform dll for " + Config.GetPlatformType().ToString() );
						DLLInterface.LoadPlatforms( Config.GetPlatformType() );

						string CommandLine = Builder.AFTTestMap + " -CleanScreenShots -CleanLogs";

						// Find all the available targets of this platform type
						Builder.Write( " ... launching on all targets" );
						foreach( Platform Platform in DLLInterface.Platforms )
						{
							if( Platform != null )
							{
								Platform.EnumerateAvailableTargets();

								// Connect to the default target
								if( Platform.DefaultTarget.Connect() )
								{
									// Launch on default console
									Builder.Write( " ... launching on default target" );
									Platform.DefaultTarget.RunGameOnTarget( Config.GameName, Config.Configuration, CommandLine, Builder.BranchDef.Branch );
								}
							}
						}

						Environment.CurrentDirectory = Builder.BranchDef.ClientRoot + "\\" + Builder.BranchDef.Branch;
						State = COMMANDS.None;
					}
				}

				Builder.CloseLog();
			}
			catch
			{
				State = COMMANDS.LaunchConsole;
				Builder.Write( "Error: exception while starting to launch game on console." );
				Builder.CloseLog();
			}

			return MODES.Finalise;
		}

		private void Deploy( COMMANDS Command, string Tagset, string CommandLine, bool AddToReport, string AdditionalOptions )
		{
			try
			{
				Builder.OpenLog( Builder.GetLogFileName( Command ), false );

				GameConfig Config = Builder.CreateGameConfig();

				string Executable = "Binaries/CookerSync.exe";
				string CookerSyncCommandLine = Builder.LabelInfo.Game + " -p " + Config.GetCookedFolderPlatform();

				string Language = Builder.LabelInfo.Language;
				if( Language.Length == 0 )
				{
					Language = "INT";
				}

				CookerSyncCommandLine += " -r " + Language;
				CookerSyncCommandLine += " -b " + Builder.BranchDef.Branch + Builder.GetSubBranch();
				CookerSyncCommandLine += " -x " + Tagset;
				CookerSyncCommandLine += " -l -o -d";
				CookerSyncCommandLine += AdditionalOptions;

				CurrentBuild = new BuildProcess( Parent, Builder, Executable, CookerSyncCommandLine, Environment.CurrentDirectory + "/Binaries", false );
				State = CurrentBuild.GetErrorLevel();

				StartTime = DateTime.UtcNow;
			}
			catch
			{
				State = Command;
				Builder.Write( "Error: exception while starting to deploy" );
				Builder.CloseLog();
			}
		}

		public MODES Deploy()
		{
			Deploy( COMMANDS.Deploy, "ConsoleSyncProgrammer", Builder.GetCurrentCommandLine(), true, "" );
			return MODES.Monitor;
		}

		public MODES RetrieveScreenShots()
		{
			try
			{
				Builder.OpenLog( Builder.GetLogFileName( COMMANDS.RetrieveScreenShots ), false );

				GameConfig Config = Builder.CreateGameConfig();
				string ScreenShotDir = Config.GetScreenShotFolderName();

				foreach( Platform Platform in DLLInterface.Platforms )
				{
					int Index = 0;
					while( Index >= 0 )
					{
						string SourceName = Builder.BranchDef.Branch + "\\" + ScreenShotDir + "\\ScreenShot" + Index.ToString( "D5" ) + ".bmp";
						string DestName = ScreenShotDir + "\\ScreenShot" + Index.ToString( "D5" ) + ".bmp";
						Parent.Log( "Attempting to copy: '" + SourceName + "' -> '" + DestName + "'", Color.Magenta );
						if( Platform.DefaultTarget.RetrieveFileFromTarget( SourceName, DestName ) )
						{
							Builder.AddScreenShot( DestName );
							Parent.Log( " ... success!", Color.Magenta );
							Index++;
						}
						else
						{
							Parent.Log( " ... failed! Exiting", Color.Magenta );
							Index = -1;
						}
					}
				}

				Builder.CloseLog();
			}
			catch
			{
				State = COMMANDS.RetrieveScreenShots;
				Builder.Write( "Error: exception while copying screenshots" );
				Builder.CloseLog();
			}

			return MODES.Finalise;
		}

		public MODES ProcessScreenShots()
		{
			try
			{
				Builder.OpenLog( Builder.GetLogFileName( COMMANDS.ProcessScreenShots ), false );

				if( Builder.AFTScreenShots.Count == 0 )
				{
					Builder.Write( "Error: No screenshots to process." );
					State = COMMANDS.ProcessScreenShots;
				}
				else if( Builder.AFTTestMap.Length == 0 )
				{
					Builder.Write( "Error: No test map to associate screenshots." );
					State = COMMANDS.ProcessScreenShots;
				}
				else
				{
					GameConfig Config = Builder.CreateGameConfig();
					// e.g. UDKGame\ScreenShots\Xbox360
					string ScreenShotDir = Config.GetScreenShotFolderName();
					// e.g. UDKGame\QA\Xbox360\DevKit\AutomatedScreenshotTest
					string AFTReferenceFolder = Config.GetAFTReferenceFolder( Builder.TargetType, Builder.AFTTestMap );

					foreach( string ScreenShot in Builder.AFTScreenShots )
					{
						// Convert the .bmp to a .png in the correct location
						string UpdatedName = Path.Combine( AFTReferenceFolder, Path.GetFileNameWithoutExtension( ScreenShot ) ) + ".png";
						Bitmap Image = new Bitmap( ScreenShot );
						Image.Save( UpdatedName );
						Image.Dispose();

						// Create the difference image
						string ReferenceName = UpdatedName.Replace( "ScreenShot", "Reference" );
						string DifferenceName = UpdatedName.Replace( "ScreenShot", "Difference" );

						// UnrealImageDiff 2 AFTReferenceFolder\Reference.png ScreenShotDir\ScreenShot.bmp AFTReferenceFolder\Difference.png
						string CommandLine = "2 " + ReferenceName + " " + UpdatedName + " " + DifferenceName;
						CurrentBuild = new BuildProcess( Parent, Builder, "Binaries\\UnrealImageDiff.exe", CommandLine, "", true );

						while( !CurrentBuild.IsFinished )
						{
							System.Threading.Thread.Sleep( 100 );
						}
					}
				}

				Builder.CloseLog();
			}
			catch
			{
				State = COMMANDS.ProcessScreenShots;
				Builder.Write( "Error: exception while processing screenshots" );
				Builder.CloseLog();
			}

			return MODES.Finalise;
		}
	}
}

