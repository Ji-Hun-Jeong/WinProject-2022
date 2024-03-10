#include "pch.h"
#include "CCore.h"
#include "Scene_01.h"
#include "CScene.h"

#include "CRes.h"
#include "CResMgr.h"
#include "Texture.h"

#include "Player.h"
#include "Monster.h"

#include "CCollisionMgr.h"
#include "PixelCollider.h"

#include "CCamera.h"

Scene_01::Scene_01()
	: m_pPlayer(nullptr)
{
}

Scene_01::~Scene_01()
{
}

void Scene_01::Enter()
{
	CCamera::GetInst().SetCamState(GROUP_CAMERA_STATE::PLAYER);
	LoadFileData();

	CObject* pPlayer = new Player;
	pPlayer->SetPos(Vec2(640.f, 200.f));
	pPlayer->SetScale(Vec2(60.f, 80.f));
	pPlayer->Init();
	m_vecObj[(UINT)GROUP_OBJECT::PLAYER].push_back(pPlayer);
	m_pPlayer = pPlayer;

	CCollisionMgr::GetInst().RequestCheck(GROUP_OBJECT::MONSTER, GROUP_OBJECT::PLAYER);

}

void Scene_01::Render(const HDC& _dc)
{
	Vec2 resolution = CCore::GetInst().GetResolution();
	Vec2 Pos = { 0,0 };
	Pos= CCamera::GetInst().GetRenderPos(Pos);
	resolution = CCamera::GetInst().GetRenderPos(resolution);
	BitBlt(_dc
		, int(Pos.x)
		, int(Pos.y)
		, ((Texture*)m_pTex)->GetWidth()
		, ((Texture*)m_pTex)->GetHeight()
		, ((Texture*)m_pTex)->GetHdc()
		, 0, 0, SRCCOPY);
	CScene::Render(_dc);
}
