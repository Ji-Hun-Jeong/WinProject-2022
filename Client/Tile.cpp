#include "pch.h"
#include "CCamera.h"
#include "Tile.h"
#include "CResMgr.h"
#include "Texture.h"
#include "SelectGDI.h"
#include "CKeyMgr.h"
#include "CCore.h"

Tile::Tile()
	: m_iIdx(-1)
{
	m_vScale = { TILE_SIZE,TILE_SIZE };
}

Tile::~Tile()
{
}

void Tile::Init()
{
	CObject::Init();
	m_strName = "Tile";
	m_pTex = CResMgr::GetInst().GetTexture("tile", "tile\\TileUI\\RectCollider.bmp");
}

void Tile::Update()
{
	if (-1 != m_iIdx)
		CreateCollider();
	const Vec2& CamPos = CCamera::GetInst().GetDestPos();
	static Vec2 resolution = CCore::GetInst().GetResolution();
	if ((m_vPos.x < CamPos.x - resolution.x / 2 - m_vScale.x) || (CamPos.x + resolution.x / 2 < m_vPos.x)
		|| (m_vPos.y < CamPos.y - resolution.y / 2 - m_vScale.y) || (CamPos.y + resolution.y / 2 < m_vPos.y))
	{
		m_bInCam = false;
	}
	else
	{
		m_bInCam = true;
	}
}

void Tile::Render(const HDC& _dc)
{
	SelectGDI brush(_dc, GROUP_BRUSH::HOLLOW);
	if (m_bInCam)
	{
		Vec2 renderPos = CCamera::GetInst().GetRenderPos(m_vPos);
		if (-1 != m_iIdx)
		{
			UINT col = m_iIdx % 8;	// ї­
			UINT row = m_iIdx / 8;	// За
			assert(row < 6);
			BitBlt(_dc
				, int(renderPos.x)
				, int(renderPos.y)
				, int(m_vScale.x)
				, int(m_vScale.y)
				, ((Texture*)m_pTex)->GetHdc()
				, col * TILE_SIZE
				, row * TILE_SIZE
				, SRCCOPY);
		}
		else
		{
			Rectangle(_dc
				, int(renderPos.x)
				, int(renderPos.y)
				, int(renderPos.x + m_vScale.x)
				, int(renderPos.y + m_vScale.y));
		}
	}
}

bool Tile::IsMouseOn()
{
	Vec2 mouse = MOUSE_POS;
	mouse = CCamera::GetInst().GetRealPos(mouse);
	if (m_vPos.x <= mouse.x && mouse.x <= m_vPos.x + m_vScale.x && m_vPos.y <= mouse.y && mouse.y <= m_vPos.y + m_vScale.y)
	{
		return true;
	}
	return false;
}

void Tile::Save(FILE* _p)
{
	fwrite(&m_vPos, sizeof(Vec2), 1, _p);
	fwrite(&m_vScale, sizeof(Vec2), 1, _p);
	fwrite(&m_iIdx, sizeof(int), 1, _p);
}

void Tile::Load(FILE* _p)
{
	fread(&m_vPos, sizeof(Vec2), 1, _p);
	fread(&m_vScale, sizeof(Vec2), 1, _p);
	fread(&m_iIdx, sizeof(int), 1, _p);
}
