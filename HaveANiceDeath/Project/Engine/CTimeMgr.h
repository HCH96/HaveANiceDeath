#pragma once
#include "singleton.h"

class CTimeMgr
	: public CSingleton<CTimeMgr>
{
	SINGLE(CTimeMgr);
private:
	LARGE_INTEGER	m_Frequency;
	LARGE_INTEGER	m_PrevCount;
	LARGE_INTEGER	m_CurCount;

	double			m_DeltaTime;
	double			m_EngineDeltaTime;

	UINT			m_CallCount;
	double			m_Time;
	bool			m_Lock;

	wchar_t			m_szText[256];

public:
	float GetDeltaTime() { return (float)m_DeltaTime; }
	double GetDeltaTime_d() { return m_DeltaTime; }

	float GetEngineDeltaTime() { return (float)m_EngineDeltaTime; }
	double GetEngineDeltaTime_d() { return m_EngineDeltaTime; }

	void LockDeltaTime(bool _Lock) { m_Lock = _Lock; }

public:
	void init();
	void tick();
	void render();
};


