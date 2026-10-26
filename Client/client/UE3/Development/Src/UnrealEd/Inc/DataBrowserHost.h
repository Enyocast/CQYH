#ifndef __DataBrowserHost_h__
#define __DataBrowserHost_h__

class FDataBrowser;
class WxDataBrowserHost;

class MySplitterWindow : public wxSplitterWindow
{
public:
	MySplitterWindow(WxBrowser* parent);
	virtual ~MySplitterWindow();
protected:
	void OnPostionChanged( wxSplitterEvent& In );
	void OnPostionChanging( wxSplitterEvent& In );

	WxBrowser* m_Parent;
private:
	DECLARE_EVENT_TABLE();
	//DECLARE_NO_COPY_CLASS(MySplitterWindow);

};

class WxDataBrowserSplitter
	: public WxBrowser
{
	DECLARE_DYNAMIC_CLASS( WxDataBrowserSplitter );

public:

	/** Constructor */
	WxDataBrowserSplitter();

	/** Destructor */
	virtual ~WxDataBrowserSplitter();


	/**
	* Forwards the call to our base class to create the window relationship.
	* Creates any internally used windows after that
	*
	* @param DockID the unique id to associate with this dockable window
	* @param FriendlyName the friendly name to assign to this window
	* @param Parent the parent of this window (should be a Notebook)
	*/
	virtual void Create( INT DockID, const TCHAR* FriendlyName, wxWindow* Parent );

	/** Tells the browser manager whether or not this browser can be cloned */
	virtual UBOOL IsClonable()
	{
		// We support multiple instances
		return TRUE;
	}

	/** Called when the browser window is activated */
	virtual void Activated();


	/** Returns the key to use when looking up values */
	virtual const TCHAR* GetLocalizationKey() const
	{
		return TEXT( "DataBrowserSplitter_Caption" );
	}

	/** Override accelerator table so that ContentBrowser can handle all the keys on its own. */
	virtual void AddAcceleratorTableEntries(TArray<wxAcceleratorEntry>& Entries);
	WxPropertyWindowHost* GetPropertyWindowHost()
	{
		return PropertyWindowHost;
	}
	void UpdateSplitter(int nPos);

	void SetDockStateToFloating();
	void SetDockStateToDocked();

protected:

	/** Called when the browser window is resized */
	void OnSize( wxSizeEvent& In );

	/** Called when the browser window receives focus */
	void OnReceiveFocus( wxFocusEvent& Event );

	UBOOL				bAreWindowsInitialized;
	wxSplitterWindow*	SplitterWindow;
	WxDataBrowserHost*	DataBrowser;
	WxPropertyWindowHost* PropertyWindowHost;
private:
	DECLARE_EVENT_TABLE();
};


/**
* Dockable host browser window for the Conten Browser
*/
class WxDataBrowserHost
	: public WxBrowser
{
	DECLARE_DYNAMIC_CLASS( WxDataBrowserHost );

public:

	/** Constructor */
	WxDataBrowserHost();

	/** Destructor */
	virtual ~WxDataBrowserHost();


	/**
	* Forwards the call to our base class to create the window relationship.
	* Creates any internally used windows after that
	*
	* @param DockID the unique id to associate with this dockable window
	* @param FriendlyName the friendly name to assign to this window
	* @param Parent the parent of this window (should be a Notebook)
	*/
	virtual void Create( INT DockID, const TCHAR* FriendlyName, wxWindow* Parent);

	/** Tells the browser manager whether or not this browser can be cloned */
	virtual UBOOL IsClonable()
	{
		// We support multiple instances
		return TRUE;
	}

	/** Called when the browser window is activated */
	virtual void Activated();


	/** Returns the key to use when looking up values */
	virtual const TCHAR* GetLocalizationKey() const
	{
		return TEXT( "DataBrowser_Caption" );
	}

	/** Override accelerator table so that ContentBrowser can handle all the keys on its own. */
	virtual void AddAcceleratorTableEntries(TArray<wxAcceleratorEntry>& Entries);

	void SetParentBrowserWindow(WxDataBrowserSplitter* Splitter)
	{
		ParentBrowserWindow = Splitter;
	}
	WxDataBrowserSplitter* GetParentBrowserWindow()
	{
		return ParentBrowserWindow;
	}

protected:

#if WITH_MANAGED_CODE
	/**
	* Accessor for retrieving a reference to this browser window's associated FContentBrowser object.
	* Useful in cases where you need to call methods in FContentBrowser and need to ensure that it is the one
	* associated with a specific WxBrowser window.
	*
	* NOTE: Using FContentBrowser::GetActiveInstance() is preferred to this method.
	*/
	FDataBrowser* GetDataBrowserInstance();
#endif

	/** Called when the browser window is resized */
	void OnSize( wxSizeEvent& In );

	/** Called when the browser window receives focus */
	void OnReceiveFocus( wxFocusEvent& Event );


private:
	WxDataBrowserSplitter*	ParentBrowserWindow;
#if WITH_MANAGED_CODE
	/** Content Browser */
	TScopedPointer< FDataBrowser > DataBrowser;
#endif

	DECLARE_EVENT_TABLE();
};


#endif // __DataBrowserHost_h__
