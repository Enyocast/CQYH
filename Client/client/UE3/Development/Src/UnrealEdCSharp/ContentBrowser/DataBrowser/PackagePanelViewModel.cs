//=============================================================================
//	SourcesPanelViewModel.xaml.cs: Content browser sources panel view model
//	Copyright 1998-2013 Epic Games, Inc. All Rights Reserved.
//=============================================================================


using System;
using System.Collections.ObjectModel;
using System.Collections.Generic;
using System.Windows;
using System.ComponentModel;
using System.Text;
using System.Windows.Media;
using System.Windows.Controls;
using System.Windows.Threading;
using System.Diagnostics;
using CustomControls;


namespace ContentBrowser
{


	/// <summary>
    /// The model for the sources panel.
    /// The Sources Panel allows the user to select sources such as collections and packages.
    /// Items contained in collections and packages appeal in the AssetView.
    /// </summary>
    public class PackagePanelModel
    {
		/// Cached content browser reference
		private DataMainControl m_ContentBrowser;

		/// A reference to the TreeView that we are populating with folders, packages, etc.
		private CustomControls.TreeView mTreeView;


		/// <summary>
        /// Default Constructor.
        /// </summary>
		public PackagePanelModel()
        {
			StartupDirectory = "";
			RootDirectory = "";
        }


		/// Tell the tree view model which tree view to interact with
		public void SetNewPackageView(CustomControls.TreeView InTreeView)
		{
			mTreeView = InTreeView;
		}

		
		/// <summary>
		/// Initialize the asset view model
		/// </summary>
		/// <param name="InContentBrowser">Content browser that the asset view model is associated with</param>
		public void Init( DataMainControl InContentBrowser )
		{
			m_ContentBrowser = InContentBrowser;
		}


		#region Collections

		/// Shared collections
		protected ObservableCollection<Collection> mSharedCollections = new ObservableCollection<Collection>();
		public ObservableCollection<Collection> SharedCollections { get { return mSharedCollections; } }


		/// Private collections
		protected ObservableCollection<Collection> mPrivateCollections = new ObservableCollection<Collection>();
		public ObservableCollection<Collection> PrivateCollections { get { return mPrivateCollections; } }


		/// <summary>
		/// Synchronize the displayed collections with those passed in.
		/// </summary>
		/// <param name="InSharedCollectionNames">List of existing shared collection names</param>
		/// <param name="InPrivateCollectionNames">List of existing private collection names</param>
		/// <param name="InLocalCollectionNames">List of existing local collection names</param>
		public void SetCollectionNames( ICollection<String> InSharedCollectionNames, ICollection<String> InPrivateCollectionNames, ICollection<String> InLocalCollectionNames )
		{
			// @todo would be nice to use Sets and or FNames, but this list should be fairly short
			// so it should be a non-issue

			// Remove any collections that are no longer present
			{
				List<Collection> PendingDeletion = new List<Collection>();
				
				foreach ( Collection MyCollection in mSharedCollections )
				{
					if (!InSharedCollectionNames.Contains(MyCollection.Name))
					{
						PendingDeletion.Add( MyCollection );
					}
				}

				foreach ( Collection ToDelete in PendingDeletion )
				{
					mSharedCollections.Remove(ToDelete);
				}
			}
			{
				List<Collection> PendingDeletion = new List<Collection>();

				foreach( Collection MyCollection in mPrivateCollections )
				{
					if( !InPrivateCollectionNames.Contains( MyCollection.Name ) )
					{
						PendingDeletion.Add( MyCollection );
					}
				}

				foreach( Collection ToDelete in PendingDeletion )
				{
					mPrivateCollections.Remove( ToDelete );
				}
			}

			// Add any collections not currently displayed
			{
				// Build a list of current collection names
				List<String> CurrentCollectionNames = new List<String>( mSharedCollections.Count );
				foreach ( Collection MyCollection in mSharedCollections )
				{
					CurrentCollectionNames.Add( MyCollection.Name );
				}
				
				// Add collections new collections
				foreach ( String Candidate in InSharedCollectionNames )
				{
					if ( !CurrentCollectionNames.Contains( Candidate ) )
					{
						mSharedCollections.Add( new Collection( Candidate, false ) );
					}
					
				}
			}
			{
				// Build a list of current collection names
				List<String> CurrentCollectionNames = new List<String>( mPrivateCollections.Count );
				foreach( Collection MyCollection in mPrivateCollections )
				{
					CurrentCollectionNames.Add( MyCollection.Name );
				}

				// Add collections new collections
				foreach( String Candidate in InPrivateCollectionNames )
				{
					if( !CurrentCollectionNames.Contains( Candidate ) )
					{
                        bool bIsLocal = InLocalCollectionNames.Contains(Candidate);
                        mPrivateCollections.Add(new Collection(Candidate, bIsLocal));
					}

				}
			}

			
		}
		
		#endregion


		#region Packages Tree


		public String StartupDirectory
		{ get; set; }

		/// <summary>
		/// The directory path to the root directory (i.e. UnrealEngine3)
		/// </summary>
		public String RootDirectory
		{ get; set; }

		/// <summary>
		/// Sets the RootDirectory to path of the root game directory (i.e. D:\Code\UnrealEngine3\)
		/// </summary>
		/// <param name="BaseDirectoryPath">the directory containing the process image - should be retrieved by calling appBaseDir()</param>
		public void SetRootDirectoryPath( String BaseDirectoryPath )
		{
			StartupDirectory = BaseDirectoryPath;

			String tmpPath = BaseDirectoryPath + System.IO.Path.DirectorySeparatorChar + ".." + System.IO.Path.DirectorySeparatorChar + "..";
			RootDirectory = System.IO.Path.GetFullPath(tmpPath) + System.IO.Path.DirectorySeparatorChar;
		}

		/// <summary>
		/// The root folder contains all the packages in a tree.
		/// </summary>
		public Folder RootFolder { get { return (Folder)mTreeView.Root; } }

		/// <summary>
		/// Ensures that the specified packages are the only tree nodes selected in the package treeview.  Called
		/// when an asset is filtered via the "Sync to Browser" level viewport context menu command.
		/// </summary>
		/// <param name="NewSelectionSet">the list of packages which should be selected</param>
		/// <returns>True if the package selection was modified; false in the selection was not modified (usually because of the trivial case where the only package being selected is already the selection).</returns>
		public bool SynchronizeSelection( List<ObjectContainerNode> NewSelectionSet )
		{
			bool SyncIsNecessary = false;
			if ( mTreeView != null )
			{
				SyncIsNecessary = true;
				
				// Handle the trivial case where modifying the selection is not necessary
				// because the single package we want to select is already the only thing selected
				ReadOnlyCollection<AbstractTreeNode> CurrentSelection = mTreeView.GetSelection();
				if ( NewSelectionSet.Count == 1 &&
					 CurrentSelection.Count == 1 &&
					 NewSelectionSet[0] == CurrentSelection[0] )
				{
					SyncIsNecessary = false;
				}

				if ( SyncIsNecessary )
				{
					// Clear the package filter because it may be hiding a package that we need to select.
					m_ContentBrowser.MyPackagePanel.ClearPackageFilter();
					
					List<AbstractTreeNode> TreeNodeList = new List<AbstractTreeNode>();
					foreach ( ObjectContainerNode item in NewSelectionSet )
					{
						TreeNodeList.Add( item );
					}

					mTreeView.SetSelection( TreeNodeList );
					foreach ( ObjectContainerNode item in NewSelectionSet )
					{
						item.EnsureVisible();
					}
				}
			}

			return SyncIsNecessary;			
		}

		/// <summary>
		/// Used for saving the expanded state of the tree.
		/// </summary>
		/// <returns></returns>
		public String ExpandedNodesString
		{
			get
			{
				StringBuilder StringBuilder = new StringBuilder();
				BuildExpandedNodesString(this.RootFolder, StringBuilder);
				return StringBuilder.ToString();
			}
		}

		/// Separator between paths. Used for saving paths.
		public static char TreeViewPathSeparator = ';';
		/// <summary>
		/// Build a string representing the expanded nodes. Useful in saving expanded nodes to config.
		/// </summary>
		/// <param name="NodeIn">Root of the Subtree to process.</param>
		/// <param name="StringBuilder">The string builder to populate with the output</param>
		private void BuildExpandedNodesString( SourceTreeNode NodeIn, StringBuilder StringBuilder )
		{
			if ( NodeIn.IsExpanded )
			{
				StringBuilder.Append(NodeIn.FullTreeviewPath);
				StringBuilder.Append(TreeViewPathSeparator);
			}
			foreach ( SourceTreeNode CurNode in NodeIn.Children )
			{
				BuildExpandedNodesString(CurNode, StringBuilder);
			}
		}

		/// <summary>
		/// Converts a string representing the path to a package on disk into a standard format where the first part of the
		/// converted name is the name of the immediate subdirectory of the root UnrealEngine3 folder. i.e. 
		/// ..\..\Engine\Content\ BECOMES Engine\Content\
		/// 
		/// D:\UnrealEngine3\Engine\Content BECOMES Engine\Content
		/// </summary>
		/// <param name="PackagePathName"></param>
		/// <returns>see comments above</returns>
		public String NormalizePackageFilePathName( String PackagePathName )
		{
			return UnrealEd.Utils.NormalizePackageFilePathName(PackagePathName, RootDirectory, StartupDirectory);
		}

        /// <summary>
        /// Add a package to the tree of packages. The package will be added to according to the path.
        /// Any intermediate folders in the path will be created if they do not already exist.
        /// If the package does not exist, create
        /// </summary>
        /// <param name="PackagePath">The path to the package; includes package name.</param>
		public Package AddPackage( String PackagePathName, bool UsingFlatList )
		{
			PackagePathName = NormalizePackageFilePathName(PackagePathName);
			List<String> pathToPackage = new List<String>(System.IO.Path.GetDirectoryName(PackagePathName).Split(System.IO.Path.DirectorySeparatorChar));
			String packageName = System.IO.Path.GetFileNameWithoutExtension(PackagePathName);

			if (UsingFlatList)
			{
				Package NewPackage = new Package(this.RootFolder, packageName);
				return ((Folder)this.RootFolder).AddChildNode<Package>(NewPackage);
			}
			else
			{
				// Ensure that the path exists
				Folder curFolder = this.RootFolder;
				foreach (String folderName in pathToPackage)
				{
					curFolder = curFolder.GetSubFolder(folderName, true);
				}

				// Add package
				// The unreal object path here would always be its name because these are top-level packages.
				Package NewPackage = new Package(curFolder, packageName);
				return curFolder.AddChildNode<Package>(NewPackage);
			}		
			
        }
		public GroupPackage AddGroup( String OuterPathName, GroupPackage Group )
		{
			ObjectContainerNode ParentNode = FindDescendantNode(OuterPathName) as ObjectContainerNode;
			if ( ParentNode != null )
			{
				return ParentNode.AddChildNode<GroupPackage>(Group);
			}
			return null;
		}
		public GroupPackage AddGroup( String OuterPathName, String GroupName )
		{
			ObjectContainerNode ParentNode = FindDescendantNode(OuterPathName) as ObjectContainerNode;
			if ( ParentNode != null )
			{
				return ParentNode.AddChildNode<GroupPackage>(new GroupPackage(ParentNode, GroupName));
			}
			return null;
		}
		public GroupPackage AddGroup( ObjectContainerNode ParentNode, GroupPackage Group )
		{
			GroupPackage Result = null;
			if ( ParentNode != null )
			{
				Result = ParentNode.AddChildNode<GroupPackage>(Group);
			}
			return Result;
		}
		public GroupPackage AddGroup( ObjectContainerNode ParentNode, String GroupName )
		{
			GroupPackage Result = null;
			if ( ParentNode != null )
			{
				Result = ParentNode.AddChildNode<GroupPackage>(new GroupPackage(ParentNode, GroupName));
			}
			return Result;
		}

		/// <summary>
		/// Remove the specified object node from the tree view.  If the parent is a folder and the last node is removed,
		/// the folder will be removed as well.
		/// </summary>
		/// <param name="PackageToRemove">the item that should be removed</param>
		public void RemovePackage( ObjectContainerNode PackageToRemove )
		{
			if ( PackageToRemove != null && PackageToRemove.Parent != null )
			{
				SourceTreeNode TreeNode = PackageToRemove.Parent as SourceTreeNode;
				if ( TreeNode.RemoveChildNode(PackageToRemove) )
				{
					Folder ParentFolder = TreeNode as Folder;
					while ( ParentFolder != null && ParentFolder.Children.Count == 0 && ParentFolder.Parent != null )
					{
						SourceTreeNode GrandparentFolder = ParentFolder.Parent as SourceTreeNode;
						if ( GrandparentFolder != null )
						{
							// if the folder is now empty, remove it too!
							GrandparentFolder.RemoveChildNode(ParentFolder);
						}

						// it's possible that removing this folder removed the last child of the next folder up
						ParentFolder = GrandparentFolder as Folder;
					}
				}
			}
		}

		/// <summary>
		/// Finds a descendant node in the tree given a path. The path is separated by /. e.g. Engine/Content/Maps/MyMap
		/// </summary>
		/// <param name="SourceTreePath">Path with / separating nodes.</param>
		/// <returns>The found node; null if node was not found.</returns>
		public SourceTreeNode FindDescendantNode( String SourceTreePath )
		{
			char[] NodeSeparator = { SourceTreeNode.TreeViewNodeSeparator };

			// convert a file-system path name into a tree-pathname, if necessary
			SourceTreePath = SourceTreePath.Replace(System.IO.Path.DirectorySeparatorChar, SourceTreeNode.TreeViewNodeSeparator);
			List<String> PathSegments = new List<String>(SourceTreePath.Split(NodeSeparator, StringSplitOptions.RemoveEmptyEntries));

			SourceTreeNode CurNode = RootFolder;

			foreach ( String PathSegment in PathSegments )
			{
				SourceTreeNode NextNode = null;

				//Find next node in the path
				for ( int ChildIdx = 0; NextNode == null && ChildIdx < CurNode.Children.Count; ++ChildIdx )
				{
					SourceTreeNode CurChild = CurNode.Children[ChildIdx] as SourceTreeNode;
					if ( CurChild.Name == PathSegment )
					{
						NextNode = CurChild;
					}
				}

				if ( NextNode == null )
				{
					// We could not find this node in the path; returning null
					return null;
				}
				else
				{
					CurNode = NextNode;
				}
			}

			return CurNode;
		}

		/// <summary>
		/// Find the source tree node given a full path to it
		/// </summary>
		/// <param name="FullPath"></param>
		/// <returns></returns>
		public Folder FindFolder( String FullPath )
		{
			List<String> Path = new List<String>( FullPath.Split(System.IO.Path.DirectorySeparatorChar) );
			
			Folder CurNode = this.RootFolder;
			for (int PathIdx = 0; PathIdx < Path.Count && CurNode != null; ++PathIdx)
			{
				String Directory = Path[PathIdx];
				CurNode = CurNode.GetSubFolder(Directory, false);
			}
			return CurNode;
		}

		public enum EPackageSearchOptions
		{
			RequireFullMatch,
			AllowIncompleteMatch,
		}

		/// <summary>
		/// Searches the tree for the a package with the specified path-name.
		/// </summary>
		/// <param name="PackagePathName">The path-name (not including folder name) for the package to find</param>
		/// <returns></returns>
		public ObjectContainerNode FindPackage( String PackagePathName, EPackageSearchOptions SearchMode  )
		{
			ObjectContainerNode Result = null;

			if ( RootFolder != null )
			{
				char[] dot = {'.'};
				List<String> ObjectNames = new List<String>(PackagePathName.Split(dot, StringSplitOptions.None));

				SourceTreeNode CurrentNode = RootFolder;
				while ( CurrentNode != null && ObjectNames.Count > 0 )
				{
					SourceTreeNode NextNode = CurrentNode.FindPackage(ObjectNames[0]);
					ObjectNames.RemoveAt(0);

					if ( NextNode == null && SearchMode != EPackageSearchOptions.RequireFullMatch )
					{
						break;
					}

					CurrentNode = NextNode;
				}
				Result = CurrentNode as ObjectContainerNode;
			}

			return Result;
		}
		/// <summary>
		/// Searches the tree for the a package with the specified path-name.
		/// </summary>
		/// <param name="PackagePathName">The path-name (not including folder name) for the package to find</param>
		/// <returns></returns>
		public ObjectContainerNode FindPackage( String PackagePathName )
		{
			ObjectContainerNode Result = null;

			if ( RootFolder != null )
			{
				char[] dot = { '.' };
				List<String> ObjectNames = new List<String>(PackagePathName.Split(dot, StringSplitOptions.None));

				SourceTreeNode CurrentNode = RootFolder;
				while ( CurrentNode != null && ObjectNames.Count > 0 )
				{
					Result = CurrentNode.FindPackage(ObjectNames[0]);
					CurrentNode = Result;

					ObjectNames.RemoveAt(0);
				}
			}

			return Result;
		}

		/// <summary>
		/// Get the list of all nodes in the tree
		/// </summary>
		/// <typeparam name="TNodeType">the node type to filter by, or SourceTreeNode for no filtering</typeparam>
		/// <param name="out_Nodes">receives the list of child nodes</param>
		public void GetChildNodes<TNodeType>( List<TNodeType> out_Nodes ) where TNodeType : SourceTreeNode
		{
			GetChildNodes<TNodeType>(out_Nodes, true);
		}
		public void GetChildNodes<TNodeType>( List<TNodeType> out_Nodes, bool bRecurse ) where TNodeType : SourceTreeNode
		{
			GetChildNodes<TNodeType>(RootFolder, out_Nodes, bRecurse);
		}
		
		/// <summary>
		/// Get the list of child nodes for the specified parent node.
		/// </summary>
		/// <typeparam name="TNodeType">the node type to filter by, or SourceTreeNode for no filtering</typeparam>
		/// <param name="parentNode">the node containing the child nodes being searched for</param>
		/// <param name="out_Nodes">receives the list of child nodes</param>
		/// <param name="bRecurse">indicates whether the search include children et al, of child nodes</param>
		public void GetChildNodes<TNodeType>( SourceTreeNode parentNode, List<TNodeType> out_Nodes, bool bRecurse ) where TNodeType : SourceTreeNode
		{
			if ( parentNode != null && out_Nodes != null )
			{
				foreach ( SourceTreeNode node in parentNode.Children )
				{
					TNodeType TNode = node as TNodeType;
					if ( TNode != null )
					{
						// if( out_Nodes.Contains( TNode ) ) throw new Exception( "Error: Duplicate entry detected" );
						out_Nodes.Add(TNode);
					}
				}

				if ( bRecurse )
				{
					foreach ( SourceTreeNode node in parentNode.Children )
					{
						GetChildNodes<TNodeType>(node, out_Nodes, true);
					}
				}
			}
		}


		#endregion

		#region Package Status


		/// <summary>
		/// Updates the status for all packages in the view model
		/// </summary>
		public void UpdateStatusForAllPackages()
		{
			UpdateStatusForAllPackagesRecursively( RootFolder );
		}
	
		/// <summary>
		/// Updates the status for the specified package
		/// </summary>
		public void UpdateStatusForPackage( Package Pkg )
		{
			if( m_ContentBrowser != null )
			{
				// Update the status of this package!
				m_ContentBrowser.Backend.UpdatePackagesTreeUI( Pkg );
			}
		}


		
		/// <summary>
		/// Recursively updates status for all packages in the specified node's hierarchy
		/// </summary>
		private void UpdateStatusForAllPackagesRecursively( SourceTreeNode ParentNode )
		{
			// If this is a package then update it's status
            Package pkgNode = ParentNode as Package;
            if( pkgNode != null )
			{
				UpdateStatusForPackage( pkgNode );
            }

			// Recurse!
            foreach( SourceTreeNode CurChildNode in ParentNode.Children )
            {
				UpdateStatusForAllPackagesRecursively( CurChildNode );
            }
		}


		#endregion
	}



}
