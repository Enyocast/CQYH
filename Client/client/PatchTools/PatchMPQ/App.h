// *************************************************************************************
// 
// 
// 	All Rights Reserved 
// 
// 	Create Date		:		2007-1-14
// *************************************************************************************

#pragma once

namespace ShowGame_Core
{
	class App
	{
	public:

		App(void);
		~App(void);

		static CString GetAppPath();

	protected:

		static CString _appPath;
	};
}