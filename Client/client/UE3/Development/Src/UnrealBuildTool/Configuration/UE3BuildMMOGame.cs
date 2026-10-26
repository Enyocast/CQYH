/**
 *
 * Copyright 1998-2013 Epic Games, Inc. All Rights Reserved.
 */

using System;
using System.Collections.Generic;
using System.Text;
//using System.Windows.Forms;

namespace UnrealBuildTool
{
	class UE3BuildMMOGame : UE3BuildGame
	{
        /** Returns the singular name of the game being built ("MMOGame", "UDKGame", etc) */
		public string GetGameName()
		{
			return "MMOGame";
		}
		
		/** Returns a subplatform (e.g. dll) to disambiguate object files */
		public string GetSubPlatform()
		{
			return ( "" );
		}

		/** Get the desired OnlineSubsystem. */
		public string GetDesiredOnlineSubsystem( CPPEnvironment CPPEnv, UnrealTargetPlatform Platform )
		{
			string ForcedOSS = UE3BuildTarget.ForceOnlineSubsystem( Platform );
			if( ForcedOSS != null )
			{
				return ( ForcedOSS );
			}

			return ( "PC" );
		}

		/** Returns true if the game wants to have PC ES2 simulator (ie ES2 Dynamic RHI) enabled */
		public bool ShouldCompileES2()
		{
			return true;
		}

        /** Allows the game add any global environment settings before building */
        public void GetGameSpecificGlobalEnvironment(CPPEnvironment GlobalEnvironment)
        {            
        }

        /** Returns the xex.xml file for the given game */
		public FileItem GetXEXConfigFile()
		{
			return FileItem.GetExistingItemByPath("MMOGame/Live/xex.xml");
		}

        /** Allows the game to add any additional environment settings before building */
		public void SetUpGameEnvironment(CPPEnvironment GameCPPEnvironment, LinkEnvironment FinalLinkEnvironment, List<UE3ProjectDesc> GameProjects)
		{
            GameCPPEnvironment.Definitions.Add("GAMENAME=MMOGAME");
            GameCPPEnvironment.Definitions.Add("IS_MMOGAME=1");
            
            GameCPPEnvironment.IncludePaths.Add("MMOGame/Inc");
            GameCPPEnvironment.IncludePaths.Add("MMOGame");

			GameProjects.Add( new UE3ProjectDesc( "MMOGame/MMOGame.vcxproj") );

            // 加入SD的包含路径

            //FinalLinkEnvironment.AdditionalLibraries.Add("sdnetwin.lib");
            //FinalLinkEnvironment.AdditionalLibraries.Add("sdclientmd.lib");

            GameCPPEnvironment.IncludePaths.Add("../../../../Common/define");
            GameCPPEnvironment.IncludePaths.Add("../../../../Common/fusion/inc");
            GameCPPEnvironment.IncludePaths.Add("../../../../Common/message");
//             GameCPPEnvironment.IncludePaths.Add("../../../../NewServer");
//            GameCPPEnvironment.IncludePaths.Add("../../../../Common/protocol/inc_client");

            GameCPPEnvironment.IncludePaths.Add("../../../../NewServer/3rd/sdu/include");
            GameCPPEnvironment.IncludePaths.Add("../../../../NewServer/3rd/sdu/include/sdu");
//             GameCPPEnvironment.IncludePaths.Add("../../../../NewServer/3rd/lua/include");
//             GameCPPEnvironment.IncludePaths.Add("../../../../NewServer/inc/baselib/");

            if (GameCPPEnvironment.TargetPlatform == CPPTargetPlatform.Win32)  
            {
                FinalLinkEnvironment.LibraryPaths.Add("../../../../NewServer/3rd/sdu/lib/win32");
//                 FinalLinkEnvironment.LibraryPaths.Add("../../../../Common/fusion/lib/win32");
//                 FinalLinkEnvironment.LibraryPaths.Add("../../../../NewServer/lib/win32");
//                 FinalLinkEnvironment.LibraryPaths.Add("../../../../NewServer/3rd/toluapp/lib/win32");
//                 FinalLinkEnvironment.LibraryPaths.Add("../../../../NewServer/3rd/lua/lib/win32");
            }
            else if (GameCPPEnvironment.TargetPlatform == CPPTargetPlatform.Win64)
            {
                FinalLinkEnvironment.LibraryPaths.Add("../../../../NewServer/3rd/sdu/lib/win64");
//                 FinalLinkEnvironment.LibraryPaths.Add("../../../../Common/fusion/lib/win64");
//                 FinalLinkEnvironment.LibraryPaths.Add("../../../../NewServer/lib/win64");
//                 FinalLinkEnvironment.LibraryPaths.Add("../../../../NewServer/3rd/toluapp/lib/win64");
//                 FinalLinkEnvironment.LibraryPaths.Add("../../../../NewServer/3rd/lua/lib/win64");
            }

            FinalLinkEnvironment.LibraryPaths.Add("../../../../Common/protocol/lib");
            FinalLinkEnvironment.LibraryPaths.Add("../../../../NewServer/3rd/libiconv/lib/win32");

            if (GameCPPEnvironment.TargetConfiguration == CPPTargetConfiguration.Debug)
            {
                if (GameCPPEnvironment.TargetPlatform == CPPTargetPlatform.Win32)
                {
//                     FinalLinkEnvironment.AdditionalLibraries.Add("fusion_32_Debug_v100.lib");
//                     FinalLinkEnvironment.AdditionalLibraries.Add("baselib_32_Debug_v100.lib");
//                     FinalLinkEnvironment.AdditionalLibraries.Add("toluapp_32_Debug_v100.lib");
//                     FinalLinkEnvironment.AdditionalLibraries.Add("lua32_Debug_v100.lib");
                }
                else if (GameCPPEnvironment.TargetPlatform == CPPTargetPlatform.Win64)
                {
//                     FinalLinkEnvironment.AdditionalLibraries.Add("fusion_64_Debug_v100.lib");
//                     FinalLinkEnvironment.AdditionalLibraries.Add("baselib_64_Debug_v100.lib");
//                     FinalLinkEnvironment.AdditionalLibraries.Add("toluapp_64_Debug_v100.lib");
//                     FinalLinkEnvironment.AdditionalLibraries.Add("lua64_Debug_v100.lib");
                }
            }
            else
            {
                if (GameCPPEnvironment.TargetPlatform == CPPTargetPlatform.Win32)
                {
//                     FinalLinkEnvironment.AdditionalLibraries.Add("fusion_32_Release_v100.lib");
//                     FinalLinkEnvironment.AdditionalLibraries.Add("baselib_32_Release_v100.lib");
//                     FinalLinkEnvironment.AdditionalLibraries.Add("toluapp_32_Release_v100.lib");
//                     FinalLinkEnvironment.AdditionalLibraries.Add("lua32_Release_v100.lib");
                }
                else if (GameCPPEnvironment.TargetPlatform == CPPTargetPlatform.Win64)
                {
//                     FinalLinkEnvironment.AdditionalLibraries.Add("fusion_64_Release_v100.lib");
//                     FinalLinkEnvironment.AdditionalLibraries.Add("baselib_64_Release_v100.lib");
//                     FinalLinkEnvironment.AdditionalLibraries.Add("toluapp_64_Release_v100.lib");
//                     FinalLinkEnvironment.AdditionalLibraries.Add("lua64_Release_v100.lib");
                }
            }

           if (UE3BuildConfiguration.bBuildEditor &&
               (GameCPPEnvironment.TargetPlatform == CPPTargetPlatform.Win32 || GameCPPEnvironment.TargetPlatform == CPPTargetPlatform.Win64))
           {
               GameProjects.Add(new UE3ProjectDesc("MMOEditor/MMOEditor.vcxproj"));
               GameCPPEnvironment.IncludePaths.Add("MMOEditor/Inc");
               GameCPPEnvironment.Definitions.Add("WITH_ACTORX=1");

               if ((GameCPPEnvironment.TargetPlatform == CPPTargetPlatform.Win32 || GameCPPEnvironment.TargetPlatform == CPPTargetPlatform.Win64))
               {
                   GameCPPEnvironment.Definitions.Add("WITH_RECAST=1");
                   GameCPPEnvironment.SystemIncludePaths.Add("../External/Recast7.1/Recast/include");
                   GameCPPEnvironment.SystemIncludePaths.Add("../External/Recast7.1/Detour/include");
                   GameCPPEnvironment.SystemIncludePaths.Add("../External/Recast7.1/UE3/include");

                   FinalLinkEnvironment.LibraryPaths.Add("../External/Recast7.1/UE3/lib");

                   string RecastLibName = "recast";
                   if (GameCPPEnvironment.TargetPlatform == CPPTargetPlatform.Win64)
                   {
                       RecastLibName += "_x64";
                   }

                   if (GameCPPEnvironment.TargetConfiguration == CPPTargetConfiguration.Debug)
                   {
                       RecastLibName += "d";
                   }

                   FinalLinkEnvironment.AdditionalLibraries.Add(RecastLibName + ".lib");
               }
           }
        }

        public bool ShouldCompilePhysXMobile()
        {
            return false;
        }

        public void GetGameSpecificGlobalEnvironment(CPPEnvironment GlobalEnvironment, UnrealTargetPlatform Platform)
        {
            //MessageBox.Show("Debug Break @ GetGameSpecificGlobalEnvironment");
            if (GlobalEnvironment.TargetConfiguration == CPPTargetConfiguration.Shipping)
            {
                UE3BuildConfiguration.bBuildEditor = false;
                GlobalEnvironment.Definitions.Add("WITH_EDITORONLY_DATA=0");
            }
        }

        public void GetGameSpecificPlatformConfigurationEnvironment(CPPEnvironment GlobalEnvironment, LinkEnvironment FinalLinkEnvironment)
        {
            //throw new NotImplementedException();
        }
    }
}
