#pragma once
class CTimeMgr
{
	SINGLE(CTimeMgr)
private:
	LARGE_INTEGER	m_llCurTime; // 이전 프레임에서의 시간
	LARGE_INTEGER	m_llPrevTime; // 현재 프레임에서의 시간
	LARGE_INTEGER	m_llFrequency; // 1초당 진동수

	UINT	m_iFps;  // FPS
	UINT	m_iCount; // 1초동안 몇 프레임을 지났는지

	double	m_dDT;	// dt
	double	m_dAcc;  // 1초를 축적하는 시간

	wchar_t m_szBuffer[256];
public:
	void Init();
	void Update();
public:
	const double& GetDT() { return m_dDT; }
	const UINT& GetFPS() { return m_iFps; }
};

