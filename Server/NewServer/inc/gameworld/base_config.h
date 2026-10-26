#ifndef _BASE_CONFIG_H_
#define _BASE_CONFIG_H_

class CTabConfig;

class CBaseConfig
{
public:
	CBaseConfig(void);
	virtual ~CBaseConfig(void);

	BOOL Load(const TCHAR* config);

protected:
	virtual BOOL _ReadLine(CTabConfig* tab, INT32 nRow) = 0;
	virtual BOOL _OnLoadFinish(void);

};


#endif // _base_config_h__
