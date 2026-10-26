/**
 * Copyright 1998-2011 Epic Games, Inc. All Rights Reserved.
 */

using System;
using System.IO;
using System.Collections.Generic;
using System.Windows.Forms;
using StandaloneSymbolParser;
using System.Diagnostics;
using System.ComponentModel;
using System.Threading;

namespace MemoryProfiler2
{
	/// <summary> Improved symbol parser for PS3. </summary>
	public class FPS3FastSymbolParser : SymbolParser
	{
		/**
		 * Loads symbols for an executable.
		 *
		 * @param	ExePath		The path to the executable whose symbols are going to be loaded.
		 * @param	Modules		The list of modules loaded by the process.
		 */
		public override bool LoadSymbols( string ExePath, ModuleInfo[] Modules )
		{
			return false;
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
			return false;
		}
	}
}