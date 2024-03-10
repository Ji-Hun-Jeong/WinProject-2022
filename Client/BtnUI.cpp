#include "pch.h"
#include "BtnUI.h"
#include "SelectGDI.h"
#include "Texture.h"
#include "CKeyMgr.h"
#include "CResMgr.h"

BtnUI::BtnUI()
	: m_arrTex{}
	, m_pCurTex(nullptr)
{
}

BtnUI::BtnUI(const BtnUI& _other)
	: UI(_other)
	, m_arrTex{}
	, m_pCurTex(nullptr)
{
	for (size_t i = 0; i < _other.m_vecUI.size(); ++i)
	{
		BtnUI* pClone = ((BtnUI*)_other.m_vecUI[i]->Clone());
		m_vecUI.push_back(pClone);
		pClone->m_pOwner = this;
	}
}

BtnUI::~BtnUI()
{
}

void BtnUI::Init()
{
	m_strName = "BtnUI";
	assert(m_arrTex[(UINT)GROUP_BTN_STATE::NORMAL]);
	m_pCurTex = m_arrTex[(UINT)GROUP_BTN_STATE::NORMAL];
}

void BtnUI::Update()
{
	StateUpdate();
	UI::Update();
}

void BtnUI::AddTex(const string& _strSamepath, const string& _strNormal, const string& _strMouseOn, const string& _strPress, const string& _strDisabled)
{
	string path = {};
	string key = {};
	path = _strSamepath + _strNormal + ".bmp";
	key = _strNormal;
	CRes* pTex = CResMgr::GetInst().GetTexture(key, path);
	m_arrTex[(UINT)GROUP_BTN_STATE::NORMAL] = pTex;

	path = _strSamepath + _strMouseOn + ".bmp";
	key = _strMouseOn;
	pTex = CResMgr::GetInst().GetTexture(key, path);
	m_arrTex[(UINT)GROUP_BTN_STATE::MOUSEON] = pTex;

	path = _strSamepath + _strPress + ".bmp";
	key = _strPress;
	pTex = CResMgr::GetInst().GetTexture(key, path);
	m_arrTex[(UINT)GROUP_BTN_STATE::PRESS] = pTex;

	path = _strSamepath + _strDisabled + ".bmp";
	key = _strDisabled;
	pTex = CResMgr::GetInst().GetTexture(key, path);
	m_arrTex[(UINT)GROUP_BTN_STATE::DISABLED] = pTex;
	
	m_pCurTex = m_arrTex[(UINT)GROUP_BTN_STATE::NORMAL];
}


void BtnUI::Render(const HDC& _dc)
{
	TransparentBlt(_dc
		, int(m_vFinalPos.x)
		, int(m_vFinalPos.y)
		, int(m_vScale.x)
		, int(m_vScale.y)
		, ((Texture*)m_pCurTex)->GetHdc()
		, 0, 0
		, ((Texture*)m_pCurTex)->GetWidth()
		, ((Texture*)m_pCurTex)->GetHeight()
		, RGB(0, 0, 0));
	ChildRender(_dc);
}

void BtnUI::StateUpdate()
{
	if (m_bLbtnDown)
	{
		m_pCurTex = m_arrTex[(UINT)GROUP_BTN_STATE::PRESS];
	}
	else if (m_bMouseOn)
	{
		m_pCurTex = m_arrTex[(UINT)GROUP_BTN_STATE::MOUSEON];
	}
	else 
	{
		m_pCurTex = m_arrTex[(UINT)GROUP_BTN_STATE::NORMAL];
	}
}

bool BtnUI::IsMouseOn()
{
	Vec2 mouse = MOUSE_POS;
	if (m_vFinalPos.x <= mouse.x && mouse.x <= m_vFinalPos.x + m_vScale.x && m_vFinalPos.y <= mouse.y && mouse.y <= m_vFinalPos.y + m_vScale.y)
	{
		m_bMouseOn = true;
		return true;
	}
	return false;
}

void BtnUI::MouseOn()
{
	m_bMouseOn = true;
}

void BtnUI::MouseLbtnDown()
{
	m_bLbtnDown = true;
}

void BtnUI::MouseLbtnUP()
{
	m_bLbtnDown = false;
}

void BtnUI::MouseLbtnClick()
{
	
}

