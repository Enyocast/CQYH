/*====================================================================
	Created Date  :		2005-8-24
	
	Specification :  
====================================================================*/
#pragma once

#include <afxinet.h>
#include "BmpRgnButton.h"
#include "DhtmlEdit.h"

#include "../ViGenerator/PatchHelper.h"
#include "afxcmn.h"
#include "afxwin.h"
#include "TransparentCaption.h"

class CFilePatchDlg : public CDialog
{
public:
	CFilePatchDlg(CWnd* pParent = NULL);	// 标准构造函数

	enum { IDD = IDD_FILEPATCH_DIALOG };

	BOOL					_bPatchSuccess;
	CString					_strServer;
	INTERNET_PORT _serverPort;
	CString					_strInitRoot;
	BOOL					_bShouldPatchSelf;
	CString					_strAdURL;
	CString					_strAdImg;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

protected:
	CString					_strLog;
	CString					_strTmpDir;
	CString					_strInstallDir;
	std::vector<SFilePatch>	_vectorFilePatches;

	std::vector<CString>	_vectorPatchInstalls;

	void					CheckLocalInfo();
	void					LoadLocalViInfo(SFilePatch& filePatch);

	bool _LoadLocalViInfo( const CString& viFile, SFilePatch &filePatch, bool newInstall = false );

	BOOL					DownLoadServerViFile(SFilePatch& filePatch, const CString& targetFileName = _T(""));
	BOOL					LoadServerViInfo(SFilePatch& filePatch);

	void					Compare(SFilePatch& filePatch);
	void					DoPatch(SFilePatch& filePatch);
	void					DoPatchVi();

	BOOL					DownLoadFile(SLocalVersionInfo* pInfo, SFilePatch& filePatch);
	int						StartProcess(const CString& strExeFilePatchName);

	static UINT __stdcall	VerCheckThread(LPVOID lpThreadParameter);
	BOOL					DownFileToString(const CString& section_name, CString& out_string);
	BOOL					VerCheckNeedExit(){ return _checkThreadExit; }

	HANDLE					_verCheckThread;
	CRITICAL_SECTION		_csCheckThread;
	BOOL					_checkThreadExit;
	DWORD					_nextVerCheckTime;
	CString					_patchVersion;

	CInternetSession*		_InternetSession;
	CHttpConnection			*_pHttpConnection;

protected:
	HICON m_hIcon;
	CBitmap			_BmpBk;

	int						_iTotalUpdate;
	int						_iCurUpdate;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();

	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT OnBeginPatch(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnBeginPatchGame(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnBeginPatchEditor(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnBeginPatchQAGame(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnBeginPatchQAEditor(WPARAM wParam, LPARAM lParam);

	afx_msg void OnCancel();
	afx_msg void OnBnClickedMin();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);	
	afx_msg void OnBnClickedStartgame();
	afx_msg void OnBnClickedStartEditor();
	afx_msg void OnBnClickedCancel();

	afx_msg void OnBnClickedUpdateGame();
	afx_msg void OnBnClickedUpdateEditor();
	afx_msg void OnBnClickedUpdateQAGame();
	afx_msg void OnBnClickedUpdateQAEditor();

	afx_msg void OnTimer(UINT_PTR nIDEvent);

	afx_msg void OnBnClickedUpdateReleaseGame();
	afx_msg void OnBnClickedStartReleaseGame();
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedRefVersion();
	afx_msg void OnBnClickedUpdateShaderCache();

	DECLARE_MESSAGE_MAP()
public:

	CString				m_strStatusDetail;
	CString				m_strTotal;
	CString				m_strCurrent;
	CProgressCtrl		m_ProgressAll;
	CProgressCtrl		m_ProgressCurrent;
	BmpRgnButton		_btnMin;
	BmpRgnButton		_btnClose;

	TransparentCaption _infoCurrent;
	TransparentCaption _infoTotal;
	TransparentCaption _infoDetail;
	TransparentCaption _infoAutoStart;
	CString _strInfoAutoStart;
	int _useEngLang;

	int _autoStartTime;

	//AdDhtmlEdit			_htmlADBar;

	CButton _btStart;
	CButton _btCancel;
	CButton _btStartEditor;

	CButton _btUpdateGame;
	CButton _btUpdateEditor;

	CButton _btUpdateQAGame;
	CButton _btUpdateQAEditor;

	CButton _btnUpdateReleaseGame;
	CButton _btnStartReleaseGame;


	//BmpRgnButton _btStart;
	//BmpRgnButton _btCancel;

	int _countDownTime;

	CString _serverSection;
	CString _strPatchConfigFile;
	CString _strVersionLocalConfigFile;

	CTime _startGenMD5Time;
	CTime _endGenMD5Time;

	CTime _startCompareMD5Time;
	CTime _endCompareMD5Time;


	CTime _startDownloadTime;
	CTime _endDownloadTime;

	BOOL _forceFix;
	BOOL _use64Bit;


	void StartPatch();
	void _UpdateADImage( const CString& strPatchConfigFile );
	void PatchOK();
	void WaitForAllWorks(class CThreadPool* thrdPool, const CString& msg = _T("工作线程数量:%d"));

};
