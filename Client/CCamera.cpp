#include "pch.h"
#include "CCamera.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CCore.h"
#include "CObject.h"
CCamera CCamera::m_mgr;
CCamera::CCamera()
	: m_fTime(1.f)
	, m_fSpeed(0.f)
	, m_State(GROUP_CAMERA_STATE::FIX)
	, m_fAccTime(0.f)
	, m_pPlayer(nullptr)
{}
CCamera::~CCamera()
{}

void CCamera::Init()
{
	m_vCorePos = Vec2(CCore::GetInst().GetResolution());
	m_vCorePos /= 2;
	m_vDestPos = m_vCorePos;
	m_vCurPos = m_vCorePos;
	m_vPrevPos = m_vCorePos;
}

void CCamera::Update()
{
	// 플레이어 쪽으로 화면을 고정시켜야 함
	
		/*if (KEYCHECK(LBTN, TAP))
		{
			Vec2 mouse = MOUSE_POS;
			m_vDestPos = GetRealPos(mouse);
			m_vPrevPos = m_vCurPos;
			m_fAccTime = 0.f;
		}*/
	if (GROUP_CAMERA_STATE::FIX == m_State)
	{
		m_vDestPos = CCore::GetInst().GetResolution();
		m_vDestPos /= 2;
	}
	else if (GROUP_CAMERA_STATE::PLAYER == m_State)
	{
		m_vDestPos = m_pPlayer->GetPos();
		m_vPrevPos = m_vDestPos;
	}
	else if (GROUP_CAMERA_STATE::FREE == m_State)
	{
		if (KEYCHECK(W, HOLD))
		{
			m_vDestPos.y -= 500.f * dt;
			m_vPrevPos = m_vDestPos;
		}
		if (KEYCHECK(S, HOLD))
		{
			m_vDestPos.y += 500.f * dt;
			m_vPrevPos = m_vDestPos;
		}
		if (KEYCHECK(A, HOLD))
		{
			m_vDestPos.x -= 500.f * dt;
			m_vPrevPos = m_vDestPos;
		}
		if (KEYCHECK(D, HOLD))
		{
			m_vDestPos.x += 500.f * dt;
			m_vPrevPos = m_vDestPos;
		}
	}
	CalDiff();
}
inline void CCamera::Calculate()
{
	m_fSpeed = (m_vDestPos - m_vPrevPos).GetLength() / m_fTime;	// 목적지부터 현재 위치까지의 거리를 시간으로 나눠 스피드를 구함
	m_vDir = (m_vDestPos - m_vPrevPos).Normallize();	// 현재위치부터 목적지까지의 방향을 구함
	m_fAccTime += dt;
}

void CCamera::CalDiff()
{
	Calculate();
	m_vCurPos = m_vPrevPos + m_vDir * (m_fAccTime * m_fSpeed);
	if (m_fAccTime >= m_fTime)
	{
		m_fAccTime = 0.f;
		m_vCurPos = m_vDestPos;
		m_vPrevPos = m_vCurPos;
	}
	m_vDiff = m_vCurPos - m_vCorePos;
}

void CCamera::Render(const HDC& _dc)
{

}

Vec2 CCamera::GetRealPos(Vec2& _Pos)
{
	return Vec2(_Pos + m_vDiff);
}

Vec2 CCamera::GetRenderPos(Vec2& _Pos)
{
	return Vec2(_Pos - m_vDiff);
}
