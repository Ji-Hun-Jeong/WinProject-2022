#include "pch.h"
#include "Scene_Start.h"
#include "CCore.h"

#include "CObject.h"
#include "Player.h"

#include "CResMgr.h"
#include "CRes.h"
#include "Texture.h"

#include "CCamera.h"

#include "BtnUI.h"

Scene_Start::Scene_Start()
{
}

Scene_Start::~Scene_Start()
{
}

void Scene_Start::Enter()
{
	CCamera::GetInst().SetCamState(GROUP_CAMERA_STATE::FIX);
	m_pTex = CResMgr::GetInst().GetTexture("Start", "texture\\start\\loginTex\\start_01.bmp");
	CCore::GetInst().SetResolution(Vec2(((Texture*)m_pTex)->GetWidth(), ((Texture*)m_pTex)->GetHeight()));
	BtnUI* pBtnUI = new BtnUI;
	pBtnUI->AddTex("texture\\start\\BtnUI\\", "StartBtn.Normal", "StartBtn.MouseOn", "StartBtn.Press", "StartBtn.Disabled");

	Vec2 pos = CCore::GetInst().GetResolution();
	Texture* pCurTex = dynamic_cast<Texture*>(pBtnUI->GetCurTex());
	Vec2 scale = Vec2(pCurTex->GetWidth(), pCurTex->GetHeight());
	assert(pCurTex);
	pBtnUI->SetPos(Vec2(pos.x / 2 - scale.x / 2.f, pos.y / 2 - scale.y / 2.f - 100));
	pBtnUI->SetScale(Vec2(scale.x, scale.y));
	pBtnUI->Init();
	m_vecObj[(UINT)GROUP_OBJECT::UI].push_back(pBtnUI);

	pCurTex = dynamic_cast<Texture*>(CResMgr::GetInst().GetTexture("MapEditer", "texture\\start\\Map_Editer.bmp"));
	pBtnUI = new BtnUI;
	assert(pCurTex);
	pBtnUI->SetPos(Vec2(pos.x / 2 - scale.x / 2.f, pos.y / 2 - scale.y / 2.f));
	pBtnUI->SetScale(Vec2(scale.x, scale.y));
	pBtnUI->AddTex("texture\\start\\", "Map_Editer", "Map_Editer", "Map_Editer", "Map_Editer");
	pBtnUI->Init();
	m_vecObj[(UINT)GROUP_OBJECT::UI].push_back(pBtnUI);
}

void Scene_Start::Update()
{
	for (UINT Object = 0; Object < (UINT)GROUP_OBJECT::END; ++Object)
	{
		for (size_t Count = 0; Count < m_vecObj[Object].size(); ++Count)
		{
			if (!m_vecObj[Object][Count]->IsDead())
			{
				// 만약 데드 상태가 아니면 Update하자
				m_vecObj[Object][Count]->Update();
			}
		}
	}
}

void Scene_Start::Render(const HDC& _dc)
{
	Vec2 resolution = CCore::GetInst().GetResolution();
	BitBlt(_dc, 0, 0, int(resolution.x), int(resolution.y), ((Texture*)m_pTex)->GetHdc(), 0, 0, SRCCOPY);
	CScene::Render(_dc);
}
