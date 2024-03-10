#include "pch.h"
#include "CKeyMgr.h"
#include "CCamera.h"
#include "CTileMgr.h"
#include "CScene.h"
#include "CSceneMgr.h"
#include "Scene_Tool.h"
#include "Tile.h"

CTileMgr CTileMgr::m_mgr;
// 텍스쳐가 있으면 그 크기를 타일 사이즈로 나눈것을 텍스쳐 타일 카운트로 설정하는 식으로
CTileMgr::CTileMgr()
	: m_iTileXCount(0)
	, m_iTileYCount(0)
	, m_iTexTileXCount(1)
	, m_iTexTileYCount(1)
	, m_iCurIndex(-1)
{}
CTileMgr::~CTileMgr()
{}

void CTileMgr::Update()
{
	CScene* pCurScene = CSceneMgr::GetInst().GetCurScene();
	Scene_Tool* pTool = dynamic_cast<Scene_Tool*>(pCurScene);
	// 예외처리
	if (pTool)
	{
		if (KEYCHECK(LBTN, HOLD))
		{
			Vec2 mouse = MOUSE_POS;
			mouse = CCamera::GetInst().GetRealPos(mouse);
			UINT col = (UINT)mouse.x / TILE_SIZE;	// 열
			UINT row = (UINT)mouse.y / TILE_SIZE;	// 행
			if (m_iTileXCount<= col || m_iTileYCount <= row || mouse.x < 0 || mouse.y < 0)
				return;
			auto vec = pCurScene->GetVec(GROUP_OBJECT::TILE);
			((Tile*)vec[m_iTileXCount * row + col])->SetIndex(m_iCurIndex);
		}
	}		
}
