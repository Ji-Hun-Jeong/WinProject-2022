#include "pch.h"
#include "CUIMgr.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "CScene.h"
#include "UI.h"
#include "CResMgr.h"
#include "Texture.h"
CUIMgr CUIMgr::m_mgr;
CUIMgr::CUIMgr()
	: m_arrTex(nullptr)
{}
CUIMgr::~CUIMgr()
{}

void CUIMgr::Init()
{
	m_arrTex = CResMgr::GetInst().GetTexture("Mouse", "texture\\Mouse\\Mouse.Normal.bmp");
}

void CUIMgr::Update()
{
	// 현재 마우스가 타겟하고 있는 UI가 어떤놈인지 알아내기
	m_vMousePos = MOUSE_POS;
	Sort();
	Progress();
}

void CUIMgr::Render(const HDC& _dc)
{
	Vec2 Scale = Vec2(((Texture*)m_arrTex)->GetWidth(), ((Texture*)m_arrTex)->GetHeight());
	TransparentBlt(_dc
		, int(m_vMousePos.x)
		, int(m_vMousePos.y)
		, int(Scale.x)
		, int(Scale.y)
		, ((Texture*)m_arrTex)->GetHdc()
		, 0, 0
		, int(Scale.x)
		, int(Scale.y)
		, RGB(1, 0, 0));
}

void CUIMgr::Progress()
{
	UI* pTarget = GetTargetUI();
	if (pTarget)
	{
		pTarget->MouseOn();
		if (KEYCHECK(LBTN, TAP))// 누른 상태
		{
			pTarget->MouseLbtnDown();
		}
		else if (KEYCHECK(LBTN, AWAY))
		{
			if (pTarget->m_bLbtnDown)
			{
				pTarget->MouseLbtnClick();
			}
			pTarget->MouseLbtnUP();
		}
	}
}

UI* CUIMgr::GetTargetUI()
{
	auto vec = CSceneMgr::GetInst().GetCurScene()->GetVec(GROUP_OBJECT::UI);
	UI* pCur = nullptr;
	UI* pTarget = nullptr;
	list<UI*> queue;
	vector<UI*> DeleteUI;
	for (size_t i = 0; i < vec.size(); ++i)
	{
		queue.push_back((UI*)vec[i]);
		while (!queue.empty())
		{
			pCur = queue.front();
			queue.pop_front();
			vector<UI*>& vec = pCur->m_vecUI;
			for (size_t i = 0; i < vec.size(); ++i)
			{
				queue.push_back(pCur->m_vecUI[i]);
			}
			if (pCur->IsMouseOn())	// 만약 마우스가 위에 있다면
			{
				pTarget = pCur;
			}
			else
			{
				pCur->m_bMouseOn = false;
			}
			DeleteUI.push_back(pCur);
		}
	}
	if (KEYCHECK(LBTN, AWAY))
	{
		for (size_t i = 0; i < DeleteUI.size(); ++i)
		{
			if (DeleteUI[i] != pTarget)
			{
				DeleteUI[i]->m_bLbtnDown = false;
			}
		}
	}
	return pTarget;
}

void CUIMgr::Sort()
{
	auto& vec = CSceneMgr::GetInst().GetCurScene()->GetVec(GROUP_OBJECT::UI);
	auto iter = vec.begin();
	auto other = vec.begin();
	UI* pTarget = nullptr;
	for (size_t i = 0; i < vec.size(); ++i, ++iter)
	{
		if (((UI*)vec[i])->IsMouseOn())
		{
			pTarget = (UI*)vec[i];
			other = iter;
		}
	}
	if (pTarget && KEYCHECK(LBTN, TAP))
	{
		vec.erase(other);
		vec.push_back(pTarget);
	}
}
