#include "pch.h"
#include "Scene_Tool.h"
#include "CCore.h"

#include "UI.h"
#include "PanelUI.h"
#include "BtnUI.h"

#include "Tile.h"

#include "PixelCollider.h"

#include "CSceneMgr.h"
#include "CScene.h"

#include "TileBtn.h"
#include "TileUI.h"
#include "NextBtn.h"

#include "CResMgr.h"
#include "Texture.h"
#include "resource.h"

#include "CPathMgr.h"

#include "CCamera.h"

#include "CTileMgr.h"
#include "CKeyMgr.h"

#include "CObject.h"
#include "Monster.h"
#include "Spoa.h"
Scene_Tool::Scene_Tool()
{
}

Scene_Tool::~Scene_Tool()
{
}

void Scene_Tool::Enter()
{
	CCamera::GetInst().SetCamState(GROUP_CAMERA_STATE::FREE);
	m_pTex = CResMgr::GetInst().GetTexture("Tool", "texture\\map\\Scene_01\\Scene_01.Copy.bmp");
	/*CreateTile(5, 5);
	UINT X = 1;
	UINT Y = 1;
	Vec2 res = CCore::GetInst().GetResolution();
	TileUI* pTileUI = new TileUI(X, Y);
	pTileUI->SetPos(Vec2(res.x - (TILE_SIZE * X), 0));
	pTileUI->SetScale(Vec2(TILE_SIZE * X, TILE_SIZE * Y + 40));
	pTileUI->Init();
	m_vecObj[(UINT)GROUP_OBJECT::UI].push_back(pTileUI);
	TileBtn* pTileBtn = nullptr;
	for (UINT i = 0; i < Y; i++)
	{
		for (UINT j = 0; j < X; ++ j)
		{
			pTileBtn = new TileBtn(Y * i + j);
			pTileUI->CreateBtnUI(pTileBtn, Vec2(TILE_SIZE * j, 20 + TILE_SIZE * i), Vec2(TILE_SIZE, TILE_SIZE));
		}
	}
	NextBtn* pNextBtn = new NextBtn;
	pTileUI->CreateBtnUI(pNextBtn, Vec2(TILE_SIZE * X - 30, TILE_SIZE * Y + 20), Vec2(15, 15));*/
}

void Scene_Tool::Update()
{
	if (GetFocus())
	{
		if (KEYCHECK(CONTROL, TAP))
		{
			SaveFileData();
		}
		else if (KEYCHECK(SPACE, TAP))
		{
			LoadFileData();
		}
		if (KEYCHECK(LBTN, TAP))
		{
			Vec2 Mouse = MOUSE_POS;
			Mouse = CCamera::GetInst().GetRealPos(Mouse);
			Monster* pMonster = new Spoa;
			pMonster->SetScale(Vec2(50.f, 50.f));
			Vec2 Scale = pMonster->GetScale();
			pMonster->SetPos(Vec2(Mouse - Scale / 2.f));
			pMonster->Init();
			m_vecObj[(UINT)GROUP_OBJECT::MONSTER].push_back(pMonster);
		}
	}
}

void Scene_Tool::FinalUpdate()
{
}

void Scene_Tool::Render(const HDC& _dc)
{
	Vec2 rePos = { 0,0 };
	Vec2 renderPos = CCamera::GetInst().GetRenderPos(rePos);
	BitBlt(_dc, int(renderPos.x), int(renderPos.y), ((Texture*)m_pTex)->GetWidth(), ((Texture*)m_pTex)->GetHeight(), ((Texture*)m_pTex)->GetHdc(), 0, 0, SRCCOPY);
	CScene::Render(_dc);
}

void Scene_Tool::SaveFileData()
{
	ShowCursor(true);
	char szName[256] = {};
	OPENFILENAMEA ofn = {};
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = CCore::GetInst().GetHwnd();
	ofn.lpstrFile = szName;
	ofn.nMaxFile = sizeof(szName);
	ofn.lpstrFilter = "ALL\0*.*\0Tile\0*.tile\0";
	ofn.nFilterIndex = 0;
	ofn.lpstrFileTitle = nullptr;
	ofn.nMaxFileTitle = 0;
	string strTileFolder = CPathMgr::GetInst().GetFinalPath("mapdata");
	ofn.lpstrInitialDir = strTileFolder.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	if (GetSaveFileNameA(&ofn))
	{
		SaveFile(szName);
	}
	ShowCursor(false);
}

void Scene_Tool::SaveFile(const char* _p)
{
	FILE* pFile = nullptr;
	fopen_s(&pFile, _p, "wb");
	assert(pFile);
	UINT iX = CTileMgr::GetInst().GetTileXCount();
	UINT iY = CTileMgr::GetInst().GetTileYCount();
	fwrite(&iX, sizeof(UINT), 1, pFile);
	fwrite(&iY, sizeof(UINT), 1, pFile);
	for (size_t i = 0; i < m_vecObj[(UINT)GROUP_OBJECT::TILE].size(); ++i)
	{
		m_vecObj[(UINT)GROUP_OBJECT::TILE][i]->Save(pFile);
	}
	string strKey= ((Texture*)m_pTex)->GetKey();
	size_t sizeKey = strKey.size();
	fwrite(&sizeKey, sizeof(size_t), 1, pFile);
	fprintf(pFile, strKey.c_str());
	string FinalPath = ((Texture*)m_pTex)->GetRelativePath();
	size_t size = FinalPath.size();
	fwrite(&size, sizeof(size_t), 1, pFile);
	fprintf(pFile, FinalPath.c_str());

	LONG TexWidth = ((Texture*)m_pTex)->GetWidth();
	LONG TexHegith = ((Texture*)m_pTex)->GetHeight();
	COLORREF eColor = {};
	PIXEL info = {};
	for (LONG i = 0; i < TexHegith; ++i)
	{
		for (LONG j = 0; j < TexWidth; ++j)
		{
			eColor = GetPixel(((Texture*)m_pTex)->GetHdc(), j, i);
			info.R = GetRValue(eColor);
			info.G = GetGValue(eColor);
			info.B = GetBValue(eColor);
			fwrite(&info, sizeof(PIXEL), 1, pFile);			
		}
	}
	size_t MonVecSize = m_vecObj[(UINT)GROUP_OBJECT::MONSTER].size();
	fwrite(&MonVecSize, sizeof(size_t), 1, pFile);
	for (size_t i = 0; i < MonVecSize; ++i)
	{
		Monster* pMonster = dynamic_cast<Monster*>(m_vecObj[(UINT)GROUP_OBJECT::MONSTER][i]);
		assert(pMonster);
		string Name = pMonster->GetMonsterName();
		const char* p = Name.c_str();
		while (*p)
		{
			fwrite(p, sizeof(char), 1, pFile);
			p += 1;
		}
		fwrite(";", sizeof(char), 1, pFile);
		Vec2 Pos = pMonster->GetPos();
		fwrite(&Pos, sizeof(Vec2), 1, pFile);
		Vec2 Scale = pMonster->GetScale();
		fwrite(&Scale, sizeof(Vec2), 1, pFile);
	}
	fclose(pFile);
}








///
///
/// 
/// 
INT_PTR CALLBACK TileCountProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	ShowCursor(true);
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		
		if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		else if (LOWORD(wParam) == IDOK)
		{
			UINT x = GetDlgItemInt(hDlg, IDC_EDIT1, nullptr, false);
			UINT y = GetDlgItemInt(hDlg, IDC_EDIT2, nullptr, false);
			CScene* p = CSceneMgr::GetInst().GetCurScene();
			Scene_Tool* pTool = dynamic_cast<Scene_Tool*>(p);
			assert(pTool);
			pTool->DeleteGroup(GROUP_OBJECT::TILE);
			pTool->CreateTile(x, y);
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	ShowCursor(false);
	return (INT_PTR)FALSE;
}