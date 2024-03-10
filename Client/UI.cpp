#include "pch.h"
#include "UI.h"
#include "CObject.h"
#include "BtnUI.h"
#include "CKeyMgr.h"
#include "CCamera.h"
#include "SelectGDI.h"

UI::UI()
	: m_pOwner(nullptr)
	, m_bMouseOn(false)
	, m_bLbtnDown(false)
{
}

UI::UI(const UI& _other)
	: CObject(_other)
	, m_pOwner(nullptr)
	, m_bMouseOn(_other.m_bMouseOn)
	, m_bLbtnDown(_other.m_bLbtnDown)
{
}

UI::~UI()
{
	Safe_Delete_Vec(m_vecUI);
}

void UI::Update()
{
	// 마우스 포지션 체크
	m_vFinalPos = m_vPos;
	if (m_pOwner)
		m_vFinalPos += m_pOwner->GetPos();
	ChildUpdate();
}

void UI::Render(const HDC& _dc)
{
	if (m_bLbtnDown)
	{
		SelectGDI pen(_dc, GROUP_PEN::GREEN);
		Rectangle(_dc
			, int(m_vFinalPos.x)
			, int(m_vFinalPos.y)
			, int(m_vFinalPos.x + m_vScale.x)
			, int(m_vFinalPos.y + m_vScale.y));
	}
	else
	{
		Rectangle(_dc
			, int(m_vFinalPos.x)
			, int(m_vFinalPos.y)
			, int(m_vFinalPos.x + m_vScale.x)
			, int(m_vFinalPos.y + m_vScale.y));
	}
	ChildRender(_dc);
}

void UI::ChildUpdate()
{
	for (size_t i = 0; i < m_vecUI.size(); ++i)
	{
		m_vecUI[i]->Update();
	}
}

void UI::ChildRender(const HDC& _dc)
{
	for (size_t i = 0; i < m_vecUI.size(); ++i)
	{
		m_vecUI[i]->Render(_dc);
	}
}

bool UI::IsMouseOn()
{
	Vec2 mouse = MOUSE_POS;
	mouse = CCamera::GetInst().GetRealPos(mouse);
	if (m_vFinalPos.x <= mouse.x && mouse.x <= m_vFinalPos.x + m_vScale.x && m_vFinalPos.y <= mouse.y && mouse.y <= m_vFinalPos.y + m_vScale.y)
	{
		m_bMouseOn = true;
		return true;
	}
	return false;
}


