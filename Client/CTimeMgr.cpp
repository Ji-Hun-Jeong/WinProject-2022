#include "pch.h"
#include "CTimeMgr.h"
#include "CCore.h"
CTimeMgr CTimeMgr::m_mgr;
CTimeMgr::CTimeMgr()
	: m_llCurTime{}
	, m_llPrevTime{}
	, m_llFrequency{}
	, m_dDT(0.f)
	, m_iFps(0)
	, m_iCount(0)
{}
CTimeMgr::~CTimeMgr()
{}

void CTimeMgr::Init()
{
	QueryPerformanceCounter(&m_llPrevTime);
	QueryPerformanceFrequency(&m_llFrequency);
}

void CTimeMgr::Update()
{
	++m_iCount;
	QueryPerformanceCounter(&m_llCurTime);
	m_dDT = (double)(m_llCurTime.QuadPart - m_llPrevTime.QuadPart) / (double)m_llFrequency.QuadPart;
	m_dAcc += m_dDT;
#ifdef _DEBUG
	if (m_dDT >= 1.f / 60.f)
		m_dDT = 1.f / 60.f;
#endif
	if (m_dAcc >= 1.f)
	{
		m_iFps = m_iCount;
		m_iCount = 0;
		m_dAcc = 0;
		swprintf_s(m_szBuffer, 256, L"FPS : %d, DT : %lf", m_iFps, m_dDT);
		SetWindowText(CCore::GetInst().GetHwnd(), m_szBuffer);
	}
	m_llPrevTime = m_llCurTime;
}
