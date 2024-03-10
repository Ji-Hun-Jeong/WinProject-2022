#include "pch.h"
#include "NextBtn.h"
#include "TileUI.h"
#include "SelectGDI.h"

NextBtn::NextBtn()
{
}

NextBtn::NextBtn(const NextBtn& _other)
	: BtnUI(_other)
{
}

NextBtn::~NextBtn()
{
}

void NextBtn::Init()
{
	m_strName = "NextBtn";
}

void NextBtn::Render(const HDC& _dc)
{
	SelectGDI pen(_dc, GROUP_PEN::GREEN);
	Rectangle(_dc
		, int(m_vFinalPos.x)
		, int(m_vFinalPos.y)
		, int(m_vFinalPos.x + m_vScale.x)
		, int(m_vFinalPos.y + m_vScale.y));
}

void NextBtn::MouseLbtnClick()
{
	((TileUI*)m_pOwner)->NextIdx();
}
