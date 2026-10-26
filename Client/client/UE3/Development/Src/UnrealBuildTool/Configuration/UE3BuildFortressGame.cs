/**
 * Copyright 1998-2012 Epic Games, Inc. All Rights Reserved.
 */

using System;
using System.Collections.Generic;
using System.Text;

namespace UnrealBuildTool
{
	class UE3BuildFortressGame : UE3BuildGame
	{
		/** Returns the singular name of the game being built ("ExampleGame", "UDKGame", etc) */
		public string GetGameName()
		{
			return "FortressGame";
		}
		
		/** Returns a subplatform (e.g. dll) to disambiguate object files */
		virtual public string GetSubPlatform()
		{
			return ( "" );
		}

		/** Get the desired OnlineSubsystem. */
		public string GetDesiredOnlineSubsystem( CPPEnvironment CPPEnv, UnrealTargetPlatform Platform )
		{
            return ("Steamworks");
		}

		/** Returns true if the game wants to have PC ES2 simulator (ie ES2 Dynamic RHI) enabled */
		public bool ShouldCompileES2()
		{
			return false;
		}

        /** Returns whether PhysX should be compiled on mobile platforms */
        public bool ShouldCompilePhysXMobile()
        {
            return UE3BuildConfiguration.bCompilePhysXWithMobile;
        }
		
		/** Allows the game add any global environment settings before building */
        public void GetGameSpecificGlobalEnvironment(CPPEnvironment GlobalEnvironment, UnrealTargetPlatform Platform)
        {
			// Fortress specific disabling of features.
			GlobalEnvironment.Definitions.Add( "WITH_TTS=0" );
			GlobalEnvironment.Definitions.Add( "WITH_SPEECH_RECOGNITION=0" );
			GlobalEnvironment.Definitions.Add( "USE_MASSIVE_LOD=0" );
            GlobalEnvironment.Definitions.Add( "SUPPORT_HARDWARE_INSTANCING=0" ); // we probably want this back
			GlobalEnvironment.Definitions.Add( "WITH_ACTORX=1" );
            GlobalEnvironment.Definitions.Add( "WITH_EDITORONLY_DATA=1" ); // we always want editor only data for our dedicated server.   @see Core.h  #ifndef WITH_EDITORONLY_DATA  ln 52
            GlobalEnvironment.Definitions.Add( "MAX_NET_CHANNELS=50000"); // need lots of channels until we group buildings together into one channel

            if (Platform == UnrealTargetPlatform.Win32)
            {
                // No Editor in win32
                UE3BuildConfiguration.bBuildEditor = false;
            }
		}

        /** Allows the game to add any Platform/Configuration environment settings before building */
        public void GetGameSpecificPlatformConfigurationEnvironment(CPPEnvironment GlobalEnvironment, LinkEnvironment FinalLinkEnvironment)
        {
            if (GlobalEnvironment.TargetPlatform == CPPTargetPlatform.Win32)
            {
                // For Fortress win32, we want to ship a version that acts more like a console
                if (GlobalEnvironment.TargetConfiguration == CPPTargetConfiguration.Shipping)
                {
                    GlobalEnvironment.Definitions.Remove("FINAL_RELEASE=0");
                    GlobalEnvironment.Definitions.Remove("SHIPPING_PC_GAME=1");

                    GlobalEnvironment.Definitions.Add("FINAL_RELEASE=1");
                    GlobalEnvironment.Definitions.Add("SHIPPING_PC_GAME=0");
                }
                else if (GlobalEnvironment.TargetConfiguration == CPPTargetConfiguration.Test)
                {
                    GlobalEnvironment.Definitions.Remove("FINAL_RELEASE=0");
                    GlobalEnvironment.Definitions.Remove("SHIPPING_PC_GAME=1");

                    GlobalEnvironment.Definitions.Add("FINAL_RELEASE=1");
                    GlobalEnvironment.Definitions.Add("FINAL_RELEASE_DEBUGCONSOLE=1");
                    GlobalEnvironment.Definitions.Add("SHIPPING_PC_GAME=0");
                }
            }
        }

        /** Returns the xex.xml file for the given game */
		public FileItem GetXEXConfigFile()
		{
			return FileItem.GetExistingItemByPath("FortressGame/Live/xex.xml");
		}

        /** Allows the game to add any additional environment settings before building */
		virtual public void SetUpGameEnvironment(CPPEnvironment GameCPPEnvironment, LinkEnvironment FinalLinkEnvironment, List<UE3ProjectDesc> GameProjects)
		{
            GameProjects.Add(new UE3ProjectDesc("FortressBase/FortressBase.vcxproj"));
            GameCPPEnvironment.IncludePaths.Add("FortressBase/Inc");

            GameProjects.Add(new UE3ProjectDesc("Fortress/Fortress.vcxproj"));
            GameCPPEnvironment.IncludePaths.Add("Fortress/Inc");

            if (UE3BuildConfiguration.bBuildEditor &&
    (GameCPPEnvironment.TargetPlatform == CPPTargetPlatform.Win32 || GameCPPEnvironment.TargetPlatform == CPPTargetPlatform.Win64))
            {
                GameProjects.Add(new UE3ProjectDesc("FortressEditor/FortressEditor.vcxproj"));
                GameCPPEnvironment.IncludePaths.Add("FortressEditor/Inc");
            }


			GameCPPEnvironment.Definitions.Add("GAMENAME=FORTRESSGAME");
		}
	}

    class UE3BuildFortressGameServer : UE3BuildFortressGame
    {
		/** Returns a subplatform (e.g. dll) to disambiguate object files */
		override public string GetSubPlatform()
		{
			return ( "Server" );
		}
    }
}
