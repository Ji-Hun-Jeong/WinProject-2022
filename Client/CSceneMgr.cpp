#include "pch.h"
#include "CSceneMgr.h"
#include "CScene.h"
#include "Scene_Start.h"
#include "Scene_01.h"
#include "Scene_Tool.h"
CSceneMgr CSceneMgr::m_mgr;
CSceneMgr::CSceneMgr()
	: m_arrScene{}
	, m_CurScene(nullptr)
{}
CSceneMgr::~CSceneMgr()
{
	for (UINT Scene = 0; Scene < (UINT)GROUP_SCENE::END; ++Scene)
	{
		if (m_arrScene[Scene])
			delete m_arrScene[Scene];
	}
}

void CSceneMgr::Init()
{
	m_arrScene[(UINT)GROUP_SCENE::TOOL] = new Scene_Tool;
	m_arrScene[(UINT)GROUP_SCENE::START] = new Scene_Start;
	m_arrScene[(UINT)GROUP_SCENE::SCENE_01] = new Scene_01;
	m_CurScene = m_arrScene[(UINT)GROUP_SCENE::SCENE_01];
	m_CurScene->Enter();
}

void CSceneMgr::Update()
{
	m_CurScene->Update();
	m_CurScene->FinalUpdate();
}

void CSceneMgr::Render(const HDC& _dc)
{
	m_CurScene->Render(_dc);
}

void CSceneMgr::ChangeScene(const GROUP_SCENE& _scene)
{
	m_CurScene->Exit();
	m_CurScene = m_arrScene[(UINT)_scene];
	m_CurScene->Enter();
}
