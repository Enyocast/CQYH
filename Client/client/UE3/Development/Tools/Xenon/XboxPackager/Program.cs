/**
 * Copyright 1998-2011 Epic Games, Inc. All Rights Reserved.
 */
using System;
using System.IO;
using System.Reflection;
using System.Text;

namespace XboxPackager
{
	public class Program
	{
		static private Assembly CurrentDomain_AssemblyResolve( Object sender, ResolveEventArgs args )
		{
			// Name is fully qualified assembly definition - e.g. "p4dn, Version=1.0.0.0, Culture=neutral, PublicKeyToken=ff968dc1933aba6f"
			string[] AssemblyInfo = args.Name.Split( ",".ToCharArray() );
			string AssemblyName = Path.GetFullPath( "Binaries\\" + AssemblyInfo[0] + ".dll" );

			if( File.Exists( AssemblyName ) )
			{
				Assembly AssemblyBinary = Assembly.LoadFile( AssemblyName );
				return ( AssemblyBinary );
			}

			return ( null );
		}

		static public void Main( string[] Args )
		{
			// Force the CWD to be the branch root
			Environment.CurrentDirectory = Path.Combine( AppDomain.CurrentDomain.BaseDirectory, "..\\.." );

			// Set up and assembly resolver to find common utility assemblies
			AppDomain.CurrentDomain.AssemblyResolve += new ResolveEventHandler( CurrentDomain_AssemblyResolve );

			XLastHandler Handler = new XLastHandler();

			Handler.ParseArguments( Args );
			switch( Handler.ProjectType )
			{
			case XLastHandler.XlastProjectType.None:
				break;

			case XLastHandler.XlastProjectType.TU:
				if( !Handler.PrepareBuild() )
				{
					return;
				}

				if( !Handler.ReadXLast() )
				{
					return;
				}

				if( !Handler.UpdateTUXLast() )
				{
					return;
				}

				if( !Handler.WriteXLast() )
				{
					return;
				}

				if( !Handler.CleanTUBuild() )
				{
					return;
				}

				if( !Handler.CreateTUPackage() )
				{
					return;
				}

				if( !Handler.RearrangeTUFiles() )
				{
					return;
				}

				Handler.Finalise();
			break;

			case XLastHandler.XlastProjectType.DLC:
				if( !Handler.ReadXLast() )
				{
					return;
				}

				if( !Handler.UpdateDLCXLast() )
				{
					return;
				}

				if( !Handler.WriteXLast() )
				{
					return;
				}

				if( !Handler.CleanDLCBuild() )
				{
					return;
				}

				if( !Handler.CreateDLCPackage() )
				{
					return;
				}

				if( !Handler.RearrangeDLCFiles() )
				{
					return;
				}

				Handler.Finalise();
			break;
			}
		}
	}
}
