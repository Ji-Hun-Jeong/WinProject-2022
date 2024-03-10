#include "pch.h"
#include "CKeyMgr.h"
#include "CCamera.h"
#include "CTileMgr.h"
#include "CScene.h"
#include "CSceneMgr.h"
#include "Scene_Tool.h"
#include "Tile.h"

CTileMgr CTileMgr::m_mgr;
// �ؽ��İ� ������ �� ũ�⸦ Ÿ�� ������� �������� �ؽ��� Ÿ�� ī��Ʈ�� �����ϴ� ������
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
	// ����ó��
	if (pTool)
	{
		if (KEYCHECK(LBTN, HOLD))
		{
			Vec2 mouse = MOUSE_POS;
			mouse = CCamera::GetInst().GetRealPos(mouse);
			UINT col = (UINT)mouse.x / TILE_SIZE;	// ��
			UINT row = (UINT)mouse.y / TILE_SIZE;	// ��
			if (m_iTileXCount<= col || m_iTileYCount <= row || mouse.x < 0 || mouse.y < 0)
				return;
			auto vec = pCurScene->GetVec(GROUP_OBJECT::TILE);
			((Tile*)vec[m_iTileXCount * row + col])->SetIndex(m_iCurIndex);
		}
	}		
}
