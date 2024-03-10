#include "pch.h"
#include "TileUI.h"
#include "CKeyMgr.h"
#include "TileBtn.h"
#include "CSceneMgr.h"
#include "CScene.h"
#include "Tile.h"
#include "CTileMgr.h"
#include "CCamera.h"

TileUI::TileUI(const UINT& _x, const UINT& _y)
	: widthCount(_x)
	, heightCount(_y)
	, m_bIsFinish(false)
{}

TileUI::TileUI(const TileUI& _other)
	: PanelUI(_other)
	, widthCount(_other.widthCount)
	, heightCount(_other.heightCount)
	, m_bIsFinish(_other.m_bIsFinish)
{}

TileUI::~TileUI()
{
}

void TileUI::Update()
{
	UI::Update();
}

void TileUI::NextIdx()
{
	if (!m_bIsFinish)
	{
		size_t iCount = m_vecUI.size() - 1;
		for (size_t i = 0; i < iCount; ++i)
		{
			((TileBtn*)m_vecUI[i])->NextIndex(widthCount * heightCount);
		}
	}
}

void TileUI::Init()
{
	m_strName = "TileUI";
}

bool TileUI::IsMouseOn()
{
	Vec2 mouse = MOUSE_POS;
	if (m_vFinalPos.x <= mouse.x && mouse.x <= m_vFinalPos.x + m_vScale.x && m_vFinalPos.y <= mouse.y && mouse.y <= m_vFinalPos.y + m_vScale.y)
	{
		m_bMouseOn = true;
		return true;
	}
	return false;
}
