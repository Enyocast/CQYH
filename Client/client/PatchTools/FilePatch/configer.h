// *************************************************************************************
// 
// 
// 	All Rights Reserved 
// 
// 	Create Date		:		2006-7-11
// *************************************************************************************

#pragma once


namespace ShowGame_Core
{
	class Configer
	{
	public:

		Configer(void);
		virtual ~Configer(void);

		virtual void	LoadFile(const CString& fileName);
		virtual void	Reload();
		virtual void	SaveFile(const CString& fileName = _T(""));
		
		virtual int		GetIntValue(const CString& section, const CString& key, int defaultVal = 0);
		virtual void	SetIntValue(const CString& section, const CString& key, int val);
		
		virtual bool	GetBoolValue(const CString& section, const CString& key, bool defaultVal = false);
		virtual void	SetBoolValue(const CString& section, const CString& key, bool val);
		
		virtual float	GetFloatValue(const CString& section, const CString& key, float defaultVal = 0.0f);
		virtual void	SetFloatValue(const CString& section, const CString& key, float val);
		
		virtual CString	GetStringValue(const CString& section, const CString& key, const CString& defaultStr = _T(""));
		virtual void	GetStringValue(const CString& section, const CString& key, CString& val);
		virtual void	SetStringValue(const CString& section, const CString& key, const CString& val);

		CString			GetFileName() const { return _fileName; }

	protected:

		CString		_fileName;
	};

} // namespace