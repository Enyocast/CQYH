#ifndef _MMOWEATHERMANAGER_H_
#define _MMOWEATHERMANAGER_H_

#include "MMOSingleton.h"
#include "MMOFacade.h"

// 天气等级
enum WeatherLevel
{
	WL_Light = 0,										// 小雨，小雪，间歇性闪电，少量扬沙，小雾
	WL_Showers,											// 中雨+闪电，中雪，中型沙暴，中雾
	WL_Heavy,											// 雨+雪，大雪，持续闪电，扬沙+龙卷风，大雾
	WL_Total
};

#define DAY_TIME_MATINEE_DURATION	2.0

class MMOWeatherManager : public SingletonMeyers<MMOWeatherManager>, public INativeGameEventHandler
{
public:
	MMOWeatherManager();
	virtual ~MMOWeatherManager();

	void Init();
	void Shutdown();
	void Clear();
	void Update(FLOAT deltaTime);

	virtual void OnNativeGameEvent(struct MMOGameEvent* evt);

	void InitStartTime(UINT32 startTime);				// 初始化游戏开始时间
	void EnterScene(UINT8 weaterType);					// 进入地图
		
	void StartWeather(UINT8 weaterType);				// 开始天气
	void StopWeather(UINT8 weaterType);					// 结束天气
	void StopAllWeather();								// 结束所有天气

	FLOAT GetCurTime() const;							// 获得当前时间,24小时制,单位:小时
	void SetCurTime(FLOAT t) { _CurrentTime = t; }
	UINT8 GetCurWeatherType();							// 获取当前天气类型

	void Enable( UBOOL bEnable );						// 开启/关闭天气系统

	bool IsNight() const;
	void TestDay();
	void TestNight();

	void SetFire( const FVector& Center, FLOAT Radius )
	{
		if( _WeatherHelper )
			_WeatherHelper->SetFire( Center, Radius );
	}
		
protected:
	void _ActivateWeatherEvent();						// 触发Kismet天气事件
	void _ActivateDayTimePlanEvent();					// 触发Kismet时间表事件
	void _ActivateDayTimeSunlightEvent();				// 触发Kismet昼夜变化事件
	void _UpdateDayTimeSunlightEvent();					// 触发Kismet昼夜变化事件

	void _SetWeatherChangeHint(const FString& content);
	void _UpdateWeatherTips();

	AMMOWeatherHelper* _WeatherHelper;
	AMMODayTimeHelper* _DayTimeHelper;

	FLOAT _StartTime;									// 游戏开始时间,24小时制,单位:小时
	FLOAT _HourPerDay;
	FLOAT _StartTotalTime;
	FLOAT _CurrentTime;

	FLOAT _AnimTime;									// 动画更新时间
	FLOAT _OldEventTime;								// 事件触发时间

	UINT8 _CurWeatherType;								// 当前天气类型	
	UINT8 _CurWeatherLv;								// 当前天气级别	
};

#endif