/**
 * Copyright 1998-2011 Epic Games, Inc. All Rights Reserved.
 */
using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Xml;
using System.Xml.Serialization;

namespace XboxPackager
{
	// TU related classes
	public class XlastTUFile
	{
		[XmlAttributeAttribute]
		public string clsid = "{EFE8CFD1-82D1-4C08-B633-4C01E701E68F}";

		[XmlAttributeAttribute]
		public string Name;

		[XmlAttributeAttribute]
		public string SourcePath;

		public void Init( FileInfo Info )
		{
			Name = Info.Name;
			SourcePath = ".\\" + Name;
		}
	}
	
	public class XlastTUFolder
	{
		[XmlAttributeAttribute]
		public string clsid = "{6712B0DF-B398-4783-8207-645BDB0EDE73}";

		[XmlElementAttribute( "File" )]
		public List<XlastTUFile> Files;

		[XmlElementAttribute( "Folder" )]
		public List<XlastTUFolder> Folders;

		[XmlAttributeAttribute]
		public string Name;

		public void Init( DirectoryInfo DirInfo )
		{
			Name = DirInfo.Name;
			Files = new List<XlastTUFile>();
			Folders = new List<XlastTUFolder>();
		}
	}

	public class XlastAutoUpdateProject
	{
		[XmlAttributeAttribute]
		public string clsid = "{2B29D4F2-D4BA-4E7F-9C44-A852105DB718}";

		public XlastTUContents Contents;

		[XmlAttributeAttribute]
		public string PackageName;

		[XmlAttributeAttribute]
		public string TitleId;

		[XmlAttributeAttribute]
		public string BaseVersion;

		[XmlAttributeAttribute]
		public string OriginalGameBuild;

		[XmlAttributeAttribute]
		public string UpdatedBinariesPath;

		[XmlAttributeAttribute]
		public string UpdateVersion;
	}

	public class XlastTUContents
	{
		[XmlAttributeAttribute]
		public string clsid = "{8F6862B0-3106-455C-9237-0561E9102657}";

		[XmlElementAttribute( "XexFile" )]
		public XlastTUContentsXexFile XexFile;

		[XmlElementAttribute( "File" )]
		public List<XlastTUFile> Files;

		[XmlElementAttribute( "Folder" )]
		public List<XlastTUFolder> Folders;
	}

	public class XlastTUContentsXexFile
	{
		[XmlAttributeAttribute]
		public string clsid = "{73C51760-35DD-4174-A8D9-0C419945F8D8}";

		[XmlAttributeAttribute]
		public string Name;

		[XmlAttributeAttribute]
		public string SourcePath;
	}

	// DLC related classes
	public class XlastDLCFile
	{
		[XmlAttributeAttribute]
		public string clsid = "{8A0BC3DD-B402-4080-8E34-C22144FC1ECE}";

		[XmlAttributeAttribute]
		public string SourceName;

		[XmlAttributeAttribute]
		public string TargetName;

		public void Init( FileInfo Info, string ContentRoot, int Depth )
		{
			TargetName = Info.Name;
			SourceName = Path.Combine( ContentRoot, TargetName );
			while( Depth-- > 0 )
			{
				SourceName = Path.Combine( "..", SourceName );
			}
		}
	}

	public class XlastDLCFolder
	{
		[XmlAttributeAttribute]
		public string clsid = "{0D8B38B9-F5A8-4050-8F8D-81F67E3B2456}";

		[XmlElementAttribute( "File" )]
		public List<XlastDLCFile> Files;

		[XmlElementAttribute( "Folder" )]
		public List<XlastDLCFolder> Folders;

		[XmlAttributeAttribute]
		public string TargetName;

		[XmlIgnore]
		public string RelativeName;

		public void Init( DirectoryInfo DirInfo, string ContentRoot )
		{
			TargetName = DirInfo.Name;
			RelativeName = Path.Combine( ContentRoot, TargetName );
			Files = new List<XlastDLCFile>();
			Folders = new List<XlastDLCFolder>();
		}
	}

	public class XlastDLCLanguage
	{
		[XmlAttributeAttribute]
		public string clsid = "{6424EAA3-FA00-4B6C-8CFB-BF063FC18845}";

		[XmlAttributeAttribute]
		public string DashDisplayName;

		[XmlAttributeAttribute]
		public string Description;
	}

	public class XlastDLCLanguageSettings
	{
		[XmlAttributeAttribute]
		public string clsid = "{F5BA1EE2-D217-447C-93C7-3C7AA6F25DD5}";

		[XmlElementAttribute]
		public List<XlastDLCLanguage> Language;
	}

	public class XlastDLCContents
	{
		[XmlAttributeAttribute]
		public string clsid = "{0D8B38B9-F5A8-4050-8F8D-81F67E3B2456}";

		[XmlElementAttribute( "File" )]
		public List<XlastDLCFile> Files;

		[XmlElementAttribute( "Folder" )]
		public List<XlastDLCFolder> Folders;
	}

	public class XlastDLCContentOffer
	{
		[XmlAttributeAttribute]
		public string clsid = "{4AF8FE5B-CCF2-4C23-852F-D91A94AE0E24}";

		[XmlAttributeAttribute]
		public string friendlyName;

		[XmlAttributeAttribute]
		public string title;

		[XmlAttributeAttribute]
		public string sellText;

		[XmlAttributeAttribute]
		public string licenseMask;

		[XmlAttributeAttribute]
		public string contentCategory;

		[XmlAttributeAttribute]
		public int visibility;

		[XmlAttributeAttribute]
		public string previewOfferId;

		[XmlAttributeAttribute]
		public string offerId;

		[XmlAttributeAttribute]
		public string banner;

		[XmlAttributeAttribute]
		public int licenseLevel;

		[XmlAttributeAttribute]
		public bool consumable;
	}
	
	public class XlastDLCContentOffers
	{
		[XmlAttributeAttribute]
		public string clsid = "{146485F0-DCD7-4AB1-97E1-9B0E64150499}";

		[XmlElementAttribute]
		public List<XlastDLCContentOffer> ContentOffer;
	}
	
	public class XlastContentProject
	{
		[XmlAttributeAttribute]
		public string clsid = "{AED6156D-A870-4FF7-924F-F375495A222A}";

		[XmlAttributeAttribute]
		public string Name;

		[XmlAttributeAttribute]
		public string TitleID;

		[XmlAttributeAttribute]
		public string TitleName;

		[XmlAttributeAttribute]
		public string ActivationDate;

		[XmlAttributeAttribute]
		public string PubOfferingID; 

		[XmlAttributeAttribute]
		public string PubBitFlags;

		[XmlAttributeAttribute]
		public bool HasCost; 

		[XmlAttributeAttribute]
		public bool IsMarketplace; 

		[XmlAttributeAttribute]
		public bool AllowProfileTransfer;

		[XmlAttributeAttribute]
		public bool AllowDeviceTransfer;

		[XmlAttributeAttribute]
		public string DashIconPath;

		[XmlAttributeAttribute]
		public string TitleIconPath;

		[XmlAttributeAttribute]
		public string ContentType;

		[XmlElementAttribute]
		public List<XlastDLCLanguageSettings> LanguageSettings;

		[XmlElementAttribute]
		public XlastDLCContents Contents;

		[XmlElementAttribute]
		public List<XlastDLCContentOffers> ContentOffers;
	}

	// XLAST container class
	public class XboxLiveSubmissionProject
	{
		[XmlElementAttribute]
		public XlastAutoUpdateProject AutoUpdateProject;

		[XmlElementAttribute]
		public XlastContentProject ContentProject;

		[XmlAttributeAttribute]
		public string Version;
	}
}