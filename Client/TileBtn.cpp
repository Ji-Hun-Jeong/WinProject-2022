#include "pch.h"
#include "TileBtn.h"
#include "TileUI.h"
#include "CResMgr.h"
#include "CRes.h"
#include "CKeyMgr.h"
#include "SelectGDI.h"
#include "Texture.h"
#include "CTileMgr.h"

TileBtn::TileBtn(const int& _idx)
	: m_iIdx(_idx)
	, m_bAgainClick(false)
{
}

TileBtn::TileBtn(const TileBtn& _other)
	: BtnUI(_other)
	, m_iIdx(_other.m_iIdx)
	, m_bAgainClick(_other.m_bAgainClick)
{
}

TileBtn::~TileBtn()
{
}

void TileBtn::Init()
{
	m_strName = "TileBtn";
	m_pTex = CResMgr::GetInst().GetTexture("Tile", "tile\\TileUI\\RectCollider.bmp");
}

void TileBtn::NextIndex(const UINT& _iNextCount)
{
	UINT xCount = CTileMgr::GetInst().GetTexTileXCount();
	UINT yCount = CTileMgr::GetInst().GetTexTileYCount();
	m_iIdx += _iNextCount;
	if (xCount* yCount <= (UINT)m_iIdx)
	{
		m_iIdx -= _iNextCount;
		((TileUI*)m_pOwner)->IsFinish(true);
	}
	else
	{
		((TileUI*)m_pOwner)->IsFinish(false);
	}
}

void TileBtn::Render(const HDC& _dc)
{
	if (-1 == m_iIdx)
		return;
	UINT col = m_iIdx % CTileMgr::GetInst().GetTexTileXCount();	// ї­
	UINT row = m_iIdx / CTileMgr::GetInst().GetTexTileXCount();	// За
	UINT i = CTileMgr::GetInst().GetTexTileYCount();
	assert(row < i);
	BitBlt(_dc
		, int(m_vFinalPos.x)
		, int(m_vFinalPos.y)
		, int(m_vScale.x)
		, int(m_vScale.y)
		, ((Texture*)m_pTex)->GetHdc()
		, col * TILE_SIZE
		, row * TILE_SIZE
		, SRCCOPY);
	ChildRender(_dc);
}

bool TileBtn::IsMouseOn()
{
	Vec2 mouse = MOUSE_POS;
	if (m_vFinalPos.x <= mouse.x && mouse.x <= m_vFinalPos.x + m_vScale.x && m_vFinalPos.y <= mouse.y && mouse.y <= m_vFinalPos.y + m_vScale.y)
	{
		m_bMouseOn = true;
		return true;
	}
	return false;
}

void TileBtn::MouseLbtnClick()
{
	if (m_bAgainClick)
	{
		CTileMgr::GetInst().SetCurIndex(-1);
		m_bAgainClick = false;
	}
	else
	{
		CTileMgr::GetInst().SetCurIndex(m_iIdx);
		m_bAgainClick = true;
	}

}
