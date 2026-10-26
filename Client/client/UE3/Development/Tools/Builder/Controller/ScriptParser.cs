/**
 * Copyright 1998-2012 Epic Games, Inc. All Rights Reserved.
 */
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Text;
using System.Threading;
using P4API;
using Ionic.Zip;
using UnrealControls;

namespace Controller
{
    public partial class ScriptParser
    {
        public enum COLLATION
        {
			Engine,
			Rendering,
			Audio,
			Editor,
			GFx,
			Game	= 10,

            Windows = 100,
			Xbox360,
            PS3,
			WiiU,
			NGP,
			iPhone,
			Android,
			Mac,
			Flash,

			OnlinePC,
			GameCenter,
			GameSpy,
			G4WLive,
			Steam,

			Infrastructure,
			Swarm,
			Lightmass,
			Tools,
			Install,
			Loc,

			Count,
        }

        public class ChangeList
        {
            public int Number;
            public string User;
            public int Time;
            public string Description;
            public COLLATION Collate;
            public List<string> Files = new List<string>();

            public ChangeList()
            {
                Number = 0;
                Time = 0;
                Collate = COLLATION.Count;
            }

            public void CleanDescription()
            {
				string WorkDescription = Description.Replace( "\r", "" ).Trim();

				// Replace any characters that could mess up a SQL query
				WorkDescription = WorkDescription.Replace( "\'", "" );
				WorkDescription = WorkDescription.Replace( "\"", "" );

				Description = "";

				// Process lines in their entirety
				string[] Lines = WorkDescription.Split( "\n".ToCharArray() );
				foreach( string Line in Lines )
				{
					// Skip any code review lines
					if( Line.ToLower().StartsWith( "#codereview" ) )
					{
						continue;
					}

					// Parse each word on the line
	                string[] Parms = Line.Trim().Split( " \t".ToCharArray() );
					string NewLine = "";
					for( int i = 0; i < Parms.Length; i++ )
					{
						string Token = Parms[i];

						if( Token.Length < 1 )
						{
							continue;
						}

						// Skip any tags
						if( Token.StartsWith( "#" ) )
						{
							if( Token.Length > 1 )
							{
								if( Token[1] < '0' || Token[1] > '9' )
								{
									continue;
								}
							}
						}

						NewLine += Token + " ";
					}

					if( NewLine.Length > 0 )
					{
						Description += "\t" + NewLine + Environment.NewLine;
					}
                }
            }
        }

        public class CollationType
        {
            public COLLATION Collation;
			public string Title;
            public bool Active;
			public List<String> FolderMatches = new List<String>();

            public CollationType( COLLATION InCollation, string InTitle )
            {
				Collation = InCollation;
				Title = InTitle;
                Active = false;
            }

			public void SetFolderMatches( List<string> Matches )
			{
				FolderMatches = Matches;
			}

            static public COLLATION GetReportType( string CollType, List<string> ValidGames )
            {
				// Is it a member of the predefined enum list?
                if( Enum.IsDefined( typeof( COLLATION ), CollType ) )
                {
                    COLLATION Report = ( COLLATION )Enum.Parse( typeof( COLLATION ), CollType, true );
                    return ( Report );
                }

				// Is it a dynamically generated enum?
				int GameCollation = ( int )COLLATION.Game;
				foreach( string ValidGame in ValidGames )
				{
					string GameName = ValidGame.ToLower();
					string GameNameMaps = GameName + "maps";
					string GameNameContent = GameName + "content";

					if( CollType.ToLower() == GameName )
					{
						return ( ( COLLATION )GameCollation );
					}
					else if( CollType.ToLower() == GameNameMaps )
					{
						return ( ( COLLATION )( GameCollation + 1 ) );
					}
					else if( CollType.ToLower() == GameNameContent )
					{
						return ( ( COLLATION )( GameCollation + 2 ) );
					}

					GameCollation += 3;
				}

                return ( COLLATION.Count );
            }
        }

		// Current command packet the builder is working on
		public COMMANDS CurrentCommandID = COMMANDS.Error;
		public string CurrentCommandLine = "";

		// Root name of the current log file
        private string LogFileRootName = "";

		// Location of DevEnv
		public string MSVC9Application { get; set; }

		// Location of DevEnv
		public string MSVC10Application { get; set; }

		// Location of signing tool - C:\Program Files\Microsoft SDKs\Windows\v6.0A\Bin
        public string SignToolName { get; set; }

		// Location of cat tool - C:\Program Files\Microsoft SDKs\Windows\v6.0A\Bin
		public string CatToolName { get; set; }

		// Location of cat tool - GFWLSDK_DIR\tools\ZeroDayPiracyProtection\ZdpSdkTool.exe
		public string ZDPPToolName { get; set; }

        // Location of source server perl script
        public string SourceServerCmd { get; set; }

        // Location of symstore
        public string SymbolStoreApp { get; set; }

        // Location of XDK tools
        public string BlastTool { get; set; }

        // The location of the symbol store database
        public string SymbolStoreLocation { get; set; }

		// The location of the pfx file used to sign installers
		public string KeyLocation { get; set; }

		// The password for the above pfx
		public string KeyPassword { get; set; }

        // Location to save error string (if any)
        public string ErrorSaveVariable { get; set; }

        // Location of make for PS3
        public string MakeApplication { get; set; }

		// Location of the Steam Content Tool
		public string SteamContentToolLocation { get; set; }

		// Location of the Steam Content Server
		public string SteamContentServerLocation { get; set; }

        // The master file that contains the version to use
        public string EngineVersionFile { get; set; }

        // The misc version files that the engine version is propagated to
        public string MiscVersionFiles { get; set; }

		// The console specific version files that the engine version is propagated to
		public string ConsoleVersionFiles { get; set; }

		// The mobile specific version files that the engine version is propagated to
		public string MobileVersionFiles { get; set; }

		// The current job to copy down from server
        public string UBTEnvVar { get; set; }

		public enum ErrorModeType
		{
			CheckErrors,
			IgnoreErrors,
			SuppressErrors,
		}

		// Whether to check for errors in the build log
		public ErrorModeType ErrorMode { get; set; }

		// Whether a suppressed error has been seen in this task
		public bool HasSuppressedErrors { get; set; }

		// Whether to allow warnings when compiling script code
		public bool AllowSloppyScript { get; set; }

		// Whether to cc EngineQA
		public bool OfficialBuild { get; set; }

		// Whether to include the disambiguating timestamp folder when acquiring an installable build
		public bool IncludeTimestampFolder { get; set; }

		// Do we allow XGE for non primary builds
		public bool AllowXGE { get; set; }

		// Do we allow PCH for compilation?
		public bool AllowPCH { get; set; }

		// Do we want to specify the output on the commandline?
		public bool SpecifyOutput { get; set; }

		// The branch that we are compiling from e.g. UnrealEngine3-Delta
        public Main.BranchDefinition BranchDef { get; set; }

		// Details from the database on the command we're running
		public Main.CommandInfo CommandDetails { get; set; }

		// Cached string containing the script root folder
		public string ScriptRoot { get; set; }

        // Cached string containing the name of the user who killed the build
        public string Killer { get; set; }

        // The most recent label that was synced to
        public string SyncedLabel { get; set; }

		// The head changelist when syncing starts
		public int HeadChangelist { get; set; }

        // Time the local build started waiting for network bandwidth
        public DateTime StartWaitForConch { get; set; }

        // The last time the local build sent a status update
        public DateTime LastWaitForConchUpdate { get; set; }

        // Whether a label has already been created to host the files
        public bool NewLabelCreated { get; set; }

		// Use this name instead of the game name in the publish folder
		public string GameNameOverride { get; set; }

		// The sub branch to use in addition to the branch the game runs out of
		public string SubBranchName { get; set; }

		// Whether to include the platform in the publish folder
		public bool IncludePlatform { get; set; }

        // Whether to block other publish operations to throttle the network
        public bool BlockOnPublish { get; set; }

        // Whether to ignore timestamps when publishing
        public bool ForceCopy { get; set; }

		// Whether to use the 64 bit or 32 bit binaries
		public bool Use64BitBinaries { get; set; }

		// Whether to strip source content when wrangling
		public bool StripSourceContent { get; set; }

		public enum PublishModeType
		{
			Files,
			Zip,
			Iso,
			Xsf
		}

		// Whether to publish raw files, add them to a zip, or add to an iso
		public PublishModeType PublishMode { get; set; }

		public enum PublishVerificationType
		{
			None,
			MD5
		}

		// The type of verification used when publishing builds
		public PublishVerificationType PublishVerification { get; set; }

		// Which audio assets to keep when wrangling
		public string KeepAssets { get; set; }

		// Whether to allow engine packages to be submitted after a several fixup redirects
		public bool bCommandletsSuccessful { get; set; }

		// The type of installer UnSetup will build
		public string UnSetupType { get; set; }

		// The database connection info
		public string DataBaseName { get; set; }
		public string DataBaseCatalog { get; set; }

        // Whether to enable unity stress testing
        public bool UnityStressTest { get; set; }

		// Whether to enable unity source file concatenation
		public bool UnityDisable { get; set; }

		// The name of the sku (currently used for disambiguating layout filenames)
		public string SkuName { get; set; }

		// The root location where the cooked files are copied to
        public string PublishFolder { get; set; }

        // The email addresses to send to when a build is triggered
        public string TriggerAddress { get; set; }

        // The email addresses to send to when a build fails
        public string FailAddress { get; set; }

        // The email addresses to send to when a build is successful
        public string SuccessAddress { get; set; }

		// A mailing list to cc all the emails to
		public string CarbonCopyAddress { get; set; }

		// A list of lines that make up the BUNs email
		public List<string> BUNs { get; set; }

        // The label or build that this build syncs to
        public string Dependency { get; set; }

        // The other build needed from cross platform conforming
		public string SourceBuild { get; set; }
        
        // A C++ define to be passed to the compiler
        public string BuildDefine { get; set; }

        // Destination folder of simple copy operations
        public string CopyDestination { get; set; }

		// The mode for saving a DVD image (e.g. ISO or XSF)
		public string ImageMode { get; set; }

        // The current mod name we are cooking for
		public string DLCName { get; set; }

        // The current command line for the builder command
        public string LogFileName { get; set; }

        // If there is a 'submit' at some point in the build script
        public bool IsBuilding { get; set; }

		// If we want to tag files to the label when submitting
		public bool IsTagging { get; set; }

		// If we want to preserve the head revision after submitting the builder's
		// changes, if we're not at the head revision already
		public bool IsRestoringNewerChanges { get; set; }

		// If there is a 'tag' at some point in the build script
        public bool IsPromoting { get; set; }

        // If there is a 'publish' at some point in the build script
        public bool IsPublishing { get; set; }

        // If there is a 'UserChanges' at some point in the build script
        public bool IsSendingQAChanges { get; set; }

		// FTP settings
		public string FTPServer { get; set; }
		public string FTPUserName { get; set; }
		public string FTPPassword { get; set; }

		// Signing identities
		public string iPhoneCompileServerOverride { get;	set; }
		public string iPhoneSigningServerOverride { get; set; }
		public string SigningPrefixOverride { get; set; }
		public string DeveloperSigningIdentityOverride { get; set; }
		public string DistributionSigningIdentityOverride { get; set; }

		// AFT settings
		public string AFTTestMap { get; set; }
		public string TargetType = "DevKit";
		public List<string> AFTScreenShots = new List<string>();

		// The thread running the FTP upload
		public Thread ManageFTPThread = null;

		// Current zip class we are adding files to
		public ZipFile CurrentZip = null;

        // Creates a unique log file name for language independent operations
        public string GetLogFileName( COMMANDS Command )
        {
            LogFileName = LogFileRootName + "_" + LineCount.ToString() + "_" + Command.ToString() + ".txt";
            return ( LogFileName );
        }

        // Creates a unique log file name for language dependent operations
        public string GetLogFileName( COMMANDS Command, string Lang )
        {
            LogFileName = LogFileRootName + "_" + LineCount.ToString() + "_" + Command.ToString() + "_" + Lang + ".txt";
            return ( LogFileName );
        }

        public List<ChangeList> ChangeLists = new List<ChangeList>();
		private CollationType[] CollationTypes = new CollationType[( int )COLLATION.Count];
		private List<COLLATION> AllReports = new List<COLLATION>();
		private Queue<COLLATION> Reports = new Queue<COLLATION>();
		private List<string> ValidGames = new List<string>();

        private Main Parent = null;
        private StreamReader Script = null;
        public int LineCount = 0;
        public LabelInfo LabelInfo;

        // Symbol store
        private Queue<string> SymStoreCommands = new Queue<string>();

        // Normally set once at the beginning of the file

        // List of language variants that have full audio loc
        private Queue<string> Languages = new Queue<string>();
        // Subset of languages that have a valid loc'd variant
        private Queue<string> ValidLanguages;
		// List of language variants that have text only loc
		private Queue<string> TextLanguages = new Queue<string>();
		private TimeSpan OperationTimeout = new TimeSpan( 0, 10, 0 );
        private TimeSpan RespondingTimeout = new TimeSpan( 0, 10, 0 );

        // Changed multiple times during script execution
        private List<string> PublishDestinations = new List<string>();

		// Additional messages to report with the final success email
		private List<string> StatusReport = new List<string>();

		public string BuildConfiguration = "UnknownBuildConfiguration";
		public string ScriptConfiguration = "";
		public string ScriptConfigurationDLC = "";
		private string CookConfiguration = "";
		private string CommandletConfiguration = "";
		private string PackageTUConfiguration = "";
		private string AnalyzeReferencedContentConfiguration = "";
		private string InstallConfiguration = "";
        private string ContentPath = "";
        private string CompressionConfiguration = "size";

        // Working variables
		private COMMANDS ErrorLevel = COMMANDS.None;
		public bool ChangelistsCollated = false;

		// Compile-specific values
		public bool bXGEHasFailed = false;

        // The log file that gets referenced
        private TextWriter Log = null;

		public ScriptParser( Main InParent, Main.CommandInfo InCommandDetails, string ScriptFolder, string LogRoot, Main.BranchDefinition InBranchDef )
        {
            Parent = InParent;
            try
            {
				// Static initialisers
				MSVC9Application = Environment.GetEnvironmentVariable( "VS90COMNTOOLS" ) + "../IDE/Devenv.com";
				MSVC10Application = Environment.GetEnvironmentVariable( "VS100COMNTOOLS" ) + "../IDE/Devenv.com";
				SignToolName = "C:/Program Files (x86)/Microsoft SDKs/Windows/v7.0A/Bin/SignTool.exe";
				CatToolName = "C:/Program Files (x86)/Microsoft SDKs/Windows/v7.0A/Bin/MakeCat.exe";
				ZDPPToolName = Environment.GetEnvironmentVariable( "GFWLSDK_DIR" ) + "tools/ZeroDayPiracyProtection/ZdpSdkTool.exe";
				SourceServerCmd = "C:/Program Files (x86)/Debugging Tools for Windows (x86)/srcsrv/p4index.cmd";
				SymbolStoreApp = "C:/Program Files (x86)/Debugging Tools for Windows (x86)/symstore.exe";
				BlastTool = Environment.GetEnvironmentVariable( "XEDK" ) + "\\bin\\win32\\blast.exe";
				SymbolStoreLocation = Properties.Settings.Default.SymbolStoreLocation;
				KeyLocation = "";
				KeyPassword = "";
		        ErrorSaveVariable = "";
				MakeApplication = "IBMake.exe";
				SteamContentToolLocation = "Development/External/Steamworks/sdk/tools/ContentTool.com";
				SteamContentServerLocation = "Development/External/Steamworks/sdk/tools/contentserver/contentserver.exe";

				UBTEnvVar = "";

				ErrorMode = ErrorModeType.CheckErrors;
				HasSuppressedErrors = false;
				AllowSloppyScript = false;
				OfficialBuild = true;
				IncludeTimestampFolder = true;
				AllowXGE = true;
				AllowPCH = true;
				SpecifyOutput = true;

				Killer = "";
				SyncedLabel = "";
				HeadChangelist = -1;

				LastWaitForConchUpdate = DateTime.UtcNow;
				NewLabelCreated = false;
				GameNameOverride = "";
				SubBranchName = "";
				IncludePlatform = true;
				BlockOnPublish = false;
				ForceCopy = false;
				Use64BitBinaries = true;
				StripSourceContent = false;
				PublishMode = PublishModeType.Files;
				PublishVerification = PublishVerificationType.MD5;
				
				KeepAssets = "";
				bCommandletsSuccessful = true;
				UnSetupType = "";
				
				UnSetupType = "UDK";
				UnityStressTest = false;
				UnityDisable = false;

				SkuName = "";
				PublishFolder = "";
				TriggerAddress = "";
				SuccessAddress = "";
				FailAddress = "";
				CarbonCopyAddress = "";
				BUNs = new List<string>();
				Dependency = "";
				SourceBuild = "";
				BuildDefine = "";
				CopyDestination = "";
				ImageMode = "ISO";
				DLCName = "";
				LogFileName = "";
				
				IsBuilding = false;
				IsTagging = false;
				IsRestoringNewerChanges = false;
				IsPromoting = false;
				IsPublishing = false;
				IsSendingQAChanges = false;

				// FTP settings
				FTPServer = "";
				FTPUserName = "";
				FTPPassword = "";

				SigningPrefixOverride = "";
				DeveloperSigningIdentityOverride = "";
				DistributionSigningIdentityOverride = "";

				// iPhone settings
				iPhoneCompileServerOverride = "";
				iPhoneSigningServerOverride = "";
				SigningPrefixOverride = "";
				DeveloperSigningIdentityOverride = "";
				DistributionSigningIdentityOverride = "";

				// AFT settings
				AFTTestMap = "";

				// Dynamic initialization
				BranchDef = InBranchDef;
				CommandDetails = InCommandDetails;
				ScriptRoot = ScriptFolder;
				StartWaitForConch = CommandDetails.BuildStarted;

				// Default version file names
				EngineVersionFile = "Development/Src/Core/Src/UnObjVer.cpp";
				MiscVersionFiles = "Development/Src/Launch/Resources/Version.h;" +
								   "Binaries/build.properties";
				ConsoleVersionFiles = "Development/Src/ExampleGame/Live/xex.xml;" +
									  "Development/Src/UTGame/Live/xex.xml;";
				MobileVersionFiles = "Development/Src/IPhone/Resources/IPhone-Info.plist;" +
									 "UDKGame/Build/IPhone/IPhone-Info.plist";

				if( BranchDef.Version >= 10 )
				{
					EngineVersionFile = "Engine/Source/Runtime/Core/Private/UObject/ObjectVersion.cpp";
					MiscVersionFiles = "Engine/Source/Runtime/Launch/Resources/Version.h;" +
									   "Engine/Build/build.properties";
					ConsoleVersionFiles = "";
					MobileVersionFiles = "";
				}

                // Always need some label
				LabelInfo = new LabelInfo( Parent, this );
				LabelInfo.Init( this );

				string ScriptFile = Path.Combine( ScriptRoot, CommandDetails.Script + ".build" );
                string NewScriptFile = Path.Combine( ScriptRoot, "Current.build" );

				CreateCurrentScriptFile( ScriptFile, NewScriptFile );

                Script = new StreamReader( NewScriptFile );
                Parent.Log( "Using build script '" + BranchDef.Branch + "/" + ScriptFile + "'", Color.Magenta );

                LogFileRootName = Path.Combine( LogRoot, "Builder_[" + GetTimeStamp() + "]" );

                // Make sure there are no defines hanging around
                Environment.SetEnvironmentVariable( "CL", "" );

				InitCollationTypes();
            }
            catch
            {
                Parent.Log( "Error, problem loading build script", Color.Red );
            }
        }

        public void Destroy()
        {
            Parent.Log( LineCount.ToString() + " lines of build script parsed", Color.Magenta );
            if( Script != null )
            {
                Script.Close();
            }
        }

		public void OpenLog( string LogFileName, bool Append )
        {
			Log = TextWriter.Synchronized( new StreamWriter( LogFileName, Append, Encoding.Unicode ) );
		}

        public void CloseLog()
        {
            if( Log != null )
            {
                Log.Close();
				Log = null;
            }
        }

		public TextWriter OpenSystemLog()
		{
			return TextWriter.Synchronized( new StreamWriter( LogFileRootName + "_SystemLog.txt", false, Encoding.Unicode ) );
		}
		
		public void Write( string Output )
        {
            if( Log != null && Output != null )
            {
                try
                {
					Log.Write( DateTime.Now.ToString( "HH:mm:ss" ) + ": " + Output + Environment.NewLine );
                }
                catch( Exception Ex )
                {
                    Parent.Log( "Log write exception: exception '" + Ex.Message + "'", Color.Red );
                    Parent.Log( "Log write exception: intended to write '" + Output + "'", Color.Red );
                }
            }
        }

		private void CreateCurrentScriptFile( string ScriptFile, string NewScriptFile )
		{
			FileInfo ScriptInfo = new FileInfo( NewScriptFile );
			if( ScriptInfo.Exists )
			{
				ScriptInfo.IsReadOnly = false;
				ScriptInfo.Delete();
			}

			StreamReader Source = new StreamReader( ScriptFile );
			StreamWriter Destination = new StreamWriter( NewScriptFile );

			while( !Source.EndOfStream )
			{
				string Line = Source.ReadLine();

				if( Line.ToLower().StartsWith( "include" ) )
				{
					Destination.WriteLine();

					string BrickName = Path.Combine( ScriptRoot, "Include", Line.Substring( "include".Length ).Trim() + ".brick" );
					FileInfo BrickInfo = new FileInfo( BrickName );

					if( BrickInfo.Exists )
					{
						string[] AllLines = File.ReadAllLines( BrickName );
						foreach( string IncludeLine in AllLines )
						{
							Destination.WriteLine( IncludeLine );
						}
					}
					else
					{
						Destination.WriteLine( "ERROR: Failed to include: " + BrickName );
					}

					Destination.WriteLine();
				}
				else
				{
					Destination.WriteLine( Line );
				}
			}

			Destination.Close();
			Source.Close();
		}

		public string[] SafeSplit( string Line, bool bPreserveQuotes )
		{
			List<string> SafeParms = new List<string>();

			string Parm = "";
			bool bInQuotes = false;
			foreach( char Letter in Line )
			{
				if( Letter == ' ' || Letter == '\t' )
				{
					if( !bInQuotes )
					{
						if( Parm.Length > 0 )
						{
							SafeParms.Add( Parm );
							Parm = "";
						}
						continue;
					}
					else
					{
						Parm += Letter;
					}
				}
				else if( Letter == '\"' )
				{
					bInQuotes = !bInQuotes;
					if( bPreserveQuotes )
					{
						Parm += Letter;
					}
				}
				else
				{
					Parm += Letter;
				}
			}

			if( Parm.Length > 0 )
			{
				SafeParms.Add( Parm );
			}

			return ( SafeParms.ToArray() );
		}

		public string[] SplitCommandline()
		{
			return ( SafeSplit( CurrentCommandLine, false ) );
		}

        public Queue<string> GetLanguages()
        {
            return ( Languages );
        }

		public Queue<string> GetTextLanguages()
		{
			return ( TextLanguages );
		}

        public void SetValidLanguages( Queue<string> ValidLangs )
        {
            ValidLanguages = ValidLangs;
        }

        public Queue<string> GetValidLanguages()
        {
            return ( ValidLanguages );
        }

		public string GetFolderName()
		{
			return ( LabelInfo.GetFolderName( GameNameOverride, IncludePlatform, BranchDef.Version ) );
		}

		public string GetSubBranch()
		{
			string SubBranch = "";
			if( SubBranchName.Length > 0 )
			{
				SubBranch = "\\" + SubBranchName;
			}

			return ( SubBranch );
		}

		public string GetImageName()
		{
			string FolderName = LabelInfo.GetFolderName( GameNameOverride, IncludePlatform, BranchDef.Version );
			if( SkuName.Length > 0 )
			{
				FolderName += "_" + SkuName;
			}
			return ( FolderName );
		}

        public string GetScriptConfiguration()
        {
			string ScriptConfig = "";
			if( ScriptConfiguration.Length > 0 )
            {
                string[] Configs = SafeSplit( ScriptConfiguration, false );
                foreach( string Config in Configs )
                {
                    if( Config.ToLower() == "fr" )
                    {
                        ScriptConfig += " -final_release";
                    }
                    else
                    {
                        ScriptConfig += " -" + Config;
                    }
                }
            }
			if( ScriptConfigurationDLC.Length > 0 )
			{
				ScriptConfig += " -dlc " + ScriptConfigurationDLC;
			}
			return ScriptConfig;
        }

        public string GetCookConfiguration()
        {
            if( CookConfiguration.Length > 0 )
            {
                return ( " -" + CookConfiguration );
            }
            return ( "" );
        }

		public string GetOptionalCommandletConfig()
		{
			if( bCommandletsSuccessful && CommandletConfiguration.Length > 0 )
			{
				return ( " -" + CommandletConfiguration );
			}

			return ( "" );
		}

		public string GetPackageTUConfig()
		{
			if( PackageTUConfiguration.Length > 0 )
			{
				return ( " " + PackageTUConfiguration );
			}

			return ( "" );
		}

		public string GetDataBaseConnectionInfo()
		{
			string ConnectionInfo = "";
			if( DataBaseName.Length > 0 && DataBaseCatalog.Length > 0 )
			{
				ConnectionInfo = " -DATABASE=" + DataBaseName + " -CATALOG=" + DataBaseCatalog;
			}

			return ( ConnectionInfo );
		}

		public string GetAnalyzeReferencedContentConfiguration()
		{
			if( AnalyzeReferencedContentConfiguration.Length > 0 )
			{
				return ( " " + AnalyzeReferencedContentConfiguration );
			}
			return ( "" );
		}

        public string GetContentPath()
        {
            if( ContentPath.Length > 0 )
            {
                return ( " -paths=" + ContentPath );
            }
            return ( "" );
        }

        public string GetDLCName()
        {
			if( DLCName.Length > 0 )
            {
				return ( " -DLCName=" + DLCName );
            }
            return ( "" );
        }

        public string GetCompressionConfiguration()
        {
            if( CompressionConfiguration.ToLower() == "speed" )
            {
                return ( " -NOPACKAGECOMPRESSION" );
            }
            return ( "" );
        }

        public void ClearPublishDestinations()
        {
            PublishDestinations.Clear();
        }

        public void AddPublishDestination( string Dest )
        {
            PublishDestinations.Add( Dest );
        }

        public List<string> GetPublishDestinations()
        {
            return ( PublishDestinations );
        }

		public void AddToSuccessStatus( string AdditionalStatus )
		{
			StatusReport.Add( AdditionalStatus );
		}

		public void AddUniqueToSuccessStatus( string AdditionalStatus )
		{
			if( !StatusReport.Contains( AdditionalStatus ) )
			{
				StatusReport.Add( AdditionalStatus );
			}
		}

		public List<string> GetStatusReport()
		{
			return( StatusReport );
		}

        public void AddUpdateSymStore( string Command )
        {
            SymStoreCommands.Enqueue( Command );
        }

        public string PopUpdateSymStore()
        {
            if( !UpdateSymStoreEmpty() )
            {
                return ( SymStoreCommands.Dequeue() );
            }

            return ( "" );
        }

        public bool UpdateSymStoreEmpty()
        {
            return ( SymStoreCommands.Count == 0 );
        }

		public void SetErrorLevel( COMMANDS Error )
        {
            ErrorLevel = Error;
        }

		public COMMANDS GetErrorLevel()
        {
            return ( ErrorLevel );
        }

        public string GetTimeStamp()
        {
			DateTime LocalTime = CommandDetails.BuildStarted.ToLocalTime();

			string TimeStamp = LocalTime.Year + "-"
						+ LocalTime.Month.ToString( "00" ) + "-"
						+ LocalTime.Day.ToString( "00" ) + "_"
						+ LocalTime.Hour.ToString( "00" ) + "."
						+ LocalTime.Minute.ToString( "00" ) + "."
						+ LocalTime.Second.ToString( "00" );
			return ( TimeStamp );
        }

        public int SafeStringToInt( string Number )
        {
            int Result = 0;

            try
            {
                Number = Number.Trim();
                Result = Int32.Parse( Number );
            }
            catch
            {
            }

            return ( Result );
        }

		public long SafeStringToLong( string Number )
		{
			long Result = 0;

			try
			{
				Number = Number.Trim();
				Result = long.Parse( Number );
			}
			catch
			{
			}

			return ( Result );
		}

		public void AddScreenShot( string ScreenShot )
		{
			AFTScreenShots.Add( ScreenShot );
		}

        public GameConfig AddCheckedOutGame()
        {
			GameConfig Config = new GameConfig( CurrentCommandLine, LabelInfo.Platform, BuildConfiguration, LabelInfo.Defines, true, Use64BitBinaries );
            LabelInfo.Games.Add( Config );

            return ( Config );
        }

        public GameConfig CreateGameConfig( string Game, string InPlatform )
        {
			GameConfig Config = new GameConfig( Game, InPlatform, BuildConfiguration, LabelInfo.Defines, true, Use64BitBinaries );

            return ( Config );
        }

        public GameConfig CreateGameConfig( string Game )
        {
			GameConfig Config = new GameConfig( Game, LabelInfo.Platform, BuildConfiguration, LabelInfo.Defines, true, Use64BitBinaries );

            return ( Config );
        }

        public GameConfig CreateGameConfig()
        {
			GameConfig Config = new GameConfig( LabelInfo.Game, LabelInfo.Platform, BuildConfiguration, LabelInfo.Defines, true, Use64BitBinaries );

            return ( Config );
        }

        public GameConfig CreateGameConfig( bool Local )
        {
			GameConfig Config = new GameConfig( LabelInfo.Game, LabelInfo.Platform, BuildConfiguration, LabelInfo.Defines, Local, Use64BitBinaries );

            return ( Config );
        }

        public TimeSpan GetTimeout()
        {
            return ( OperationTimeout );
        }

        public TimeSpan GetRespondingTimeout()
        {
            return ( RespondingTimeout );
        }

        // Set the CL env var based on required defines
        public void HandleMSVCDefines()
        {
			// Clear out env var
            Environment.SetEnvironmentVariable( "CL", "" );

			// Set up new one if necessary
			string EnvVar = "";
			if( LabelInfo.Defines.Count > 0 )
			{
				foreach( string Define in LabelInfo.Defines )
				{
					EnvVar += "/D " + Define + " ";
				}

				Environment.SetEnvironmentVariable( "CL", EnvVar.Trim() );
			}

            Write( "Setting CL=" + EnvVar );
        }

        // Passed in on the command line, nothing special to do here
        public string HandleUBTDefines()
        {
			// Clear out env var
			Environment.SetEnvironmentVariable( "CL", "" );

			// Set up new parameter
			string CommandLine = "";
			if( LabelInfo.Defines.Count > 0 )
			{
				foreach( string Define in LabelInfo.Defines )
				{
					CommandLine += "-define " + Define + " ";
				}
				CommandLine = " " + CommandLine.Trim();
			}

            return ( CommandLine );
        }

        // Passed in on the command line, nothing special to do here
        public string HandleUBTEnvVar()
        {
            string CommandLine = "";
            if( UBTEnvVar.Length > 0 )
            {
                CommandLine += " -EnvVar " + UBTEnvVar;
            }

            return ( CommandLine );
        }

        public Main.CommandPacket ParseNextLine()
        {
            string Line;
			Main.CommandPacket NextCommand = new Main.CommandPacket( COMMANDS.Error, "" );

            if( Script == null )
            {
				ErrorLevel = COMMANDS.NoScript;
                return( NextCommand );
            }

            Line = Script.ReadLine();
            if( Line == null )
            {
                Parent.Log( "[STATUS] Script parsing completed", Color.Magenta );
				NextCommand.CommandID = COMMANDS.Finished;
                return( NextCommand );
            }

            LineCount++;
			NextCommand.CommandID = COMMANDS.Config;
            NextCommand.CommandLine = "";
            string[] Parms = SafeSplit( Line, false );
            if( Parms.Length > 0 )
            {
                string Command = Parms[0].ToLower();
                NextCommand.CommandLine = Line.Substring( Parms[0].Length ).Trim();
				NextCommand.CommandLine = NextCommand.CommandLine.Replace( '\\', '/' );
                // Need to keep the double backslashes for network locations
				NextCommand.CommandLine = NextCommand.CommandLine.Replace( "//", "\\\\" );

                if( Command.Length == 0 || Command == "//" )
                {
                    // Comment - ignore
					NextCommand.CommandID = COMMANDS.Config;
                }
                else if( Command == "status" )
                {
                    // Status string - just echo
					Parent.Log( "[STATUS] " + Parent.ExpandString( NextCommand.CommandLine ), Color.Magenta );
					NextCommand.CommandID = COMMANDS.Config;
                }
                else if( Command == "watchstart" )
                {
                    // Start a timer
					string PerfKeyName = Parent.ExpandString( NextCommand.CommandLine );
                    Parent.Log( "[WATCHSTART " + PerfKeyName + "]", Color.Magenta );
					NextCommand.CommandID = COMMANDS.Config;
                }
                else if( Command == "watchstop" )
                {
                    // Stop a timer
                    Parent.Log( "[WATCHSTOP]", Color.Magenta );
					NextCommand.CommandID = COMMANDS.Config;
                }
				else if( Command == "errormode" )
				{
					string ErrorModeString = Parent.ExpandString( NextCommand.CommandLine );
					try
					{
						ErrorMode = ( ErrorModeType )Enum.Parse( typeof( ErrorModeType ), ErrorModeString, true );
					}
					catch
					{
						ErrorMode = ErrorModeType.CheckErrors;
					}

					Parent.Log( "ErrorMode set to '" + ErrorMode.ToString() + "'", Color.Magenta );
					NextCommand.CommandID = COMMANDS.Config;
				}
				else if( Command == "allowsloppyscript" )
				{
					AllowSloppyScript = true;
					Parent.Log( "Script warnings will not fail the build", Color.Magenta );
					NextCommand.CommandID = COMMANDS.Config;
				}
				else if( Command == "unofficial" )
				{
					OfficialBuild = false;
					Parent.Log( "EngineQA will not be cc'd on build failure", Color.Magenta );
					NextCommand.CommandID = COMMANDS.Config;
				}
				else if( Command == "ambiguousfoldername" )
				{
					IncludeTimestampFolder = false;
					Parent.Log( "The timestamped folder will not be used when getting an installable build", Color.Magenta );
					NextCommand.CommandID = COMMANDS.Config;
				}
				else if( Command == "ubtenablexge" )
				{
					AllowXGE = true;
					Parent.Log( "XGE is now ENABLED in UBT", Color.Magenta );
					NextCommand.CommandID = COMMANDS.Config;
				}
				else if( Command == "ubtdisablexge" )
				{
					AllowXGE = false;
					Parent.Log( "XGE is now DISABLED in UBT", Color.Magenta );
					NextCommand.CommandID = COMMANDS.Config;
				}
				else if( Command == "ubtenablepch" )
				{
					AllowPCH = true;
					Parent.Log( "PCHs are now ENABLED in UBT", Color.Magenta );
					NextCommand.CommandID = COMMANDS.Config;
				}
				else if( Command == "ubtdisablepch" )
				{
					AllowPCH = false;
					Parent.Log( "PCHs are now DISABLED in UBT", Color.Magenta );
					NextCommand.CommandID = COMMANDS.Config;
				}
				else if( Command == "ubtspecifyoutput" )
				{
					SpecifyOutput = true;
					Parent.Log( "The output is now SPECIFIED in UBT", Color.Magenta );
					NextCommand.CommandID = COMMANDS.Config;
				}
				else if( Command == "ubtnospecifyoutput" )
				{
					SpecifyOutput = false;
					Parent.Log( "The output is now NOT SPECIFIED in UBT", Color.Magenta );
					NextCommand.CommandID = COMMANDS.Config;
				}
				else if( Command == "platformspecific" )
				{
					IncludePlatform = true;
					Parent.Log( "Publish folder includes the platform", Color.Magenta );
					NextCommand.CommandID = COMMANDS.Config;
				}
				else if( Command == "platformagnostic" )
				{
					IncludePlatform = false;
					Parent.Log( "Publish folder does NOT include the platform", Color.Magenta );
					NextCommand.CommandID = COMMANDS.Config;
				}
				else if( Command == "gamenameoverride" )
				{
					GameNameOverride = Parent.ExpandString( NextCommand.CommandLine );
					Parent.Log( "Publish folder uses '" + GameNameOverride + "' rather than the game name", Color.Magenta );
					NextCommand.CommandID = COMMANDS.Config;
				}
				else if( Command == "subbranch" )
				{
					SubBranchName = Parent.ExpandString( NextCommand.CommandLine );
					Parent.Log( "Publish folder adds in '" + SubBranchName + "' to the branch name", Color.Magenta );
					NextCommand.CommandID = COMMANDS.Config;
				}
				else if( Command == "languagespecific" )
                {
					Parent.Log( "[DEPRECATED] languagespecific", Color.Magenta );
					NextCommand.CommandID = COMMANDS.Config;
                }
                else if( Command == "languageagnostic" )
                {
					Parent.Log( "[DEPRECATED] languageagnostic", Color.Magenta );
					NextCommand.CommandID = COMMANDS.Config;
                }
                else if( Command == "touchlabel" )
                {
					// This is used to update the timestamp of the folder to publish to
                    LabelInfo.Touch();
                    Parent.Log( "The current label has been touched", Color.Magenta );
					NextCommand.CommandID = COMMANDS.Config;
                }
                else if( Command == "updatelabel" )
                {
					NextCommand.CommandID = COMMANDS.UpdateLabel;
                }
                else if( Command == "updatefolder" )
                {
					NextCommand.CommandID = COMMANDS.UpdateFolder;
                }
				else if( Command == "clearpublishdestinations" )
				{
					Parent.Log( "Clearing publish destinations", Color.Magenta );
					ClearPublishDestinations();
					NextCommand.CommandID = COMMANDS.Config;
				}
				else if( Command == "saveerror" )
				{
					ErrorSaveVariable = Parent.ExpandString( NextCommand.CommandLine );
					NextCommand.CommandID = COMMANDS.Config;
				}
				else if( Command == "keylocation" )
				{
					KeyLocation = Parent.ExpandString( NextCommand.CommandLine );
					NextCommand.CommandID = COMMANDS.Config;
				}
				else if( Command == "keypassword" )
				{
					KeyPassword = Parent.ExpandString( NextCommand.CommandLine );
					NextCommand.CommandID = COMMANDS.Config;
				}
				else if( Command == "tag" )
				{
					Parent.Log( "The latest build label will be copied to '" + NextCommand.CommandLine + "'", Color.Magenta );
					IsPromoting = true;
					NextCommand.CommandID = COMMANDS.SCC_Tag;
				}
				else if( Command == "report" )
				{
					Reports.Clear();

					string ExpandedCommandLine = Parent.ExpandString( NextCommand.CommandLine );
					string[] NewParms = SafeSplit( ExpandedCommandLine, false );

					for( int i = 0; i < NewParms.Length; i++ )
					{
						if( NewParms[i].Length > 0 )
						{
							COLLATION Collation = CollationType.GetReportType( NewParms[i], ValidGames );
							if( Collation != COLLATION.Count )
							{
								Reports.Enqueue( Collation );
							}
							else
							{
								Parent.Log( "Missing COLLATION type: " + NewParms[i], Color.Red );
							}
						}
					}
				}
				else if( Command == "triggeraddress" )
				{
					Parent.SendErrorMail( "Deprecated command 'TriggerAddress'", "" );
					NextCommand.CommandID = COMMANDS.Config;
				}
				else if( Command == "failaddress" )
				{
					// Email addresses to use if the build fails
					FailAddress = Parent.ExpandString( NextCommand.CommandLine );
					Parent.Log( "FailAddress set to '" + FailAddress + "'", Color.Magenta );
					NextCommand.CommandID = COMMANDS.Config;
				}
				else if( Command == "successaddress" )
				{
					// Email addresses to use if the build succeeds
					SuccessAddress = Parent.ExpandString( NextCommand.CommandLine );
					Parent.Log( "SuccessAddress set to '" + SuccessAddress + "'", Color.Magenta );
					NextCommand.CommandID = COMMANDS.Config;
				}
				else if( Command == "carboncopyaddress" )
				{
					// Email addresses to use when the build is triggered
					CarbonCopyAddress = Parent.ExpandString( NextCommand.CommandLine );
					Parent.Log( "CarbonCopyAddress set to '" + CarbonCopyAddress + "'", Color.Magenta );
					NextCommand.CommandID = COMMANDS.Config;
				}
				else if( Command == "sendemail" )
				{
					// Send an email based on the current state of the build
					Parent.Log( "Sending update email", Color.Magenta );
					NextCommand.CommandID = COMMANDS.SendEmail;
				}
				else if( Command == "addbunline" )
				{
					BUNs.Add( NextCommand.CommandLine.Trim( '\"' ) );
					NextCommand.CommandID = COMMANDS.Config;
				}
				else if( Command == "cisprocessp4changes" )
				{
					// Instruct the controller to process all unprocessed p4 changes for CIS tasks
					Parent.Log( "Processing P4 changes...", Color.Magenta );
					NextCommand.CommandID = COMMANDS.CISProcessP4Changes;
				}
				else if( Command == "cisupdatemonitorvalues" )
				{
					// Instruct the controller to evaluate all completed CIS jobs and post results
					// the CIS Monitor can use
					Parent.Log( "Processing completed CIS jobs...", Color.Magenta );
					NextCommand.CommandID = COMMANDS.CISUpdateMonitorValues;
				}
				else if( Command == "sku" )
				{
					SkuName = Parent.ExpandString( NextCommand.CommandLine );
					Parent.Log( "Sku set to: " + SkuName, Color.Magenta );
					NextCommand.CommandID = COMMANDS.Config;
				}
				else if( Command == "createmgstrigger" )
				{
					NextCommand.CommandID = COMMANDS.CreateMGSTrigger;
				}
				else if( Command == "ftpserver" )
				{
					FTPServer = Parent.ExpandString( NextCommand.CommandLine );
					Parent.Log( "FTP server set to: " + FTPServer, Color.Magenta );
					NextCommand.CommandID = COMMANDS.Config;
				}
				else if( Command == "ftpusername" )
				{
					FTPUserName = Parent.ExpandString( NextCommand.CommandLine );
					Parent.Log( "FTP username set to: " + FTPUserName, Color.Magenta );
					NextCommand.CommandID = COMMANDS.Config;
				}
				else if( Command == "ftppassword" )
				{
					FTPPassword = Parent.ExpandString( NextCommand.CommandLine );
					Parent.Log( "FTP password set to: <NOT TELLING!>", Color.Magenta );
					NextCommand.CommandID = COMMANDS.Config;
				}
				else if( Command == "ftpsendfile" )
				{
					NextCommand.CommandID = COMMANDS.FTPSendFile;
				}
				else if( Command == "ftpsendimage" )
				{
					NextCommand.CommandID = COMMANDS.FTPSendImage;
				}
				else if( Command == "ftpsendfolder" )
				{
					NextCommand.CommandID = COMMANDS.FTPSendFolder;
				}
				else if( Command == "zipaddimage" )
				{
					NextCommand.CommandID = COMMANDS.ZipAddImage;
				}
				else if( Command == "zipaddfile" )
				{
					NextCommand.CommandID = COMMANDS.ZipAddFile;
				}
				else if( Command == "zipsave" )
				{
					NextCommand.CommandID = COMMANDS.ZipSave;
				}
				else if( Command == "cleanupsymbolserver" )
				{
					NextCommand.CommandID = COMMANDS.CleanupSymbolServer;
				}
				else if( Command == "define" )
				{
					// Define for the compiler to use
					LabelInfo.ClearDefines();

					BuildDefine = Parent.ExpandString( NextCommand.CommandLine );
					if( BuildDefine.Length > 0 )
					{
						string[] DefineParms = SafeSplit( BuildDefine, false );
						foreach( string Define in DefineParms )
						{
							LabelInfo.AddDefine( Define );
						}
					}
					Parent.Log( "Define set to '" + BuildDefine + "'", Color.Magenta );
					NextCommand.CommandID = COMMANDS.Config;
				}
				else if( Command == "ubtsetenv" )
				{
					UBTEnvVar = Parent.ExpandString( NextCommand.CommandLine );
					Parent.Log( "[DEPRECATED] Setting UBT environment variable '" + UBTEnvVar + "'", Color.Magenta );
				}
				else if( Command == "language" )
				{
					// Language for the cooker to use
					LabelInfo.Language = Parent.ExpandString( NextCommand.CommandLine ).ToUpper();
					Parent.Log( "Language set to '" + LabelInfo.Language + "'", Color.Magenta );
					NextCommand.CommandID = COMMANDS.Config;
				}
				else if( Command == "languages" )
				{
					// List of languages used to conform or ML cook
					Languages.Clear();

					string LangLine = Parent.ExpandString( NextCommand.CommandLine ).ToUpper();
					string[] LangParms = SafeSplit( LangLine, false );
					foreach( string Lang in LangParms )
					{
						if( Lang.Length > 0 )
						{
							Languages.Enqueue( Lang );
						}
					}

					Parent.Log( "Number of languages to process: " + Languages.Count, Color.Magenta );
					NextCommand.CommandID = COMMANDS.Config;
				}
				else if( Command == "textlanguages" )
				{
					// List of languages that only have text loc
					TextLanguages.Clear();

					string LangLine = Parent.ExpandString( NextCommand.CommandLine ).ToUpper();
					string[] LangParms = SafeSplit( LangLine, false );
					foreach( string Lang in LangParms )
					{
						if( Lang.Length > 0 )
						{
							TextLanguages.Enqueue( Lang );
						}
					}

					Parent.Log( "Number of text languages to process: " + TextLanguages.Count, Color.Magenta );
					NextCommand.CommandID = COMMANDS.Config;
				}
				else if( Command == "clientspec" )
				{
					Parent.SendErrorMail( "Deprecated command 'ClientSpec'", "" );
					NextCommand.CommandID = COMMANDS.Config;
				}
				else if( Command == "timeout" )
				{
					// Number of minutes to failure
					int OpTimeout = SafeStringToInt( Parent.ExpandString( NextCommand.CommandLine ) );
					OperationTimeout = new TimeSpan( 0, OpTimeout, 0 );
					Parent.Log( "Timeout set to " + OpTimeout.ToString() + " minutes", Color.Magenta );
					NextCommand.CommandID = COMMANDS.Config;
				}
				else if( Command == "msvc9application" )
				{
					// MSVC command line app
					MSVC9Application = Parent.ExpandString( NextCommand.CommandLine );
					Parent.Log( "MSVC9 executable set to '" + MSVC9Application + "'", Color.Magenta );
					NextCommand.CommandID = COMMANDS.Config;
				}
				else if( Command == "msvc10application" )
				{
					// MSVC command line app
					MSVC10Application = Parent.ExpandString( NextCommand.CommandLine );
					Parent.Log( "MSVC10 executable set to '" + MSVC10Application + "'", Color.Magenta );
					NextCommand.CommandID = COMMANDS.Config;
				}
				else if( Command == "makeapplication" )
				{
					// make app
					MakeApplication = Parent.ExpandString( NextCommand.CommandLine );
					Parent.Log( "Make executable set to '" + MakeApplication + "'", Color.Magenta );
					NextCommand.CommandID = COMMANDS.Config;
				}
				else if( Command == "symbolstoreapplication" )
				{
					// Symbol store tool location
					SymbolStoreApp = Parent.ExpandString( NextCommand.CommandLine );
					Parent.Log( "Symbol store executable set to '" + SymbolStoreApp + "'", Color.Magenta );
					NextCommand.CommandID = COMMANDS.Config;
				}
				else if( Command == "signtoolapplication" )
				{
					// Sign tool location
					SignToolName = Parent.ExpandString( NextCommand.CommandLine );
					Parent.Log( "Sign tool executable set to '" + SignToolName + "'", Color.Magenta );
					NextCommand.CommandID = COMMANDS.Config;
				}
				else if( Command == "sourceservercommand" )
				{
					// bat/perl script to index pdbs
					SourceServerCmd = Parent.ExpandString( NextCommand.CommandLine );
					Parent.Log( "Source server script set to '" + SourceServerCmd + "'", Color.Magenta );
					NextCommand.CommandID = COMMANDS.Config;
				}
				else if( Command == "symbolstorelocation" )
				{
					// bat/perl script to index pdbs
					SymbolStoreLocation = Parent.ExpandString( NextCommand.CommandLine );
					Parent.Log( "Symbol store location set to '" + SymbolStoreLocation + "'", Color.Magenta );
					NextCommand.CommandID = COMMANDS.Config;
				}
				else if( Command == "versionfile" )
				{
					// Main version file
					EngineVersionFile = Parent.ExpandString( NextCommand.CommandLine );
					Parent.Log( "Engine version file set to '" + EngineVersionFile + "'", Color.Magenta );
					NextCommand.CommandID = COMMANDS.Config;
				}
				else if( Command == "miscversionfiles" )
				{
					// Version files that have a version propagated to
					MiscVersionFiles = Parent.ExpandString( NextCommand.CommandLine );
					Parent.Log( "Misc version files set to '" + MiscVersionFiles + "'", Color.Magenta );
					NextCommand.CommandID = COMMANDS.Config;
				}
				else if( Command == "consoleversionfiles" )
				{
					// Version files that have a version propagated to
					ConsoleVersionFiles = Parent.ExpandString( NextCommand.CommandLine );
					Parent.Log( "Console version files set to '" + ConsoleVersionFiles + "'", Color.Magenta );
					NextCommand.CommandID = COMMANDS.Config;
				}
				else if( Command == "mobileversionfiles" )
				{
					// Version files that have a version propagated to
					MobileVersionFiles = Parent.ExpandString( NextCommand.CommandLine );
					Parent.Log( "Mobile version files set to '" + MobileVersionFiles + "'", Color.Magenta );
					NextCommand.CommandID = COMMANDS.Config;
				}
				else if( Command == "game" )
				{
					// Game we are interested in
					LabelInfo.Game = Parent.ExpandString( NextCommand.CommandLine );
					Parent.Log( "Game set to '" + LabelInfo.Game + "'", Color.Magenta );
					NextCommand.CommandID = COMMANDS.Config;
				}
				else if( Command == "platform" )
				{
					// Platform we are interested in
					LabelInfo.Platform = Parent.ExpandString( NextCommand.CommandLine );
					Parent.Log( "Platform set to '" + LabelInfo.Platform + "'", Color.Magenta );
					NextCommand.CommandID = COMMANDS.Config;
				}
				else if( Command == "targettype" )
				{
					// Platform we are interested in
					TargetType = Parent.ExpandString( NextCommand.CommandLine );
					Parent.Log( "TargetType set to '" + TargetType + "'", Color.Magenta );
					NextCommand.CommandID = COMMANDS.Config;
				}
				else if( Command == "buildconfig" )
				{
					// Build we are interested in
					BuildConfiguration = Parent.ExpandString( NextCommand.CommandLine );
					Parent.Log( "Build configuration set to '" + BuildConfiguration + "'", Color.Magenta );
					NextCommand.CommandID = COMMANDS.Config;
				}
				else if( Command == "scriptconfig" )
				{
					// Script release or final_release we are interested in
					ScriptConfiguration = Parent.ExpandString( NextCommand.CommandLine );
					Parent.Log( "Script configuration set to '" + ScriptConfiguration + "'", Color.Magenta );
					NextCommand.CommandID = COMMANDS.Config;
				}
				else if( Command == "scriptconfigdlc" )
				{
					// Script release or final_release we are interested in
					ScriptConfigurationDLC = Parent.ExpandString( NextCommand.CommandLine );
					Parent.Log( "DLC script configuration set to '" + ScriptConfigurationDLC + "'", Color.Magenta );
					NextCommand.CommandID = COMMANDS.Config;
				}
				else if( Command == "cookconfig" )
				{
					// Cook config we are interested in (eg. CookForServer - dedicated server trimming)
					CookConfiguration = Parent.ExpandString( NextCommand.CommandLine );
					Parent.Log( "Cook configuration set to '" + CookConfiguration + "'", Color.Magenta );
					NextCommand.CommandID = COMMANDS.Config;
				}
				else if( Command == "dlcname" )
				{
					// The mod name we are cooking for
					DLCName = Parent.ExpandString( NextCommand.CommandLine );
					Parent.Log( "DLCName set to '" + DLCName + "'", Color.Magenta );
					NextCommand.CommandID = COMMANDS.Config;
				}
				else if( Command == "installconfig" )
				{
					// Install we are interested in
					InstallConfiguration = Parent.ExpandString( NextCommand.CommandLine );
					Parent.Log( "Install configuration set to '" + InstallConfiguration + "'", Color.Magenta );
					NextCommand.CommandID = COMMANDS.Config;
				}
				else if( Command == "contentpath" )
				{
					// Used after a wrangle
					ContentPath = Parent.ExpandString( NextCommand.CommandLine );
					Parent.Log( "ContentPath set to '" + ContentPath + "'", Color.Magenta );
					NextCommand.CommandID = COMMANDS.Config;
				}
				else if( Command == "compressionconfig" )
				{
					// Set to size or speed
					CompressionConfiguration = Parent.ExpandString( NextCommand.CommandLine );
					Parent.Log( "Compression biased for '" + CompressionConfiguration + "'", Color.Magenta );
					NextCommand.CommandID = COMMANDS.Config;
				}
				else if( Command == "commandlet" )
				{
					NextCommand.CommandID = COMMANDS.Commandlet;
				}
				else if( Command == "commandletconfig" )
				{
					// Set to size or speed
					CommandletConfiguration = Parent.ExpandString( NextCommand.CommandLine );
					Parent.Log( "CommandletConfiguration set to '" + CommandletConfiguration + "'", Color.Magenta );
					NextCommand.CommandID = COMMANDS.Config;
				}
				else if( Command == "packagetuconfig" )
				{
					// Set to size or speed
					PackageTUConfiguration = Parent.ExpandString( NextCommand.CommandLine );
					Parent.Log( "PackageTUConfiguration set to '" + PackageTUConfiguration + "'", Color.Magenta );
					NextCommand.CommandID = COMMANDS.Config;
				}
				else if( Command == "database" )
				{
					string[] DataBaseConnection = SplitCommandline();
					if( DataBaseConnection.Length == 2 )
					{
						DataBaseName = DataBaseConnection[0];
						DataBaseCatalog = DataBaseConnection[1];
						Parent.Log( "Database connection set to '" + DataBaseName + "' and '" + DataBaseCatalog + "'", Color.Magenta );
						NextCommand.CommandID = COMMANDS.Config;
					}
					else
					{
						Parent.Log( "Error, need both database and catalog in database definition", Color.Magenta );

						ErrorLevel = COMMANDS.IllegalCommand;
						NextCommand.CommandID = COMMANDS.Error;
					}
				}
				else if( Command == "dependency" )
				{
					Dependency = Parent.ExpandString( NextCommand.CommandLine );
					Parent.Log( "Dependency set to '" + Dependency + "'", Color.DarkGreen );
					NextCommand.CommandID = COMMANDS.SetDependency;
				}
				else if( Command == "sourcebuild" )
				{
					SourceBuild = Parent.ExpandString( NextCommand.CommandLine );
					Parent.Log( "SourceBuild set to '" + SourceBuild + "'", Color.DarkGreen );
					NextCommand.CommandID = COMMANDS.Config;
				}
				else if( Command == "copydest" )
				{
					CopyDestination = Parent.ExpandString( NextCommand.CommandLine );
					NextCommand.CommandID = COMMANDS.Config;
				}
				else if( Command == "blockonpublish" )
				{
					BlockOnPublish = true;
					NextCommand.CommandID = COMMANDS.Config;
				}
				else if( Command == "forcecopy" )
				{
					ForceCopy = true;
					NextCommand.CommandID = COMMANDS.Config;
				}
				else if( Command == "use64bit" )
				{
					Use64BitBinaries = true;
					NextCommand.CommandID = COMMANDS.Config;
				}
				else if( Command == "use32bit" )
				{
					Use64BitBinaries = false;
					NextCommand.CommandID = COMMANDS.Config;
				}
				else if( Command == "stripsourcecontent" )
				{
					StripSourceContent = true;
					NextCommand.CommandID = COMMANDS.Config;
				}
				else if( Command == "publishmode" )
				{
					string PublishModeString = Parent.ExpandString( NextCommand.CommandLine );
					try
					{
						PublishMode = ( PublishModeType )Enum.Parse( typeof( PublishModeType ), PublishModeString, true );
					}
					catch
					{
						PublishMode = PublishModeType.Files;
					}

					Parent.Log( "Publishing mode set to '" + PublishMode.ToString() + "'", Color.Magenta );
					NextCommand.CommandID = COMMANDS.Config;
				}
				else if( Command == "publishverification" )
				{
					string PublishVerificationString = Parent.ExpandString( NextCommand.CommandLine );
					try
					{
						PublishVerification = ( PublishVerificationType )Enum.Parse( typeof( PublishVerificationType ), PublishVerificationString, true );
					}
					catch
					{
						PublishVerification = PublishVerificationType.MD5;
					}

					Parent.Log( "Publishing verification set to '" + PublishVerification.ToString() + "'", Color.Magenta );
					NextCommand.CommandID = COMMANDS.Config;
				}
				else if( Command == "keepassets" )
				{
					KeepAssets = Parent.ExpandString( NextCommand.CommandLine );
					NextCommand.CommandID = COMMANDS.Config;
				}
				else if( Command == "imagemode" )
				{
					ImageMode = Parent.ExpandString( NextCommand.CommandLine );
					NextCommand.CommandID = COMMANDS.Config;
				}
				else if( Command == "unity" )
				{
					string UnityParameter = Parent.ExpandString( NextCommand.CommandLine );
					if( UnityParameter == "disable" )
					{
						UnityDisable = true;
					}
					else if( UnityParameter == "stresstest" )
					{
						UnityStressTest = true;
					}
					Parent.Log( "Unity set to '" + UnityParameter + "'", Color.Magenta );
					NextCommand.CommandID = COMMANDS.Config;
				}
				else if( Command == "cleanup" )
				{
					NextCommand.CommandID = COMMANDS.PreHeatMapOven;
				}
				else if( Command == "copyscriptpatchfiles" )
				{
					NextCommand.CommandID = COMMANDS.CopyScriptPatchFiles;
				}
				else if( Command == "copy" )
				{
					NextCommand.CommandID = COMMANDS.SimpleCopy;
				}
				else if( Command == "sourcebuildcopy" )
				{
					NextCommand.CommandID = COMMANDS.SourceBuildCopy;
				}
				else if( Command == "delete" )
				{
					NextCommand.CommandID = COMMANDS.SimpleDelete;
				}
				else if( Command == "rename" )
				{
					NextCommand.CommandID = COMMANDS.SimpleRename;
				}
				else if( Command == "renamecopy" )
				{
					NextCommand.CommandID = COMMANDS.RenamedCopy;
				}
				else if( Command == "setsteamid" )
				{
					NextCommand.CommandID = COMMANDS.SetSteamID;
				}
				else if( Command == "checkconsistency" )
				{
					NextCommand.CommandID = COMMANDS.SCC_CheckConsistency;
				}
				else if( Command == "getchangelist" )
				{
					NextCommand.CommandID = COMMANDS.SCC_GetChangelist;
				}
				else if( Command == "getpublisheddata" )
				{
					NextCommand.CommandID = COMMANDS.GetPublishedData;
				}
				else if( Command == "launchgame" )
				{
					NextCommand.CommandID = COMMANDS.LaunchGame;
				}
				else if( Command == "launchconsole" )
				{
					NextCommand.CommandID = COMMANDS.LaunchConsole;
				}
				else if( Command == "testmap" )
				{
					AFTTestMap = Parent.ExpandString( NextCommand.CommandLine );
					AFTScreenShots.Clear();

					Parent.Log( "AFT: Test map set to '" + AFTTestMap + "'", Color.Magenta );
					NextCommand.CommandID = COMMANDS.Config;
				}
				else if( Command == "waittargetstate" )
				{
					NextCommand.CommandID = COMMANDS.WaitTargetState;
				}
				else if( Command == "retrievescreenshots" )
				{
					NextCommand.CommandID = COMMANDS.RetrieveScreenShots;
				}
				else if( Command == "processscreenshots" )
				{
					NextCommand.CommandID = COMMANDS.ProcessScreenShots;
				}
				else if( Command == "steammakeversion" )
				{
					NextCommand.CommandID = COMMANDS.SteamMakeVersion;
				}
				else if( Command == "updatesteamserver" )
				{
					NextCommand.CommandID = COMMANDS.UpdateSteamServer;
				}
				else if( Command == "restartsteamserver" )
				{
					NextCommand.CommandID = COMMANDS.RestartSteamServer;
				}
				else if( Command == "unsetuptype" )
				{
					UnSetupType = Parent.ExpandString( NextCommand.CommandLine );
					NextCommand.CommandID = COMMANDS.Config;
				}
				else if( Command == "unsetup" )
				{
					NextCommand.CommandID = COMMANDS.UnSetup;
				}
				else if( Command == "createdvdlayout" )
				{
					NextCommand.CommandID = COMMANDS.CreateDVDLayout;
				}
				else if( Command == "sync" )
				{
					NextCommand.CommandID = COMMANDS.SCC_Sync;
				}
				else if( Command == "synctohead" )
				{
					NextCommand.CommandID = COMMANDS.SCC_SyncToHead;
				}
				else if( Command == "artistsync" )
				{
					NextCommand.CommandID = COMMANDS.SCC_ArtistSync;
				}
				else if( Command == "getchanges" )
				{
					NextCommand.CommandID = COMMANDS.SCC_GetChanges;
				}
				else if( Command == "sendqachanges" )
				{
					NextCommand.CommandID = COMMANDS.Config;
					IsSendingQAChanges = true;
				}
				else if( Command == "syncsinglechangelist" )
				{
					NextCommand.CommandID = COMMANDS.SCC_SyncSingleChangeList;
				}
				else if( Command == "checkout" )
				{
					NextCommand.CommandID = COMMANDS.SCC_Checkout;
				}
				else if( Command == "openfordelete" )
				{
					NextCommand.CommandID = COMMANDS.SCC_OpenForDelete;
				}
				else if( Command == "checkoutgame" )
				{
					NextCommand.CommandID = COMMANDS.SCC_CheckoutGame;
				}
				else if( Command == "checkoutgfwlgame" )
				{
					NextCommand.CommandID = COMMANDS.SCC_CheckoutGFWLGame;
				}
				else if( Command == "checkoutgadcheckpoint" )
				{
					NextCommand.CommandID = COMMANDS.SCC_CheckoutGADCheckpoint;
				}
				else if( Command == "checkoutshader" )
				{
					NextCommand.CommandID = COMMANDS.SCC_CheckoutShader;
				}
				else if( Command == "checkoutdialog" )
				{
					NextCommand.CommandID = COMMANDS.SCC_CheckoutDialog;
				}
				else if( Command == "checkoutfonts" )
				{
					NextCommand.CommandID = COMMANDS.SCC_CheckoutFonts;
				}
				else if( Command == "checkoutlocpackage" )
				{
					NextCommand.CommandID = COMMANDS.SCC_CheckoutLocPackage;
				}
				else if( Command == "checkoutgdf" )
				{
					NextCommand.CommandID = COMMANDS.SCC_CheckoutGDF;
				}
				else if( Command == "checkoutcat" )
				{
					NextCommand.CommandID = COMMANDS.SCC_CheckoutCat;
				}
				else if( Command == "checkoutlayout" )
				{
					NextCommand.CommandID = COMMANDS.SCC_CheckoutLayout;
				}
				else if( Command == "checkouthashes" )
				{
					NextCommand.CommandID = COMMANDS.SCC_CheckoutHashes;
				}
				else if( Command == "checkoutdlc" )
				{
					NextCommand.CommandID = COMMANDS.SCC_CheckoutDLC;
				}
				else if( Command == "checkoutenginecontent" )
				{
					NextCommand.CommandID = COMMANDS.SCC_CheckoutEngineContent;
				}
				else if( Command == "checkoutgamecontent" )
				{
					NextCommand.CommandID = COMMANDS.SCC_CheckoutGameContent;
				}
				else if( Command == "checkoutaftscreenshots" )
				{
					NextCommand.CommandID = COMMANDS.SCC_CheckoutAFTScreenshots;
				}
				else if( Command == "checkoutconncache" )
				{
					NextCommand.CommandID = COMMANDS.SCC_CheckoutConnCache;
				}
				else if( Command == "getnextchangelist" )
				{
					NextCommand.CommandID = COMMANDS.SCC_GetNextChangelist;
				}
				else if( Command == "submit" )
				{
					IsBuilding = true;
					IsTagging = false;
					NextCommand.CommandID = COMMANDS.SCC_SignUnsubmitted;
				}
				else if( Command == "submitandtag" )
				{
					IsBuilding = true;
					IsTagging = true;
					NextCommand.CommandID = COMMANDS.SCC_SignUnsubmitted;
				}
				else if( Command == "enablerestorenewerchanges" )
				{
					IsRestoringNewerChanges = true;
					Parent.Log( "The submission restore/no overwrite mode is now TRUE", Color.Magenta );
					NextCommand.CommandID = COMMANDS.Config;
				}
				else if( Command == "disablerestorenewerchanges" )
				{
					IsRestoringNewerChanges = false;
					Parent.Log( "The submission restore/no overwrite mode is now FALSE", Color.Magenta );
					NextCommand.CommandID = COMMANDS.Config;
				}
				else if( Command == "createnewlabel" || Command == "createlabel" )
				{
					NextCommand.CommandID = COMMANDS.SCC_CreateNewLabel;
				}
				else if( Command == "updatelabeldescription" )
				{
					NextCommand.CommandID = COMMANDS.SCC_LabelUpdateDescription;
				}
				else if( Command == "revert" )
				{
					NextCommand.CommandID = COMMANDS.SCC_Revert;
				}
				else if( Command == "revertfilespec" || Command == "revertfile" )
				{
					NextCommand.CommandID = COMMANDS.SCC_RevertFileSpec;
				}
				else if( Command == "waitforactive" )
				{
					NextCommand.CommandID = COMMANDS.WaitForActive;
				}
				else if( Command == "waitforjobs" )
				{
					NextCommand.CommandID = COMMANDS.WaitForJobs;
				}
				else if( Command == "addunrealgamejob" )
				{
					NextCommand.CommandID = COMMANDS.AddUnrealGameJob;
				}
				else if( Command == "addunrealagnosticjob" )
				{
					NextCommand.CommandID = COMMANDS.AddUnrealAgnosticJob;
				}
				else if( Command == "addunrealfullgamejob" )
				{
					NextCommand.CommandID = COMMANDS.AddUnrealFullGameJob;
				}
				else if( Command == "addunrealgfwlgamejob" )
				{
					NextCommand.CommandID = COMMANDS.AddUnrealGFWLGameJob;
				}
				else if( Command == "addunrealgfwlfullgamejob" )
				{
					NextCommand.CommandID = COMMANDS.AddUnrealGFWLFullGameJob;
				}
				else if( Command == "addconformjob" )
				{
					NextCommand.CommandID = COMMANDS.AddConformJob;
				}
				else if( Command == "clean" )
				{
					NextCommand.CommandID = COMMANDS.Clean;
				}
				else if( Command == "cleanmacs" )
				{
					NextCommand.CommandID = COMMANDS.CleanMacs;
				}
				else if( Command == "buildubt" || Command == "buildubt9" )
				{
					NextCommand.CommandID = COMMANDS.BuildUBT9;
				}
				else if( Command == "buildubt10" )
				{
					NextCommand.CommandID = COMMANDS.BuildUBT10;
				}
				else if( Command == "ms9build" )
				{
					NextCommand.CommandID = COMMANDS.MS9Build;
				}
				else if( Command == "ms10build" )
				{
					NextCommand.CommandID = COMMANDS.MS10Build;
				}
				else if( Command == "unrealbuild" )
				{
					NextCommand.CommandID = COMMANDS.UnrealBuild;
				}
				else if( Command == "msvc9clean" )
				{
					NextCommand.CommandID = COMMANDS.MSVC9Clean;
				}
				else if( Command == "msvc9build" )
				{
					NextCommand.CommandID = COMMANDS.MSVC9Build;
				}
				else if( Command == "msvc9deploy" )
				{
					NextCommand.CommandID = COMMANDS.MSVC9Deploy;
				}
				else if( Command == "msvc9full" )
				{
					NextCommand.CommandID = COMMANDS.MSVC9Full;
				}
				else if( Command == "msvc10clean" )
				{
					NextCommand.CommandID = COMMANDS.MSVC10Clean;
				}
				else if( Command == "msvc10build" )
				{
					NextCommand.CommandID = COMMANDS.MSVC10Build;
				}
				else if( Command == "msvc10deploy" )
				{
					NextCommand.CommandID = COMMANDS.MSVC10Deploy;
				}
				else if( Command == "msvc10full" )
				{
					NextCommand.CommandID = COMMANDS.MSVC10Full;
				}
				else if( Command == "shaderclean" )
				{
					NextCommand.CommandID = COMMANDS.ShaderClean;
				}
				else if( Command == "shaderbuild" )
				{
					NextCommand.CommandID = COMMANDS.ShaderBuild;
				}
				else if( Command == "connectionbuild" )
				{
					NextCommand.CommandID = COMMANDS.ConnectionBuild;
				}
				else if( Command == "localshaderbuild" )
				{
					NextCommand.CommandID = COMMANDS.LocalShaderBuild;
				}
				else if( Command == "cookshaderbuild" )
				{
					NextCommand.CommandID = COMMANDS.CookShaderBuild;
				}
				else if( Command == "shaderfull" )
				{
					NextCommand.CommandID = COMMANDS.ShaderFull;
				}
				else if( Command == "ps3makepatchbinary" )
				{
					NextCommand.CommandID = COMMANDS.PS3MakePatchBinary;
				}
				else if( Command == "ps3makepatch" )
				{
					NextCommand.CommandID = COMMANDS.PS3MakePatch;
				}
				else if( Command == "ps3makedlc" )
				{
					NextCommand.CommandID = COMMANDS.PS3MakeDLC;
				}
				else if( Command == "ps3maketu" )
				{
					NextCommand.CommandID = COMMANDS.PS3MakeTU;
				}
				else if( Command == "pcmaketu" )
				{
					NextCommand.CommandID = COMMANDS.PCMakeTU;
				}
				else if( Command == "pcpackagetu" )
				{
					NextCommand.CommandID = COMMANDS.PCPackageTU;
				}
				else if( Command == "buildscript" )
				{
					NextCommand.CommandID = COMMANDS.BuildScript;
				}
				else if( Command == "buildscriptnoclean" )
				{
					NextCommand.CommandID = COMMANDS.BuildScriptNoClean;
				}
				else if( Command == "iphonepackage" )
				{
					NextCommand.CommandID = COMMANDS.iPhonePackage;
				}
				else if( Command == "iphonesetsigningprefix" )
				{
					SigningPrefixOverride = NextCommand.CommandLine;
					Parent.Log( "SigningPrefixOverride is now set to " + NextCommand.CommandLine, Color.Magenta );
					NextCommand.CommandID = COMMANDS.Config;
				}
				else if( Command == "iphonesetdevelopersigningidentity" )
				{
					DeveloperSigningIdentityOverride = NextCommand.CommandLine;
					Parent.Log( "DeveloperSigningIdentityOverride is now set to " + NextCommand.CommandLine, Color.Magenta );
					NextCommand.CommandID = COMMANDS.Config;
				}
				else if( Command == "iphonesetdistributionsigningidentity" )
				{
					DistributionSigningIdentityOverride = NextCommand.CommandLine;
					Parent.Log( "DistributionSigningIdentityOverride is now set to " + NextCommand.CommandLine, Color.Magenta );
					NextCommand.CommandID = COMMANDS.Config;
				}
				else if( Command == "iphonecompileserver" )
				{
					iPhoneCompileServerOverride = NextCommand.CommandLine;
					Parent.Log( "iPhoneCompileServerOverride is now set to " + NextCommand.CommandLine, Color.Magenta );
					NextCommand.CommandID = COMMANDS.Config;
				}
				else if( Command == "iphonesigningserver" )
				{
					iPhoneSigningServerOverride = NextCommand.CommandLine;
					Parent.Log( "iPhoneSigningServerOverride is now set to " + NextCommand.CommandLine, Color.Magenta );
					NextCommand.CommandID = COMMANDS.Config;
				}
				else if( Command == "preheatmapoven" )
				{
					NextCommand.CommandID = COMMANDS.PreHeatMapOven;
				}
				else if( Command == "preheatdlc" )
				{
					NextCommand.CommandID = COMMANDS.PreHeatDLC;
				}
				else if( Command == "packagetu" )
				{
					NextCommand.CommandID = COMMANDS.PackageTU;
				}
				else if( Command == "packagedlc" )
				{
					NextCommand.CommandID = COMMANDS.PackageDLC;
				}
				else if( Command == "cookmaps" )
				{
					NextCommand.CommandID = COMMANDS.CookMaps;
				}
				else if( Command == "cookinimaps" )
				{
					NextCommand.CommandID = COMMANDS.CookIniMaps;
				}
				else if( Command == "cooksounds" )
				{
					NextCommand.CommandID = COMMANDS.CookSounds;
				}
				else if( Command == "createhashes" )
				{
					NextCommand.CommandID = COMMANDS.CreateHashes;
				}
				else if( Command == "wrangle" )
				{
					NextCommand.CommandID = COMMANDS.Wrangle;
				}
				else if( Command == "publish" )
				{
					IsPublishing = true;
					NextCommand.CommandID = COMMANDS.Publish;
				}
				else if( Command == "publishtagset" )
				{
					IsPublishing = true;
					NextCommand.CommandID = COMMANDS.PublishTagset;
				}
				else if( Command == "publishlanguage" )
				{
					IsPublishing = true;
					NextCommand.CommandID = COMMANDS.PublishLanguage;
				}
				else if( Command == "publishlayout" )
				{
					IsPublishing = true;
					NextCommand.CommandID = COMMANDS.PublishLayout;
				}
				else if( Command == "publishlayoutlanguage" )
				{
					IsPublishing = true;
					NextCommand.CommandID = COMMANDS.PublishLayoutLanguage;
				}
				else if( Command == "publishdlc" )
				{
					IsPublishing = true;
					NextCommand.CommandID = COMMANDS.PublishDLC;
				}
				else if( Command == "publishtu" )
				{
					IsPublishing = true;
					NextCommand.CommandID = COMMANDS.PublishTU;
				}
				else if( Command == "publishfiles" )
				{
					IsPublishing = true;
					NextCommand.CommandID = COMMANDS.PublishFiles;
				}
				else if( Command == "publishrawfiles" )
				{
					IsPublishing = true;
					NextCommand.CommandID = COMMANDS.PublishRawFiles;
				}
				else if( Command == "generatetoc" )
				{
					NextCommand.CommandID = COMMANDS.GenerateTOC;
				}
				else if( Command == "deploy" )
				{
					NextCommand.CommandID = COMMANDS.Deploy;
				}
				else if( Command == "makeiso" )
				{
					NextCommand.CommandID = COMMANDS.MakeISO;
				}
				else if( Command == "makemd5" )
				{
					NextCommand.CommandID = COMMANDS.MakeMD5;
				}
				else if( Command == "copyfolder" )
				{
					NextCommand.CommandID = COMMANDS.CopyFolder;
				}
				else if( Command == "movefolder" )
				{
					NextCommand.CommandID = COMMANDS.MoveFolder;
				}
				else if( Command == "cleanfolder" )
				{
					NextCommand.CommandID = COMMANDS.CleanFolder;
				}
				else if( Command == "conform" )
				{
					NextCommand.CommandID = COMMANDS.Conform;
				}
				else if( Command == "patchscript" )
				{
					NextCommand.CommandID = COMMANDS.PatchScript;
				}
				else if( Command == "checkpointgameassetdatabase" )
				{
					NextCommand.CommandID = COMMANDS.CheckpointGameAssetDatabase;
				}
				else if( Command == "updategameassetdatabase" )
				{
					NextCommand.CommandID = COMMANDS.UpdateGameAssetDatabase;
				}
				else if( Command == "tagreferencedassets" )
				{
					NextCommand.CommandID = COMMANDS.TagReferencedAssets;
				}
				else if( Command == "tagdvdassets" )
				{
					NextCommand.CommandID = COMMANDS.TagDVDAssets;
				}
				else if( Command == "auditcontent" )
				{
					NextCommand.CommandID = COMMANDS.AuditContent;
				}
				else if( Command == "findstaticmeshcanbecomedynamic" )
				{
					NextCommand.CommandID = COMMANDS.FindStaticMeshCanBecomeDynamic;
				}
				else if( Command == "fixupredirects" )
				{
					NextCommand.CommandID = COMMANDS.FixupRedirects;
				}
				else if( Command == "resavedeprecatedpackages" )
				{
					NextCommand.CommandID = COMMANDS.ResaveDeprecatedPackages;
				}
				else if( Command == "analyzereferencedcontent" )
				{
					AnalyzeReferencedContentConfiguration = Parent.ExpandString( NextCommand.CommandLine );
					Parent.Log( "AnalyzeReferencedContentConfiguration set to '" + AnalyzeReferencedContentConfiguration + "'", Color.Magenta );
					NextCommand.CommandID = COMMANDS.AnalyzeReferencedContent;
				}
				else if( Command == "minecookedpackages" )
				{
					NextCommand.CommandID = COMMANDS.MineCookedPackages;
				}
				else if( Command == "contentcomparison" )
				{
					NextCommand.CommandID = COMMANDS.ContentComparison;
				}
				else if( Command == "dumpmapsummary" )
				{
					NextCommand.CommandID = COMMANDS.DumpMapSummary;
				}
				else if( Command == "crossbuildconform" )
				{
					NextCommand.CommandID = COMMANDS.CrossBuildConform;
				}
				else if( Command == "trigger" )
				{
					NextCommand.CommandID = COMMANDS.Trigger;
				}
				else if( Command == "cleantrigger" )
				{
					NextCommand.CommandID = COMMANDS.CleanTrigger;
				}
				else if( Command == "autotrigger" )
				{
					NextCommand.CommandID = COMMANDS.AutoTrigger;
				}
				else if( Command == "sqlexecint" )
				{
					NextCommand.CommandID = COMMANDS.SQLExecInt;
				}
				else if( Command == "sqlexecdouble" )
				{
					NextCommand.CommandID = COMMANDS.SQLExecDouble;
				}
				else if( Command == "validateinstall" )
				{
					NextCommand.CommandID = COMMANDS.ValidateInstall;
				}
				else if( Command == "validateshas" )
				{
					NextCommand.CommandID = COMMANDS.ExtractSHAs;
				}
				else if( Command == "bumpagentversion" )
				{
					NextCommand.CommandID = COMMANDS.BumpAgentVersion;
				}
				else if( Command == "bumpengineversion" )
				{
					NextCommand.CommandID = COMMANDS.BumpEngineVersion;
				}
				else if( Command == "getengineversion" )
				{
					NextCommand.CommandID = COMMANDS.GetEngineVersion;
				}
				else if( Command == "updategdfversion" )
				{
					NextCommand.CommandID = COMMANDS.UpdateGDFVersion;
				}
				else if( Command == "makegfwlcat" )
				{
					NextCommand.CommandID = COMMANDS.MakeGFWLCat;
				}
				else if( Command == "zdpp" )
				{
					NextCommand.CommandID = COMMANDS.ZDPP;
				}
				else if( Command == "steamdrm" )
				{
					NextCommand.CommandID = COMMANDS.SteamDRM;
				}
				else if( Command == "savedefines" )
				{
					NextCommand.CommandID = COMMANDS.SaveDefines;
				}
				else if( Command == "updatesymbolserver" )
				{
					NextCommand.CommandID = COMMANDS.UpdateSourceServer;
				}
				else if( Command == "addexetosymbolserver" )
				{
					NextCommand.CommandID = COMMANDS.AddExeToSymbolServer;
				}
				else if( Command == "adddlltosymbolserver" )
				{
					NextCommand.CommandID = COMMANDS.AddDllToSymbolServer;
				}
				else if( Command == "sign" )
				{
					NextCommand.CommandID = COMMANDS.CheckSigned;
				}
				else if( Command == "signcat" )
				{
					NextCommand.CommandID = COMMANDS.SignCat;
				}
				else if( Command == "signbinary" )
				{
					NextCommand.CommandID = COMMANDS.SignBinary;
				}
				else if( Command == "signfile" )
				{
					NextCommand.CommandID = COMMANDS.SignFile;
				}
				else if( Command == "trackfilesize" )
				{
					NextCommand.CommandID = COMMANDS.TrackFileSize;
				}
				else if( Command == "trackfoldersize" )
				{
					NextCommand.CommandID = COMMANDS.TrackFolderSize;
				}
				else if( Command == "wait" )
				{
					NextCommand.CommandID = COMMANDS.Wait;
				}
				else if( Command == "checkforucinvcprojfiles" )
				{
					NextCommand.CommandID = COMMANDS.CheckForUCInVCProjFiles;
				}
				else if( Command == "smoketest" )
				{
					NextCommand.CommandID = COMMANDS.SmokeTest;
				}
				else if( Command == "loadpackages" )
				{
					NextCommand.CommandID = COMMANDS.LoadPackages;
				}
				else if( Command == "cookpackages" )
				{
					NextCommand.CommandID = COMMANDS.CookPackages;
				}
				else
				{
					ErrorLevel = COMMANDS.IllegalCommand;
					NextCommand.CommandID = COMMANDS.Error;
					NextCommand.CommandLine = Line;
				}
            }
            return NextCommand;
        }

		/**
		 * Init the collation types for processing changelists
		 */
		public void InitCollationTypes()
		{
			ValidGames = UnrealControls.GameLocator.LocateGames( Environment.CurrentDirectory );

			CollationTypes[( int )COLLATION.Engine]	= new CollationType( COLLATION.Engine, "Engine Code Changes" );
			CollationTypes[( int )COLLATION.Rendering] = new CollationType( COLLATION.Rendering, "Rendering Code Changes" );
			CollationTypes[( int )COLLATION.Audio] = new CollationType( COLLATION.Audio, "Audio Code Changes" );
			CollationTypes[( int )COLLATION.Editor]	= new CollationType( COLLATION.Editor, "Editor Code Changes" );
			CollationTypes[( int )COLLATION.GFx] = new CollationType( COLLATION.GFx, "GFx Code Changes" );

			int GameCollation = ( int )COLLATION.Game;
			foreach( string ValidGame in ValidGames )
			{
				CollationTypes[GameCollation] = new CollationType( ( COLLATION )GameCollation, ValidGame + " Code Changes" );
				GameCollation++;
				CollationTypes[GameCollation] = new CollationType( ( COLLATION )GameCollation, ValidGame + " Map Changes" );
				GameCollation++;
				CollationTypes[GameCollation] = new CollationType( ( COLLATION )GameCollation, ValidGame + " Content Changes" );
				GameCollation++;
			}

			CollationTypes[( int )COLLATION.Windows] = new CollationType( COLLATION.Windows, "Windows Specific Changes" );
			CollationTypes[( int )COLLATION.Xbox360] = new CollationType( COLLATION.Xbox360, "Xbox360 Changes" );
			CollationTypes[( int )COLLATION.PS3] = new CollationType( COLLATION.PS3, "PS3 Changes" );
			CollationTypes[( int )COLLATION.WiiU] = new CollationType( COLLATION.WiiU, "WiiU Changes" );
			CollationTypes[( int )COLLATION.NGP] = new CollationType( COLLATION.iPhone, "NGP Changes" );
			CollationTypes[( int )COLLATION.iPhone] = new CollationType( COLLATION.iPhone, "iPhone Changes" );
			CollationTypes[( int )COLLATION.Android] = new CollationType( COLLATION.Android, "Android Changes" );
			CollationTypes[( int )COLLATION.Mac] = new CollationType( COLLATION.Mac, "Mac Changes" );
			CollationTypes[( int )COLLATION.Flash] = new CollationType( COLLATION.Mac, "Flash Changes" );

			CollationTypes[( int )COLLATION.OnlinePC] = new CollationType( COLLATION.OnlinePC, "Online PC Changes" );
			CollationTypes[( int )COLLATION.GameCenter] = new CollationType( COLLATION.GameSpy, "GameCenter Changes" );
			CollationTypes[( int )COLLATION.GameSpy] = new CollationType( COLLATION.GameSpy, "GameSpy Changes" );
			CollationTypes[( int )COLLATION.G4WLive] = new CollationType( COLLATION.G4WLive, "G4W Live Changes" );
			CollationTypes[( int )COLLATION.Steam] = new CollationType( COLLATION.Steam, "Steam Changes" );

			CollationTypes[( int )COLLATION.Infrastructure] = new CollationType( COLLATION.Infrastructure, "Infrastructure Changes" );
			CollationTypes[( int )COLLATION.Install] = new CollationType( COLLATION.Install, "Installer Changes" );
			CollationTypes[( int )COLLATION.Swarm] = new CollationType( COLLATION.Swarm, "Swarm Changes" );
			CollationTypes[( int )COLLATION.Lightmass] = new CollationType( COLLATION.Lightmass, "Lightmass Changes" );
			CollationTypes[( int )COLLATION.Tools] = new CollationType( COLLATION.Tools, "Tools Changes" );
			CollationTypes[( int )COLLATION.Loc] = new CollationType( COLLATION.Loc, "Localisation Changes" );

			// Set the folders to look for 
			CollationTypes[( int )COLLATION.Engine].SetFolderMatches( 
				new List<string>()
				{
					// UE3
					"development/src/core",
					"development/src/engine",
					"development/src/gameframework",
					"development/src/ipdrv",
					"development/src/launch",
					"engine/config", 
					"engine/content",
					"engine/shaders",
					// UE4
					"engine/source/runtime"
				} );

			CollationTypes[( int )COLLATION.Rendering].SetFolderMatches(
				new List<string>()
				{
					"development/src/es2drv",
					"development/src/opengldrv",
					"development/src/d3d9drv",
					"development/src/d3d11drv"
				} );

			CollationTypes[( int )COLLATION.Audio].SetFolderMatches(
				new List<string>()
				{
					"development/src/alaudio",
					"development/src/coreaudio",
					"development/src/xaudio2"
				} );

			CollationTypes[( int )COLLATION.Editor].SetFolderMatches(
				new List<string>()
				{
					// UE3
					"development/src/unrealed",
					"engine/editorresources/facefx",
					"engine/editorresources/wpf/controls",
					"engine/editorresources/wx",
					// UE4
					"engine/source/editor"
				} );

			CollationTypes[( int )COLLATION.GFx].SetFolderMatches(
				new List<string>()
				{
					"development/src/gfxui",
					"development/src/gfxuieditor",
					"development/external/gfx"
				} );

			CollationTypes[( int )COLLATION.Windows].SetFolderMatches(
				new List<string>()
				{
					"development/src/windrv",
					"development/src/windows"
				} );

			CollationTypes[( int )COLLATION.Xbox360].SetFolderMatches(
				new List<string>()
				{
					"development/src/xenon",
					"development/tools/xenon",
					"development/src/xbox360"
				} );

			CollationTypes[( int )COLLATION.PS3].SetFolderMatches(
				new List<string>()
				{
					"development/src/ps3"
				} );

			CollationTypes[( int )COLLATION.WiiU].SetFolderMatches(
				new List<string>()
				{
					"development/src/wiiu"
				} );

			CollationTypes[( int )COLLATION.NGP].SetFolderMatches(
				new List<string>()
				{
					"development/src/ngp"
				} );

			CollationTypes[( int )COLLATION.iPhone].SetFolderMatches(
				new List<string>()
				{
					"development/tools/mobile/iphone",
					"development/src/iphone",
				} );

			CollationTypes[( int )COLLATION.Android].SetFolderMatches(
				new List<string>()
				{
					"development/src/android"
				} );

			CollationTypes[( int )COLLATION.Mac].SetFolderMatches(
				new List<string>()
				{
					"development/src/mac",
					"development/tools/macpackager"
				} );

			CollationTypes[( int )COLLATION.Flash].SetFolderMatches(
				new List<string>()
				{
					"development/src/flash"
				} );

			CollationTypes[( int )COLLATION.OnlinePC].SetFolderMatches(
				new List<string>()
				{
					"development/src/onlinesubsystempc",
				} );

			CollationTypes[( int )COLLATION.GameCenter].SetFolderMatches(
				new List<string>()
				{
					"development/src/onlinesubsystemgamecenter"
				} );

			CollationTypes[( int )COLLATION.GameSpy].SetFolderMatches(
				new List<string>()
				{
					"development/src/onlinesubsystemgamespy"
				} );

			CollationTypes[( int )COLLATION.G4WLive].SetFolderMatches(
				new List<string>()
				{
					"development/src/onlinesubsystemlive"
				} );

			CollationTypes[( int )COLLATION.Steam].SetFolderMatches(
				new List<string>()
				{
					"development/src/onlinesubsystemsteamworks"
				} );

			CollationTypes[( int )COLLATION.Infrastructure].SetFolderMatches(
				new List<string>()
				{
					"development/builder",
					"development/tools/builder",
					"development/tools/unrealprop",
					"development/src/targets",
					"development/src/unrealbuildtool",
					"development/src/xenon/unrealbuildtool",
					"development/src/ps3/unrealbuildtool",
					"development/src/wiiu/unrealbuildtool",
					"binaries/cookersync.xml"
				} );

			CollationTypes[( int )COLLATION.Install].SetFolderMatches(
				new List<string>()
				{
					"development/tools/unsetup"
				} );

			CollationTypes[( int )COLLATION.Swarm].SetFolderMatches(
				new List<string>()
				{
					"development/src/unrealswarm",
					"development/tools/unrealswarm"
				} );

			CollationTypes[( int )COLLATION.Lightmass].SetFolderMatches(
				new List<string>()
				{
					"development/tools/unreallightmass"
				} );

			CollationTypes[( int )COLLATION.Tools].SetFolderMatches(
				new List<string>()
				{
					// UE3
					"development/tools",
					// UE4
					"engine/source/developer",
					"engine/source/programs"
				} );

			CollationTypes[( int )COLLATION.Loc].SetFolderMatches(
				new List<string>()
				{
					"engine/localization",
					"engine/editorresources/wpf/localized"
				} );

			// Set the order of the reports 
			Reports.Enqueue( COLLATION.Engine );
			Reports.Enqueue( COLLATION.Rendering );
			Reports.Enqueue( COLLATION.Audio );
			Reports.Enqueue( COLLATION.Editor );
			Reports.Enqueue( COLLATION.GFx );

			int GameStep = ValidGames.Count;

			// Add in source changes per game
			GameCollation = ( int )COLLATION.Game;
			foreach( string ValidGame in ValidGames )
			{
				Reports.Enqueue( ( COLLATION )GameCollation );
				GameCollation += 3;
			}

			// Add in map changes per game
			GameCollation = ( ( int )COLLATION.Game ) + 1;
			foreach( string ValidGame in ValidGames )
			{
				Reports.Enqueue( ( COLLATION )GameCollation );
				GameCollation += 3;
			}

			// Add in content changes per game
			GameCollation = ( ( int )COLLATION.Game ) + 2;
			foreach( string ValidGame in ValidGames )
			{
				Reports.Enqueue( ( COLLATION )GameCollation );
				GameCollation += 3;
			}

			Reports.Enqueue( COLLATION.Windows );
			Reports.Enqueue( COLLATION.Xbox360 );
			Reports.Enqueue( COLLATION.PS3 );
			Reports.Enqueue( COLLATION.WiiU );
			Reports.Enqueue( COLLATION.NGP );
			Reports.Enqueue( COLLATION.iPhone );
			Reports.Enqueue( COLLATION.Android );
			Reports.Enqueue( COLLATION.Mac );
			Reports.Enqueue( COLLATION.Flash );

			Reports.Enqueue( COLLATION.OnlinePC );
			Reports.Enqueue( COLLATION.GameCenter );
			Reports.Enqueue( COLLATION.GameSpy );
			Reports.Enqueue( COLLATION.G4WLive );
			Reports.Enqueue( COLLATION.Steam );

			Reports.Enqueue( COLLATION.Infrastructure );
			Reports.Enqueue( COLLATION.Install );
			Reports.Enqueue( COLLATION.Swarm );
			Reports.Enqueue( COLLATION.Lightmass );
			Reports.Enqueue( COLLATION.Tools );
			Reports.Enqueue( COLLATION.Loc );

			// Remember the prioritised order of the reporting tags
			AllReports = new List<COLLATION>( Reports );
			AllReports.Add( COLLATION.Count );
		}

		// Iterate over all submitted changelists, and extract a list of users
		public string[] GetPerforceUsers()
		{
			List<string> Users = new List<string>();

			// Extract unique P4 users
			foreach( ChangeList CL in ChangeLists )
			{
				if( !Users.Contains( CL.User.ToLower() ) )
				{
					Users.Add( CL.User.ToLower() );
				}
			}

			Users.Sort();
			return ( Users.ToArray() );
		}

        // Goes over a changelist description and extracts the relevant information
        public void ProcessChangeList( P4Record Record )
        {
			// Add any changelist that isn't from builder to a list for later processing
			if( Record.Fields["user"].ToLower() != "build_machine" )
			{
				ChangeList CL = new ChangeList();

				CL.Description = Record.Fields["desc"];
				CL.CleanDescription();

				// Get the latest changelist number in this build - even if it is from the builder
				CL.Number = SafeStringToInt( Record.Fields["change"] );
				if( CL.Number > LabelInfo.Changelist )
				{
					LabelInfo.Changelist = CL.Number;
				}

				CL.User = Record.Fields["user"];
				CL.Time = SafeStringToInt( Record.Fields["time"] );

				if( Record.ArrayFields["depotFile"] != null )
				{
					foreach( string DepotFile in Record.ArrayFields["depotFile"] )
					{
						CL.Files.Add( "    ... " + DepotFile );
					}
				}

				ChangeLists.Add( CL );
			}
        }

        private COLLATION CollateGameChanges( COLLATION NewCollation, ChangeList CL, string CleanFile, string Game, int GameCollation )
        {
			// Cannot override a previously found collation of higher priority
			if( GameCollation >= ( int )NewCollation )
			{
				return NewCollation;
			}

			// Check for an extension the same as the game name - this is a map
            if( CleanFile.IndexOf( "." + Game ) >= 0 )
            {
				return ( ( COLLATION )( GameCollation + 1 ) );
            }
			// Check for game specific UE3 source files
            else if( CleanFile.IndexOf( "development/src/" + Game ) >= 0 )
            {
				return ( ( COLLATION )GameCollation );
            }
			// Check for game specific UE4 source files
			else if( CleanFile.IndexOf( Game + "/source" ) >= 0 )
			{
				return ( ( COLLATION )GameCollation );
			}
			// Check for content changes
			else if( CleanFile.IndexOf( Game + "game/" ) >= 0 )
            {
				return ( ( COLLATION )( GameCollation + 2 ) );
            }

			return ( NewCollation );
        }

		private COLLATION CheckCollation( COLLATION NewCollation, string CleanFile, COLLATION Check )
		{
			// Cannot override a previously found collation of higher priority
			if( Check >= NewCollation )
			{
				return NewCollation;
			}

			// See if the file name contains any of the folders for this type
			foreach( string FolderMatch in CollationTypes[( int )Check].FolderMatches )
			{
				if( CleanFile.IndexOf( FolderMatch ) >= 0 )
				{
					return Check;
				}
			}

			return NewCollation;
		}

        private void CollateChanges()
        {
			if( ChangelistsCollated == true )
			{
				return;
			}

            foreach( ChangeList CL in ChangeLists )
            {
				COLLATION NewCollation = COLLATION.Count;

				// Check files that were checked in
				foreach( string File in CL.Files )
				{
					string CleanFile = File.ToLower().Replace( '\\', '/' );

					NewCollation = CheckCollation( NewCollation, CleanFile, COLLATION.Engine );
					NewCollation = CheckCollation( NewCollation, CleanFile, COLLATION.Rendering );
					NewCollation = CheckCollation( NewCollation, CleanFile, COLLATION.Audio );
					NewCollation = CheckCollation( NewCollation, CleanFile, COLLATION.Editor );
					NewCollation = CheckCollation( NewCollation, CleanFile, COLLATION.GFx );

					int GameCollation = ( int )COLLATION.Game;
					foreach( string ValidGame in ValidGames )
					{
						NewCollation = CollateGameChanges( NewCollation, CL, CleanFile, ValidGame.ToLower(), GameCollation );
						GameCollation += 3;
					}

					NewCollation = CheckCollation( NewCollation, CleanFile, COLLATION.Windows );
					NewCollation = CheckCollation( NewCollation, CleanFile, COLLATION.Xbox360 );
					NewCollation = CheckCollation( NewCollation, CleanFile, COLLATION.PS3 );
					NewCollation = CheckCollation( NewCollation, CleanFile, COLLATION.WiiU );
					NewCollation = CheckCollation( NewCollation, CleanFile, COLLATION.NGP );
					NewCollation = CheckCollation( NewCollation, CleanFile, COLLATION.iPhone );
					NewCollation = CheckCollation( NewCollation, CleanFile, COLLATION.Android );
					NewCollation = CheckCollation( NewCollation, CleanFile, COLLATION.Mac );
					NewCollation = CheckCollation( NewCollation, CleanFile, COLLATION.Flash );

					NewCollation = CheckCollation( NewCollation, CleanFile, COLLATION.OnlinePC );
					NewCollation = CheckCollation( NewCollation, CleanFile, COLLATION.GameCenter );
					NewCollation = CheckCollation( NewCollation, CleanFile, COLLATION.GameSpy );
					NewCollation = CheckCollation( NewCollation, CleanFile, COLLATION.G4WLive );
					NewCollation = CheckCollation( NewCollation, CleanFile, COLLATION.Steam );

					NewCollation = CheckCollation( NewCollation, CleanFile, COLLATION.Infrastructure );
					NewCollation = CheckCollation( NewCollation, CleanFile, COLLATION.Install );
					NewCollation = CheckCollation( NewCollation, CleanFile, COLLATION.Swarm );
					NewCollation = CheckCollation( NewCollation, CleanFile, COLLATION.Lightmass );
					NewCollation = CheckCollation( NewCollation, CleanFile, COLLATION.Tools );
					NewCollation = CheckCollation( NewCollation, CleanFile, COLLATION.Loc );

					if( AllReports.IndexOf( NewCollation ) < AllReports.IndexOf( CL.Collate ) )
					{
						CL.Collate = NewCollation;
					}
				}

				if( NewCollation == COLLATION.Count )
				{
					NewCollation = COLLATION.Engine;
				}

				if( CL.Collate < COLLATION.Count )
				{
					CollationTypes[( int )CL.Collate].Active = true;
				}

				Parent.Log( " ... changelist " + CL.Number.ToString() + " placed in collation " + CL.Collate.ToString(), Color.DarkGreen );
            }

			ChangelistsCollated = true;
        }

        private bool GetCollatedChanges( StringBuilder Changes, COLLATION Collate, string User )
        {
            bool CollTypeHasEntries = false;
            CollationType CollType = CollationTypes[( int )Collate];
            if( CollType.Active )
            {
                foreach( ChangeList CL in ChangeLists )
                {
                    if( CL.Collate == Collate && ( User.Length == 0 || User.ToLower() == CL.User.ToLower() ) )
                    {
                        CollTypeHasEntries = true;
                        break;
                    }
                }

                if( CollTypeHasEntries )
                {
                    Changes.Append( "------------------------------------------------------------" + Environment.NewLine );
                    Changes.Append( "\t" + CollType.Title + Environment.NewLine );
                    Changes.Append( "------------------------------------------------------------" + Environment.NewLine + Environment.NewLine );

                    foreach( ChangeList CL in ChangeLists )
                    {
                        if( CL.Collate == Collate && ( User.Length == 0 || User.ToLower() == CL.User.ToLower() ) )
                        {
                            DateTime Time = new DateTime( 1970, 1, 1 );
                            Time += new TimeSpan( ( long )CL.Time * 10000 * 1000 );
                            Changes.Append( "Change: " + CL.Number.ToString() + " by " + CL.User + " on " + Time.ToLocalTime().ToString() + Environment.NewLine );
                            Changes.Append( CL.Description + Environment.NewLine );
                        }
                    }
                }
            }

            return ( CollTypeHasEntries );
        }

        public string GetChanges( string User )
        {
            bool HasChanges = false;
            StringBuilder Changes = new StringBuilder();

            Changes.Append( LabelInfo.Description );

            Changes.Append( Environment.NewLine );

            CollateChanges();

            foreach( COLLATION Collation in Reports )
            {
                HasChanges |= GetCollatedChanges( Changes, Collation, User );
            }

            if( HasChanges )
            {
                return ( Changes.ToString() );
            }

            return ( "" );
        }
	}
}
