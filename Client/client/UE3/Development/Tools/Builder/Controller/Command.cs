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

using Controller.Models;
using System.Net.Sockets;

namespace Controller
{
	public class JobInfo
	{
		[XmlAttribute]
		public string Name = "";

		[XmlAttribute]
		public string Command = "";

		[XmlAttribute]
		public string Parameter = "";
	}

	public class JobDescriptions
	{
		[XmlArray( "Jobs" )]
		public JobInfo[] Jobs = new JobInfo[0];

		public JobDescriptions()
		{
		}
	}

	/** 
	 * A class containing the rules to complete an artist sync
	 */
	public class ArtistSyncRules
	{
		[XmlElement]
		public string PromotionLabel;
		[XmlArray]
		public List<string> FilesToClean;
		[XmlArray]
		public List<string> Rules;

		public ArtistSyncRules()
		{
			PromotionLabel = "";
			FilesToClean = new List<string>();
			Rules = new List<string>();
		}
	}

	public partial class Command
	{
		public Main Parent = null;

		private P4 SCC = null;
		private ScriptParser Builder = null;

		private COMMANDS ErrorLevel = COMMANDS.None;
		private BuildProcess CurrentBuild = null;
		private DateTime StartTime = DateTime.UtcNow;
		private DateTime LastRespondingTime = DateTime.UtcNow;

		public COMMANDS LastExecutedCommand = COMMANDS.Error;

		private string CommonCommandLine = "-unattended -nopause -buildmachine -forcelogflush";

		public Command( Main InParent, P4 InSCC, ScriptParser InBuilder, COMMANDS InCommandID, string InCommandLine )
		{
			Parent = InParent;
			SCC = InSCC;
			Builder = InBuilder;

			// Add source control info to the common command line params.
			CommonCommandLine += " -gadbranchname=" + Builder.BranchDef.Branch;

			Builder.CurrentCommandID = InCommandID;
			Builder.CurrentCommandLine = InCommandLine;
		}

		public COMMANDS GetErrorLevel()
		{
			return ( ErrorLevel );
		}

		public BuildProcess GetCurrentBuild()
		{
			return ( CurrentBuild );
		}

		private void CleanIniFiles( GameConfig Config )
		{
			string ConfigFolder = Config.GetConfigFolderName();
			DirectoryInfo Dir = new DirectoryInfo( ConfigFolder );

			if( Dir.Exists )
			{
				foreach( FileInfo File in Dir.GetFiles() )
				{
					Builder.Write( " ... checking: " + File.Name );
					if( File.IsReadOnly == false )
					{
						File.Delete();
						Builder.Write( " ...... deleted: " + File.Name );
					}
				}
			}
		}

		private void CleanArtistSyncFiles( List<string> FilePatterns )
		{
			foreach( string FilePattern in FilePatterns )
			{
				try
				{
					string FullPath = Path.GetFullPath( FilePattern );
					string Folder = Path.GetDirectoryName( FullPath );
					string FileSpec = Path.GetFileName( FullPath );

					DirectoryInfo DirInfo = new DirectoryInfo( Folder );
					if( DirInfo.Exists )
					{
						FileInfo[] FileInfos = DirInfo.GetFiles( FileSpec );
						foreach( FileInfo Info in FileInfos )
						{
							Info.IsReadOnly = false;
							Info.Delete();
						}
					}
				}
				catch
				{
				}
			}
		}

		private void SCC_CheckConsistency()
		{
			try
			{
				Builder.OpenLog( Builder.GetLogFileName( COMMANDS.SCC_CheckConsistency ), false );

				SCC.CheckConsistency( Builder, Builder.CurrentCommandLine );

				ErrorLevel = SCC.GetErrorLevel();
				Builder.CloseLog();
			}
			catch
			{
				ErrorLevel = COMMANDS.SCC_CheckConsistency;
				Builder.Write( "Error: exception while calling CheckConsistency" );
				Builder.CloseLog();
			}
		}

		private void SCC_Sync()
		{
			try
			{
				Builder.OpenLog( Builder.GetLogFileName( COMMANDS.SCC_Sync ), false );

				PrepareForSync();

				// Update database with head revision
				int HeadChangelist = SCC.GetLatestChangelist( Builder, "//" + Parent.MachineName + Builder.BranchDef.ClientSpec + "/" + Builder.BranchDef.Branch + "/..." );
				if( HeadChangelist > 0 )
				{
					BuilderLinq.UpdateBranchConfigInt( Builder.BranchDef.ID, "HeadChangelist", HeadChangelist );
				}

				// Find label to sync to
				Builder.SyncedLabel = Parent.GetLabelToSync();
				string LabelName = Builder.SyncedLabel.TrimStart( "@".ToCharArray() );

				if( Builder.LabelInfo.RevisionType == RevisionType.Label )
				{
					if( !SCC.GetLabelInfo( Builder, LabelName, null ) )
					{
						ErrorLevel = COMMANDS.SCC_Sync;
						Builder.Write( "P4ERROR: Sync - Non existent label, cannot sync to: " + LabelName );
						return;
					}
				}

				// Name of a build type that we wish to get the last good build from
				SCC.SyncToRevision( Builder, Builder.SyncedLabel, "/..." );

				// Don't get the list of changelists for CIS type builds or jobs
				if( Builder.LabelInfo.RevisionType == RevisionType.Label || Builder.LabelInfo.RevisionType == RevisionType.Head )
				{
					SCC.GetChangesSinceLastBuild( Builder );
				}

				ErrorLevel = SCC.GetErrorLevel();
				Builder.CloseLog();
			}
			catch
			{
				ErrorLevel = COMMANDS.SCC_Sync;
				Builder.Write( "Error: exception while calling sync" );
				Builder.CloseLog();
			}
		}

		private void SCC_SyncToHead()
		{
			try
			{
				Builder.OpenLog( Builder.GetLogFileName( COMMANDS.SCC_SyncToHead ), false );

				PrepareForSync();
				SCC.SyncToHead( Builder, Builder.CurrentCommandLine );

				ErrorLevel = SCC.GetErrorLevel();
				Builder.CloseLog();
			}
			catch
			{
				ErrorLevel = COMMANDS.SCC_SyncToHead;
				Builder.Write( "Error: exception while calling sync to head" );
				Builder.CloseLog();
			}
		}

		private void SCC_ArtistSync()
		{
			try
			{
				Builder.OpenLog( Builder.GetLogFileName( COMMANDS.SCC_ArtistSync ), false );

				if( Builder.LabelInfo.Game.Length == 0 )
				{
					Builder.Write( "ERROR: Must artist sync to a specific game!" );
				}
				else
				{
					PrepareForSync();

					// Name of a build type that we wish to get the last good build from
					Builder.SyncedLabel = Parent.GetLabelToSync();

					// Don't get the list of changelists for CIS type builds or jobs
					if( Builder.LabelInfo.RevisionType == RevisionType.Label )
					{
						// Hack the get changes to return all changes to #head
						Builder.LabelInfo.RevisionType = RevisionType.Head;
						SCC.GetChangesSinceLastBuild( Builder );
						Builder.LabelInfo.RevisionType = RevisionType.Label;
					}

					GameConfig Config = Builder.CreateGameConfig();
					SCC.SyncToHead( Builder, Config.GetArtistSyncRulesFileName() );

					ArtistSyncRules Rules = UnrealControls.XmlHandler.ReadXml<ArtistSyncRules>( Config.GetArtistSyncRulesFileName() );
					if( Rules.PromotionLabel.Length > 0 )
					{
						CleanArtistSyncFiles( Rules.FilesToClean );

						foreach( string SyncCommand in Rules.Rules )
						{
							if( SyncCommand.Contains( "%LABEL_TO_SYNC_TO%" ) )
							{
								SCC.SyncToRevision( Builder, Builder.SyncedLabel, SyncCommand.Replace( "%LABEL_TO_SYNC_TO%", "" ) );
							}
							else
							{
								SCC.SyncToRevision( Builder, "#head", SyncCommand );
							}
						}
					}
				}

				ErrorLevel = SCC.GetErrorLevel();
				Builder.CloseLog();
			}
			catch
			{
				ErrorLevel = COMMANDS.SCC_ArtistSync;
				Builder.Write( "Error: exception while calling artist sync" );
				Builder.CloseLog();
			}
		}

		private void SCC_GetChanges()
		{
			try
			{
				Builder.OpenLog( Builder.GetLogFileName( COMMANDS.SCC_GetChanges ), false );

				// Name of a build type that we wish to get the last good build from
				Builder.SyncedLabel = Parent.GetLabelToSync();

				SCC.GetChangesSinceLastBuild( Builder );

				ErrorLevel = SCC.GetErrorLevel();
				Builder.CloseLog();
			}
			catch
			{
				ErrorLevel = COMMANDS.SCC_GetChanges;
				Builder.Write( "Error: exception while getting user changes" );
				Builder.CloseLog();
			}
		}

		private void SCC_SyncSingleChangeList()
		{
			try
			{
				Builder.OpenLog( Builder.GetLogFileName( COMMANDS.SCC_SyncSingleChangeList ), false );

				PrepareForSync();

				// Name of a build type that we wish to get the last good build from
				SCC.SyncSingleChangeList( Builder );

				ErrorLevel = SCC.GetErrorLevel();
				Builder.CloseLog();
			}
			catch
			{
				ErrorLevel = COMMANDS.SCC_SyncSingleChangeList;
				Builder.Write( "Error: exception while calling sync single changelist" );
				Builder.CloseLog();
			}
		}

		private void SCC_Checkout()
		{
			try
			{
				Builder.OpenLog( Builder.GetLogFileName( COMMANDS.SCC_Checkout ), false );

				SCC.CheckoutFileSpec( Builder, Builder.CurrentCommandLine );

				ErrorLevel = SCC.GetErrorLevel();
				Builder.CloseLog();
			}
			catch
			{
				ErrorLevel = COMMANDS.SCC_Checkout;
				Builder.Write( "Error: exception while calling checkout" );
				Builder.CloseLog();
			}
		}

		private void SCC_OpenForDelete()
		{
			try
			{
				Builder.OpenLog( Builder.GetLogFileName( COMMANDS.SCC_OpenForDelete ), false );

				SCC.OpenForDeleteFileSpec( Builder, Builder.CurrentCommandLine );

				ErrorLevel = SCC.GetErrorLevel();
				Builder.CloseLog();
			}
			catch
			{
				ErrorLevel = COMMANDS.SCC_OpenForDelete;
				Builder.Write( "Error: exception while calling open for delete" );
				Builder.CloseLog();
			}
		}

		private void SCC_CheckoutGameFiles( GameConfig Config, bool CheckoutConfig )
		{
			List<string> Executables = Config.GetExecutableNames( Builder.BranchDef.Version );
			foreach( string Executable in Executables )
			{
				SCC.CheckoutFileSpec( Builder, Executable );
			}

			List<string> SymbolFiles = Config.GetSymbolFileNames( Builder.BranchDef.Version );
			foreach( string SymbolFile in SymbolFiles )
			{
				SCC.CheckoutFileSpec( Builder, SymbolFile );
			}

			if( CheckoutConfig )
			{
				string CfgFileName = Config.GetCfgName( Builder.BranchDef.Version );
				SCC.CheckoutFileSpec( Builder, CfgFileName );
			}

			List<string> FilesToClean = Config.GetFilesToClean( Builder.BranchDef.Version );
			foreach( string FileToClean in FilesToClean )
			{
				try
				{
					File.Delete( FileToClean );
				}
				catch
				{
					Parent.SendWarningMail( "Failed to delete", FileToClean, false );
				}
			}
		}

		private void SCC_CheckoutDLC()
		{
			try
			{
				Builder.OpenLog( Builder.GetLogFileName( COMMANDS.SCC_CheckoutDLC ), false );

				string[] Parms = Builder.SplitCommandline();
				if( Parms.Length != 1 )
				{
					Builder.Write( "Error: incorrect number of parameters for CheckoutDLC <DLCName>." );
				}
				else
				{
					GameConfig Config = Builder.CreateGameConfig();
					string DLCFileName = Config.GetDLCFileName( Parms[0] );

					SCC.CheckoutFileSpec( Builder, DLCFileName );
				}

				ErrorLevel = SCC.GetErrorLevel();
				Builder.CloseLog();
			}
			catch
			{
				ErrorLevel = COMMANDS.SCC_CheckoutDLC;
				Builder.Write( "Error: exception while calling checkout DLC." );
				Builder.CloseLog();
			}
		}

		private void SCC_GenericCheckout( COMMANDS CheckoutType )
		{
			try
			{
				Builder.OpenLog( Builder.GetLogFileName( CheckoutType ), false );

				GameConfig Config = null;
				switch( CheckoutType )
				{
				case COMMANDS.SCC_CheckoutGame:
					Config = Builder.AddCheckedOutGame();
					SCC_CheckoutGameFiles( Config, false );
					break;

				case COMMANDS.SCC_CheckoutGFWLGame:
					Config = Builder.AddCheckedOutGame();
					SCC_CheckoutGameFiles( Config, true );
					break;

				case COMMANDS.SCC_CheckoutGADCheckpoint:
					Config = Builder.CreateGameConfig();
					string FileName = Config.GetGADCheckpointFileName();
					SCC.CheckoutFileSpec( Builder, FileName );
					break;

				case COMMANDS.SCC_CheckoutLayout:
					Config = Builder.CreateGameConfig();
					string LayoutFileName = Config.GetLayoutFileName( Builder.SkuName, Builder.GetLanguages().ToArray(), Builder.GetTextLanguages().ToArray() );
					SCC.CheckoutFileSpec( Builder, LayoutFileName );
					break;

				case COMMANDS.SCC_CheckoutHashes:
					Config = Builder.CreateGameConfig();
					string HashesFileName = Config.GetHashesFileName();
					SCC.CheckoutFileSpec( Builder, HashesFileName );
					break;

				case COMMANDS.SCC_CheckoutEngineContent:
					string EngineContentSpec = "Engine/Content/....upk";
					SCC.CheckoutFileSpec( Builder, EngineContentSpec );
					break;

				case COMMANDS.SCC_CheckoutGameContent:
					Config = Builder.CreateGameConfig();
					string GameContentSpec = Config.GetContentSpec();
					SCC.CheckoutFileSpec( Builder, GameContentSpec );
					break;

				case COMMANDS.SCC_CheckoutAFTScreenshots:
					Config = Builder.CreateGameConfig();
					string AFTReferenceFolder = Config.GetAFTReferenceFolder( "DevKit", Builder.AFTTestMap );
					SCC.CheckoutFileSpec( Builder, AFTReferenceFolder + "/*.png" );
					break;

				case COMMANDS.SCC_CheckoutConnCache:
					Config = Builder.CreateGameConfig();
					string ConnCacheName = Config.GetConnCacheName();
					SCC.CheckoutFileSpec( Builder, ConnCacheName );
					break;

				case COMMANDS.SCC_CheckoutShader:
					Config = Builder.CreateGameConfig();
					string ShaderFile = Config.GetRefShaderName();
					SCC.CheckoutFileSpec( Builder, ShaderFile );
					break;
				}

				ErrorLevel = SCC.GetErrorLevel();
				Builder.CloseLog();
			}
			catch
			{
				ErrorLevel = CheckoutType;
				Builder.Write( "Error: exception while calling generic checkout." );
				Builder.CloseLog();
			}
		}

		private void SCC_CheckoutDialog()
		{
			try
			{
				Builder.OpenLog( Builder.GetLogFileName( COMMANDS.SCC_CheckoutDialog ), false );

				string[] Parms = Builder.SplitCommandline();
				if( Parms.Length != 2 )
				{
					Builder.Write( "Error: not enough parameters for CheckoutDialog." );
				}
				else
				{
					GameConfig Config = Builder.CreateGameConfig( Parms[0] );
					Queue<string> Languages = Builder.GetLanguages();
					Queue<string> ValidLanguages = new Queue<string>();

					foreach( string Language in Languages )
					{
						string DialogFile = Config.GetDialogFileName( Builder.DLCName, Language, Parms[1] );
						if( SCC.CheckoutFileSpec( Builder, DialogFile ) )
						{
							ValidLanguages.Enqueue( Language );
						}
					}

					Builder.SetValidLanguages( ValidLanguages );
				}

				// Some files are allowed to not exist (and fail checkout)
				ErrorLevel = COMMANDS.None;
				Builder.CloseLog();
			}
			catch
			{
				ErrorLevel = COMMANDS.SCC_CheckoutDialog;
				Builder.Write( "Error: exception while calling checkout dialog" );
				Builder.CloseLog();
			}
		}

		private void SCC_CheckoutFonts()
		{
			try
			{
				Builder.OpenLog( Builder.GetLogFileName( COMMANDS.SCC_CheckoutFonts ), false );

				string[] Parms = Builder.SplitCommandline();
				if( Parms.Length != 2 )
				{
					Builder.Write( "Error: not enough parameters for CheckoutFonts" );
				}
				else
				{
					GameConfig Config = Builder.CreateGameConfig( Parms[0] );
					Queue<string> Languages = Builder.GetLanguages();
					Queue<string> ValidLanguages = new Queue<string>();

					foreach( string Language in Languages )
					{
						string FontFile = Config.GetFontFileName( Language, Parms[1] );
						if( SCC.CheckoutFileSpec( Builder, FontFile ) )
						{
							ValidLanguages.Enqueue( Language );
						}
					}

					Builder.SetValidLanguages( ValidLanguages );
				}

				// Some files are allowed to not exist (and fail checkout)
				ErrorLevel = COMMANDS.None;
				Builder.CloseLog();
			}
			catch
			{
				ErrorLevel = COMMANDS.SCC_CheckoutFonts;
				Builder.Write( "Error: exception while calling checkout dialog" );
				Builder.CloseLog();
			}
		}

		private void SCC_CheckoutLocPackage()
		{
			try
			{
				Builder.OpenLog( Builder.GetLogFileName( COMMANDS.SCC_CheckoutLocPackage ), false );

				string[] Parms = Builder.SplitCommandline();
				if( Parms.Length != 1 )
				{
					Builder.Write( "Error: not enough parameters for CheckoutLocPackage" );
				}
				else
				{
					GameConfig Config = Builder.CreateGameConfig( "Example" );
					Queue<string> Languages = Builder.GetLanguages();
					Queue<string> ValidLanguages = new Queue<string>();

					foreach( string Language in Languages )
					{
						string PackageFile = Config.GetPackageFileName( Language, Parms[0] );
						if( SCC.CheckoutFileSpec( Builder, PackageFile ) )
						{
							ValidLanguages.Enqueue( Language );
						}
					}

					Builder.SetValidLanguages( ValidLanguages );
				}

				// Some files are allowed to not exist (and fail checkout)
				ErrorLevel = COMMANDS.None;
				Builder.CloseLog();
			}
			catch
			{
				ErrorLevel = COMMANDS.SCC_CheckoutFonts;
				Builder.Write( "Error: exception while calling checkout dialog" );
				Builder.CloseLog();
			}
		}

		private void SCC_CheckoutGDF()
		{
			try
			{
				Builder.OpenLog( Builder.GetLogFileName( COMMANDS.SCC_CheckoutGDF ), false );

				string[] Parms = Builder.SplitCommandline();
				if( Parms.Length != 2 )
				{
					Builder.Write( "Error: incorrect number of parameters for CheckoutGDF" );
					ErrorLevel = COMMANDS.SCC_CheckoutGDF;
				}
				else
				{
					Queue<string> Languages = Builder.GetLanguages();

					foreach( string Lang in Languages )
					{
						string GDFFileName = Parms[1] + "/" + Lang.ToUpper() + "/" + Parms[0] + "Game.gdf.xml";
						SCC.CheckoutFileSpec( Builder, GDFFileName );
					}
				}

				// Some files are allowed to not exist (and fail checkout)
				ErrorLevel = COMMANDS.None;
				Builder.CloseLog();
			}
			catch
			{
				ErrorLevel = COMMANDS.SCC_CheckoutGDF;
				Builder.Write( "Error: exception while calling checkout GDF" );
				Builder.CloseLog();
			}
		}

		private void SCC_CheckoutCat()
		{
			try
			{
				Builder.OpenLog( Builder.GetLogFileName( COMMANDS.SCC_CheckoutCat ), false );

				string[] Parms = Builder.SplitCommandline();
				if( Parms.Length != 1 )
				{
					Builder.Write( "Error: not enough parameters for CheckoutCat" );
				}
				else
				{
					GameConfig Config = Builder.CreateGameConfig( Parms[0] );

					List<string> CatNames = Config.GetCatNames( Builder.BranchDef.Version );
					foreach( string CatName in CatNames )
					{
						SCC.CheckoutFileSpec( Builder, CatName );
					}
				}

				ErrorLevel = COMMANDS.None;
				Builder.CloseLog();
			}
			catch
			{
				ErrorLevel = COMMANDS.SCC_CheckoutCat;
				Builder.Write( "Error: exception while calling checkoutcat" );
				Builder.CloseLog();
			}
		}

		private void SCC_GetNextChangelist()
		{
			try
			{
				Builder.OpenLog( Builder.GetLogFileName( COMMANDS.SCC_GetNextChangelist ), false );

				if( Builder.CurrentCommandLine.Length == 0 )
				{
					Builder.LabelInfo.Changelist = SCC.GetNextChangelist( Builder, "//" + Parent.MachineName + Builder.BranchDef.ClientSpec + "/" + Builder.BranchDef.Branch + "/..." );
				}
				else
				{
					Builder.LabelInfo.Changelist = SCC.GetNextChangelist( Builder, "//" + Parent.MachineName + Builder.BranchDef.ClientSpec + "/" + Builder.BranchDef.Branch + "/" + Builder.CurrentCommandLine );
				}

				if( Builder.LabelInfo.Changelist > 0 )
				{
					Builder.LabelInfo.RevisionType = RevisionType.ChangeList;
				}

				Builder.CloseLog();
			}
			catch
			{
				ErrorLevel = COMMANDS.SCC_GetNextChangelist;
				Builder.Write( "Error: exception getting the next changelist" );
				Builder.CloseLog();
			}
		}

		private void SCC_Submit()
		{
			try
			{
				Builder.OpenLog( Builder.GetLogFileName( COMMANDS.SCC_Submit ), false );
				SCC.Submit( Builder, false );

				ErrorLevel = SCC.GetErrorLevel();
				if( ErrorLevel == COMMANDS.SCC_Submit )
				{
					// Interrogate P4 and resolve any conflicts
					List<string> FilesNotAtHeadRevision = SCC.AutoResolveFiles( Builder );

					ErrorLevel = SCC.GetErrorLevel();
					if( ErrorLevel == COMMANDS.None )
					{
						SCC.Submit( Builder, true );
						ErrorLevel = SCC.GetErrorLevel();

						// If everything submitted properly and we're protecting the (previous) head revision
						if( ErrorLevel == COMMANDS.None &&
							Builder.IsRestoringNewerChanges &&
							FilesNotAtHeadRevision.Count > 0 )
						{
							foreach( string NextFileToRestore in FilesNotAtHeadRevision )
							{
								// Back out the (just checked in) head revision and then check in the
								// previous one, restoring the newer changes that were at head
								SCC.BackOutHeadRevision( Builder, NextFileToRestore );
							}
							SCC.Submit( Builder, true );
							ErrorLevel = SCC.GetErrorLevel();
						}
					}
				}

				Builder.CloseLog();
			}
			catch
			{
				ErrorLevel = COMMANDS.SCC_Submit;
				Builder.Write( "Error: exception while calling submit" );
				Builder.CloseLog();
			}
		}

		private void SCC_CreateNewLabel()
		{
			try
			{
				Builder.OpenLog( Builder.GetLogFileName( COMMANDS.SCC_CreateNewLabel ), false );

				SCC.CreateNewLabel( Builder );
				Builder.Dependency = Builder.LabelInfo.GetLabelName();

				ErrorLevel = SCC.GetErrorLevel();
				Builder.CloseLog();
			}
			catch
			{
				ErrorLevel = COMMANDS.SCC_LabelCreateNew;
				Builder.Write( "Error: exception while creating a new Perforce label" );
				Builder.CloseLog();
			}
		}

		private void SCC_LabelUpdateDescription()
		{
			try
			{
				Builder.OpenLog( Builder.GetLogFileName( COMMANDS.SCC_LabelUpdateDescription ), false );

				SCC.UpdateLabelDescription( Builder );

				ErrorLevel = SCC.GetErrorLevel();
				Builder.CloseLog();
			}
			catch
			{
				ErrorLevel = COMMANDS.SCC_LabelUpdateDescription;
				Builder.Write( "Error: exception while updating a Perforce label" );
				Builder.CloseLog();
			}
		}

		private void SCC_Revert()
		{
			try
			{
				Builder.OpenLog( Builder.GetLogFileName( COMMANDS.SCC_Revert ), false );

				SCC.DeleteEmptyChangelists( Builder );

				SCC.Revert( Builder, "..." );

				ErrorLevel = SCC.GetErrorLevel();
				Builder.CloseLog();
			}
			catch
			{
				ErrorLevel = COMMANDS.SCC_Revert;
				Builder.Write( "Error: exception while calling revert" );
				Builder.CloseLog();
			}
		}

		private void SCC_RevertFileSpec()
		{
			try
			{
				Builder.OpenLog( Builder.GetLogFileName( COMMANDS.SCC_RevertFileSpec ), false );

				Parent.Log( "[STATUS] Reverting: '" + Builder.CurrentCommandLine + "'", Color.Magenta );
				SCC.Revert( Builder, Builder.CurrentCommandLine );

				ErrorLevel = SCC.GetErrorLevel();
				Builder.CloseLog();
			}
			catch
			{
				ErrorLevel = COMMANDS.SCC_RevertFileSpec;
				Builder.Write( "Error: exception while calling revert" );
				Builder.CloseLog();
			}
		}

		private void SCC_Tag()
		{
			try
			{
				Builder.OpenLog( Builder.GetLogFileName( COMMANDS.SCC_Tag ), false );

				SCC.Tag( Builder );

				ErrorLevel = SCC.GetErrorLevel();
				Builder.CloseLog();
			}
			catch
			{
				ErrorLevel = COMMANDS.SCC_Tag;
				Builder.Write( "Error: exception while tagging build" );
				Builder.CloseLog();
			}
		}

		private void AddSimpleJob( string Command, string Parameter )
		{
			JobInfo Job = new JobInfo();

			Job.Name = "Job";
			if( Builder.LabelInfo.Game.Length > 0 )
			{
				Job.Name += "_" + Builder.LabelInfo.Game;
			}
			if( Builder.LabelInfo.Platform.Length > 0 )
			{
				Job.Name += "_" + Builder.LabelInfo.Platform;
			}
			Job.Name += "_" + Builder.BuildConfiguration;

			Job.Command = Command;
			Job.Parameter = Parameter;

			Parent.AddJob( Job );

			Builder.Write( "Added Job: " + Job.Name );
		}

		private void AddUnrealGameJob()
		{
			try
			{
				Builder.OpenLog( Builder.GetLogFileName( COMMANDS.AddUnrealGameJob ), false );

				AddSimpleJob( "Jobs/UnrealGameJob", Builder.CurrentCommandLine );

				GameConfig Config = Builder.CreateGameConfig( false );
				Builder.LabelInfo.Games.Add( Config );

				Builder.CloseLog();
			}
			catch
			{
				ErrorLevel = COMMANDS.AddUnrealGameJob;
				Builder.Write( "Error: exception while adding a game job." );
				Builder.CloseLog();
			}
		}

		private void AddUnrealAgnosticJob()
		{
			try
			{
				Builder.OpenLog( Builder.GetLogFileName( COMMANDS.AddUnrealAgnosticJob ), false );

				AddSimpleJob( "Jobs/UnrealAgnosticJob", Builder.CurrentCommandLine );

				GameConfig Config = Builder.CreateGameConfig( false );
				Builder.LabelInfo.Games.Add( Config );

				Builder.CloseLog();
			}
			catch
			{
				ErrorLevel = COMMANDS.AddUnrealAgnosticJob;
				Builder.Write( "Error: exception while adding a game agnostic job." );
				Builder.CloseLog();
			}
		}

		private void AddUnrealFullGameJob()
		{
			try
			{
				Builder.OpenLog( Builder.GetLogFileName( COMMANDS.AddUnrealGameJob ), false );

				AddSimpleJob( "Jobs/UnrealFullGameJob", Builder.CurrentCommandLine );

				GameConfig Config = Builder.CreateGameConfig( false );
				Builder.LabelInfo.Games.Add( Config );

				Builder.CloseLog();
			}
			catch
			{
				ErrorLevel = COMMANDS.AddUnrealFullGameJob;
				Builder.Write( "Error: exception while adding a full game job." );
				Builder.CloseLog();
			}
		}

		private void AddUnrealGFWLGameJob()
		{
			try
			{
				Builder.OpenLog( Builder.GetLogFileName( COMMANDS.AddUnrealGFWLGameJob ), false );

				AddSimpleJob( "Jobs/UnrealGFWLGameJob", Builder.CurrentCommandLine );

				GameConfig Config = Builder.CreateGameConfig( false );
				Builder.LabelInfo.Games.Add( Config );

				Builder.CloseLog();
			}
			catch
			{
				ErrorLevel = COMMANDS.AddUnrealFullGameJob;
				Builder.Write( "Error: exception while adding a GFWL game job." );
				Builder.CloseLog();
			}
		}

		private void AddUnrealGFWLFullGameJob()
		{
			try
			{
				Builder.OpenLog( Builder.GetLogFileName( COMMANDS.AddUnrealGFWLFullGameJob ), false );

				AddSimpleJob( "Jobs/UnrealGFWLFullGameJob", Builder.CurrentCommandLine );

				GameConfig Config = Builder.CreateGameConfig( false );
				Builder.LabelInfo.Games.Add( Config );

				Builder.CloseLog();
			}
			catch
			{
				ErrorLevel = COMMANDS.AddUnrealGFWLFullGameJob;
				Builder.Write( "Error: exception while adding a GFWL full game job." );
				Builder.CloseLog();
			}
		}

		private void AddConformJob()
		{
			try
			{
				Builder.OpenLog( Builder.GetLogFileName( COMMANDS.AddConformJob ), false );

				AddSimpleJob( "Jobs/ConformJob", Builder.CurrentCommandLine );

				Builder.CloseLog();
			}
			catch
			{
				ErrorLevel = COMMANDS.AddConformJob;
				Builder.Write( "Error: exception while adding a conform job." );
				Builder.CloseLog();
			}
		}


		private string GetWorkingDirectory( string Path, ref string Solution )
		{
			string Directory = "";
			Solution = "";

			int Index = Path.LastIndexOf( '/' );
			if( Index >= 0 )
			{
				Directory = Path.Substring( 0, Index );
				Solution = Path.Substring( Index + 1, Path.Length - Index - 1 );
			}

			return ( Directory );
		}

		private string GetCWD( int BranchVersion )
		{
			if( BranchVersion >= 10 )
			{
				return "Engine/Source";
			}

			return "Development/Src";
		}

		private void BuildUBT( string DotNetVer )
		{
			try
			{
				Builder.OpenLog( Builder.GetLogFileName( COMMANDS.BuildUBT9 ), false );

				string MSBuildAppName = Environment.GetEnvironmentVariable( "FrameworkDir" ) + "/" + DotNetVer + "/MSBuild.exe";

				string CommandLine;
				if( Builder.BranchDef.Version >= 10 )
				{
					CommandLine = "../../Engine/Source/Programs/UnrealBuildTool/UnrealBuildTool.csproj /verbosity:normal /target:Rebuild /property:Configuration=\"Development\"";
				}
				else
				{
					CommandLine = "UnrealBuildTool/UnrealBuildTool.csproj /verbosity:normal /target:Rebuild /property:Configuration=\"Release\"";
				}
				CurrentBuild = new BuildProcess( Parent, Builder, MSBuildAppName, CommandLine, GetCWD( Builder.BranchDef.Version ), false );
				ErrorLevel = CurrentBuild.GetErrorLevel();

				StartTime = DateTime.UtcNow;
			}
			catch
			{
				ErrorLevel = COMMANDS.BuildUBT9;
				Builder.Write( "Error: exception while starting to build UnrealBuildTool (" + DotNetVer + ")" );
				Builder.CloseLog();
			}
		}

		private void MS_Build( COMMANDS Command )
		{
			try
			{
				Builder.OpenLog( Builder.GetLogFileName( Command ), false );

				// Use the version of MSBuild that matches the Visual Studio version we're building with
				string MSBuildAppName;
				if( Command == COMMANDS.MS9Build )
				{
					MSBuildAppName = Environment.GetEnvironmentVariable( "FrameworkDir" ) + "/v3.5/MSBuild.exe";
				}
				else if( Command == COMMANDS.MS10Build )
				{
					MSBuildAppName = Environment.GetEnvironmentVariable( "FrameworkDir" ) + "/v4.0.30319/MSBuild.exe";
				}
				else
				{
					throw new Exception( "Unsupported version of Visual Studio" );
				}

				Builder.HandleMSVCDefines();

				string CommandLine = "";
				string[] Parms = Builder.SplitCommandline();
				if( Parms.Length != 1 )
				{
					Builder.Write( "Error: incorrect number of parameters. Usage: MSBuild <Project>" );
					ErrorLevel = COMMANDS.MSBuild;
				}
				else
				{
					CommandLine = "\"" + Parms[0] + "\" /verbosity:normal /target:Rebuild /property:Configuration=\"" + Builder.BuildConfiguration + "\"";

					CurrentBuild = new BuildProcess( Parent, Builder, MSBuildAppName, CommandLine, GetCWD( Builder.BranchDef.Version ), false );
					ErrorLevel = CurrentBuild.GetErrorLevel();
				}

				StartTime = DateTime.UtcNow;
			}
			catch
			{
				ErrorLevel = COMMANDS.MSBuild;
				Builder.Write( "Error: exception while starting to build using MSBuild" );
				Builder.CloseLog();
			}
		}

		private void MSVC_Clean( COMMANDS Command, string AppName )
		{
			try
			{
				Builder.OpenLog( Builder.GetLogFileName( Command ), false );

				Builder.HandleMSVCDefines();

				string CommandLine = "";
				string[] Parms = Builder.SplitCommandline();
				if( Parms.Length < 1 || Parms.Length > 2 )
				{
					Builder.Write( "Error: incorrect number of parameters. Usage: MSVCClean <Solution> [Project]" );
					ErrorLevel = COMMANDS.MSVCClean;
				}
				else
				{
					GameConfig Config = Builder.CreateGameConfig();

					if( Parms.Length == 1 )
					{
						CommandLine = "\"" + Parms[0] + ".sln\" /clean \"" + Config.Configuration + "\"";
					}
					else if( Parms.Length == 2 )
					{
						CommandLine = "\"" + Parms[0] + ".sln\" /project \"" + Parms[1] + "\" /clean \"" + Config.Configuration + "\"";
					}

					CurrentBuild = new BuildProcess( Parent, Builder, AppName, CommandLine, "", false );
					ErrorLevel = CurrentBuild.GetErrorLevel();
				}

				StartTime = DateTime.UtcNow;
			}
			catch
			{
				ErrorLevel = COMMANDS.MSVCClean;
				Builder.Write( "Error: exception while starting to clean using devenv" );
				Builder.CloseLog();
			}
		}

		private void MSVC_Build( COMMANDS Command, string AppName )
		{
			try
			{
				Builder.OpenLog( Builder.GetLogFileName( Command ), false );

				Builder.HandleMSVCDefines();

				string CommandLine = "";
				string[] Parms = Builder.SplitCommandline();
				if( Parms.Length < 1 || Parms.Length > 2 )
				{
					Builder.Write( "Error: incorrect number of parameters. Usage: MSVCBuild <Solution> [Project]" );
					ErrorLevel = COMMANDS.MSVCBuild;
				}
				else
				{
					GameConfig Config = Builder.CreateGameConfig();

					if( Parms.Length == 1 )
					{
						CommandLine = "\"" + Parms[0] + ".sln\" /build \"" + Config.Configuration + "\"";
					}
					else if( Parms.Length == 2 )
					{
						CommandLine = "\"" + Parms[0] + ".sln\" /project \"" + Parms[1] + "\" /build \"" + Config.Configuration + "\"";
					}

					CurrentBuild = new BuildProcess( Parent, Builder, AppName, CommandLine, "", false );
					ErrorLevel = CurrentBuild.GetErrorLevel();
				}

				StartTime = DateTime.UtcNow;
			}
			catch
			{
				ErrorLevel = COMMANDS.MSVCBuild;
				Builder.Write( "Error: exception while starting to build using devenv" );
				Builder.CloseLog();
			}
		}

		private void MS_Deploy( COMMANDS Command )
		{
			try
			{
				Builder.OpenLog( Builder.GetLogFileName( Command ), false );

				// Use the version of MSBuild that matches the Visual Studio version we're building with
				string MSBuildAppName;
				if( Command == COMMANDS.MSVC9Deploy )
				{
					MSBuildAppName = Environment.GetEnvironmentVariable( "FrameworkDir" ) + "/v3.5/MSBuild.exe";
				}
				else if( Command == COMMANDS.MSVC10Deploy )
				{
					MSBuildAppName = Environment.GetEnvironmentVariable( "FrameworkDir" ) + "/v4.0.30319/MSBuild.exe";
				}
				else
				{
					throw new Exception( "Unsupported version of Visual Studio" );
				}

				Builder.HandleMSVCDefines();

				string CommandLine = "";
				string[] Params = Builder.CurrentCommandLine.Split( ",".ToCharArray() );
				if( Params.Length != 3 )
				{
					Builder.Write( "Error: incorrect number of parameters. Usage: MSVCDeploy SolutionName,ProjectName,PublishLocation" );
					ErrorLevel = COMMANDS.MSVCDeploy;
				}
				else
				{
					GameConfig Config = Builder.CreateGameConfig();

					CommandLine = String.Format( "/t:{1}:publish /v:normal /property:Configuration=\"{3}\";PublishDir=\"{2}\" {0}.sln",
						Params[0],
						Params[1],
						Params[2],
						Config.Configuration );

					CurrentBuild = new BuildProcess( Parent, Builder, MSBuildAppName, CommandLine, "", false );
					ErrorLevel = CurrentBuild.GetErrorLevel();
				}

				StartTime = DateTime.UtcNow;
			}
			catch( Exception Ex )
			{
				ErrorLevel = COMMANDS.MSVCDeploy;
				Builder.Write( "Error: exception while starting to publish using msbuild" );
				Builder.Write( "Error: " + Ex.ToString() );
				Builder.CloseLog();
			}
		}

		private void Unreal_Build( bool bAllowXGE )
		{
			try
			{
				Builder.OpenLog( Builder.GetLogFileName( COMMANDS.UnrealBuild ), false );

				string UBTConfigName = "Release";
				if( Builder.BranchDef.Version >= 10 )
				{
					UBTConfigName = "Development";
				}

				string Executable = "";
				if( Builder.BranchDef.Version >= 10 )
				{
					Executable = "Engine/Intermediate/BuildData/UnrealBuildTool/" + UBTConfigName + "/UnrealBuildTool.exe";
				}
				else
				{
					Executable = "Development/Intermediate/UnrealBuildTool/" + UBTConfigName + "/UnrealBuildTool.exe";
				}
				GameConfig Config = Builder.CreateGameConfig();

				string CommandLine = Config.GetUBTCommandLine( Builder.BranchDef.Version, Builder.CommandDetails.bIsPrimaryBuild, bAllowXGE, Builder.AllowPCH, Builder.SpecifyOutput );
				if( Builder.UnityStressTest )
				{
					CommandLine += " -StressTestUnity";
				}
				if( Builder.UnityDisable )
				{
					CommandLine += " -DisableUnity";
				}

				CommandLine += Builder.HandleUBTDefines();

				CurrentBuild = new BuildProcess( Parent, Builder, Executable, CommandLine, GetCWD( Builder.BranchDef.Version ), false );
				ErrorLevel = CurrentBuild.GetErrorLevel();

				StartTime = DateTime.UtcNow;
			}
			catch( Exception Ex )
			{
				ErrorLevel = COMMANDS.UnrealBuild;
				Builder.Write( "Error: exception while starting to build using UnrealBuildTool" );
				Builder.Write( "Error: " + Ex.ToString() );
				Builder.CloseLog();
			}
		}

		private void Shader_Clean()
		{
			try
			{
				string LogFileName = Builder.GetLogFileName( COMMANDS.ShaderClean );
				Builder.OpenLog( LogFileName, false );

				string ShaderName;
				FileInfo Info;

				GameConfig Config = Builder.CreateGameConfig();

				// Delete ref shader cache
				ShaderName = Config.GetRefShaderName();
				Builder.Write( " ... checking for: " + ShaderName );
				Info = new FileInfo( ShaderName );
				if( Info.Exists )
				{
					Info.IsReadOnly = false;
					Info.Delete();
					Builder.Write( " ...... deleted: " + ShaderName );
				}

				// Delete local shader cache
				ShaderName = Config.GetLocalShaderName();
				Builder.Write( " ... checking for: " + ShaderName );
				Info = new FileInfo( ShaderName );
				if( Info.Exists )
				{
					Info.IsReadOnly = false;
					Info.Delete();
					Builder.Write( " ...... deleted: " + ShaderName );
				}

				CleanIniFiles( Config );

				ErrorLevel = COMMANDS.None;
				Builder.CloseLog();
			}
			catch
			{
				ErrorLevel = COMMANDS.ShaderClean;
				Builder.Write( "Error: exception while starting to clean precompiled shaders" );
				Builder.CloseLog();
			}
		}

		private void Shader_Build()
		{
			try
			{
				string LogFileName = Builder.GetLogFileName( COMMANDS.ShaderBuild );
				Builder.OpenLog( LogFileName, false );

				GameConfig Config = Builder.CreateGameConfig();

				string CommandLine = "";
				string Executable = Config.GetComName( Builder.BranchDef.Version, ref CommandLine );
				if( Builder.CurrentCommandLine.Length > 0 )
				{
					string EncodedFoldername = Builder.GetFolderName();
					Executable = Config.GetUDKComName( Executable, Builder.BranchDef.Branch, EncodedFoldername, Builder.CurrentCommandLine );
				}

				string ShaderPlatform = Config.GetShaderPlatform( Builder.BranchDef.Version );
				CommandLine += "PrecompileShaders Platform=" + ShaderPlatform + " -RefCache -ALLOW_PARALLEL_PRECOMPILESHADERS " + CommonCommandLine;

				CurrentBuild = new BuildProcess( Parent, Builder, Executable, CommandLine, "", true );
				ErrorLevel = CurrentBuild.GetErrorLevel();

				StartTime = DateTime.UtcNow;
			}
			catch
			{
				ErrorLevel = COMMANDS.ShaderBuild;
				Builder.Write( "Error: exception while starting to build precompiled shaders" );
				Builder.CloseLog();
			}
		}

		private void LocalShader_Build()
		{
			try
			{
				string LogFileName = Builder.GetLogFileName( COMMANDS.LocalShaderBuild );
				Builder.OpenLog( LogFileName, false );

				GameConfig Config = Builder.CreateGameConfig();

				string CommandLine = "";
				string Executable = Config.GetComName( Builder.BranchDef.Version, ref CommandLine );
				if( Builder.CurrentCommandLine.Length > 0 )
				{
					string EncodedFoldername = Builder.GetFolderName();
					Executable = Config.GetUDKComName( Executable, Builder.BranchDef.Branch, EncodedFoldername, Builder.CurrentCommandLine );
				}

				string ShaderPlatform = Config.GetShaderPlatform( Builder.BranchDef.Version );

				CommandLine += "PrecompileShaders Platform=" + ShaderPlatform + " -SkipMaps " + CommonCommandLine;

				CurrentBuild = new BuildProcess( Parent, Builder, Executable, CommandLine, "", true );
				ErrorLevel = CurrentBuild.GetErrorLevel();

				StartTime = DateTime.UtcNow;
			}
			catch
			{
				ErrorLevel = COMMANDS.LocalShaderBuild;
				Builder.Write( "Error: exception while starting to build local precompiled shaders" );
				Builder.CloseLog();
			}
		}

		private void CookShader_Build()
		{
			try
			{
				string LogFileName = Builder.GetLogFileName( COMMANDS.CookShaderBuild );
				Builder.OpenLog( LogFileName, false );

				GameConfig Config = Builder.CreateGameConfig();

				string CommandLine = "";
				string Executable = Config.GetComName( Builder.BranchDef.Version, ref CommandLine );
				if( Builder.CurrentCommandLine.Length > 0 )
				{
					string EncodedFoldername = Builder.GetFolderName();
					Executable = Config.GetUDKComName( Executable, Builder.BranchDef.Branch, EncodedFoldername, Builder.CurrentCommandLine );
				}

				string ShaderPlatform = Config.GetShaderPlatform( Builder.BranchDef.Version );
				CommandLine += "PrecompileShaders Platform=" + ShaderPlatform + " -SkipMaps  -precook " + CommonCommandLine;

				CurrentBuild = new BuildProcess( Parent, Builder, Executable, CommandLine, "", true );
				ErrorLevel = CurrentBuild.GetErrorLevel();

				StartTime = DateTime.UtcNow;
			}
			catch
			{
				ErrorLevel = COMMANDS.CookShaderBuild;
				Builder.Write( "Error: exception while starting to build local precompiled shaders for cooking" );
				Builder.CloseLog();
			}
		}

		private void ConnectionBuild()
		{
			try
			{
				string LogFileName = Builder.GetLogFileName( COMMANDS.ConnectionBuild );
				Builder.OpenLog( LogFileName, false );

				GameConfig Config = Builder.CreateGameConfig();

				// Delete the local connection caches
				DeletePatternFromFolder( Builder.LabelInfo.Game + "Game\\Content", "LocalConnCache.upk", false );

				string CommandLine = "";
				string Executable = Config.GetComName( Builder.BranchDef.Version, ref CommandLine );
				CommandLine += "BuildRefConnCache " + CommonCommandLine;

				CurrentBuild = new BuildProcess( Parent, Builder, Executable, CommandLine, "", true );
				ErrorLevel = CurrentBuild.GetErrorLevel();

				StartTime = DateTime.UtcNow;
			}
			catch
			{
				ErrorLevel = COMMANDS.ConnectionBuild;
				Builder.Write( "Error: exception while starting to build connection cache." );
				Builder.CloseLog();
			}
		}

		private void PS3MakePatchBinary()
		{
			try
			{
				string LogFileName = Builder.GetLogFileName( COMMANDS.PS3MakePatchBinary );
				string[] Parameters = Builder.SplitCommandline();
				if( Parameters.Length != 2 )
				{
					ErrorLevel = COMMANDS.PS3MakePatchBinary;
				}
				else
				{
					string CommandLine = "/c make_fself_npdrm " + Parameters[0] + " " + Parameters[1] + "  > " + LogFileName + " 2>&1";

					CurrentBuild = new BuildProcess( Parent, Builder, CommandLine, "" );
					ErrorLevel = CurrentBuild.GetErrorLevel();
				}

				StartTime = DateTime.UtcNow;
			}
			catch
			{
				ErrorLevel = COMMANDS.PS3MakePatchBinary;
			}
		}

		private void PS3MakePatch()
		{
			try
			{
				Builder.OpenLog( Builder.GetLogFileName( COMMANDS.PS3MakePatch ), false );

				string[] Parameters = Builder.SplitCommandline();

				if( Parameters.Length != 2 )
				{
					ErrorLevel = COMMANDS.PS3MakePatch;
					Builder.Write( "Error: incorrect number of parameters" );
				}
				else
				{
					string Executable = "make_package_npdrm.exe";
					string CommandLine = "--patch " + Parameters[0] + " " + Parameters[1];

					GameConfig Config = Builder.CreateGameConfig();
					string WorkingDirectory = Config.GetPatchFolderName();

					CurrentBuild = new BuildProcess( Parent, Builder, Executable, CommandLine, WorkingDirectory, true );
					ErrorLevel = CurrentBuild.GetErrorLevel();
				}

				StartTime = DateTime.UtcNow;
			}
			catch
			{
				Builder.Write( "Error: exception while starting to make PS3 patch" );
				ErrorLevel = COMMANDS.PS3MakePatch;
			}
		}

		private void PS3MakeDLC()
		{
			try
			{
				Builder.OpenLog( Builder.GetLogFileName( COMMANDS.PS3MakeDLC ), false );

				string[] Parameters = Builder.SplitCommandline();

				if( Parameters.Length != 2 )
				{
					ErrorLevel = COMMANDS.PS3MakeDLC;
					Builder.Write( "Error: incorrect number of parameters (needs 2: the DLC directory and the region" );
				}
				else
				{
					// setup PS3Packager run
					string Executable = "Binaries/PS3/PS3Packager.exe";
					string DLCName = Parameters[0];
					string Region = Parameters[1];

					GameConfig Config = Builder.CreateGameConfig();
					string CommandLine = "DLC " + Config.GameName + " " + DLCName + " " + Region;

					// we can run from anywhere
					string WorkingDirectory = Environment.CurrentDirectory;

					CurrentBuild = new BuildProcess( Parent, Builder, Executable, CommandLine, WorkingDirectory, false );
					ErrorLevel = CurrentBuild.GetErrorLevel();
				}

				StartTime = DateTime.UtcNow;
			}
			catch
			{
				Builder.Write( "Error: exception while starting to make PS3 DLC" );
				ErrorLevel = COMMANDS.PS3MakeDLC;
			}
		}

		private void PS3MakeTU()
		{
			try
			{
				Builder.OpenLog( Builder.GetLogFileName( COMMANDS.PS3MakeTU ), false );

				string[] Parameters = Builder.SplitCommandline();

				if( Parameters.Length != 2 )
				{
					ErrorLevel = COMMANDS.PS3MakeTU;
					Builder.Write( "Error: incorrect number of parameters (needs 2: the TU directory name and the region" );
				}
				else
				{
					// setup PS3Packager run
					string Executable = "Binaries/PS3/PS3Packager.exe";
					string TUName = Parameters[0];
					string Region = Parameters[1];

					GameConfig Config = Builder.CreateGameConfig();
					string CommandLine = "PATCH " + Config.GameName + " " + TUName + " " + Region;

					// we can run from anywhere
					string WorkingDirectory = Environment.CurrentDirectory;

					CurrentBuild = new BuildProcess( Parent, Builder, Executable, CommandLine, WorkingDirectory, false );
					ErrorLevel = CurrentBuild.GetErrorLevel();
				}

				StartTime = DateTime.UtcNow;
			}
			catch
			{
				Builder.Write( "Error: exception while starting to make PS3 TU" );
				ErrorLevel = COMMANDS.PS3MakeTU;
			}
		}

		private void PCMakeTU()
		{
			try
			{
				Builder.OpenLog( Builder.GetLogFileName( COMMANDS.PCMakeTU ), false );

				string[] Parameters = Builder.SplitCommandline();

				if( Parameters.Length != 1 )
				{
					ErrorLevel = COMMANDS.PCMakeTU;
					Builder.Write( "Error: incorrect number of parameters (needs 1: the TU directory name" );
				}
				else
				{
					// setup PCPackager run
					string Executable = "Binaries/Win32/PCPackager.exe";
					string TUName = Parameters[0];

					GameConfig Config = Builder.CreateGameConfig();
					string CommandLine = Config.GameName + " " + TUName;

					// we can run from anywhere
					string WorkingDirectory = Environment.CurrentDirectory;

					CurrentBuild = new BuildProcess( Parent, Builder, Executable, CommandLine, WorkingDirectory, false );
					ErrorLevel = CurrentBuild.GetErrorLevel();
				}

				StartTime = DateTime.UtcNow;
			}
			catch
			{
				Builder.Write( "Error: exception while starting to make PC TU" );
				ErrorLevel = COMMANDS.PCMakeTU;
			}
		}

		private void PCPackageTU()
		{
			try
			{
				Builder.OpenLog( Builder.GetLogFileName( COMMANDS.PCPackageTU ), false );

				string[] Parameters = Builder.SplitCommandline();

				if( Parameters.Length != 1 )
				{
					ErrorLevel = COMMANDS.PCPackageTU;
					Builder.Write( "Error: incorrect number of parameters (needs 1: the TU directory name" );
				}
				else
				{
					string Executable = "cmd.exe";
					string TUName = Parameters[0];

					GameConfig Config = Builder.CreateGameConfig();
					string WorkingDirectory = Environment.CurrentDirectory + "/" + Config.GameName + "/Build/PCConsole";
					string CommandLine = "/c PackageTitleUpdate.bat " + TUName;

					CurrentBuild = new BuildProcess( Parent, Builder, Executable, CommandLine, WorkingDirectory, false );
					ErrorLevel = CurrentBuild.GetErrorLevel();
				}

				StartTime = DateTime.UtcNow;
			}
			catch
			{
				Builder.Write( "Error: exception while starting to package PC TU" );
				ErrorLevel = COMMANDS.PCPackageTU;
			}
		}

		private void PackageTU()
		{
			try
			{
				string LogFileName = Builder.GetLogFileName( COMMANDS.PackageTU );
				Builder.OpenLog( LogFileName, false );

				if( Builder.LabelInfo.BuildVersion.Build == 0 )
				{
					Builder.Write( "Error: while package title update." );
					Builder.Write( "Error: no engine version found; has BumpEngineVersion/GetEngineVersion been called?" );
					ErrorLevel = COMMANDS.PackageTU;
				}
				else
				{
					string[] Parameters = Builder.SplitCommandline();

					string Executable = "";
					switch( Builder.LabelInfo.Platform.ToLower() )
					{
					case "xbox360":
						Executable = "Binaries\\Xbox360\\XboxPackager.exe";
						break;
					default:
						break;
					}

					if( Executable.Length == 0 )
					{
						ErrorLevel = COMMANDS.PackageTU;
					}
					else
					{
						GameConfig Config = Builder.CreateGameConfig();

						string EngineVersion = Builder.LabelInfo.BuildVersion.Build.ToString();
						string CommandLine = Builder.LabelInfo.Game + " TU " + Parameters[0] + " /verbose /EngineVersion=" + EngineVersion + " /BuildConfig=" + Config.Configuration + Builder.GetPackageTUConfig();
						CurrentBuild = new BuildProcess( Parent, Builder, Executable, CommandLine, "", false );
						ErrorLevel = CurrentBuild.GetErrorLevel();
					}
				}

				StartTime = DateTime.UtcNow;
			}
			catch( Exception Ex )
			{
				ErrorLevel = COMMANDS.PackageTU;
				Builder.Write( "Error: exception while starting to PackageTU: " + Ex.Message );
				Builder.CloseLog();
			}
		}

		private void PackageDLC()
		{
			try
			{
				string LogFileName = Builder.GetLogFileName( COMMANDS.PackageDLC );
				Builder.OpenLog( LogFileName, false );

				string[] Parameters = Builder.SplitCommandline();

				string Executable = "";
				switch( Builder.LabelInfo.Platform.ToLower() )
				{
				case "xbox360":
					Executable = "Binaries\\Xbox360\\XboxPackager.exe";
					break;
				default:
					break;
				}

				if( Executable.Length == 0 )
				{
					ErrorLevel = COMMANDS.PackageDLC;
				}
				else
				{
					string CommandLine = Builder.LabelInfo.Game + " DLC " + Parameters[0] + " /verbose";
					CurrentBuild = new BuildProcess( Parent, Builder, Executable, CommandLine, "", false );
					ErrorLevel = CurrentBuild.GetErrorLevel();
				}

				StartTime = DateTime.UtcNow;
			}
			catch( Exception Ex )
			{
				ErrorLevel = COMMANDS.PackageDLC;
				Builder.Write( "Error: exception while starting to PackageDLC: " + Ex.Message );
				Builder.CloseLog();
			}
		}

		private void BuildScript( COMMANDS CommandID )
		{
			try
			{
				string LogFileName = Builder.GetLogFileName( CommandID );
				Builder.OpenLog( LogFileName, false );

				if( Builder.CurrentCommandLine.Length == 0 )
				{
					Builder.Write( "Error: missing required parameter. Usage: BuildScript <Game>." );
					ErrorLevel = CommandID;
				}
				else
				{
					GameConfig Config = Builder.CreateGameConfig( Builder.CurrentCommandLine );
					CleanIniFiles( Config );

					string CommandLine = "";
					string Executable = Config.GetComName( Builder.BranchDef.Version, ref CommandLine );
					CommandLine += "make";
					if( CommandID == COMMANDS.BuildScript )
					{
						CommandLine += " -full";
					}
					CommandLine += " -silentbuild -stripsource " + CommonCommandLine + " " + Builder.GetScriptConfiguration();
					if( !Builder.AllowSloppyScript )
					{
						CommandLine += " -warningsaserrors";
					}

					CurrentBuild = new BuildProcess( Parent, Builder, Executable, CommandLine, "", true );
					ErrorLevel = CurrentBuild.GetErrorLevel();
				}

				StartTime = DateTime.UtcNow;
			}
			catch
			{
				ErrorLevel = CommandID;
				Builder.Write( "Error: exception while starting to build script" );
				Builder.CloseLog();
			}
		}

		private void Commandlet()
		{
			try
			{
				string LogFileName = Builder.GetLogFileName( COMMANDS.Commandlet );
				Builder.OpenLog( LogFileName, false );

				string[] Parms = Builder.SplitCommandline();
				GameConfig Config = Builder.CreateGameConfig();

				string CommandLine = "";
				string Executable = Config.GetComName( Builder.BranchDef.Version, ref CommandLine );

				for( int i = 0; i < Parms.Length; i++ )
				{
					CommandLine += " " + Parms[i];
				}

				CommandLine += " " + CommonCommandLine + Builder.GetOptionalCommandletConfig();

				CurrentBuild = new BuildProcess( Parent, Builder, Executable, CommandLine, "", true );
				ErrorLevel = CurrentBuild.GetErrorLevel();

				StartTime = DateTime.UtcNow;
			}
			catch( Exception Ex )
			{
				ErrorLevel = COMMANDS.Commandlet;

				Builder.Write( "Error: Exception when executing commandlet" + Ex.ToString() );
				Builder.CloseLog();
			}
		}

		private void iPhonePackage()
		{
			try
			{
				string LogFileName = Builder.GetLogFileName( COMMANDS.iPhonePackage );
				Builder.OpenLog( LogFileName, false );

				GameConfig Config = Builder.CreateGameConfig();
				string PackageCommandLine = "PackageIPA " + Config.GameName + " " + Config.Configuration;

				string ExtraFlags = " -compress=best -strip";
				if( Builder.CurrentCommandLine.Length != 0 )
				{
					ExtraFlags += " " + Builder.CurrentCommandLine;
				}

				string CWD = "Binaries\\" + Config.Platform;
				string Executable = CWD + "\\iPhonePackager.exe";
				string CommandLine = PackageCommandLine + ExtraFlags;

				CurrentBuild = new BuildProcess( Parent, Builder, Executable, CommandLine, CWD, false );
				ErrorLevel = CurrentBuild.GetErrorLevel();

				StartTime = DateTime.UtcNow;
			}
			catch
			{
				ErrorLevel = COMMANDS.iPhonePackage;
				Builder.Write( "Error: exception while starting to package IPA" );
				Builder.CloseLog();
			}
		}

		private void DeleteLocalShaderCache( GameConfig Game )
		{
			string[] LocalShaderCaches = Game.GetLocalShaderNames();
			foreach( string LocalShaderCache in LocalShaderCaches )
			{
				Builder.Write( "Deleting: '" + Builder.BranchDef.Branch + "/" + LocalShaderCache + "'" );
				FileInfo LCSInfo = new FileInfo( LocalShaderCache );
				if( LCSInfo.Exists )
				{
					LCSInfo.IsReadOnly = false;
					LCSInfo.Delete();
					Builder.Write( " ... done" );
				}
			}
		}

		private void DeleteGlobalShaderCache( GameConfig Game )
		{
			string[] GlobalShaderCaches = Game.GetGlobalShaderNames();
			foreach( string GlobalShaderCache in GlobalShaderCaches )
			{
				Builder.Write( "Deleting: '" + Builder.BranchDef.Branch + "/" + GlobalShaderCache + "'" );
				FileInfo GCSInfo = new FileInfo( GlobalShaderCache );
				if( GCSInfo.Exists )
				{
					GCSInfo.IsReadOnly = false;
					GCSInfo.Delete();
					Builder.Write( " ... done" );
				}
			}
		}

		private bool DeletePatternFromFolder( string Folder, string Pattern, bool Recurse )
		{
			Builder.Write( "Attempting delete of '" + Pattern + "' from '" + Folder + "'" );
			try
			{
				DirectoryInfo DirInfo = new DirectoryInfo( Folder );
				if( DirInfo.Exists )
				{
					Builder.Write( "Deleting '" + Pattern + "' from: '" + Builder.BranchDef.Branch + "/" + Folder + "'" );
					FileInfo[] Files = DirInfo.GetFiles( Pattern );
					foreach( FileInfo File in Files )
					{
						if( File.Exists )
						{
							File.IsReadOnly = false;
							File.Delete();
						}
					}

					if( Recurse )
					{
						DirectoryInfo[] Dirs = DirInfo.GetDirectories();
						foreach( DirectoryInfo Dir in Dirs )
						{
							DeletePatternFromFolder( Dir.FullName, Pattern, Recurse );
						}
					}
				}
			}
			catch( Exception Ex )
			{
				Builder.Write( "Error: Exception when deleting pattern from folder: " + Ex.ToString() );
				return false;
			}

			return true;
		}

		private void PreHeat()
		{
			try
			{
				Builder.OpenLog( Builder.GetLogFileName( COMMANDS.PreHeatMapOven ), false );

				if( Builder.CurrentCommandLine.Length > 0 )
				{
					Builder.Write( "Error: too many parameters. Usage: PreheatMapOven." );
					ErrorLevel = COMMANDS.PreHeatMapOven;
				}
				else if( Builder.LabelInfo.Game.Length == 0 )
				{
					Builder.Write( "Error: no game defined for PreheatMapOven." );
					ErrorLevel = COMMANDS.PreHeatMapOven;
				}
				else
				{
					// Create a game config to interrogate
					GameConfig Config = Builder.CreateGameConfig();

					// Delete the cooked folder to start from scratch
					string CookedFolder = Config.GetCookedFolderName( Builder.BranchDef.Version );
					Builder.Write( "Deleting: '" + Builder.BranchDef.Branch + "/" + CookedFolder + "'" );
					if( Directory.Exists( CookedFolder ) )
					{
						Parent.DeleteDirectory( CookedFolder, 0 );
						Builder.Write( " ... done" );
					}

					// Delete any old wrangled content
					string CutdownPackagesFolder = Config.GetWrangledFolderName();
					Builder.Write( "Deleting: '" + Builder.BranchDef.Branch + "/" + CutdownPackagesFolder + "'" );
					if( Directory.Exists( CutdownPackagesFolder ) )
					{
						Parent.DeleteDirectory( CutdownPackagesFolder, 0 );
						Builder.Write( " ... done" );
					}

					// Delete the config folder to start from scratch
					string ConfigFolder = Config.GetCookedConfigFolderName( Builder.BranchDef.Version );
					Builder.Write( "Deleting: '" + Builder.BranchDef.Branch + "/" + ConfigFolder + "'" );
					if( Directory.Exists( ConfigFolder ) )
					{
						Parent.DeleteDirectory( ConfigFolder, 0 );
						Builder.Write( " ... done" );
					}

					// Delete any screenshots
					DeletePatternFromFolder( Builder.LabelInfo.Game + "Game\\Screenshots", "*.bmp", false );
					DeletePatternFromFolder( Builder.LabelInfo.Game + "Game\\Screenshots", "*.png", false );

					// Delete the encrypted shaders
					string EncryptedShaderFolder = "Engine\\Shaders\\Binaries";
					Builder.Write( "Deleting: '" + Builder.BranchDef.Branch + "/" + EncryptedShaderFolder + "'" );
					if( Directory.Exists( EncryptedShaderFolder ) )
					{
						Parent.DeleteDirectory( EncryptedShaderFolder, 0 );
						Builder.Write( " ... done" );
					}

					// Delete any map summary data
					string MapSummaryFolder = Config.GetDMSFolderName();
					Builder.Write( "Deleting: '" + Builder.BranchDef.Branch + "/" + MapSummaryFolder + "'" );
					if( Directory.Exists( MapSummaryFolder ) )
					{
						Parent.DeleteDirectory( MapSummaryFolder, 0 );
						Builder.Write( " ... done" );
					}

					// Delete any map patch work files
					string PatchWorkFolder = Config.GetPatchesFolderName();
					Builder.Write( "Deleting: '" + Builder.BranchDef.Branch + "/" + PatchWorkFolder + "'" );
					if( Directory.Exists( PatchWorkFolder ) )
					{
						Parent.DeleteDirectory( PatchWorkFolder, 0 );
						Builder.Write( " ... done" );
					}

					// Delete any generated mobile shaders/keys
					string MobileShadersFolder = Config.GetMobileShadersFolderName();
					Builder.Write( "Deleting: '" + Builder.BranchDef.Branch + "/" + MobileShadersFolder + "'" );
					if( Directory.Exists( MobileShadersFolder ) )
					{
						Parent.DeleteDirectory( MobileShadersFolder, 0 );
						Builder.Write( " ... done" );
					}

					// Delete any ZDPP files
					string ZDP32Redist = "Binaries\\Win32\\Zdp";
					Builder.Write( "Deleting: '" + Builder.BranchDef.Branch + "/" + ZDP32Redist + "'" );
					if( Directory.Exists( ZDP32Redist ) )
					{
						Parent.DeleteDirectory( ZDP32Redist, 0 );
						Builder.Write( " ... done" );
					}

					string ZDP64Redist = "Binaries\\Win64\\Zdp";
					Builder.Write( "Deleting: '" + Builder.BranchDef.Branch + "/" + ZDP64Redist + "'" );
					if( Directory.Exists( ZDP64Redist ) )
					{
						Parent.DeleteDirectory( ZDP64Redist, 0 );
						Builder.Write( " ... done" );
					}

					string ZDP32SdkOutput = "Binaries\\Win32\\ZdpSdkOutput";
					Builder.Write( "Deleting: '" + Builder.BranchDef.Branch + "/" + ZDP32SdkOutput + "'" );
					if( Directory.Exists( ZDP32SdkOutput ) )
					{
						Parent.DeleteDirectory( ZDP32SdkOutput, 0 );
						Builder.Write( " ... done" );
					}

					string ZDP64SdkOutput = "Binaries\\Win64\\ZdpSdkOutput";
					Builder.Write( "Deleting: '" + Builder.BranchDef.Branch + "/" + ZDP64SdkOutput + "'" );
					if( Directory.Exists( ZDP64SdkOutput ) )
					{
						Parent.DeleteDirectory( ZDP64SdkOutput, 0 );
						Builder.Write( " ... done" );
					}

					DeletePatternFromFolder( "Binaries\\Win32", "*.zdp", false );
					DeletePatternFromFolder( "Binaries\\Win64", "*.zdp", false );

					// Delete any stale TOC files
					DeletePatternFromFolder( Builder.LabelInfo.Game + "Game", "*.txt", false );

					// Delete the config folder to start from scratch
					DeletePatternFromFolder( Builder.LabelInfo.Game + "Game/Localization", "Coalesced*", false );

					// Delete any leftover files from layout creation
					DeletePatternFromFolder( ".", "*.", false );
					DeletePatternFromFolder( ".", "default.xex", false );
					DeletePatternFromFolder( ".", "*.xdb", false );

					// Delete the local connection caches
					DeletePatternFromFolder( Builder.LabelInfo.Game + "Game\\Content", "LocalConnCache.upk", false );

					// Delete the local shader caches
					DeleteLocalShaderCache( Config );

					// Delete the local global caches
					DeleteGlobalShaderCache( Config );

					Builder.Write( "Deleting ini files" );
					CleanIniFiles( Config );

					Builder.ClearPublishDestinations();
				}

				Builder.CloseLog();
			}
			catch
			{
				ErrorLevel = COMMANDS.PreHeatMapOven;
				Builder.Write( "Error: exception while cleaning cooked data." );
				Builder.CloseLog();
			}
		}

		private void PreHeatDLC()
		{
			try
			{
				Builder.OpenLog( Builder.GetLogFileName( COMMANDS.PreHeatDLC ), false );

				Parent.Log( "PreHeating DLC directories for: " + Builder.DLCName, Color.Magenta );
				if( Builder.CurrentCommandLine.Length > 0 )
				{
					Builder.Write( "Error: too many parameters. Usage: PreheatDLC." );
					ErrorLevel = COMMANDS.PreHeatDLC;
				}
				else if( Builder.LabelInfo.Game.Length == 0 )
				{
					Builder.Write( "Error: no game defined for PreheatDLC." );
					ErrorLevel = COMMANDS.PreHeatDLC;
				}
				else if( Builder.DLCName.Length == 0 )
				{
					Builder.Write( "Error: no modname defined for PreheatDLC." );
					ErrorLevel = COMMANDS.PreHeatDLC;
				}
				else
				{
					// Create a game config to abstract the folder names
					GameConfig Config = Builder.CreateGameConfig();

					// Delete the DLC cooked folder to start from scratch
					string[] CookedFolders = Config.GetDLCCookedFolderNames( Builder.DLCName, Builder.BranchDef.Version );

					foreach( string CookedFolder in CookedFolders )
					{
						Builder.Write( "Deleting: '" + Builder.BranchDef.Branch + "/" + CookedFolder + "'" );
						if( Directory.Exists( CookedFolder ) )
						{
							Parent.DeleteDirectory( CookedFolder, 0 );
							Builder.Write( " ... done" );
						}
					}

					// Delete the created DLC file(s)
					string DLCFolder = Config.GetDLCFolderName( Builder.DLCName );
					DirectoryInfo DirInfo = new DirectoryInfo( DLCFolder );
					if( DirInfo.Exists )
					{
						foreach( FileInfo Info in DirInfo.GetFiles( "*." ) )
						{
							if( Info.Exists )
							{
								Info.IsReadOnly = false;
								Info.Delete();
							}
						}
					}
				}

				Builder.CloseLog();
			}
			catch
			{
				ErrorLevel = COMMANDS.PreHeatDLC;
				Builder.Write( "Error: exception while cleaning cooked DLC data." );
				Builder.CloseLog();
			}
		}

		// Recursively delete an entire directory tree
		private void PrintDirectory( string Path, int Level )
		{
			DirectoryInfo DirInfo = new DirectoryInfo( Path );
			if( DirInfo.Exists )
			{
				string Indent = "";
				for( int IndentLevel = 0; IndentLevel < Level; IndentLevel++ )
				{
					Indent += "    ";
				}
				Builder.Write( Indent + Path );

				DirectoryInfo[] Directories = DirInfo.GetDirectories();
				foreach( DirectoryInfo Directory in Directories )
				{
					PrintDirectory( Directory.FullName, Level + 1 );
				}

				Indent += "    ";
				FileInfo[] Files = DirInfo.GetFiles();
				foreach( FileInfo File in Files )
				{
					Builder.Write( Indent + File.Name );
				}
			}
		}

		private void PrintCurrentDriveStats( string LogicalDrive )
		{
			try
			{
				DriveInfo LogicalDriveInfo = new DriveInfo( LogicalDrive );
				Builder.Write( "    Drive " + LogicalDrive );
				Builder.Write( "        Total disk size : " + LogicalDriveInfo.TotalSize.ToString() );
				Builder.Write( "        Total free size : " + LogicalDriveInfo.AvailableFreeSpace.ToString() );
			}
			catch( System.Exception Ex )
			{
				Builder.Write( "        Error getting drive stats: " + Ex.Message );
			}
		}

		private void Clean()
		{
			Builder.OpenLog( Builder.GetLogFileName( COMMANDS.Clean ), false );

			string IntermediateFolder = "Development/Intermediate";
			if( Builder.BranchDef.Version >= 10 )
			{
				IntermediateFolder = "Engine/Intermediate/BuildData";
			}

			try
			{
				// Delete object and other compilation work files
				Builder.Write( "Deleting: '" + Builder.BranchDef.Branch + "/" + IntermediateFolder + "'" );

				if( Directory.Exists( IntermediateFolder ) )
				{
					// Log out some drive stats before and after the clean
					Builder.Write( "Drive stats before clean:" );
					PrintCurrentDriveStats( Directory.GetDirectoryRoot( IntermediateFolder ) );

					if( Parent.DeleteDirectory( IntermediateFolder, 0 ) )
					{
						Builder.Write( " ... done" );
					}
					else
					{
						ErrorLevel = COMMANDS.Clean;

						// Enumerate the contents of the directory for debugging
						Builder.Write( "Folder structure -" );
						PrintDirectory( IntermediateFolder, 0 );
					}

					Builder.Write( "Drive stats after clean:" );
					PrintCurrentDriveStats( Directory.GetDirectoryRoot( IntermediateFolder ) );
				}
			}
			catch( System.Exception Ex )
			{
				ErrorLevel = COMMANDS.Clean;
				Parent.Log( Ex.Message, Color.Red );
				Builder.Write( "Error: Exception while cleaning: '" + Ex.Message + "'" );
			}

			Builder.CloseLog();
		}

		private void CleanMac()
		{
			Builder.OpenLog( Builder.GetLogFileName( COMMANDS.CleanMac ), false );

			try
			{
				Builder.Write( "Cleaning remote iPhone/Mac build directories for Mac: " + Builder.CurrentCommandLine );

				FileInfo RPCUtilityInfo = new FileInfo( "Binaries/RPCUtility.exe" );
				if( !RPCUtilityInfo.Exists )
				{
					RPCUtilityInfo = new FileInfo( "Binaries/iPhone/RPCUtility.exe" );
				}

				if( RPCUtilityInfo.Exists )
				{
					string CommandLine = Builder.CurrentCommandLine + " / rm -rf /UnrealEngine3/Builds/" + Parent.MachineName;
					CurrentBuild = new BuildProcess( Parent, Builder, RPCUtilityInfo.FullName, CommandLine, "", true );
				}
				else
				{
					Builder.Write( "Error: Failed to find RPCUtility.exe" );
				}

				StartTime = DateTime.UtcNow;
			}
			catch( System.Exception Ex )
			{
				ErrorLevel = COMMANDS.CleanMac;
				Parent.Log( Ex.Message, Color.Red );
				Builder.Write( "Error: Exception while cleaning Mac up: '" + Ex.Message + "'" );
				Builder.CloseLog();
			}
		}

		private string GetMTCommand()
		{
			int NumProcesses = Parent.PhysicalMemory / 5;
			if( NumProcesses > 28 )
			{
				NumProcesses = 28;
			}
			return ( " -Processes=" + NumProcesses.ToString() );
		}

		private void Cook()
		{
			try
			{
				string LogFileName = Builder.GetLogFileName( COMMANDS.CookMaps );
				Builder.OpenLog( LogFileName, false );

				string[] Parms = Builder.SplitCommandline();
				GameConfig Config = Builder.CreateGameConfig();

				string CommandLine = "";
				string Executable = Config.GetComName( Builder.BranchDef.Version, ref CommandLine );
				CommandLine += "CookPackages -Platform=" + Config.GetCookedFolderPlatform();

				for( int i = 0; i < Parms.Length; i++ )
				{
					CommandLine += " " + Parms[i];
				}

				CommandLine += " " + CommonCommandLine;

				string Language = Builder.LabelInfo.Language;
				if( Language.Length == 0 )
				{
					Language = "INT";
				}

				CommandLine += " -LanguageForCooking=" + Language + Builder.GetCompressionConfiguration() + Builder.GetScriptConfiguration() + Builder.GetCookConfiguration();
				CommandLine += GetMTCommand();
				CommandLine += Builder.GetContentPath() + Builder.GetDLCName();

				CurrentBuild = new BuildProcess( Parent, Builder, Executable, CommandLine, "", true );
				ErrorLevel = CurrentBuild.GetErrorLevel();

				StartTime = DateTime.UtcNow;
			}
			catch
			{
				ErrorLevel = COMMANDS.CookMaps;
				Builder.Write( "Error: exception while starting to cook" );
				Builder.CloseLog();
			}
		}

		private void CookIniMaps()
		{
			try
			{
				string LogFileName = Builder.GetLogFileName( COMMANDS.CookIniMaps );
				Builder.OpenLog( LogFileName, false );

				GameConfig Config = Builder.CreateGameConfig();

				string CommandLine = "";
				string Executable = Config.GetComName( Builder.BranchDef.Version, ref CommandLine );
				CommandLine += "CookPackages -Platform=" + Config.GetCookedFolderPlatform();
				CommandLine += " -MapIniSection=" + Builder.CurrentCommandLine;
				CommandLine += " " + CommonCommandLine;

				Queue<string> Languages = Builder.GetLanguages();
				Queue<string> TextLanguages = Builder.GetTextLanguages();

				if( Languages.Count > 0 || TextLanguages.Count > 0 )
				{
					CommandLine += " -multilanguagecook=INT";
					foreach( string Language in Languages )
					{
						if( Language != "INT" )
						{
							CommandLine += "+" + Language;
						}
					}

					foreach( string Language in TextLanguages )
					{
						if( Language != "INT" )
						{
							CommandLine += "-" + Language;
						}
					}

					CommandLine += " -sha";
				}
				else
				{
					string Language = Builder.LabelInfo.Language;
					if( Language.Length == 0 )
					{
						Language = "INT";
					}

					CommandLine += " -LanguageForCooking=" + Language;
				}

				CommandLine += Builder.GetCompressionConfiguration() + Builder.GetScriptConfiguration() + Builder.GetCookConfiguration();
				CommandLine += GetMTCommand();
				CommandLine += Builder.GetContentPath() + Builder.GetDLCName();

				CurrentBuild = new BuildProcess( Parent, Builder, Executable, CommandLine, "", true );
				ErrorLevel = CurrentBuild.GetErrorLevel();

				StartTime = DateTime.UtcNow;
			}
			catch
			{
				ErrorLevel = COMMANDS.CookIniMaps;
				Builder.Write( "Error: exception while starting to cook from maps from ini" );
				Builder.CloseLog();
			}
		}

		private void CookSounds()
		{
			try
			{
				string LogFileName = Builder.GetLogFileName( COMMANDS.CookSounds );
				Builder.OpenLog( LogFileName, false );

				string[] Parms = Builder.SplitCommandline();
				if( Parms.Length != 1 )
				{
					Builder.Write( "Error: Incorrect number of parameters. Usage: " + COMMANDS.CookSounds.ToString() + " <Package>" );
					ErrorLevel = COMMANDS.CookSounds;
				}
				else
				{
					GameConfig Config = Builder.CreateGameConfig();

					string CommandLine = "";
					string Executable = Config.GetComName( Builder.BranchDef.Version, ref CommandLine );
					CommandLine += "ResavePackages -ResaveClass=SoundNodeWave -ForceSoundRecook";

					Queue<string> Languages = Builder.GetLanguages();
					foreach( string Language in Languages )
					{
						CommandLine += " -Package=" + Parms[0];
						if( Language.Length > 0 && Language != "INT" )
						{
							CommandLine += "_" + Language;
						}
					}

					CommandLine += " " + CommonCommandLine;

					CurrentBuild = new BuildProcess( Parent, Builder, Executable, CommandLine, "", true );
					ErrorLevel = CurrentBuild.GetErrorLevel();
				}

				StartTime = DateTime.UtcNow;
			}
			catch
			{
				ErrorLevel = COMMANDS.CookSounds;
				Builder.Write( "Error: exception while starting to cook sounds" );
				Builder.CloseLog();
			}
		}

		private void CreateHashes()
		{
			try
			{
				string LogFileName = Builder.GetLogFileName( COMMANDS.CreateHashes );
				Builder.OpenLog( LogFileName, false );

				GameConfig Config = Builder.CreateGameConfig();
				CleanIniFiles( Config );

				string CommandLine = "";
				string Executable = Config.GetComName( Builder.BranchDef.Version, ref CommandLine );
				CommandLine += "CookPackages -Platform=" + Config.GetCookedFolderPlatform();

				CommandLine += " -sha -inisonly " + CommonCommandLine;

				string Language = Builder.LabelInfo.Language;
				if( Language.Length == 0 )
				{
					Language = "INT";
				}
				CommandLine += " -LanguageForCooking=" + Language + Builder.GetScriptConfiguration();

				CurrentBuild = new BuildProcess( Parent, Builder, Executable, CommandLine, "", true );
				ErrorLevel = CurrentBuild.GetErrorLevel();

				StartTime = DateTime.UtcNow;
			}
			catch
			{
				ErrorLevel = COMMANDS.CreateHashes;
				Builder.Write( "Error: exception while starting to create hashes" );
				Builder.CloseLog();
			}
		}

		private void Wrangle()
		{
			try
			{
				string LogFileName = Builder.GetLogFileName( COMMANDS.Wrangle );
				Builder.OpenLog( LogFileName, false );

				string[] Parms = Builder.SplitCommandline();
				if( Parms.Length < 1 )
				{
					Builder.Write( "Error: too few parameters. Usage: Wrangle <section>." );
					ErrorLevel = COMMANDS.Wrangle;
				}
				else
				{
					GameConfig Config = Builder.CreateGameConfig();
					CleanIniFiles( Config );

					Builder.Write( "Deleting cutdown packages folder ... " );
					Config.DeleteCutdownPackages( Parent );
					Builder.Write( " ... cutdown packages folder deleted " );

					string CommandLine = "";
					string Executable = Config.GetComName( Builder.BranchDef.Version, ref CommandLine );
					CommandLine += "WrangleContent ";

					CommandLine += "SECTION=" + Parms[0] + " ";

					CommandLine += "-nosaveunreferenced ";

					if( Builder.KeepAssets.Length > 0 )
					{
						CommandLine += "-PlatformsToKeep=" + Builder.KeepAssets + " ";
					}

					if( Builder.StripSourceContent )
					{
						CommandLine += "-StripLargeEditorData ";
					}

					CommandLine += CommonCommandLine;

					CurrentBuild = new BuildProcess( Parent, Builder, Executable, CommandLine, "", true );
					ErrorLevel = CurrentBuild.GetErrorLevel();
				}

				StartTime = DateTime.UtcNow;
			}
			catch
			{
				ErrorLevel = COMMANDS.Wrangle;
				Builder.Write( "Error: exception while starting to wrangle" );
				Builder.CloseLog();
			}
		}

		private void Publish( COMMANDS Command, string Tagset, bool AddToReport, string AdditionalOptions )
		{
			try
			{
				Builder.OpenLog( Builder.GetLogFileName( Command ), false );

				string[] Parms = Builder.SplitCommandline();
				if( Parms.Length < 1 )
				{
					Builder.Write( "Error: too few parameters. Usage: " + Command.ToString() + " <Dest1> [Dest2...]" );
					ErrorLevel = Command;
				}
				else
				{
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
					CookerSyncCommandLine += " -crc -l";

					switch( Builder.PublishVerification )
					{
					case ScriptParser.PublishVerificationType.MD5:
					default:
						CookerSyncCommandLine += " -v";
						break;

					case ScriptParser.PublishVerificationType.None:
						break;
					}

					if( Builder.ForceCopy )
					{
						CookerSyncCommandLine += " -f";
					}
					CookerSyncCommandLine += AdditionalOptions;

					// Get the timestamped folder name with game and platform
					string DestFolder = "";
					if( Builder.IncludeTimestampFolder )
					{
						DestFolder = "\\" + Builder.GetFolderName();
					}

					// Set to publish to a zip file if requested
					switch( Builder.PublishMode )
					{
					case ScriptParser.PublishModeType.Zip:
						DestFolder += ".zip";
						break;

					case ScriptParser.PublishModeType.Iso:
						DestFolder += ".iso";
						break;

					default:
						// no extension by default - free files
						break;
					}

					// Add in all the destination paths
					for( int i = 0; i < Parms.Length; i++ )
					{
						string PublishFolder = Parms[i].Replace( '/', '\\' ) + DestFolder;
						CookerSyncCommandLine += " " + PublishFolder;
						if( AddToReport )
						{
							Builder.AddPublishDestination( PublishFolder );
						}
					}

					CurrentBuild = new BuildProcess( Parent, Builder, Executable, CookerSyncCommandLine, Environment.CurrentDirectory + "/Binaries", false );
					ErrorLevel = CurrentBuild.GetErrorLevel();
				}

				StartTime = DateTime.UtcNow;
			}
			catch
			{
				ErrorLevel = Command;
				Builder.Write( "Error: exception while starting to publish" );
				Builder.CloseLog();
			}
		}

		private void PublishTagset()
		{
			// Extract the tagset name
			string[] Parms = Builder.SplitCommandline();
			if( Parms.Length < 2 )
			{
				Builder.Write( "Error: too few parameters. Usage: " + COMMANDS.PublishTagset.ToString() + " <Tagset> <Dest1> [<Dest2>...]" );
				ErrorLevel = COMMANDS.PublishTagset;
			}
			else
			{
				string TagsetName = Parms[0];
				Builder.CurrentCommandLine = Builder.CurrentCommandLine.Substring( TagsetName.Length ).Trim();

				Publish( COMMANDS.PublishTagset, TagsetName, true, "" );
			}
		}

		private void Publish()
		{
			Publish( COMMANDS.Publish, "CompleteBuild", true, "" );
		}

		private void PublishLanguage()
		{
			Publish( COMMANDS.PublishLanguage, "Loc", false, "" );
		}

		private void PublishLayout()
		{
			Publish( COMMANDS.PublishLayout, "CompleteBuild", true, " -notoc" );
		}

		private void PublishLayoutLanguage()
		{
			Publish( COMMANDS.PublishLayout, "Loc", false, " -notoc" );
		}

		private void PublishDLC()
		{
			Publish( COMMANDS.PublishDLC, "DLC", true, "" );
		}

		private void PublishTU()
		{
			Publish( COMMANDS.PublishTU, "TU", true, "" );
		}

		private void PublishFiles()
		{
			try
			{
				string LogFileName = Builder.GetLogFileName( COMMANDS.PublishFiles );
				Builder.OpenLog( LogFileName, false );

				string[] Parms = Builder.SplitCommandline();
				if( Parms.Length < 2 )
				{
					Builder.Write( "Error: too few parameters. Usage: PublishFiles <Dest> [Src] <FilePatten>." );
					ErrorLevel = COMMANDS.PublishFiles;
				}
				else
				{
					string ActiveFolder = Builder.GetFolderName();
					string SourceFolder = ".\\";
					string PublishFolder = ".\\";
					string FilePattern = "";

					if( Parms.Length < 3 )
					{
						switch( Builder.PublishMode )
						{
						case ScriptParser.PublishModeType.Files:
							// Publish from local source control branch
							PublishFolder = Path.Combine( Parms[0], Path.Combine( ActiveFolder + "_Loose", Builder.BranchDef.Branch ) );
							FilePattern = Parms[1];
							break;

						case ScriptParser.PublishModeType.Zip:
						case ScriptParser.PublishModeType.Iso:
						case ScriptParser.PublishModeType.Xsf:
							// Publish from local source control branch
							PublishFolder = Parms[0];
							SourceFolder = Parms[1];
							FilePattern = ActiveFolder + "." + Builder.PublishMode.ToString();
							break;
						}
					}
					else
					{
						// Publish from alternate location if it is specified
						SourceFolder = Path.Combine( Parms[1], Path.Combine( ActiveFolder, Builder.BranchDef.Branch ) );
						PublishFolder = Path.Combine( Parms[0], Path.Combine( ActiveFolder + "_Install", Builder.BranchDef.Branch ) );
						FilePattern = Parms[2];
					}

					string CommandLine = SourceFolder;
					CommandLine += " ";
					CommandLine += PublishFolder;
					CommandLine += " ";
					CommandLine += FilePattern;
					CommandLine += " /S /COPY:DAT";

					CurrentBuild = new BuildProcess( Parent, Builder, "RoboCopy.exe", CommandLine, "", true );

					Builder.AddPublishDestination( PublishFolder );

					ErrorLevel = CurrentBuild.GetErrorLevel();
				}

				StartTime = DateTime.UtcNow;
			}
			catch
			{
				ErrorLevel = COMMANDS.PublishFiles;
				Builder.Write( "Error: exception while starting to publish files" );
				Builder.CloseLog();
			}
		}

		private void PublishRawFiles()
		{
			try
			{
				string LogFileName = Builder.GetLogFileName( COMMANDS.PublishRawFiles );
				Builder.OpenLog( LogFileName, false );

				string[] Parms = Builder.SplitCommandline();
				if( Parms.Length != 3 )
				{
					Builder.Write( "Error: incorrect number of parameters. Usage: PublishRawFiles <Dest> <Src> <FilePatten>." );
					ErrorLevel = COMMANDS.PublishRawFiles;
				}
				else
				{
					string ActiveFolder = Builder.GetFolderName();

					// Construct the folder or file name based on the image mode
					string SourceFolder = Parms[1];
					if( Builder.ImageMode == "" )
					{
						SourceFolder = Path.Combine( Parms[1], ActiveFolder );
					}

					string SubPath = Parms[2].Replace( '/', '\\' );
					int PathSeparatorIndex = SubPath.LastIndexOf( '\\' );
					string FilePattern = SubPath;
					if( PathSeparatorIndex > 0 )
					{
						SourceFolder = Path.Combine( SourceFolder, SubPath.Substring( 0, PathSeparatorIndex ) );
						FilePattern = SubPath.Substring( PathSeparatorIndex + 1 );
					}

					string PublishFolder = Path.Combine( Parms[0], ActiveFolder + "_Install" );

					string CommandLine = SourceFolder;
					CommandLine += " ";
					CommandLine += PublishFolder;
					CommandLine += " ";
					CommandLine += FilePattern;
					CommandLine += " /S /COPY:DAT";

					CurrentBuild = new BuildProcess( Parent, Builder, "RoboCopy.exe", CommandLine, "", true );

					Builder.AddPublishDestination( PublishFolder );

					ErrorLevel = CurrentBuild.GetErrorLevel();
				}

				StartTime = DateTime.UtcNow;
			}
			catch
			{
				ErrorLevel = COMMANDS.PublishRawFiles;
				Builder.Write( "Error: exception while starting to publish raw files" );
				Builder.CloseLog();
			}
		}

		private void GenerateTOC()
		{
			try
			{
				string LogFileName = Builder.GetLogFileName( COMMANDS.GenerateTOC );
				Builder.OpenLog( LogFileName, false );

				string Tagset = "CompleteBuild";
				string[] Parms = Builder.SplitCommandline();
				if( Parms.Length == 1 )
				{
					Tagset = Parms[0];
				}

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
				CookerSyncCommandLine += " -crc -l -nd";

				CurrentBuild = new BuildProcess( Parent, Builder, Executable, CookerSyncCommandLine, Environment.CurrentDirectory + "/Binaries", false );
				ErrorLevel = CurrentBuild.GetErrorLevel();

				StartTime = DateTime.UtcNow;
			}
			catch
			{
				ErrorLevel = COMMANDS.GenerateTOC;
				Builder.Write( "Error: exception while starting to make generate TOC file." );
				Builder.CloseLog();
			}
		}

		private void MakeISO()
		{
			try
			{
				string LogFileName = Builder.GetLogFileName( COMMANDS.MakeISO );
				Builder.OpenLog( LogFileName, false );

				string[] Parms = Builder.SplitCommandline();
				if( Parms.Length < 3 )
				{
					Builder.Write( "Error: incorrect number of parameters. Usage: MakeISO <Dest> <Src> <Subfolder> [<VolumeName>]." );
					ErrorLevel = COMMANDS.MakeISO;
				}
				else
				{
					string ActiveFolder = Builder.GetFolderName();

					// Publish from alternate location if it is specified
					string SourceFolder = Path.Combine( Parms[1], ActiveFolder );
					SourceFolder = Path.Combine( SourceFolder, Parms[2] );
					string PublishFile = Path.Combine( Parms[0], ActiveFolder + "." + Builder.ImageMode );

					string CommandLine = "-Source " + SourceFolder;
					CommandLine += " -Dest " + PublishFile;
					if( Parms.Length == 4 )
					{
						CommandLine += " -Volume " + Parms[3];
					}

					CurrentBuild = new BuildProcess( Parent, Builder, "Binaries\\MakeISO.exe", CommandLine, "", true );

					ErrorLevel = CurrentBuild.GetErrorLevel();
				}

				StartTime = DateTime.UtcNow;
			}
			catch
			{
				ErrorLevel = COMMANDS.MakeISO;
				Builder.Write( "Error: exception while starting to make an ISO." );
				Builder.CloseLog();
			}
		}

		private void MakeMD5()
		{
			try
			{
				string LogFileName = Builder.GetLogFileName( COMMANDS.MakeMD5 );
				Builder.OpenLog( LogFileName, false );

				string[] Parms = Builder.SplitCommandline();
				if( Parms.Length < 1 )
				{
					Builder.Write( "Error: too few parameters. Usage: MakeMD5 [Src] <FilePatten>." );
					ErrorLevel = COMMANDS.MakeMD5;
				}
				else
				{
					string ActiveFolder = Builder.GetFolderName();
					string SourceFolder = ".\\";
					string FilePattern = "";

					if( Parms.Length < 2 )
					{
						// Checksum from local source control branch
						FilePattern = Parms[0];
					}
					else
					{
						// Checksum from alternate location if it is specified
						SourceFolder = Path.Combine( Parms[0], Path.Combine( ActiveFolder, Builder.BranchDef.Branch ) );
						FilePattern = Parms[1];
					}

					MD5Creation Checksummer = new MD5Creation( Builder, SourceFolder );

					ErrorLevel = Checksummer.CalculateChecksums( FilePattern );
					if( ErrorLevel == COMMANDS.None )
					{
						ErrorLevel = Checksummer.WriteChecksumFile( "Checksums" );
					}
				}

				Builder.CloseLog();
			}
			catch
			{
				ErrorLevel = COMMANDS.MakeMD5;
				Builder.Write( "Error: exception while making MD5 checksum" );
				Builder.CloseLog();
			}
		}

		private void FolderOperation( COMMANDS Command, string Options )
		{
			try
			{
				string LogFileName = Builder.GetLogFileName( Command );
				Builder.OpenLog( LogFileName, false );

				string[] Parms = Builder.SplitCommandline();
				if( Parms.Length < 3 )
				{
					Builder.Write( "Error: too few parameters. Usage: " + Command.ToString() + " <RootFolder> <Src> <Dest> [filespec]." );
					ErrorLevel = Command;
				}
				else
				{
					// If RootFolder is ".", it's a simple local copy
					string SourceFolder = Parms[1];
					string DestFolder = Parms[2];

					// If it isn't, it's an out of branch copy
					if( Parms[0] != "." )
					{
						// UT_PC_[2000-00-00_00.00]
						string ActiveFolder = Builder.GetFolderName();

						// C:\Builds\UT_PC_[2000-00-00_00.00]\UnrealEngine3
						string RootFolder = Path.Combine( Parms[0], Path.Combine( ActiveFolder, Builder.BranchDef.Branch ) );

						// C:\Builds\UT_PC_[2000-00-00_00.00]\UnrealEngine3\UTGame\CutdownPackages\UTGame
						SourceFolder = Path.Combine( RootFolder, Parms[1] );
						// C:\Builds\UT_PC_[2000-00-00_00.00]\UnrealEngine3\UTGame
						DestFolder = Path.Combine( RootFolder, Parms[2] );
					}

					string CommandLine = SourceFolder;
					CommandLine += " ";
					CommandLine += DestFolder;
					if( Parms.Length > 3 )
					{
						for( int Index = 3; Index < Parms.Length; Index++ )
						{
							CommandLine += " " + Parms[Index];
						}
					}
					else
					{
						CommandLine += " *.*";
					}

					CommandLine += " " + Options;

					CurrentBuild = new BuildProcess( Parent, Builder, "RoboCopy.exe", CommandLine, "", true );

					ErrorLevel = CurrentBuild.GetErrorLevel();
				}

				StartTime = DateTime.UtcNow;
			}
			catch
			{
				ErrorLevel = Command;
				Builder.Write( "Error: exception while starting to " + Command.ToString() + " operation." );
				Builder.CloseLog();
			}
		}

		private void CopyFolder()
		{
			FolderOperation( COMMANDS.CopyFolder, "/V /S /COPY:DAT" );
		}

		private void MoveFolder()
		{
			FolderOperation( COMMANDS.MoveFolder, "/V /S /MOVE /COPY:DAT" );
		}

		private void CleanFolder()
		{
			try
			{
				Builder.OpenLog( Builder.GetLogFileName( COMMANDS.CleanFolder ), false );

				string[] Params = Builder.SplitCommandline();
				if( Params.Length != 2 )
				{
					Builder.Write( "Error: wrong number of parameters. Usage: CleanFolder <FolderName> <Pattern>." );
					ErrorLevel = COMMANDS.CleanFolder;
				}
				else
				{
					Builder.Write( "Deleting: '" + Params[0] + "/" + Params[1] + "'" );
					if( Directory.Exists( Params[0] ) )
					{
						DeletePatternFromFolder( Params[0], Params[1], false );
						Builder.Write( " ... done" );
					}
				}

				Builder.CloseLog();
			}
			catch( Exception Ex )
			{
				ErrorLevel = COMMANDS.CleanFolder;
				Builder.Write( "Error: exception while starting to CleanFolder operation: " + Ex.Message );
				Builder.CloseLog();
			}
		}

		private void GetPublishedData()
		{
			try
			{
				Builder.OpenLog( Builder.GetLogFileName( COMMANDS.GetPublishedData ), false );

				// Extract the tagset name
				string[] Parms = Builder.SplitCommandline();
				if( Parms.Length < 2 )
				{
					Builder.Write( "Error: too few parameters. Usage: GetPublishedData <Tagset> <Source>" );
					ErrorLevel = COMMANDS.GetPublishedData;
				}
				else
				{
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
					CookerSyncCommandLine += " -x " + Parms[0];
					CookerSyncCommandLine += " -crc -l";
					CookerSyncCommandLine += " -i -notoc";

					switch( Builder.PublishVerification )
					{
					case ScriptParser.PublishVerificationType.MD5:
					default:
						CookerSyncCommandLine += " -v";
						break;

					case ScriptParser.PublishVerificationType.None:
						break;
					}

					string DestFolder = Parms[1];
					if( Builder.IncludeTimestampFolder )
					{
						DestFolder = Path.Combine( Parms[1], Builder.GetFolderName() );
					}

					CookerSyncCommandLine += " " + DestFolder;

					CurrentBuild = new BuildProcess( Parent, Builder, Executable, CookerSyncCommandLine, "", false );
					ErrorLevel = CurrentBuild.GetErrorLevel();
				}

				StartTime = DateTime.UtcNow;
			}
			catch
			{
				Builder.Write( "Error: exception while starting to get published data" );
				Builder.CloseLog();
			}
		}

		private void SteamMakeVersion()
		{
			try
			{
				Builder.OpenLog( Builder.GetLogFileName( COMMANDS.SteamMakeVersion ), false );

				string[] Parms = Builder.SplitCommandline();
				if( Parms.Length < 1 )
				{
					Builder.Write( "Error: too few parameters. Usage: SteamMakeVersion <ScriptFile>" );
					ErrorLevel = COMMANDS.SteamMakeVersion;
				}
				else
				{
					string PublishedFolder = Builder.GetFolderName();

					string Executable = Builder.SteamContentToolLocation;
					string CommandLine = "/console /verbose /filename " + Parms[0] + ".smd";

					CurrentBuild = new BuildProcess( Parent, Builder, Executable, CommandLine, "", false );
					ErrorLevel = CurrentBuild.GetErrorLevel();
				}

				StartTime = DateTime.UtcNow;
			}
			catch
			{
				ErrorLevel = COMMANDS.SteamMakeVersion;
				Builder.Write( "Error: exception while starting to make a steam version" );
				Builder.CloseLog();
			}
		}

		private void UpdateSteamServer()
		{
			try
			{
				Builder.OpenLog( Builder.GetLogFileName( COMMANDS.UpdateSteamServer ), false );

				string[] Parms = Builder.SplitCommandline();
				if( Parms.Length < 2 )
				{
					Builder.Write( "Error: too few parameters. Usage: UpdateSteamServer <appid> <Depot>" );
					ErrorLevel = COMMANDS.UpdateSteamServer;
				}
				else
				{
					string CommandLine = Parms[1] + " " + Builder.CopyDestination + " " + Parms[0] + "_*.* /XO";

					CurrentBuild = new BuildProcess( Parent, Builder, "RoboCopy.exe", CommandLine, "", false );
					ErrorLevel = CurrentBuild.GetErrorLevel();
				}

				StartTime = DateTime.UtcNow;
			}
			catch
			{
				ErrorLevel = COMMANDS.UpdateSteamServer;
				Builder.Write( "Error: exception while trying to publish files to a local test server" );
				Builder.CloseLog();
			}
		}

		private void StartSteamServer()
		{
			try
			{
				Builder.OpenLog( Builder.GetLogFileName( COMMANDS.StartSteamServer ), false );

				string Executable = Builder.SteamContentServerLocation;

				CurrentBuild = new BuildProcess( Parent, Builder, Executable, "/start", "", false );
				ErrorLevel = CurrentBuild.GetErrorLevel();

				System.Threading.Thread.Sleep( 1000 );

				StartTime = DateTime.UtcNow;
			}
			catch
			{
				ErrorLevel = COMMANDS.StartSteamServer;
				Builder.Write( "Error: exception while starting Steam content server" );
				Builder.CloseLog();
			}
		}

		private void StopSteamServer()
		{
			try
			{
				Builder.OpenLog( Builder.GetLogFileName( COMMANDS.StopSteamServer ), false );

				string Executable = Builder.SteamContentServerLocation;

				CurrentBuild = new BuildProcess( Parent, Builder, Executable, "/stop", "", false );
				ErrorLevel = CurrentBuild.GetErrorLevel();

				System.Threading.Thread.Sleep( 1000 );

				StartTime = DateTime.UtcNow;
			}
			catch
			{
				ErrorLevel = COMMANDS.StopSteamServer;
				Builder.Write( "Error: exception while stopping Steam content server" );
				Builder.CloseLog();
			}
		}

		private void UnSetup()
		{
			try
			{
				Builder.OpenLog( Builder.GetLogFileName( COMMANDS.UnSetup ), false );

				string[] Parms = Builder.SplitCommandline();
				if( Parms.Length < 1 )
				{
					Builder.Write( "Error: too few parameters. Usage: UnSetup <Command>" );
					ErrorLevel = COMMANDS.UnSetup;
				}
				else
				{
					string CWD = Path.Combine( "D:\\Builds", Builder.GetFolderName() );
					CWD = Path.Combine( CWD, Builder.BranchDef.Branch );
					string Executable = Path.Combine( CWD, "Binaries/UnSetup.exe" );
					string CommandLine = "-" + Parms[0];
					if( Builder.UnSetupType.Length > 0 )
					{
						CommandLine += " -installer=" + Builder.UnSetupType;
					}

					CurrentBuild = new BuildProcess( Parent, Builder, Executable, CommandLine, CWD, false );
					ErrorLevel = CurrentBuild.GetErrorLevel();
				}

				StartTime = DateTime.UtcNow;
			}
			catch
			{
				ErrorLevel = COMMANDS.UnSetup;
				Builder.Write( "Error: exception while starting UnSetup" );
				Builder.CloseLog();
			}
		}

		private void CreateDVDLayout()
		{
			try
			{
				string LogFileName = Builder.GetLogFileName( COMMANDS.CreateDVDLayout );
				Builder.OpenLog( LogFileName, false );

				string[] Parms = Builder.SplitCommandline();
				if( Parms.Length > 1 )
				{
					Builder.Write( "Error: Spurious parameter(s)." );
					ErrorLevel = COMMANDS.CreateDVDLayout;
				}
				else
				{
					GameConfig Config = Builder.CreateGameConfig();

					string Executable = "Binaries/UnrealDVDLayout.exe";
					string CommandLine = Builder.LabelInfo.Game + " " + Config.GetCookedFolderPlatform();

					string LayoutFileName = Config.GetLayoutFileName( Builder.SkuName, Builder.GetLanguages().ToArray(), Builder.GetTextLanguages().ToArray() );
					CommandLine += " " + LayoutFileName;

					Queue<string> Langs = Builder.GetLanguages();
					foreach( string Lang in Langs )
					{
						CommandLine += " " + Lang.ToUpper();
					}

					Queue<string> TextLangs = Builder.GetTextLanguages();
					foreach( string TextLang in TextLangs )
					{
						CommandLine += " " + TextLang.ToUpper();
					}

					CommandLine += " -MaxFull " + Langs.Count.ToString();

					if( Parms.Length > 0 )
					{
						CommandLine += " -image " + Path.Combine( Parms[0], Builder.GetFolderName() );
						if( Builder.ImageMode.Length > 0 )
						{
							CommandLine += "." + Builder.ImageMode;
						}

						if( Builder.KeyLocation.Length > 0 && Builder.KeyPassword.Length > 0 )
						{
							CommandLine += " -keylocation " + Builder.KeyLocation;
							CommandLine += " -keypassword " + Builder.KeyPassword;
						}
					}

					CurrentBuild = new BuildProcess( Parent, Builder, Executable, CommandLine, "", false );
					ErrorLevel = CurrentBuild.GetErrorLevel();
				}

				StartTime = DateTime.UtcNow;
			}
			catch
			{
				ErrorLevel = COMMANDS.CreateDVDLayout;
				Builder.Write( "Error: exception while starting to CreateDVDLayout" );
				Builder.CloseLog();
			}
		}

		private void Conform()
		{
			try
			{
				if( Builder.GetValidLanguages() == null || Builder.GetValidLanguages().Count < 2 )
				{
					Parent.Log( "Error: not enough languages to conform.", Color.Red );
					ErrorLevel = COMMANDS.Conform;
				}
				else
				{
					string Package, LastPackage;

					string LastLanguage = Builder.GetValidLanguages().Dequeue();
					string Language = Builder.GetValidLanguages().Peek();

					string LogFileName = Builder.GetLogFileName( COMMANDS.Conform, Language );
					Builder.OpenLog( LogFileName, false );

					string[] Parms = Builder.SplitCommandline();
					if( Parms.Length != 1 )
					{
						Builder.Write( "Error: missing package name. Usage: Conform <Package>." );
						ErrorLevel = COMMANDS.Conform;
					}
					else
					{
						GameConfig Config = Builder.CreateGameConfig();
						CleanIniFiles( Config );

						string CommandLine = "";
						string Executable = Config.GetComName( Builder.BranchDef.Version, ref CommandLine );

						if( LastLanguage == "INT" )
						{
							LastPackage = Parms[0];
						}
						else
						{
							LastPackage = Parms[0] + "_" + LastLanguage;
						}
						Package = Parms[0] + "_" + Language;

						CommandLine += "conform " + Package + " " + LastPackage + " " + CommonCommandLine + Builder.GetCookConfiguration();

						CurrentBuild = new BuildProcess( Parent, Builder, Executable, CommandLine, "", true );
						ErrorLevel = CurrentBuild.GetErrorLevel();
					}

					StartTime = DateTime.UtcNow;
				}
			}
			catch
			{
				ErrorLevel = COMMANDS.Conform;
				Builder.Write( "Error: exception while starting to conform dialog" );
				Builder.CloseLog();
			}
		}

		private void PatchScript()
		{
			try
			{
				string LogFileName = Builder.GetLogFileName( COMMANDS.PatchScript );
				Builder.OpenLog( LogFileName, false );

				string[] Parms = Builder.SplitCommandline();
				if( Parms.Length != 1 )
				{
					Builder.Write( "Error: missing package name. Usage: PatchScript <Package>." );
					ErrorLevel = COMMANDS.PatchScript;
				}
				else
				{
					GameConfig Config = Builder.CreateGameConfig();
					CleanIniFiles( Config );

					string CommandLine = "";
					string Executable = Config.GetComName( Builder.BranchDef.Version, ref CommandLine );
					CommandLine += "patchscript " + Parms[0] + " -Platform=" + Config.GetCookedFolderPlatform() + " " + Builder.GetScriptConfiguration() + " ..\\..\\" + Config.GetCookedFolderName( Builder.BranchDef.Version ) + " ..\\..\\" + Config.GetOriginalCookedFolderName( Builder.BranchDef.Version ) + " " + CommonCommandLine;

					CurrentBuild = new BuildProcess( Parent, Builder, Executable, CommandLine, "", true );
					ErrorLevel = CurrentBuild.GetErrorLevel();
				}

				StartTime = DateTime.UtcNow;
			}
			catch
			{
				ErrorLevel = COMMANDS.PatchScript;
				Builder.Write( "Error: exception while starting to patch script" );
				Builder.CloseLog();
			}
		}

		private void CheckpointGameAssetDatabase( string AdditionalOptions )
		{
			try
			{
				string LogFileName = Builder.GetLogFileName( COMMANDS.CheckpointGameAssetDatabase );
				Builder.OpenLog( LogFileName, false );

				GameConfig Config = Builder.CreateGameConfig();
				CleanIniFiles( Config );

				string CommandLine = "";
				string Executable = Config.GetComName( Builder.BranchDef.Version, ref CommandLine );
				if( AdditionalOptions.Length > 0 )
				{
					string EncodedFoldername = Builder.GetFolderName();
					Executable = Config.GetUDKComName( Executable, Builder.BranchDef.Branch, EncodedFoldername, Builder.CurrentCommandLine );
				}
				CommandLine += "CheckpointGameAssetDatabase " + AdditionalOptions + CommonCommandLine;

				CurrentBuild = new BuildProcess( Parent, Builder, Executable, CommandLine, "", true );
				ErrorLevel = CurrentBuild.GetErrorLevel();

				StartTime = DateTime.UtcNow;
			}
			catch
			{
				ErrorLevel = COMMANDS.CheckpointGameAssetDatabase;
				Builder.Write( "Error: exception while starting to checkpoint the game asset database." );
				Builder.CloseLog();
			}
		}

		private void TagReferencedAssets( bool bUseCookedData )
		{
			try
			{
				string LogFileName = Builder.GetLogFileName( COMMANDS.TagReferencedAssets );
				Builder.OpenLog( LogFileName, false );

				GameConfig Config = Builder.CreateGameConfig();
				CleanIniFiles( Config );

				string CommandLine = "";
				string Executable = Config.GetComName( Builder.BranchDef.Version, ref CommandLine );
				CommandLine += "TagReferencedAssets ";
				if( bUseCookedData )
				{
					CommandLine = "TagCookedReferencedAssets -Platform=" + Config.GetCookedFolderPlatform() + " ";
				}
				CommandLine += Builder.GetDLCName() + " ";
				CommandLine += CommonCommandLine;

				CurrentBuild = new BuildProcess( Parent, Builder, Executable, CommandLine, "", true );
				ErrorLevel = CurrentBuild.GetErrorLevel();

				StartTime = DateTime.UtcNow;
			}
			catch
			{
				ErrorLevel = COMMANDS.TagReferencedAssets;
				Builder.Write( "Error: exception while starting to tag referenced assets." );
				Builder.CloseLog();
			}
		}

		private void AuditContent()
		{
			try
			{
				string LogFileName = Builder.GetLogFileName( COMMANDS.AuditContent );
				Builder.OpenLog( LogFileName, false );

				GameConfig Config = Builder.CreateGameConfig();
				CleanIniFiles( Config );

				string CommandLine = "";
				string Executable = Config.GetComName( Builder.BranchDef.Version, ref CommandLine );
				CommandLine += "ContentAuditCommandlet " + CommonCommandLine;

				CurrentBuild = new BuildProcess( Parent, Builder, Executable, CommandLine, "", true );
				ErrorLevel = CurrentBuild.GetErrorLevel();

				StartTime = DateTime.UtcNow;
			}
			catch
			{
				ErrorLevel = COMMANDS.AuditContent;
				Builder.Write( "Error: exception while starting to audit content." );
				Builder.CloseLog();
			}
		}

		private void FindStaticMeshCanBecomeDynamic()
		{
			try
			{
				string LogFileName = Builder.GetLogFileName( COMMANDS.FindStaticMeshCanBecomeDynamic );
				Builder.OpenLog( LogFileName, false );

				GameConfig Config = Builder.CreateGameConfig();
				CleanIniFiles( Config );

				string CommandLine = "";
				string Executable = Config.GetComName( Builder.BranchDef.Version, ref CommandLine );
				CommandLine += "FindStaticMeshCanBecomeDynamic " + CommonCommandLine;

				CurrentBuild = new BuildProcess( Parent, Builder, Executable, CommandLine, "", true );
				ErrorLevel = CurrentBuild.GetErrorLevel();

				StartTime = DateTime.UtcNow;
			}
			catch
			{
				ErrorLevel = COMMANDS.FindStaticMeshCanBecomeDynamic;
				Builder.Write( "Error: exception while starting to find static meshes that can become dynamic." );
				Builder.CloseLog();
			}
		}

		private void FixupRedirects()
		{
			try
			{
				string LogFileName = Builder.GetLogFileName( COMMANDS.FixupRedirects );
				Builder.OpenLog( LogFileName, false );

				GameConfig Config = Builder.CreateGameConfig();
				CleanIniFiles( Config );

				string CommandLine = "";
				string Executable = Config.GetComName( Builder.BranchDef.Version, ref CommandLine );
				CommandLine += "FixupRedirects " + CommonCommandLine + Builder.GetOptionalCommandletConfig();

				CurrentBuild = new BuildProcess( Parent, Builder, Executable, CommandLine, "", true );
				ErrorLevel = CurrentBuild.GetErrorLevel();

				StartTime = DateTime.UtcNow;
			}
			catch
			{
				ErrorLevel = COMMANDS.FixupRedirects;
				Builder.Write( "Error: exception while starting to Fix Up Redirects." );
				Builder.CloseLog();
			}
		}

		private void ResaveDeprecatedPackages()
		{
			try
			{
				string LogFileName = Builder.GetLogFileName( COMMANDS.ResaveDeprecatedPackages );
				Builder.OpenLog( LogFileName, false );

				GameConfig Config = Builder.CreateGameConfig();
				CleanIniFiles( Config );

				string CommandLine = "";
				string Executable = Config.GetComName( Builder.BranchDef.Version, ref CommandLine );
				CommandLine += "ResavePackages -ResaveDeprecated -MaxPackagesToResave=50 -AutoCheckoutPackages " + CommonCommandLine + Builder.GetOptionalCommandletConfig();

				CurrentBuild = new BuildProcess( Parent, Builder, Executable, CommandLine, "", true );
				ErrorLevel = CurrentBuild.GetErrorLevel();

				StartTime = DateTime.UtcNow;
			}
			catch
			{
				ErrorLevel = COMMANDS.ResaveDeprecatedPackages;
				Builder.Write( "Error: exception while starting to resave deprecated packages." );
				Builder.CloseLog();
			}
		}

		private void AnalyzeReferencedContent()
		{
			try
			{
				string LogFileName = Builder.GetLogFileName( COMMANDS.AnalyzeReferencedContent );
				Builder.OpenLog( LogFileName, false );

				GameConfig Config = Builder.CreateGameConfig();
				CleanIniFiles( Config );

				string CommandLine = "";
				string Executable = Config.GetComName( Builder.BranchDef.Version, ref CommandLine );
				CommandLine += "AnalyzeReferencedContent " + CommonCommandLine + Builder.GetAnalyzeReferencedContentConfiguration();

				CurrentBuild = new BuildProcess( Parent, Builder, Executable, CommandLine, "", true );
				ErrorLevel = CurrentBuild.GetErrorLevel();

				StartTime = DateTime.UtcNow;
			}
			catch
			{
				ErrorLevel = COMMANDS.AnalyzeReferencedContent;
				Builder.Write( "Error: exception while starting to Analyze Referenced Content." );
				Builder.CloseLog();
			}
		}

		private void MineCookedPackages()
		{
			try
			{
				string LogFileName = Builder.GetLogFileName( COMMANDS.MineCookedPackages );
				Builder.OpenLog( LogFileName, false );

				GameConfig Config = Builder.CreateGameConfig();
				CleanIniFiles( Config );

				string CommandLine = "";
				string Executable = Config.GetComName( Builder.BranchDef.Version, ref CommandLine );
				CommandLine += "MineCookedPackages " + CommonCommandLine + Builder.GetOptionalCommandletConfig() + Builder.GetDataBaseConnectionInfo() + " ../../" + Config.GetCookedFolderName( Builder.BranchDef.Version ) + "/*.xxx";

				CurrentBuild = new BuildProcess( Parent, Builder, Executable, CommandLine, "", true );
				ErrorLevel = CurrentBuild.GetErrorLevel();

				StartTime = DateTime.UtcNow;
			}
			catch
			{
				ErrorLevel = COMMANDS.MineCookedPackages;
				Builder.Write( "Error: exception while starting to Mine Cooked Packages." );
				Builder.CloseLog();
			}
		}

		private void ContentComparison()
		{
			try
			{
				string LogFileName = Builder.GetLogFileName( COMMANDS.ContentComparison );
				Builder.OpenLog( LogFileName, false );

				GameConfig Config = Builder.CreateGameConfig();
				CleanIniFiles( Config );

				string CommandLine = "";
				string Executable = Config.GetComName( Builder.BranchDef.Version, ref CommandLine );
				CommandLine += "ContentComparison " + CommonCommandLine;

				CurrentBuild = new BuildProcess( Parent, Builder, Executable, CommandLine, "", true );
				ErrorLevel = CurrentBuild.GetErrorLevel();

				StartTime = DateTime.UtcNow;
			}
			catch
			{
				ErrorLevel = COMMANDS.ContentComparison;
				Builder.Write( "Error: exception while starting to Compare Content." );
				Builder.CloseLog();
			}
		}

		private void DumpMapSummary()
		{
			try
			{
				string LogFileName = Builder.GetLogFileName( COMMANDS.DumpMapSummary );
				Builder.OpenLog( LogFileName, false );

				string[] Parms = Builder.SplitCommandline();
				if( Parms.Length < 1 )
				{
					Builder.Write( "Error: missing map name. Usage: DumpMapSummary <map>." );
					ErrorLevel = COMMANDS.DumpMapSummary;
				}
				else
				{
					GameConfig Config = Builder.CreateGameConfig();
					CleanIniFiles( Config );

					string CommandLine = "";
					string Executable = Config.GetComName( Builder.BranchDef.Version, ref CommandLine );
					CommandLine += "DumpMapSummary ";

					foreach( string Parm in Parms )
					{
						CommandLine += Parm + " ";
					}

					CommandLine += CommonCommandLine;
					CurrentBuild = new BuildProcess( Parent, Builder, Executable, CommandLine, "", true );
					ErrorLevel = CurrentBuild.GetErrorLevel();

					StartTime = DateTime.UtcNow;
				}
			}
			catch
			{
				ErrorLevel = COMMANDS.DumpMapSummary;
				Builder.Write( "Error: exception while starting to dump map summary." );
				Builder.CloseLog();
			}
		}

		private void ExtractSHAs()
		{
			try
			{
				string LogFileName = Builder.GetLogFileName( COMMANDS.ExtractSHAs );
				Builder.OpenLog( LogFileName, false );

				string[] Parms = Builder.SplitCommandline();
				if( Parms.Length < 1 )
				{
					Builder.Write( "Error: missing section name. Usage: ValidateSHA <section>." );
					ErrorLevel = COMMANDS.ExtractSHAs;
				}
				else
				{
					GameConfig Config = Builder.CreateGameConfig();
					List<string> Binaries = Config.GetExecutableNames( 1 );

					string Executable = "imagexex.exe";
					string CommandLine = "/dump /sectionname:" + Parms[0] + " /sectionfile:" + Parms[0] + ".bin " + Binaries[0];

					CurrentBuild = new BuildProcess( Parent, Builder, Executable, CommandLine, "", true );
					ErrorLevel = CurrentBuild.GetErrorLevel();
				}
			}
			catch
			{
				ErrorLevel = COMMANDS.ExtractSHAs;
				Builder.Write( "Error: exception while validating SHA section." );
				Builder.CloseLog();
			}
		}

		private void CheckSHAs()
		{
			try
			{
				string LogFileName = Builder.GetLogFileName( COMMANDS.CheckSHAs );
				Builder.OpenLog( LogFileName, false );

				string[] Parms = Builder.SplitCommandline();
				if( Parms.Length < 1 )
				{
					Builder.Write( "Error: missing section name. Usage: ValidateSHA <section>." );
					ErrorLevel = COMMANDS.CheckSHAs;
				}
				else
				{
					FileInfo Info = new FileInfo( Parms[0] + ".bin" );
					if( !Info.Exists )
					{
						Builder.Write( "Error: Extracted SHA file does not exist!" );
						ErrorLevel = COMMANDS.CheckSHAs;
					}
					else if( Info.Length < 2 )
					{
						Builder.Write( "Error: Extracted SHA file is too small! (" + Info.Length.ToString() + " bytes)" );
						ErrorLevel = COMMANDS.CheckSHAs;
					}
					else
					{
						Builder.Write( "[REPORT] SHA section is " + Info.Length.ToString() + " bytes for " + Builder.BuildConfiguration + " config." );
						Info.Delete();
					}
				}

				Builder.CloseLog();
			}
			catch
			{
				ErrorLevel = COMMANDS.CheckSHAs;
				Builder.Write( "Error: exception while checking SHA section." );
				Builder.CloseLog();
			}
		}

		private void BumpEngineCpp( ScriptParser Builder, List<string> Lines )
		{
			// Bump ENGINE_VERSION and BUILT_FROM_CHANGELIST
			int BumpIncrement = 1;
			if( Builder.CurrentCommandLine.Length > 0 )
			{
				BumpIncrement = Builder.SafeStringToInt( Builder.CurrentCommandLine );
			}

			for( int i = 0; i < Lines.Count; i++ )
			{
				string[] Parms = Builder.SafeSplit( Lines[i], false );

				// Looks for the template of 'define', 'constant', 'value'
				if( Parms.Length == 3 && Parms[0].ToUpper() == "#DEFINE" )
				{
					if( Parms[1].ToUpper() == "MAJOR_VERSION" )
					{
						Builder.LabelInfo.BuildVersion = new Version( Builder.LabelInfo.SafeStringToInt( Parms[2] ),
																		Builder.LabelInfo.BuildVersion.Minor,
																		Builder.LabelInfo.BuildVersion.Build,
																		Builder.LabelInfo.BuildVersion.Revision );
					}

					if( Parms[1].ToUpper() == "MINOR_VERSION" )
					{
						Builder.LabelInfo.BuildVersion = new Version( Builder.LabelInfo.BuildVersion.Major,
																		Builder.LabelInfo.SafeStringToInt( Parms[2] ),
																		Builder.LabelInfo.BuildVersion.Build,
																		Builder.LabelInfo.BuildVersion.Revision );
					}

					if( Parms[1].ToUpper() == "ENGINE_VERSION" )
					{
						Builder.LabelInfo.BuildVersion = new Version( Builder.LabelInfo.BuildVersion.Major,
																		Builder.LabelInfo.BuildVersion.Minor,
																		Builder.LabelInfo.SafeStringToInt( Parms[2] ) + BumpIncrement,
																		Builder.LabelInfo.BuildVersion.Revision );

						Lines[i] = "#define\tENGINE_VERSION\t" + Builder.LabelInfo.BuildVersion.Build.ToString();
					}

					if( Parms[1].ToUpper() == "PRIVATE_VERSION" )
					{
						Builder.LabelInfo.BuildVersion = new Version( Builder.LabelInfo.BuildVersion.Major,
																		Builder.LabelInfo.BuildVersion.Minor,
																		Builder.LabelInfo.BuildVersion.Build,
																		Builder.LabelInfo.SafeStringToInt( Parms[2] ) );
					}

					if( Parms[1].ToUpper() == "BUILT_FROM_CHANGELIST" )
					{
						Lines[i] = "#define\tBUILT_FROM_CHANGELIST\t" + Builder.LabelInfo.Changelist.ToString();
					}
				}
			}
		}

		private string GetHexVersion( int EngineVersion )
		{
			string HexVersion = "";
			char[] HexDigits = "0123456789abcdef".ToCharArray();

			int MajorVer = Builder.LabelInfo.BuildVersion.Major;
			int MinorVer = Builder.LabelInfo.BuildVersion.Minor;

			// First 4 bits is major version
			HexVersion += HexDigits[MajorVer & 0xf];
			// Next 4 bits is minor version
			HexVersion += HexDigits[MinorVer & 0xf];
			// Next 16 bits is build number
			HexVersion += HexDigits[( EngineVersion >> 12 ) & 0xf];
			HexVersion += HexDigits[( EngineVersion >> 8 ) & 0xf];
			HexVersion += HexDigits[( EngineVersion >> 4 ) & 0xf];
			HexVersion += HexDigits[( EngineVersion >> 0 ) & 0xf];
			// Client code is required to have the first 4 bits be 0x8, where server code is required to have the first 4 bits be 0xC.
			HexVersion += HexDigits[0x8];
			// DiscID varies for different languages
			HexVersion += HexDigits[0x1];

			return ( HexVersion );
		}

		private void BumpAgentVersion()
		{
			try
			{
				Builder.OpenLog( Builder.GetLogFileName( COMMANDS.BumpAgentVersion ), false );

				// We have two files to update the version in
				string AgentFile = "Binaries/SwarmAgent.exe";
				string ProjectFile = "Development/Tools/UnrealSwarm/Agent/Agent.csproj";
				string AssemblyInfoFile = "Development/Tools/UnrealSwarm/Agent/Properties/AssemblyInfo.cs";
				string SwarmDefinesFile = "Development/Src/UnrealSwarm/Inc/SwarmDefines.h";
				string AgentInterfaceFile = "Development/Tools/UnrealSwarm/AgentInterface/AgentInterface.h";

				// Make sure they all exist
				if( !File.Exists( AgentFile ) )
				{
					ErrorLevel = COMMANDS.BumpAgentVersion;
					Builder.Write( "Error: File does not exist: '" + AgentFile + "'" );
					return;
				}
				if( !File.Exists( ProjectFile ) )
				{
					ErrorLevel = COMMANDS.BumpAgentVersion;
					Builder.Write( "Error: File does not exist: '" + ProjectFile + "'" );
					return;
				}
				if( !File.Exists( AssemblyInfoFile ) )
				{
					ErrorLevel = COMMANDS.BumpAgentVersion;
					Builder.Write( "Error: File does not exist: '" + AssemblyInfoFile + "'" );
					return;
				}
				if( !File.Exists( SwarmDefinesFile ) )
				{
					ErrorLevel = COMMANDS.BumpAgentVersion;
					Builder.Write( "Error: File does not exist: '" + SwarmDefinesFile + "'" );
					return;
				}
				if( !File.Exists( AgentInterfaceFile ) )
				{
					ErrorLevel = COMMANDS.BumpAgentVersion;
					Builder.Write( "Error: File does not exist: '" + AgentInterfaceFile + "'" );
					return;
				}

				// 				// Use the SCC revision numbers to create the minor version number
				// 				int SwarmDefinesFileVersion = SCC.GetHaveRevision( Builder, SwarmDefinesFile );
				// 				if( SwarmDefinesFileVersion == 0 )
				// 				{
				// 					ErrorLevel = COMMANDS.BumpAgentVersion;
				// 					Builder.Write( "Error: revision of file is 0: '" + SwarmDefinesFile + "'" );
				// 					return;
				// 				}
				// 
				// 				int AgentInterfaceFileVersion = SCC.GetHaveRevision( Builder, AgentInterfaceFile );
				// 				if( AgentInterfaceFileVersion == 0 )
				// 				{
				// 					ErrorLevel = COMMANDS.BumpAgentVersion;
				// 					Builder.Write( "Error: revision of file is 0: '" + AgentInterfaceFile + "'" );
				// 					return;
				// 				}

				// Get the current version of the agent and increment it
				Builder.Write( "Getting version info for " + AgentFile );
				FileVersionInfo AgentFileVersionInfo = FileVersionInfo.GetVersionInfo( Path.Combine( Environment.CurrentDirectory, AgentFile ) );
				Version OldAgentVersion = new Version( AgentFileVersionInfo.FileVersion );

				// Keep the old major version number
				int NewVersionMajor = OldAgentVersion.Major;

				// 				// The minor version is a simple sum of have revisions of the files that matter
				// 				int NewVersionMinor = SwarmDefinesFileVersion + AgentInterfaceFileVersion;
				// 
				// 				// Determine the build and revision values
				// 				int NewVersionBuild;
				// 				int NewVersionRevision;
				// 
				// 				if( NewVersionMinor == OldAgentVersion.Minor )
				// 				{
				// 					// Only increment the build version
				// 					NewVersionBuild = OldAgentVersion.Build + 1;
				// 					// And clear out the revision
				// 					NewVersionRevision = 0;
				// 				}
				// 				else
				// 				{
				// 					// If the minor version changed, reset the build and revision
				// 					NewVersionBuild = 0;
				// 					NewVersionRevision = 0;
				// 				}

				// The minor version is a simple sum of have revisions of the files that matter
				int NewVersionMinor = OldAgentVersion.Minor;

				// Only increment the build version
				int NewVersionBuild = OldAgentVersion.Build + 1;

				// And clear out the revision
				int NewVersionRevision = 0;

				Version NewAgentVersion = new Version( NewVersionMajor, NewVersionMinor, NewVersionBuild, NewVersionRevision );
				Builder.Write( "New version is " + NewAgentVersion.ToString() );

				StreamReader Reader;
				TextWriter Writer;
				List<string> Lines;
				string Line;

				// Bump the project version
				{
					Lines = new List<string>();
					Reader = new StreamReader( ProjectFile );
					if( Reader == null )
					{
						ErrorLevel = COMMANDS.BumpAgentVersion;
						Builder.Write( "Error: failed to open for reading '" + ProjectFile + "'" );
						return;
					}

					Line = Reader.ReadLine();
					while( Line != null )
					{
						Lines.Add( Line );
						Line = Reader.ReadLine();
					}
					Reader.Close();

					// Look for the line to edit
					for( int i = 0; i < Lines.Count; i++ )
					{
						// Looking for something like "<ApplicationVersion>1.0.0.0</ApplicationVersion>"
						if( Lines[i].Trim().StartsWith( "<ApplicationVersion>" ) )
						{
							Lines[i] = "    <ApplicationVersion>" + NewAgentVersion.ToString() + "</ApplicationVersion>";
						}
					}

					Writer = TextWriter.Synchronized( new StreamWriter( ProjectFile, false, Encoding.ASCII ) );
					if( Writer == null )
					{
						ErrorLevel = COMMANDS.BumpAgentVersion;
						Builder.Write( "Error: failed to open for writing '" + ProjectFile + "'" );
						return;
					}
					foreach( string SingleLine in Lines )
					{
						Writer.Write( SingleLine + Environment.NewLine );
					}
					Writer.Close();
				}

				// Bump the assembly info version
				{
					Lines = new List<string>();
					Reader = new StreamReader( AssemblyInfoFile );
					if( Reader == null )
					{
						ErrorLevel = COMMANDS.BumpAgentVersion;
						Builder.Write( "Error: failed to open for reading '" + AssemblyInfoFile + "'" );
						return;
					}

					Line = Reader.ReadLine();
					while( Line != null )
					{
						Lines.Add( Line );
						Line = Reader.ReadLine();
					}
					Reader.Close();

					// Look for the line to edit
					for( int i = 0; i < Lines.Count; i++ )
					{
						// Looking for something like "[assembly: AssemblyVersion( "1.0.0.171" )]"
						if( Lines[i].Trim().StartsWith( "[assembly: AssemblyVersion(" ) )
						{
							Lines[i] = "[assembly: AssemblyVersion( \"" + NewAgentVersion.ToString() + "\" )]";
						}
					}

					Writer = TextWriter.Synchronized( new StreamWriter( AssemblyInfoFile, false, Encoding.ASCII ) );
					if( Writer == null )
					{
						ErrorLevel = COMMANDS.BumpAgentVersion;
						Builder.Write( "Error: failed to open for writing '" + AssemblyInfoFile + "'" );
						return;
					}
					foreach( string SingleLine in Lines )
					{
						Writer.Write( SingleLine + Environment.NewLine );
					}
					Writer.Close();
				}

				Builder.CloseLog();
			}
			catch
			{
				ErrorLevel = COMMANDS.BumpAgentVersion;
				Builder.Write( "Error: while bumping agent version" );
				Builder.CloseLog();
			}
		}

		private void BumpEngineXml( ScriptParser Builder, List<string> Lines )
		{
			// Bump build version in Live! stuff
			for( int i = 0; i < Lines.Count; i++ )
			{
				if( Lines[i].Trim().StartsWith( "build=" ) )
				{
					Lines[i] = "     build=\"" + Builder.LabelInfo.BuildVersion.Build.ToString() + "\"";
				}
				else if( Lines[i].Trim().StartsWith( "<titleversion>" ) )
				{
					Lines[i] = "  <titleversion>" + GetHexVersion( Builder.LabelInfo.BuildVersion.Build ) + "</titleversion>";
				}
				else if( Lines[i].Trim().StartsWith( "<VersionNumber versionNumber=" ) )
				{
					Lines[i] = "      <VersionNumber versionNumber=\"" + Builder.LabelInfo.BuildVersion.ToString() + "\" />";
				}
			}
		}

		private void BumpEngineHeader( ScriptParser Builder, List<string> Lines )
		{
			// Bump the defines in the header files
			for( int i = 0; i < Lines.Count; i++ )
			{
				if( Lines[i].Trim().StartsWith( "#define ENGINE_VERSION" ) )
				{
					Lines[i] = "#define ENGINE_VERSION " + Builder.LabelInfo.BuildVersion.Build.ToString();
				}
				else if( Lines[i].Trim().StartsWith( "#define BUILT_FROM_CHANGELIST" ) )
				{
					Lines[i] = "#define BUILT_FROM_CHANGELIST " + Builder.LabelInfo.Changelist.ToString();
				}
			}
		}

		private void BumpEngineResource( ScriptParser Builder, List<string> Lines )
		{
			// Bump the versions in the rc file
			for( int i = 0; i < Lines.Count; i++ )
			{
				// FILEVERSION 1,0,0,0
				if( Lines[i].Trim().StartsWith( "FILEVERSION" ) )
				{
					Lines[i] = " FILEVERSION 1,0," + Builder.LabelInfo.BuildVersion.Build.ToString() + ",0";
				}
				// PRODUCTVERSION 1,0,0,0
				else if( Lines[i].Trim().StartsWith( "PRODUCTVERSION" ) )
				{
					Lines[i] = " PRODUCTVERSION 1,0," + Builder.LabelInfo.BuildVersion.Build.ToString() + ",0";
				}
				// VALUE "FileVersion", "1, 0, 0, 0"
				else if( Lines[i].Trim().StartsWith( "VALUE \"FileVersion\"" ) )
				{
					Lines[i] = "\t\t\tVALUE \"FileVersion\", \"1, 0, " + Builder.LabelInfo.BuildVersion.Build.ToString() + ", 0\"";
				}
				// VALUE "ProductVersion", "1, 0, 0, 0"
				else if( Lines[i].Trim().StartsWith( "VALUE \"ProductVersion\"" ) )
				{
					Lines[i] = "\t\t\tVALUE \"ProductVersion\", \"1, 0, " + Builder.LabelInfo.BuildVersion.Build.ToString() + ", 0\"";
				}
			}
		}

		private void BumpEngineProperties( ScriptParser Builder, List<string> Lines, string TimeStamp, int ChangeList, int EngineVersion )
		{
			// Bump build version in properties file
			for( int i = 0; i < Lines.Count; i++ )
			{
				if( Lines[i].Trim().StartsWith( "timestampForBVT=" ) )
				{
					Lines[i] = "timestampForBVT=" + TimeStamp;
				}
				else if( Lines[i].Trim().StartsWith( "changelistBuiltFrom=" ) )
				{
					Lines[i] = "changelistBuiltFrom=" + ChangeList.ToString();
				}
				else if( Lines[i].Trim().StartsWith( "engineVersion=" ) )
				{
					Lines[i] = "engineVersion=" + EngineVersion.ToString();
				}
			}
		}

		private void BumpEngineRDF( ScriptParser Builder, List<string> Lines )
		{
			string Spaces = "                                          ";

			// Bump build version in rdf file
			for( int i = 0; i < Lines.Count; i++ )
			{
				// [spaces]em:version="1.0.0.1"
				if( Lines[i].Trim().StartsWith( "em:version=" ) )
				{
					int NumSpaces = Lines[i].IndexOf( "em:version=" );
					Lines[i] = "";
					if( NumSpaces > -1 )
					{
						Lines[i] = Spaces.Substring( Spaces.Length - NumSpaces );
					}

					Lines[i] += "em:version=\"1.0." + Builder.LabelInfo.BuildVersion.Build.ToString() + ".0\"";
				}
			}
		}

		private void BumpEngineINF( ScriptParser Builder, List<string> Lines )
		{
			// Bump build version in inf file
			for( int i = 0; i < Lines.Count; i++ )
			{
				// FileVersion=1,0,6713,0
				if( Lines[i].Trim().StartsWith( "FileVersion=" ) )
				{
					Lines[i] = "FileVersion=1,0," + Builder.LabelInfo.BuildVersion.Build.ToString() + ",0";
				}
			}
		}

		private void BumpEngineJSON( ScriptParser Builder, List<string> Lines )
		{
			// Bump build version in json file
			for( int i = 0; i < Lines.Count; i++ )
			{
				// "version": "1.0.6777.0",
				if( Lines[i].Trim().StartsWith( "\"version\":" ) )
				{
					Lines[i] = "  \"version\": \"1.0." + Builder.LabelInfo.BuildVersion.Build.ToString() + ".0\",";
				}
			}
		}

		private void BumpEnginePList( ScriptParser Builder, List<string> Lines )
		{
			// Bump build version in a plist file
			for( int i = 0; i < Lines.Count; i++ )
			{
				// <key>CFBundleVersion</key>
				if( Lines[i].Trim().StartsWith( "<key>CFBundleVersion</key>" ) && Lines.Count > i + 1 )
				{
					Lines[i + 1] = "\t<string>" + Builder.LabelInfo.BuildVersion.Build.ToString() + ".0</string>";
					break;
				}
			}
		}

		private List<string> ReadTextFileToArray( FileInfo Info )
		{
			List<string> Lines = new List<string>();
			string Line;

			// Check to see if the version file is writable (otherwise the StreamWriter creation will exception)
			if( Info.IsReadOnly )
			{
				ErrorLevel = COMMANDS.BumpEngineVersion;
				Builder.Write( "Error: version file is read only '" + Info.FullName + "'" );
				return ( Lines );
			}

			// Read in existing file
			StreamReader Reader = new StreamReader( Info.FullName );
			if( Reader == null )
			{
				ErrorLevel = COMMANDS.BumpEngineVersion;
				Builder.Write( "Error: failed to open for reading '" + Info.FullName + "'" );
				return ( Lines );
			}

			Line = Reader.ReadLine();
			while( Line != null )
			{
				Lines.Add( Line );

				Line = Reader.ReadLine();
			}

			Reader.Close();

			return ( Lines );
		}

		private void SaveLinesToTextFile( string FileName, List<string> Lines, bool bUseASCII )
		{
			TextWriter Writer;

			if( bUseASCII )
			{
				Writer = TextWriter.Synchronized( new StreamWriter( FileName, false, Encoding.ASCII ) );
			}
			else
			{
				Writer = TextWriter.Synchronized( new StreamWriter( FileName, false, Encoding.Unicode ) );
			}

			if( Writer == null )
			{
				ErrorLevel = COMMANDS.BumpEngineVersion;
				Builder.Write( "Error: failed to open for writing '" + FileName + "'" );
				return;
			}

			foreach( string SingleLine in Lines )
			{
				Writer.Write( SingleLine + Environment.NewLine );
			}

			Writer.Close();
		}

		private void BumpVersionFile( ScriptParser Builder, string File, bool GetVersion )
		{
			bool bUseASCII = true;
			FileInfo Info = new FileInfo( File );
			List<string> Lines = ReadTextFileToArray( Info );

			// Bump the version dependent on the file extension
			if( GetVersion && Info.Extension.ToLower() == ".cpp" )
			{
				BumpEngineCpp( Builder, Lines );
			}
			else
			{
				if( Info.Extension.ToLower() == ".xml" )
				{
					BumpEngineXml( Builder, Lines );
					bUseASCII = ( File.ToLower().IndexOf( ".gdf.xml" ) < 0 );
				}
				else if( Info.Extension.ToLower() == ".properties" )
				{
					BumpEngineProperties( Builder, Lines, Builder.GetTimeStamp(), Builder.LabelInfo.Changelist, Builder.LabelInfo.BuildVersion.Build );
				}
				else if( Info.Extension.ToLower() == ".h" )
				{
					BumpEngineHeader( Builder, Lines );
				}
				else if( Info.Extension.ToLower() == ".rc" )
				{
					BumpEngineResource( Builder, Lines );
				}
				else if( Info.Extension.ToLower() == ".rdf" )
				{
					BumpEngineRDF( Builder, Lines );
					bUseASCII = false;
				}
				else if( Info.Extension.ToLower() == ".inf" )
				{
					BumpEngineINF( Builder, Lines );
				}
				else if( Info.Extension.ToLower() == ".json" )
				{
					BumpEngineJSON( Builder, Lines );
				}
				else if( Info.Extension.ToLower() == ".plist" )
				{
					BumpEnginePList( Builder, Lines );
				}
				else
				{
					ErrorLevel = COMMANDS.BumpEngineVersion;
					Builder.Write( "Error: invalid extension for '" + File + "'" );
					return;
				}
			}

			// Write out version
			SaveLinesToTextFile( File, Lines, bUseASCII );
		}

		private void BumpEngineVersion()
		{
			try
			{
				Builder.OpenLog( Builder.GetLogFileName( COMMANDS.BumpEngineVersion ), false );

				string File = Builder.EngineVersionFile;
				BumpVersionFile( Builder, File, true );

				string VersionFiles = Builder.MiscVersionFiles + ";" + Builder.ConsoleVersionFiles + ";" + Builder.MobileVersionFiles;

				string[] Files = VersionFiles.Split( ";".ToCharArray() );
				foreach( string XmlFile in Files )
				{
					if( XmlFile.Trim().Length > 0 )
					{
						BumpVersionFile( Builder, XmlFile.Trim(), false );
					}
				}

				Builder.CloseLog();
			}
			catch
			{
				ErrorLevel = COMMANDS.BumpEngineVersion;
				Builder.Write( "Error: while bumping engine version in '" + Builder.EngineVersionFile + "'" );
				Builder.CloseLog();
			}
		}

		private int GetVersionFile( ScriptParser Builder, string File )
		{
			List<string> Lines = new List<string>();
			string Line;
			int NewEngineVersion = 0;

			// Check to see if the version file is writable (otherwise the StreamWriter creation will exception)
			FileInfo Info = new FileInfo( File );

			// Read in existing file
			StreamReader Reader = new StreamReader( File );
			if( Reader == null )
			{
				ErrorLevel = COMMANDS.GetEngineVersion;
				Builder.Write( "Error: failed to open for reading '" + File + "'" );
				return ( 0 );
			}

			Line = Reader.ReadLine();
			while( Line != null )
			{
				Lines.Add( Line );

				Line = Reader.ReadLine();
			}

			Reader.Close();

			for( int i = 0; i < Lines.Count; i++ )
			{
				string[] Parms = Builder.SafeSplit( Lines[i], false );

				if( Parms.Length == 3 && Parms[0].ToUpper() == "#DEFINE" )
				{
					if( Parms[1].ToUpper() == "ENGINE_VERSION" )
					{
						NewEngineVersion = Builder.SafeStringToInt( Parms[2] );
					}
				}
			}

			return ( NewEngineVersion );
		}

		private void GetEngineVersion()
		{
			try
			{
				Builder.OpenLog( Builder.GetLogFileName( COMMANDS.GetEngineVersion ), false );

				int EngineVersion = GetVersionFile( Builder, Builder.EngineVersionFile );
				Builder.LabelInfo.BuildVersion = new Version( Builder.LabelInfo.BuildVersion.Major,
																Builder.LabelInfo.BuildVersion.Minor,
																EngineVersion,
																Builder.LabelInfo.BuildVersion.Revision );

				Builder.CloseLog();
			}
			catch
			{
				ErrorLevel = COMMANDS.BumpEngineVersion;
				Builder.Write( "Error: while getting engine version in '" + Builder.EngineVersionFile + "'" );
				Builder.CloseLog();
			}
		}

		private void UpdateGDFVersion()
		{
			try
			{
				Builder.OpenLog( Builder.GetLogFileName( COMMANDS.UpdateGDFVersion ), false );

				string[] Parms = Builder.SplitCommandline();
				if( Parms.Length != 2 )
				{
					Builder.Write( "Error: too few parameters. Usage: UpdateGDFVersion <Game> <ResourcePath>." );
					ErrorLevel = COMMANDS.UpdateGDFVersion;
				}
				else
				{
					int EngineVersion = Builder.LabelInfo.BuildVersion.Build;
					Queue<string> Languages = Builder.GetLanguages();

					foreach( string Lang in Languages )
					{
						string GDFFileName = Parms[1] + "/" + Lang.ToUpper() + "/" + Parms[0] + "Game.gdf.xml";
						BumpVersionFile( Builder, GDFFileName, false );
					}
				}

				Builder.CloseLog();
			}
			catch
			{
				ErrorLevel = COMMANDS.UpdateGDFVersion;
				Builder.Write( "Error: while bumping engine version in '" + Builder.EngineVersionFile + "'" );
				Builder.CloseLog();
			}
		}

		private void MakeGFWLCat()
		{
			try
			{
				Builder.OpenLog( Builder.GetLogFileName( COMMANDS.MakeGFWLCat ), false );

				GameConfig Config = Builder.CreateGameConfig();
				List<string> CatNames = Config.GetCatNames( Builder.BranchDef.Version );

				string Folder = Path.GetDirectoryName( CatNames[1] );
				string CdfFile = Path.GetFileName( CatNames[1] );

				Parent.Log( "[STATUS] Making cat for '" + CdfFile + "' in folder '" + Folder + "'", Color.Magenta );

				string MakeCatName = Builder.CatToolName;
				string CommandLine = "-v " + CdfFile;
				string WorkingFolder = Folder;

				CurrentBuild = new BuildProcess( Parent, Builder, MakeCatName, CommandLine, WorkingFolder, false );
				ErrorLevel = CurrentBuild.GetErrorLevel();
				StartTime = DateTime.UtcNow;
			}
			catch
			{
				ErrorLevel = COMMANDS.MakeGFWLCat;
				Builder.Write( "Error: while making cat file" );
				Builder.CloseLog();
			}
		}

		private void ZDPP()
		{
			try
			{
				Builder.OpenLog( Builder.GetLogFileName( COMMANDS.ZDPP ), false );

				// ZDP tool can't operate if the redist portion has already been copied - so delete it
				string ZDPFolder = "Binaries\\Win32\\Zdp";
				Builder.Write( "Deleting: '" + Builder.BranchDef.Branch + "/" + ZDPFolder + "'" );
				if( Directory.Exists( ZDPFolder ) )
				{
					Parent.DeleteDirectory( ZDPFolder, 0 );
					Builder.Write( " ... done" );
				}

				string ZDPOutputFolder = "Binaries\\Win32\\ZdpSdkOutput";
				Builder.Write( "Deleting: '" + Builder.BranchDef.Branch + "/" + ZDPOutputFolder + "'" );
				if( Directory.Exists( ZDPOutputFolder ) )
				{
					Parent.DeleteDirectory( ZDPOutputFolder, 0 );
					Builder.Write( " ... done" );
				}

				// Running the ZDP tool copies the redist files back in
				GameConfig Config = Builder.CreateGameConfig();
				List<string> ExeNames = Config.GetExecutableNames( Builder.BranchDef.Version );

				string Exectable = Builder.ZDPPToolName;
				string WorkingFolder = "Binaries\\Win32";
				string CommandLine = "-s ..\\..\\StormGame\\Build\\ZDPP\\ZdpSettings.xml -x " + Path.GetFileName( ExeNames[0] );

				CurrentBuild = new BuildProcess( Parent, Builder, Exectable, CommandLine, WorkingFolder, false );
				ErrorLevel = CurrentBuild.GetErrorLevel();
				StartTime = DateTime.UtcNow;
			}
			catch
			{
				ErrorLevel = COMMANDS.ZDPP;
				Builder.Write( "Error: while applying ZDPP" );
				Builder.CloseLog();
			}
		}

		private void SteamDRM()
		{
			try
			{
				Builder.OpenLog( Builder.GetLogFileName( COMMANDS.SteamDRM ), false );

				string[] Parms = Builder.SplitCommandline();
				if( Parms.Length != 2 )
				{
					Builder.Write( "Error: too few parameters. Usage: SteamDRM <AppId> <flags>." );
					ErrorLevel = COMMANDS.SteamDRM;
				}
				else
				{
					GameConfig Config = Builder.CreateGameConfig();
					List<string> ExeNames = Config.GetExecutableNames( Builder.BranchDef.Version );
					string Exectable = "Binaries\\Win32\\drmtool.exe";
					string WorkingFolder = "Binaries\\Win32";

					string CommandLine = "-drm " + Path.GetFileName( ExeNames[0] ) + " " + Parms[0] + " " + Parms[1];

					CurrentBuild = new BuildProcess( Parent, Builder, Exectable, CommandLine, WorkingFolder, false );
					ErrorLevel = CurrentBuild.GetErrorLevel();
					StartTime = DateTime.UtcNow;
				}
			}
			catch
			{
				ErrorLevel = COMMANDS.SteamDRM;
				Builder.Write( "Error: while applying Steam DRM" );
				Builder.CloseLog();
			}
		}

		private void FixupSteamDRM()
		{
			try
			{
				Builder.OpenLog( Builder.GetLogFileName( COMMANDS.FixupSteamDRM ), false );

				GameConfig Config = Builder.CreateGameConfig();
				List<string> ExeNames = Config.GetExecutableNames( Builder.BranchDef.Version );

				Builder.Write( "Fixing up: " + ExeNames[0] );
				string ExeFolder = Path.GetDirectoryName( ExeNames[0] );
				string ExeName = Path.GetFileNameWithoutExtension( ExeNames[0] );

				DirectoryInfo FolderInfo = new DirectoryInfo( ExeFolder );
				Builder.Write( " ... finding: " + ExeName + "_*.exe in " + FolderInfo.FullName );
				FileInfo[] Executables = FolderInfo.GetFiles( ExeName + "_*.exe" );
				Builder.Write( " ... found: " + Executables.Length.ToString() + " files" );

				if( Executables.Length == 1 )
				{
					FileInfo ExeInfo = new FileInfo( ExeNames[0] );
					ExeInfo.Delete();

					Executables[0].MoveTo( ExeNames[0] );
				}
				else
				{
					ErrorLevel = COMMANDS.FixupSteamDRM;
					Builder.Write( "Error: while fixing up Steam DRMed filenames (no or multiple executables found)" );
				}

				Builder.CloseLog();
			}
			catch
			{
				ErrorLevel = COMMANDS.FixupSteamDRM;
				Builder.Write( "Error: while fixing up Steam DRMed filenames" );
				Builder.CloseLog();
			}
		}

		private void SaveDefines()
		{
			try
			{
				Builder.OpenLog( Builder.GetLogFileName( COMMANDS.SaveDefines ), false );

				// Read in the properties file
				Builder.Write( "Reading: Binaries/build.properties" );
				FileInfo Info = new FileInfo( "Binaries/build.properties" );
				List<string> Lines = ReadTextFileToArray( Info );

				// Remove any stale defines
				if( Lines.Count > 3 )
				{
					Lines.RemoveRange( 3, Lines.Count - 3 );
				}

				// Set the new defines
				foreach( string Define in Builder.LabelInfo.Defines )
				{
					Builder.Write( "Adding: " + Define );
					Lines.Add( Define );
				}

				// Write out the updated file
				Builder.Write( "Writing: Binaries/build.properties" );
				SaveLinesToTextFile( "Binaries/build.properties", Lines, true );

				Builder.CloseLog();
			}
			catch
			{
				ErrorLevel = COMMANDS.SaveDefines;
				Builder.Write( "Error: while saving defines to build.properties" );
				Builder.CloseLog();
			}
		}

		// Force the source server ini file to do the right thing
		private void UpdateSourceServerIni()
		{
			string IniFileName = Path.Combine( Path.GetDirectoryName( Builder.SourceServerCmd ), "srcsrv.ini" );
			FileInfo IniFile = new FileInfo( IniFileName );
			if( IniFile.Exists )
			{
				IniFile.IsReadOnly = false;
				IniFile.Delete();
			}

			StreamWriter Writer = IniFile.AppendText();

			Writer.WriteLine( "[variables]" );
			Writer.WriteLine( "MYSERVER=P4-03.epicgames.net:1666" );

			Writer.WriteLine( "[trusted commands]" );
			Writer.WriteLine( "p4.exe" );

			Writer.WriteLine( "[server errors]" );
			Writer.WriteLine( "perforce=var2,Connect to server failed;" );

			Writer.Close();
		}

		private void UpdateSourceServer()
		{
			try
			{
				Builder.OpenLog( Builder.GetLogFileName( COMMANDS.UpdateSourceServer ), false );

				// Create a source server ini file that will work
				UpdateSourceServerIni();

				string Executable = "Cmd.exe";
				string CommandLine = "/c \"" + Builder.SourceServerCmd + "\" " + Environment.CurrentDirectory + " " + Environment.CurrentDirectory + "\\Binaries -DEBUG 5";
				CurrentBuild = new BuildProcess( Parent, Builder, Executable, CommandLine, "", false );

				ErrorLevel = CurrentBuild.GetErrorLevel();
				StartTime = DateTime.UtcNow;
			}
			catch
			{
				ErrorLevel = COMMANDS.UpdateSourceServer;
				Builder.Write( "Error: while updating source server." );
				Builder.CloseLog();
			}
		}

		private void CreateCommandList( string Title, string Exec, string SymbolFile )
		{
			string Executable = "";

			string SymStore = Builder.SymbolStoreLocation;
			string ChangeList = Builder.LabelInfo.Changelist.ToString();
			string Version = Builder.LabelInfo.BuildVersion.Build.ToString();

			Builder.AddUpdateSymStore( "status " + Exec );

			// Symstore requires \ for some reason
			Executable = Environment.CurrentDirectory + "\\" + Exec.Replace( '/', '\\' );
			SymbolFile = Environment.CurrentDirectory + "\\" + SymbolFile.Replace( '/', '\\' );

			Builder.AddUpdateSymStore( "add /f " + Executable + " /s " + SymStore + " /t " + Title + " /v " + ChangeList + " /c " + Version + " /o" );
			Builder.AddUpdateSymStore( "add /f " + SymbolFile + " /s " + SymStore + " /t " + Title + " /v " + ChangeList + " /c " + Version + " /o" );
		}

		private void UpdateSymbolServer()
		{
			try
			{
				Builder.OpenLog( Builder.GetLogFileName( COMMANDS.UpdateSymbolServer ), false );

				if( Builder.LabelInfo.BuildVersion.Build == 0 )
				{
					Builder.Write( "Error: while updating symbol server." );
					Builder.Write( "Error: no engine version found; has BumpEngineVersion/GetEngineVersion been called?" );
					ErrorLevel = COMMANDS.UpdateSymbolServer;
				}
				else
				{
					List<GameConfig> GameConfigs = Builder.LabelInfo.GetGameConfigs();

					foreach( GameConfig Config in GameConfigs )
					{
						if( Config.IsLocal )
						{
							string Title = Config.GetTitle();
							List<string> Executables = Config.GetExecutableNames( Builder.BranchDef.Version );
							List<string> SymbolFiles = Config.GetSymbolFileNames( Builder.BranchDef.Version );

							if( Executables.Count > 0 && SymbolFiles.Count > 0 )
							{
								CreateCommandList( Title, Executables[0], SymbolFiles[0] );
							}
						}
					}
				}

				Builder.CloseLog();
			}
			catch
			{
				ErrorLevel = COMMANDS.UpdateSymbolServer;
				Builder.Write( "Error: while updating symbol server." );
				Builder.CloseLog();
			}
		}

		private void AddToSymbolServer( bool bIsExe )
		{
			try
			{
				Builder.OpenLog( Builder.GetLogFileName( COMMANDS.AddExeToSymbolServer ), false );

				if( Builder.LabelInfo.BuildVersion.Build == 0 )
				{
					Builder.Write( "Error: while adding to symbol server." );
					Builder.Write( "Error: no engine version found; has BumpEngineVersion/GetEngineVersion been called?" );
					ErrorLevel = COMMANDS.AddExeToSymbolServer;
				}
				else
				{
					string Title = "UnrealEngine3-Tools";
					string ExeName = Builder.CurrentCommandLine + ".exe";
					if( !bIsExe )
					{
						ExeName = Builder.CurrentCommandLine + ".dll";
					}
					string PdbName = Builder.CurrentCommandLine + ".pdb";

					CreateCommandList( Title, ExeName, PdbName );

					// Clean up the files that may have permissions problems
					Builder.AddUpdateSymStore( "delete" );
				}

				Builder.CloseLog();
			}
			catch
			{
				ErrorLevel = COMMANDS.AddExeToSymbolServer;
				Builder.Write( "Error: while adding to symbol server." );
				Builder.CloseLog();
			}
		}

		private void UpdateSymbolServerTick()
		{
			try
			{
				Builder.OpenLog( Builder.GetLogFileName( COMMANDS.UpdateSymbolServerTick ), true );

				if( Builder.UpdateSymStoreEmpty() )
				{
					// Force a finish
					CurrentBuild = null;
					Builder.Write( "Finished!" );
					Builder.CloseLog();
				}
				else
				{
					string Executable = Builder.SymbolStoreApp;
					string CommandLine = Builder.PopUpdateSymStore();

					if( CommandLine.StartsWith( "status " ) )
					{
						Parent.Log( "[STATUS] Updating symbol server for '" + CommandLine.Substring( "status ".Length ) + "'", Color.Magenta );

						CommandLine = Builder.PopUpdateSymStore();
					}

					CurrentBuild = new BuildProcess( Parent, Builder, Executable, CommandLine, "", false );
					ErrorLevel = CurrentBuild.GetErrorLevel();
				}

				StartTime = DateTime.UtcNow;
			}
			catch
			{
				ErrorLevel = COMMANDS.UpdateSymbolServer;
				Builder.Write( "Error: while updating symbol server." );
				Builder.CloseLog();
			}
		}

		private void CheckSigned()
		{
			try
			{
				Builder.OpenLog( Builder.GetLogFileName( COMMANDS.CheckSigned ), true );

				Parent.Log( "[STATUS] Checking '" + Builder.CurrentCommandLine + "' for signature", Color.Magenta );

				string SignToolName = Builder.SignToolName;
				string CommandLine = "verify /pa /v /tw " + Builder.CurrentCommandLine;

				CurrentBuild = new BuildProcess( Parent, Builder, SignToolName, CommandLine, "", false );
				ErrorLevel = COMMANDS.CheckSigned;
				StartTime = DateTime.UtcNow;
			}
			catch
			{
				ErrorLevel = COMMANDS.CheckSigned;
				Builder.Write( "Error: while checking for signed binaries." );
				Builder.CloseLog();
			}
		}

		private void SignHelper( COMMANDS Command, string FileToSign )
		{
			Builder.OpenLog( Builder.GetLogFileName( Command ), true );
			Parent.Log( "[STATUS] Signing '" + FileToSign + "'", Color.Magenta );

			string SignToolName = Builder.SignToolName;
			string CommandLine = "sign /a";
			if( Builder.BranchDef.PFXSubjectName.Length > 0 )
			{
				CommandLine += " /n \"" + Builder.BranchDef.PFXSubjectName + "\"";
			}
			CommandLine += " /t http://timestamp.verisign.com/scripts/timestamp.dll /v " + FileToSign;

			CurrentBuild = new BuildProcess( Parent, Builder, SignToolName, CommandLine, "", false );
			ErrorLevel = CurrentBuild.GetErrorLevel();
			StartTime = DateTime.UtcNow;
		}

		private void Sign()
		{
			try
			{
				SignHelper( COMMANDS.Sign, Builder.CurrentCommandLine );
			}
			catch
			{
				ErrorLevel = COMMANDS.Sign;
				Builder.Write( "Error: while signing binaries." );
				Builder.CloseLog();
			}
		}

		private void SignCat()
		{
			try
			{
				GameConfig Config = Builder.CreateGameConfig();
				List<string> CatFiles = Config.GetCatNames( Builder.BranchDef.Version );

				SignHelper( COMMANDS.SignCat, CatFiles[0] );
			}
			catch
			{
				ErrorLevel = COMMANDS.SignCat;
				Builder.Write( "Error: while signing cat file." );
				Builder.CloseLog();
			}
		}

		private void SignBinary()
		{
			try
			{
				GameConfig Config = Builder.CreateGameConfig();
				List<string> ExeFiles = Config.GetExecutableNames( Builder.BranchDef.Version );

				SignHelper( COMMANDS.SignBinary, ExeFiles[0] );
			}
			catch
			{
				ErrorLevel = COMMANDS.SignBinary;
				Builder.Write( "Error: while signing binary." );
				Builder.CloseLog();
			}
		}

		private void SignFile()
		{
			try
			{
				string[] Parms = Builder.SplitCommandline();
				string ActiveFolder = Builder.GetFolderName();
				string SourceFile = Path.Combine( Parms[0], Path.Combine( ActiveFolder, Builder.BranchDef.Branch ) ) + "\\" + Parms[1];

				SignHelper( COMMANDS.SignFile, SourceFile );
			}
			catch
			{
				ErrorLevel = COMMANDS.SignFile;
				Builder.Write( "Error: while signing file." );
				Builder.CloseLog();
			}
		}

		private void CopyScriptPatchFiles()
		{
			try
			{
				Builder.OpenLog( Builder.GetLogFileName( COMMANDS.CopyScriptPatchFiles ), true );

				GameConfig Config = Builder.CreateGameConfig();
				string ScriptPatchFolder = Path.Combine( Config.GetPatchesFolderName(), Config.GetCookedFolderPlatform() );
				string TUScriptPatchFolder = Path.Combine( Config.GetTUFolderName( Builder.CurrentCommandLine.Trim() ), Config.GetPatchesFolderName() );

				Builder.Write( "Copying: " + ScriptPatchFolder );
				Builder.Write( " ... to: " + TUScriptPatchFolder );

				// Copy over all the script patch files
				DirectoryInfo DirInfo = new DirectoryInfo( ScriptPatchFolder );
				if( DirInfo.Exists )
				{
					DirectoryInfo DestDirInfo = new DirectoryInfo( TUScriptPatchFolder );

					// Ensure the parent exists
					Parent.EnsureDirectoryExists( DestDirInfo.Parent.FullName );
					// Ensure the actual folder does *not* exist
					if( DestDirInfo.Exists )
					{
						DestDirInfo.Delete( true );
					}

					DirInfo.MoveTo( TUScriptPatchFolder );
				}
				else
				{
					Builder.Write( "Error: Source folder does not exist!" );
				}

				Builder.CloseLog();
			}
			catch( Exception Ex )
			{
				ErrorLevel = COMMANDS.CopyScriptPatchFiles;
				Builder.Write( "Error: exception copying script patch files." );
				Builder.Write( "Error: " + Ex.Message );
				Builder.CloseLog();
			}
		}

		private void DoCopy( string SourcePath, string DestFolder )
		{
			Builder.Write( "Copying: " + SourcePath );
			Builder.Write( " ... to: " + DestFolder );

			FileInfo Source = new FileInfo( SourcePath );
			if( Source.Exists )
			{
				// Get the filename
				int FileNameOffset = SourcePath.LastIndexOf( '/' );
				string FileName = SourcePath.Substring( FileNameOffset + 1 );
				string DestPathName = DestFolder + "/" + FileName;

				// Create the dest folder if it doesn't exist
				DirectoryInfo DestDir = new DirectoryInfo( DestFolder );
				if( !DestDir.Exists )
				{
					Builder.Write( " ... creating: " + DestDir.FullName );
					DestDir.Create();
				}

				// Copy the file
				FileInfo Dest = new FileInfo( DestPathName );
				if( Dest.Exists )
				{
					Builder.Write( " ... deleting: " + Dest.FullName );
					Dest.IsReadOnly = false;
					Dest.Delete();
				}

				Source.CopyTo( DestPathName, true );
			}
			else
			{
				Builder.Write( "Error: source file does not exist for copying" );
				ErrorLevel = COMMANDS.SimpleCopy;
			}
		}

		private void SimpleCopy()
		{
			try
			{
				Builder.OpenLog( Builder.GetLogFileName( COMMANDS.SimpleCopy ), true );

				string PathName = Builder.CurrentCommandLine.Trim();
				DoCopy( PathName, Builder.CopyDestination );

				Builder.CloseLog();
			}
			catch
			{
				ErrorLevel = COMMANDS.SimpleCopy;
				Builder.Write( "Error: exception copying file" );
				Builder.CloseLog();
			}
		}

		private void SetSteamID()
		{
			try
			{
				Builder.OpenLog( Builder.GetLogFileName( COMMANDS.SetSteamID ), false );

				GameConfig Config = Builder.CreateGameConfig( Builder.LabelInfo.Game, "Win32" );
				string Source = Config.GetSteamIDSource();
				string Destination = Config.GetSteamIDestinationFolder();
				DoCopy( Source, Destination );

				Config = Builder.CreateGameConfig( Builder.LabelInfo.Game, "Win64" );
				Destination = Config.GetSteamIDestinationFolder();
				DoCopy( Source, Destination );

				Builder.CloseLog();
			}
			catch
			{
				ErrorLevel = COMMANDS.SimpleCopy;
				Builder.Write( "Error: exception copying file" );
				Builder.CloseLog();
			}
		}

		private void SourceBuildCopy()
		{
			try
			{
				Builder.OpenLog( Builder.GetLogFileName( COMMANDS.SourceBuildCopy ), true );

				string DestFile = Builder.CurrentCommandLine.Trim();
				string SourceFile = Builder.SourceBuild + "/" + Builder.BranchDef.Branch + "/" + DestFile;

				Builder.Write( "Copying: " );
				Builder.Write( " ... from: " + SourceFile );
				Builder.Write( " ... to: " + DestFile );

				FileInfo Source = new FileInfo( SourceFile );
				if( Source.Exists )
				{
					FileInfo Dest = new FileInfo( DestFile );
					if( Dest.Exists && Dest.IsReadOnly )
					{
						Dest.IsReadOnly = false;
					}

					// Create the dest folder if it doesn't exist
					DirectoryInfo DestDir = new DirectoryInfo( Dest.DirectoryName );
					if( !DestDir.Exists )
					{
						Builder.Write( " ... creating: " + DestDir.FullName );
						DestDir.Create();
					}

					Source.CopyTo( DestFile, true );
				}
				else
				{
					Builder.Write( "Error: source file does not exist for copying" );
					ErrorLevel = COMMANDS.SourceBuildCopy;
				}

				Builder.CloseLog();
			}
			catch
			{
				ErrorLevel = COMMANDS.SourceBuildCopy;
				Builder.Write( "Error: exception copying file from alternate build" );
				Builder.CloseLog();
			}
		}

		private void SimpleDelete()
		{
			try
			{
				Builder.OpenLog( Builder.GetLogFileName( COMMANDS.SimpleDelete ), true );

				string PathName = Builder.CurrentCommandLine.Trim();

				Builder.Write( "Deleting: " + PathName );

				FileInfo Source = new FileInfo( PathName );
				if( Source.Exists )
				{
					Source.Delete();
				}
				else
				{
					// Silent "error" that will log the event, but not actually kill the build
					Builder.Write( "Warning: source file does not exist for deletion" );
				}

				Builder.CloseLog();
			}
			catch
			{
				ErrorLevel = COMMANDS.SimpleDelete;
				Builder.Write( "Error: exception deleting file" );
				Builder.CloseLog();
			}
		}

		private void SimpleRename()
		{
			try
			{
				Builder.OpenLog( Builder.GetLogFileName( COMMANDS.SimpleRename ), true );

				string[] Parms = Builder.SplitCommandline();
				if( Parms.Length != 2 )
				{
					Builder.Write( "Error: while renaming file (wrong number of parameters)" );
					ErrorLevel = COMMANDS.SimpleRename;
				}
				else
				{
					string BaseFolder = "";
					if( Builder.CopyDestination.Length > 0 )
					{
						BaseFolder = Builder.CopyDestination + "/" + Builder.BranchDef.Branch + "/";
					}

					Builder.Write( "Renaming: " );
					Builder.Write( " ... from: " + BaseFolder + Parms[0] );
					Builder.Write( " ... to: " + BaseFolder + Parms[1] );

					FileInfo Source = new FileInfo( BaseFolder + Parms[0] );
					if( Source.Exists )
					{
						FileInfo Dest = new FileInfo( BaseFolder + Parms[1] );
						if( Dest.Exists )
						{
							Dest.IsReadOnly = false;
							Dest.Delete();
						}
						Source.IsReadOnly = false;

						Source.CopyTo( Dest.FullName );
						Source.Delete();
					}
					else
					{
						Builder.Write( "Error: source file does not exist for renaming" );
						ErrorLevel = COMMANDS.SimpleRename;
					}
				}

				Builder.CloseLog();
			}
			catch
			{
				ErrorLevel = COMMANDS.SimpleRename;
				Builder.Write( "Error: exception renaming file" );
				Builder.CloseLog();
			}
		}

		private void RenamedCopy()
		{
			try
			{
				Builder.OpenLog( Builder.GetLogFileName( COMMANDS.RenamedCopy ), true );

				string[] Parms = Builder.SplitCommandline();
				if( Parms.Length != 2 )
				{
					Builder.Write( "Error: while renaming and copying file (wrong number of parameters)" );
					ErrorLevel = COMMANDS.RenamedCopy;
				}
				else
				{
					Builder.Write( "Renaming and copying: " );
					Builder.Write( " ... from: " + Parms[0] );
					Builder.Write( " ... to: " + Parms[1] );

					FileInfo Source = new FileInfo( Parms[0] );
					if( Source.Exists )
					{
						FileInfo Dest = new FileInfo( Parms[1] );
						if( Dest.Exists )
						{
							Builder.Write( " ... deleting: " + Dest.FullName );
							Dest.IsReadOnly = false;
							Dest.Delete();
						}

						Builder.Write( " ... creating: " + Dest.DirectoryName );
						Parent.EnsureDirectoryExists( Dest.DirectoryName );

						Source.CopyTo( Dest.FullName );
					}
					else
					{
						Builder.Write( "Error: source file does not exist for renaming and copying" );
						ErrorLevel = COMMANDS.RenamedCopy;
					}
				}

				Builder.CloseLog();
			}
			catch
			{
				ErrorLevel = COMMANDS.RenamedCopy;
				Builder.Write( "Error: exception renaming and copying file" );
				Builder.CloseLog();
			}
		}

		// Reads the list of files in a project from the specified project file
		private List<string> CheckForUCInVCProjFiles_GetProjectFiles( string ProjectPath, string FileExtension )
		{
			List<string> RelativeFilePaths = new List<string>();
			using( FileStream ProjectStream = new FileStream( ProjectPath, FileMode.Open, FileAccess.Read ) )
			{
				// Parse the project's root node.
				XPathDocument Doc = new XPathDocument( ProjectStream );
				XPathNavigator Nav = Doc.CreateNavigator();

				var MyNameTable = new NameTable();
				var NSManager = new XmlNamespaceManager( MyNameTable );
				NSManager.AddNamespace( "ns", "http://schemas.microsoft.com/developer/msbuild/2003" );

				XPathNavigator MSBuildProjVersion = Nav.SelectSingleNode( "/ns:Project/@ToolsVersion", NSManager );
				if( MSBuildProjVersion != null && ( MSBuildProjVersion.Value == "4.0" || MSBuildProjVersion.Value == "4,0" ) )
				{
					XPathNodeIterator UCIter = Nav.Select( "/ns:Project/ns:ItemGroup/ns:None/@Include", NSManager );
					foreach( XPathNavigator It in UCIter )
					{
						// Add all matching files to the tracking array
						if( It.Value.EndsWith( FileExtension, true, CultureInfo.CurrentCulture ) )
						{
							RelativeFilePaths.Add( Path.GetFileName( It.Value ).ToLowerInvariant() );
						}
					}
				}
			}
			return RelativeFilePaths;
		}

		// Gets the list of files that matches a specified pattern
		private void CheckForUCInVCProjFiles_DirectorySearch( string RootDirectory, string FilePattern, ref List<string> ListToAddTo )
		{
			foreach( string FileName in Directory.GetFiles( RootDirectory, FilePattern, SearchOption.AllDirectories ) )
			{
				ListToAddTo.Add( FileName.ToLowerInvariant() );
			}
		}

		private void CheckForUCInVCProjFiles()
		{
			List<string> ListOfUCFiles = new List<string>();
			List<string> ListOfProjects = new List<string>();
			Dictionary<string, List<string>> ListOfFilesInProjects = new Dictionary<string, List<string>>();

			Builder.OpenLog( Builder.GetLogFileName( COMMANDS.CheckForUCInVCProjFiles ), true );

			// We run from <branch>\Development\Builder and we need to get to <branch>\Development\Src
			string RootDirectory = Path.Combine( Environment.CurrentDirectory, "Development\\Src" );
			CheckForUCInVCProjFiles_DirectorySearch( RootDirectory, "*.uc", ref ListOfUCFiles );
			CheckForUCInVCProjFiles_DirectorySearch( RootDirectory, "*.vcxproj", ref ListOfProjects );
			foreach( string ProjectName in ListOfProjects )
			{
				ListOfFilesInProjects.Add( ProjectName, CheckForUCInVCProjFiles_GetProjectFiles( ProjectName, ".uc" ) );
			}

			// Check for any files on disk that are missing in the project
			int NumberOfMissingFiles = 0;
			foreach( string UCFile in ListOfUCFiles )
			{
				// For each script file...
				string UCFileDirName = Path.GetDirectoryName( UCFile ) + "\\";
				foreach( string ProjectName in ListOfProjects )
				{
					// Look in each project...
					List<string> ListOfFilesInProject;
					if( ListOfFilesInProjects.TryGetValue( ProjectName, out ListOfFilesInProject ) )
					{
						// Find the appropriate project...
						string ProjectDirectoryName = Path.GetDirectoryName( ProjectName ) + "\\";
						if( UCFileDirName.Contains( ProjectDirectoryName ) )
						{
							// If it's not there, log out an error...
							if( !ListOfFilesInProject.Contains( Path.GetFileName( UCFile ).ToLowerInvariant() ) )
							{
								Builder.Write( "Error: " + ProjectName + " is missing " + UCFile );
								NumberOfMissingFiles++;
							}
						}
					}
				}
			}
			if( NumberOfMissingFiles > 0 )
			{
				Builder.Write( "Error: missing " + NumberOfMissingFiles.ToString() + " file(s) from the project file" );
				ErrorLevel = COMMANDS.CheckForUCInVCProjFiles;
			}
			else
			{
				Builder.Write( "Not missing any files in the project file" );
			}

			// Check for any files in the project, missing from disk (forgot to check in a new file?)
			NumberOfMissingFiles = 0;
			foreach( string ProjectName in ListOfProjects )
			{
				// For each project...
				List<string> ListOfFilesInProject;
				if( ListOfFilesInProjects.TryGetValue( ProjectName, out ListOfFilesInProject ) )
				{
					// For each script file in the project...
					string ProjectClassesDirectoryName = Path.GetDirectoryName( ProjectName ) + "\\classes\\";
					foreach( string FileInProject in ListOfFilesInProject )
					{
						// Check for the script file on disk...
						string UCFileInProjectClassesDirectory = Path.Combine( ProjectClassesDirectoryName, FileInProject );
						if( !ListOfUCFiles.Contains( UCFileInProjectClassesDirectory ) )
						{
							Builder.Write( "Error: " + ProjectName + " contains a reference to " + UCFileInProjectClassesDirectory + ", which is missing on disk" );
							NumberOfMissingFiles++;
						}
					}
				}
			}
			if( NumberOfMissingFiles > 0 )
			{
				Builder.Write( "Error: missing " + NumberOfMissingFiles.ToString() + " script file(s) on disk that are referenced in projects" );
				ErrorLevel = COMMANDS.CheckForUCInVCProjFiles;
			}
			else
			{
				Builder.Write( "Not missing any files on disk" );
			}

			Builder.CloseLog();
		}

		private void SmokeTest()
		{
			try
			{
				string LogFileName = Builder.GetLogFileName( COMMANDS.SmokeTest );
				Builder.OpenLog( LogFileName, false );

				GameConfig Config = Builder.CreateGameConfig();
				CleanIniFiles( Config );

				List<string> Executables = Config.GetExecutableNames( Builder.BranchDef.Version );
				if( Executables.Count > 0 )
				{
					string CommandLine = "smoketest " + CommonCommandLine;

					// Special smoketest for dedicated servers
					if( Config.Platform.ToLower() == "win32server" )
					{
						CommandLine = "-smoketest -login=epicsmoketest@xboxtest.com -password=supersecret " + CommonCommandLine;
					}

					CurrentBuild = new BuildProcess( Parent, Builder, Executables[0], CommandLine, "", true );
					ErrorLevel = CurrentBuild.GetErrorLevel();

					StartTime = DateTime.UtcNow;
				}
				else
				{
					ErrorLevel = COMMANDS.SmokeTest;
					Builder.Write( "Error: could not evaluate executable name" );
					Builder.CloseLog();
				}
			}
			catch
			{
				ErrorLevel = COMMANDS.SmokeTest;
				Builder.Write( "Error: exception while starting smoke test" );
				Builder.CloseLog();
			}
		}

		private void LoadPackages()
		{
			try
			{
				string LogFileName = Builder.GetLogFileName( COMMANDS.LoadPackages );
				Builder.OpenLog( LogFileName, false );

				// Optional command line parameter to set the packages to load
				string PackageNames = "-all";
				if( Builder.CurrentCommandLine.Length > 0 )
				{
					PackageNames = Builder.CurrentCommandLine;
				}

				GameConfig Config = Builder.CreateGameConfig();
				CleanIniFiles( Config );

				string CommandLine = "";
				string Executable = Config.GetComName( Builder.BranchDef.Version, ref CommandLine );
				CommandLine += "loadpackage " + PackageNames + " " + CommonCommandLine;

				CurrentBuild = new BuildProcess( Parent, Builder, Executable, CommandLine, "", true );
				ErrorLevel = CurrentBuild.GetErrorLevel();

				StartTime = DateTime.UtcNow;
			}
			catch
			{
				ErrorLevel = COMMANDS.LoadPackages;
				Builder.Write( "Error: exception while starting loading all packages" );
				Builder.CloseLog();
			}
		}

		private void CookPackages()
		{
			try
			{
				string LogFileName = Builder.GetLogFileName( COMMANDS.CookPackages );
				Builder.OpenLog( LogFileName, false );

				string[] Params = Builder.SplitCommandline();
				if( Params.Length < 1 )
				{
					Builder.Write( "Error: wrong number of parameters. Usage: " + COMMANDS.CookPackages.ToString() + " <Platform>" );
					ErrorLevel = COMMANDS.CookPackages;
					return;
				}

				// Optional command line parameter to set the packages to load
				string PackageNames = "-full";
				if( Params.Length > 1 )
				{
					PackageNames = Builder.CurrentCommandLine.Substring( Params[0].Length ).Trim();
				}

				GameConfig Config = Builder.CreateGameConfig();

				string CommandLine = "";
				string Executable = Config.GetComName( Builder.BranchDef.Version, ref CommandLine );
				CommandLine += "cookpackages -platform=" + Params[0] + " " + PackageNames + " " + CommonCommandLine;

				CurrentBuild = new BuildProcess( Parent, Builder, Executable, CommandLine, "", true );
				ErrorLevel = CurrentBuild.GetErrorLevel();

				StartTime = DateTime.UtcNow;
			}
			catch
			{
				ErrorLevel = COMMANDS.CookPackages;
				Builder.Write( "Error: exception while starting cooking all packages" );
				Builder.CloseLog();
			}
		}

		private void CleanupSymbolServer()
		{
			try
			{
				string LogFileName = Builder.GetLogFileName( COMMANDS.CleanupSymbolServer );
				Builder.OpenLog( LogFileName, false );

				// Remove everything older than 90 days
				DateTime PurgeDate = DateTime.Now - new TimeSpan( 60, 0, 0, 0, 0 );
				string SymbolStoreLoc = @"\\epicgames.net\root\UE3\Builder\BuilderSymbols";
				//				string SymbolStoreApp = @"C:\Program Files (x86)\Debugging Tools for Windows (x86)\symstore.exe";
				string[] ServerLogLines = File.ReadAllLines( SymbolStoreLoc + @"\000Admin\server.txt" );
				TimeSpan TimeToPurge = new TimeSpan();
				foreach( string LogLine in ServerLogLines )
				{
					string[] SplitLogLine = LogLine.Split( ',' );
					// We expect a very specific format for these strings. Something like:
					// 0000000003,add,file,04/18/2007,15:16:36,"UnrealEngine3-Xenon","0","2983",
					if( SplitLogLine.Length == 9 )
					{
						// Parse to an int to strip off the leading zeros
						string SymbolTransactionID = SplitLogLine[0];
						DateTime EntryDate = DateTime.Parse( SplitLogLine[3] );
						if( EntryDate < PurgeDate )
						{
							Builder.Write( "Removing symbol transaction " + SymbolTransactionID );
							DateTime StartTime = DateTime.Now;

							// The official way
							// 							Process DeleteProcess = Process.Start( SymbolStoreApp, "del /s " + SymbolStoreLoc + " /i " + SymbolTransactionID );
							// 							DeleteProcess.WaitForExit();

							// The less-than-official way
							string TransactionFilename = SymbolStoreLoc + @"\000Admin\" + SymbolTransactionID;
							if( File.Exists( TransactionFilename ) )
							{
								string[] TransactionFileLines = File.ReadAllLines( TransactionFilename );
								foreach( string TransactionLine in TransactionFileLines )
								{
									string[] SplitTransactionLine = TransactionLine.Split( ',' );
									string TransactionDirectoryNameRaw = SplitTransactionLine[0].Substring( 1, SplitTransactionLine[0].Length - 2 );
									string TransactionDirectoryName = SymbolStoreLoc + "\\" + TransactionDirectoryNameRaw;
									if( Directory.Exists( TransactionDirectoryName ) )
									{
										try
										{
											Directory.Delete( TransactionDirectoryName, true );
										}
										catch( Exception Ex )
										{
											Builder.Write( "Delete error: " + Ex.ToString() );
										}
									}
								}
								try
								{
									File.Move( TransactionFilename, TransactionFilename + ".deleted" );
								}
								catch( Exception Ex )
								{
									Builder.Write( "Move error: " + Ex.ToString() );
								}
							}

							TimeToPurge = DateTime.Now - StartTime;
							Builder.Write( "Last removal took " + TimeToPurge.ToString() );
						}
						else
						{
							//Builder.Write( "Keeping symbol transaction " + SymbolTransactionID );
						}
					}
				}
			}
			catch( Exception Ex )
			{
				ErrorLevel = COMMANDS.CleanupSymbolServer;
				Builder.Write( "Error: exception while cleaning up the symbol server" );
				Builder.Write( "Exception: " + Ex.ToString() );
			}
			Builder.CloseLog();
		}

		public MODES Execute()
		{
			switch( Builder.CurrentCommandID )
			{
			case COMMANDS.SCC_CheckConsistency:
				SCC_CheckConsistency();
				return ( MODES.Finalise );

			case COMMANDS.SCC_Sync:
				SCC_Sync();
				return ( MODES.Finalise );

			case COMMANDS.SCC_SyncToHead:
				SCC_SyncToHead();
				return ( MODES.Finalise );

			case COMMANDS.SCC_ArtistSync:
				SCC_ArtistSync();
				return ( MODES.Finalise );

			case COMMANDS.SCC_GetChanges:
				SCC_GetChanges();
				return ( MODES.Finalise );

			case COMMANDS.SCC_SyncSingleChangeList:
				SCC_SyncSingleChangeList();
				return ( MODES.Finalise );

			case COMMANDS.SCC_Checkout:
				SCC_Checkout();
				return ( MODES.Finalise );

			case COMMANDS.SCC_OpenForDelete:
				SCC_OpenForDelete();
				return ( MODES.Finalise );

			case COMMANDS.SCC_CheckoutGame:
				SCC_GenericCheckout( COMMANDS.SCC_CheckoutGame );
				return ( MODES.Finalise );

			case COMMANDS.SCC_CheckoutGFWLGame:
				SCC_GenericCheckout( COMMANDS.SCC_CheckoutGFWLGame );
				return ( MODES.Finalise );

			case COMMANDS.SCC_CheckoutGADCheckpoint:
				SCC_GenericCheckout( COMMANDS.SCC_CheckoutGADCheckpoint );
				return ( MODES.Finalise );

			case COMMANDS.SCC_CheckoutShader:
				SCC_GenericCheckout( COMMANDS.SCC_CheckoutShader );
				return ( MODES.Finalise );

			case COMMANDS.SCC_CheckoutDialog:
				SCC_CheckoutDialog();
				return ( MODES.Finalise );

			case COMMANDS.SCC_CheckoutFonts:
				SCC_CheckoutFonts();
				return ( MODES.Finalise );

			case COMMANDS.SCC_CheckoutLocPackage:
				SCC_CheckoutLocPackage();
				return ( MODES.Finalise );

			case COMMANDS.SCC_CheckoutGDF:
				SCC_CheckoutGDF();
				return ( MODES.Finalise );

			case COMMANDS.SCC_CheckoutCat:
				SCC_CheckoutCat();
				return ( MODES.Finalise );

			case COMMANDS.SCC_CheckoutLayout:
				SCC_GenericCheckout( COMMANDS.SCC_CheckoutLayout );
				return ( MODES.Finalise );

			case COMMANDS.SCC_CheckoutHashes:
				SCC_GenericCheckout( COMMANDS.SCC_CheckoutHashes );
				return ( MODES.Finalise );

			case COMMANDS.SCC_CheckoutDLC:
				SCC_CheckoutDLC();
				return ( MODES.Finalise );

			case COMMANDS.SCC_CheckoutEngineContent:
				SCC_GenericCheckout( COMMANDS.SCC_CheckoutEngineContent );
				return ( MODES.Finalise );

			case COMMANDS.SCC_CheckoutGameContent:
				SCC_GenericCheckout( COMMANDS.SCC_CheckoutGameContent );
				return ( MODES.Finalise );

			case COMMANDS.SCC_CheckoutAFTScreenshots:
				SCC_GenericCheckout( COMMANDS.SCC_CheckoutAFTScreenshots );
				return ( MODES.Finalise );

			case COMMANDS.SCC_CheckoutConnCache:
				SCC_GenericCheckout( COMMANDS.SCC_CheckoutConnCache );
				return ( MODES.Finalise );

			case COMMANDS.SCC_GetNextChangelist:
				SCC_GetNextChangelist();
				return ( MODES.Finalise );

			case COMMANDS.SCC_Submit:
				SCC_Submit();
				return ( MODES.Finalise );

			case COMMANDS.SCC_CreateNewLabel:
				SCC_CreateNewLabel();
				return ( MODES.Finalise );

			case COMMANDS.SCC_LabelUpdateDescription:
				SCC_LabelUpdateDescription();
				return ( MODES.Finalise );

			case COMMANDS.SCC_Revert:
				SCC_Revert();
				return ( MODES.Finalise );

			case COMMANDS.SCC_RevertFileSpec:
				SCC_RevertFileSpec();
				return ( MODES.Finalise );

			case COMMANDS.SCC_Tag:
				SCC_Tag();
				return ( MODES.Finalise );

			case COMMANDS.AddUnrealGameJob:
				AddUnrealGameJob();
				return ( MODES.Finalise );

			case COMMANDS.AddUnrealAgnosticJob:
				AddUnrealAgnosticJob();
				return ( MODES.Finalise );

			case COMMANDS.AddUnrealFullGameJob:
				AddUnrealFullGameJob();
				return ( MODES.Finalise );

			case COMMANDS.AddUnrealGFWLGameJob:
				AddUnrealGFWLGameJob();
				return ( MODES.Finalise );

			case COMMANDS.AddUnrealGFWLFullGameJob:
				AddUnrealGFWLFullGameJob();
				return ( MODES.Finalise );

			case COMMANDS.AddConformJob:
				AddConformJob();
				return ( MODES.Finalise );

			case COMMANDS.Clean:
				Clean();
				return ( MODES.Finalise );

			case COMMANDS.CleanMac:
				CleanMac();
				return ( MODES.Monitor );

			case COMMANDS.BuildUBT9:
				BuildUBT( "v3.5" );
				return ( MODES.Monitor );

			case COMMANDS.BuildUBT10:
				BuildUBT( "v4.0.30319" );
				return ( MODES.Monitor );

			case COMMANDS.MS9Build:
				MS_Build( COMMANDS.MS9Build );
				return ( MODES.Monitor );

			case COMMANDS.MS10Build:
				MS_Build( COMMANDS.MS10Build );
				return ( MODES.Monitor );

			case COMMANDS.MSVC9Clean:
				MSVC_Clean( COMMANDS.MSVC9Clean, Builder.MSVC9Application );
				return ( MODES.Monitor );

			case COMMANDS.MSVC9Build:
				MSVC_Build( COMMANDS.MSVC9Build, Builder.MSVC9Application );
				return ( MODES.Monitor );

			case COMMANDS.MSVC9Deploy:
				MS_Deploy( COMMANDS.MSVC9Deploy );
				return ( MODES.Monitor );

			case COMMANDS.MSVC10Clean:
				MSVC_Clean( COMMANDS.MSVC10Clean, Builder.MSVC10Application );
				return ( MODES.Monitor );

			case COMMANDS.MSVC10Build:
				MSVC_Build( COMMANDS.MSVC10Build, Builder.MSVC10Application );
				return ( MODES.Monitor );

			case COMMANDS.MSVC10Deploy:
				MS_Deploy( COMMANDS.MSVC10Deploy );
				return ( MODES.Monitor );

			case COMMANDS.UnrealBuild:
				Unreal_Build( !Builder.bXGEHasFailed && Builder.AllowXGE );
				return ( MODES.Monitor );

			case COMMANDS.ShaderClean:
				Shader_Clean();
				return ( MODES.Finalise );

			case COMMANDS.ShaderBuild:
				Shader_Build();
				return ( MODES.Monitor );

			case COMMANDS.LocalShaderBuild:
				LocalShader_Build();
				return ( MODES.Monitor );

			case COMMANDS.CookShaderBuild:
				CookShader_Build();
				return ( MODES.Monitor );

			case COMMANDS.ConnectionBuild:
				ConnectionBuild();
				return ( MODES.Monitor );

			case COMMANDS.PS3MakePatchBinary:
				PS3MakePatchBinary();
				return ( MODES.Monitor );

			case COMMANDS.PS3MakePatch:
				PS3MakePatch();
				return ( MODES.Monitor );

			case COMMANDS.PS3MakeDLC:
				PS3MakeDLC();
				return ( MODES.Monitor );

			case COMMANDS.PS3MakeTU:
				PS3MakeTU();
				return ( MODES.Monitor );

			case COMMANDS.PCMakeTU:
				PCMakeTU();
				return ( MODES.Monitor );

			case COMMANDS.PCPackageTU:
				PCPackageTU();
				return ( MODES.Monitor );

			case COMMANDS.BuildScript:
				BuildScript( COMMANDS.BuildScript );
				return ( MODES.Monitor );

			case COMMANDS.BuildScriptNoClean:
				BuildScript( COMMANDS.BuildScriptNoClean );
				return ( MODES.Monitor );

			case COMMANDS.Commandlet:
				Commandlet();
				return ( MODES.Monitor );

			case COMMANDS.iPhonePackage:
				iPhonePackage();
				return ( MODES.Monitor );

			case COMMANDS.PreHeatMapOven:
				PreHeat();
				return ( MODES.Finalise );

			case COMMANDS.PreHeatDLC:
				PreHeatDLC();
				return ( MODES.Finalise );

			case COMMANDS.CookMaps:
				Cook();
				return ( MODES.Monitor );

			case COMMANDS.CookIniMaps:
				CookIniMaps();
				return ( MODES.Monitor );

			case COMMANDS.CookSounds:
				CookSounds();
				return ( MODES.Monitor );

			case COMMANDS.CreateHashes:
				CreateHashes();
				return ( MODES.Monitor );

			case COMMANDS.Wrangle:
				Wrangle();
				return ( MODES.Monitor );

			case COMMANDS.Publish:
				Publish();
				return ( MODES.Monitor );

			case COMMANDS.PublishTagset:
				PublishTagset();
				return ( MODES.Monitor );

			case COMMANDS.PublishLanguage:
				PublishLanguage();
				return ( MODES.Monitor );

			case COMMANDS.PublishLayout:
				PublishLayout();
				return ( MODES.Monitor );

			case COMMANDS.PublishLayoutLanguage:
				PublishLayoutLanguage();
				return ( MODES.Monitor );

			case COMMANDS.PublishDLC:
				PublishDLC();
				return ( MODES.Monitor );

			case COMMANDS.PublishTU:
				PublishTU();
				return ( MODES.Monitor );

			case COMMANDS.PublishFiles:
				PublishFiles();
				return ( MODES.Monitor );

			case COMMANDS.PublishRawFiles:
				PublishRawFiles();
				return ( MODES.Monitor );

			case COMMANDS.GenerateTOC:
				GenerateTOC();
				return ( MODES.Monitor );

			case COMMANDS.Deploy:
				Deploy();
				return ( MODES.Monitor );

			case COMMANDS.MakeISO:
				MakeISO();
				return ( MODES.Monitor );

			case COMMANDS.MakeMD5:
				MakeMD5();
				return ( MODES.Finalise );

			case COMMANDS.CopyFolder:
				CopyFolder();
				return ( MODES.Monitor );

			case COMMANDS.MoveFolder:
				MoveFolder();
				return ( MODES.Monitor );

			case COMMANDS.CleanFolder:
				CleanFolder();
				return ( MODES.Monitor );

			case COMMANDS.GetPublishedData:
				GetPublishedData();
				return ( MODES.Monitor );

			case COMMANDS.LaunchGame:
				LaunchGame();
				return ( MODES.Monitor );

			case COMMANDS.LaunchConsole:
				LaunchConsole();
				return ( MODES.Finalise );

			case COMMANDS.RetrieveScreenShots:
				RetrieveScreenShots();
				return ( MODES.Finalise );

			case COMMANDS.ProcessScreenShots:
				ProcessScreenShots();
				return ( MODES.Finalise );

			case COMMANDS.SteamMakeVersion:
				SteamMakeVersion();
				return ( MODES.Monitor );

			case COMMANDS.UpdateSteamServer:
				UpdateSteamServer();
				return ( MODES.Monitor );

			case COMMANDS.StartSteamServer:
				StartSteamServer();
				return ( MODES.Monitor );

			case COMMANDS.StopSteamServer:
				StopSteamServer();
				return ( MODES.Monitor );

			case COMMANDS.UnSetup:
				UnSetup();
				return ( MODES.Monitor );

			case COMMANDS.CreateDVDLayout:
				CreateDVDLayout();
				return ( MODES.Monitor );

			case COMMANDS.Conform:
				Conform();
				return ( MODES.Monitor );

			case COMMANDS.PatchScript:
				PatchScript();
				return ( MODES.Monitor );

			case COMMANDS.CheckpointGameAssetDatabase:
				CheckpointGameAssetDatabase( "" );
				return ( MODES.Monitor );

			case COMMANDS.UpdateGameAssetDatabase:
				// Note: This will delete all private collections and any collection whose name does not begin with "UDK"!
				CheckpointGameAssetDatabase( "-NoDeletes -Repair -PurgeGhosts -DeletePrivateCollections -DeleteNonUDKCollections " );
				return ( MODES.Monitor );

			case COMMANDS.TagReferencedAssets:
				TagReferencedAssets( false );
				return ( MODES.Monitor );

			case COMMANDS.TagDVDAssets:
				TagReferencedAssets( true );
				return ( MODES.Monitor );

			case COMMANDS.AuditContent:
				AuditContent();
				return ( MODES.Monitor );

			case COMMANDS.FindStaticMeshCanBecomeDynamic:
				FindStaticMeshCanBecomeDynamic();
				return ( MODES.Monitor );

			case COMMANDS.FixupRedirects:
				FixupRedirects();
				return ( MODES.Monitor );

			case COMMANDS.ResaveDeprecatedPackages:
				ResaveDeprecatedPackages();
				return ( MODES.Monitor );

			case COMMANDS.AnalyzeReferencedContent:
				AnalyzeReferencedContent();
				return ( MODES.Monitor );

			case COMMANDS.MineCookedPackages:
				MineCookedPackages();
				return ( MODES.Monitor );

			case COMMANDS.ContentComparison:
				ContentComparison();
				return ( MODES.Monitor );

			case COMMANDS.DumpMapSummary:
				DumpMapSummary();
				return ( MODES.Monitor );

			case COMMANDS.ValidateInstall:
				ValidateInstall();
				return ( MODES.Monitor );

			case COMMANDS.ExtractSHAs:
				ExtractSHAs();
				return ( MODES.Monitor );

			case COMMANDS.CheckSHAs:
				CheckSHAs();
				return ( MODES.Finalise );

			case COMMANDS.BumpAgentVersion:
				BumpAgentVersion();
				return ( MODES.Finalise );

			case COMMANDS.BumpEngineVersion:
				BumpEngineVersion();
				return ( MODES.Finalise );

			case COMMANDS.GetEngineVersion:
				GetEngineVersion();
				return ( MODES.Finalise );

			case COMMANDS.UpdateGDFVersion:
				UpdateGDFVersion();
				return ( MODES.Finalise );

			case COMMANDS.MakeGFWLCat:
				MakeGFWLCat();
				return ( MODES.Monitor );

			case COMMANDS.ZDPP:
				ZDPP();
				return ( MODES.Monitor );

			case COMMANDS.SteamDRM:
				SteamDRM();
				return ( MODES.Monitor );

			case COMMANDS.FixupSteamDRM:
				FixupSteamDRM();
				return ( MODES.Finalise );

			case COMMANDS.SaveDefines:
				SaveDefines();
				return ( MODES.Finalise );

			case COMMANDS.UpdateSourceServer:
				UpdateSourceServer();
				return ( MODES.Monitor );

			case COMMANDS.UpdateSymbolServer:
				UpdateSymbolServer();
				return ( MODES.Finalise );

			case COMMANDS.AddExeToSymbolServer:
				AddToSymbolServer( true );
				return ( MODES.Finalise );

			case COMMANDS.AddDllToSymbolServer:
				AddToSymbolServer( false );
				return ( MODES.Finalise );

			case COMMANDS.UpdateSymbolServerTick:
				UpdateSymbolServerTick();
				return ( MODES.Monitor );

			case COMMANDS.PackageTU:
				PackageTU();
				return ( MODES.Monitor );

			case COMMANDS.PackageDLC:
				PackageDLC();
				return ( MODES.Monitor );

			case COMMANDS.CheckSigned:
				CheckSigned();
				return ( MODES.Monitor );

			case COMMANDS.Sign:
				Sign();
				return ( MODES.Monitor );

			case COMMANDS.SignCat:
				SignCat();
				return ( MODES.Monitor );

			case COMMANDS.SignBinary:
				SignBinary();
				return ( MODES.Monitor );

			case COMMANDS.SignFile:
				SignFile();
				return ( MODES.Monitor );

			case COMMANDS.SimpleCopy:
				SimpleCopy();
				return ( MODES.Finalise );

			case COMMANDS.SetSteamID:
				SetSteamID();
				return ( MODES.Finalise );

			case COMMANDS.CopyScriptPatchFiles:
				CopyScriptPatchFiles();
				return ( MODES.Finalise );

			case COMMANDS.SourceBuildCopy:
				SourceBuildCopy();
				return ( MODES.Finalise );

			case COMMANDS.SimpleDelete:
				SimpleDelete();
				return ( MODES.Finalise );

			case COMMANDS.SimpleRename:
				SimpleRename();
				return ( MODES.Finalise );

			case COMMANDS.RenamedCopy:
				RenamedCopy();
				return ( MODES.Finalise );

			case COMMANDS.CheckForUCInVCProjFiles:
				CheckForUCInVCProjFiles();
				return ( MODES.Finalise );

			case COMMANDS.SmokeTest:
				SmokeTest();
				return ( MODES.Monitor );

			case COMMANDS.LoadPackages:
				LoadPackages();
				return ( MODES.Monitor );

			case COMMANDS.CookPackages:
				CookPackages();
				return ( MODES.Monitor );

			case COMMANDS.CreateMGSTrigger:
				CreateMGSTrigger();
				return ( MODES.Finalise );

			case COMMANDS.FTPSendFile:
				FTPSendFile();
				return ( MODES.WaitForFTP );

			case COMMANDS.FTPSendFolder:
				FTPSendFolder();
				return ( MODES.WaitForFTP );

			case COMMANDS.FTPSendImage:
				FTPSendImage();
				return ( MODES.WaitForFTP );

			case COMMANDS.ZipAddImage:
				ZipAddItem( COMMANDS.ZipAddImage );
				return ( MODES.Finalise );

			case COMMANDS.ZipAddFile:
				ZipAddItem( COMMANDS.ZipAddFile );
				return ( MODES.Finalise );

			case COMMANDS.ZipSave:
				ZipSave();
				return ( MODES.Finalise );

			case COMMANDS.CleanupSymbolServer:
				CleanupSymbolServer();
				return ( MODES.Monitor );
			}

			return ( MODES.Init );
		}

		public bool IsTimedOut()
		{
			return ( DateTime.UtcNow - StartTime > Builder.GetTimeout() );
		}

		public MODES IsFinished()
		{
			// Also check for timeout
			if( CurrentBuild != null )
			{
				if( CurrentBuild.IsFinished )
				{
					CurrentBuild.Cleanup();
					return ( MODES.Finalise );
				}

				if( IsTimedOut() )
				{
					CurrentBuild.Kill();
					ErrorLevel = COMMANDS.TimedOut;
					return ( MODES.Finalise );
				}

				if( !CurrentBuild.IsResponding() )
				{
					if( DateTime.UtcNow - LastRespondingTime > Builder.GetRespondingTimeout() )
					{
						CurrentBuild.Kill();
						ErrorLevel = COMMANDS.Crashed;
						return ( MODES.Finalise );
					}
				}
				else
				{
					LastRespondingTime = DateTime.UtcNow;
				}

				return ( MODES.Monitor );
			}

			// No running build? Something went wrong
			return ( MODES.Finalise );
		}

		public void Kill()
		{
			if( CurrentBuild != null )
			{
				CurrentBuild.Kill();
			}
		}
	}
}
