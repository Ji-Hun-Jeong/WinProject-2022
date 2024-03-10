#include "pch.h"
#include "PanelUI.h"
#include "BtnUI.h"
#include "UI.h"
#include "CKeyMgr.h"

PanelUI::PanelUI()
{
}

PanelUI::PanelUI(const PanelUI& _other)
	: UI(_other)
{
	for (size_t i = 0; i < _other.m_vecUI.size(); ++i)
	{
		BtnUI* pClone = ((BtnUI*)_other.m_vecUI[i]->Clone());
		m_vecUI.push_back(pClone);
		pClone->m_pOwner = this;
	}
}

PanelUI::~PanelUI()
{
}

void PanelUI::CreateBtnUI(BtnUI* pBtn, const Vec2& _vPos, const Vec2& _vScale)
{
	pBtn->SetPos(_vPos);
	pBtn->SetScale(_vScale);
	((BtnUI*)pBtn)->m_pOwner = this;
	pBtn->Init();
	m_vecUI.push_back(pBtn);
}

void PanelUI::Init()
{
	m_strName = "PanelUI";
}

void PanelUI::StateUpdate()
{
}

void PanelUI::Update()
{
	/*m_vCurPos = MOUSE_POS;
	if (m_bLbtnDown)
	{
		m_vPos += m_vCurPos - m_vPrevPos;
	}
	m_vPrevPos = m_vCurPos;*/
	m_vFinalPos = m_vPos;
	if (m_pOwner)
		m_vFinalPos += m_pOwner->GetPos();
	ChildUpdate();
}

void PanelUI::MouseOn()
{
	m_bMouseOn = true;
}

void PanelUI::MouseLbtnDown()
{
	m_bLbtnDown = true;
}

void PanelUI::MouseLbtnUP()
{
	m_bLbtnDown = false;
}

void PanelUI::MouseLbtnClick()
{
}
