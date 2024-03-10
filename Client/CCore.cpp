#include "pch.h"
#include "CCore.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CCamera.h"
#include "CSceneMgr.h"
#include "CCollisionMgr.h"
#include "CUIMgr.h"
#include "CTileMgr.h"
CCore CCore::m_mgr;
CCore::CCore()
	: m_Resolution{}
	, m_hWnd(0)
	, m_hDC(0)
	, m_hBitmap(0)
	, m_hMemDC(0)
{
}

CCore::~CCore()
{
	ReleaseDC(m_hWnd, m_hDC);
	DeleteObject(m_hBitmap);
	DeleteDC(m_hMemDC);
}

void CCore::Init(const HWND& _hWnd, POINT& _Resolution)
{
	ShowCursor(false);
	m_hWnd = _hWnd;
	m_Resolution = _Resolution;
	RECT res = { 0,0,m_Resolution.x,m_Resolution.y };
	m_hDC = GetDC(m_hWnd);
	AdjustWindowRect(&res, WS_OVERLAPPEDWINDOW, true);
	SetWindowPos(m_hWnd, 0, 100, 100, res.right, res.bottom, 0);
	m_hBitmap = CreateCompatibleBitmap(m_hDC, res.right, res.bottom);
	m_hMemDC = CreateCompatibleDC(m_hDC);
	HBITMAP oldBitmap = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);
	DeleteObject(oldBitmap);
	CTimeMgr::GetInst().Init();
	CCamera::GetInst().Init();
	CSceneMgr::GetInst().Init();
	CUIMgr::GetInst().Init();
}

void CCore::Progress()
{
	CCamera::GetInst().Update();
	CTimeMgr::GetInst().Update();
	CKeyMgr::GetInst().Update();
	CSceneMgr::GetInst().Update();
	CCollisionMgr::GetInst().Update();
	CTileMgr::GetInst().Update();
	CUIMgr::GetInst().Update();
	// 버퍼쪽 화면 지우기
	Rectangle(m_hMemDC, 0, 0, m_Resolution.x, m_Resolution.y);

	// 렌더링	

	CSceneMgr::GetInst().Render(m_hMemDC);
	CCamera::GetInst().Render(m_hMemDC);
	CUIMgr::GetInst().Render(m_hMemDC);

	BitBlt(m_hDC, 0, 0, m_Resolution.x, m_Resolution.y, m_hMemDC, 0, 0, SRCCOPY);
}

void CCore::SetResolution(const Vec2& _Resolution)
{
	m_Resolution = { (long)_Resolution.x,(long)_Resolution.y };
	RECT res = { 0,0,m_Resolution.x,m_Resolution.y };
	AdjustWindowRect(&res, WS_OVERLAPPEDWINDOW, true);
	SetWindowPos(m_hWnd, 0, 100, 100, res.right, res.bottom, 0);
}
