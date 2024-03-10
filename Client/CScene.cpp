#include "pch.h"
#include "CScene.h"

#include "CObject.h"
#include "Monster.h"
#include "Spoa.h"

#include "Texture.h"
#include "CRes.h"

#include "CCollisionMgr.h"
#include "PixelCollider.h"

#include "Tile.h"
#include "CTileMgr.h"

#include "CCore.h"
#include "CPathMgr.h"
#include "CResMgr.h"
#include "CRes.h"

#include "CKeyMgr.h"

CScene::CScene()
	: m_pTex(nullptr)
	, m_pAnotherTex(nullptr)
	, m_bShowCollider(true)
{
}

CScene::~CScene()
{
	for (UINT Object = 0; Object < (UINT)GROUP_OBJECT::END; ++Object)
	{
		Safe_Delete_Vec(m_vecObj[Object]);
	}
	Safe_Delete_Vec(m_vecCol);
}

void CScene::AddObject(CObject* _obj, const GROUP_OBJECT& _group)
{
	m_vecObj[(UINT)_group].push_back(_obj);
}

void CScene::DeleteGroup(const GROUP_OBJECT& _group)
{
	Safe_Delete_Vec(m_vecObj[(UINT)_group]);
}

void CScene::CreateTile(const UINT& _x, const UINT& _y)
{
	CTileMgr::GetInst().SetTileCount(_x, _y);
	for (UINT i = 0; i < _y; ++i)
	{
		for (UINT j = 0; j < _x; ++j)
		{
			Tile* pTile = new Tile;
			pTile->SetPos(Vec2(TILE_SIZE * j, TILE_SIZE * i));
			pTile->Init();
			m_vecObj[(UINT)GROUP_OBJECT::TILE].push_back(pTile);
		}
	}
}

void CScene::Enter()
{
}

void CScene::Exit()
{
	DeleteAll();
	CCollisionMgr::GetInst().ClearAll();
}

void CScene::Update()
{
	if (KEYCHECK(ENTER, TAP))
	{
		m_bShowCollider = !m_bShowCollider;
	}
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
	if (m_bShowCollider)
	{
		m_pTex = CResMgr::GetInst().GetTexture("test", "texture\\map\\Scene_01\\Scene_01.Copy.bmp");
	}
	else
	{
		m_pTex = CResMgr::GetInst().GetTexture("Scene_01.test", "texture\\map\\Scene_01\\Scene_01.bmp");
	}
}

void CScene::FinalUpdate()
{
	for (UINT Object = 0; Object < (UINT)GROUP_OBJECT::END; ++Object)
	{
		for (size_t Count = 0; Count < m_vecObj[Object].size(); ++Count)
		{
			if (m_vecObj[Object][Count])
			{
				m_vecObj[Object][Count]->ComponentUpdate();
			}
		}
	}
}

void CScene::Render(const HDC& _dc)
{
	for (UINT Object = 0; Object < (UINT)GROUP_OBJECT::END; ++Object)
	{
		auto iter = m_vecObj[Object].begin();
		for (; iter != m_vecObj[Object].end();)
		{
			if ((*iter)->IsDead())
			{
				iter = m_vecObj[Object].erase(iter);
			}
			else
			{
				(*iter)->Render(_dc);
				++iter;
			}
		}
	}
}

void CScene::DeleteAll()
{
	for (UINT Object = 0; Object < (UINT)GROUP_OBJECT::END; ++Object)
	{
		Safe_Delete_Vec(m_vecObj[Object]);
	}
}

void CScene::LoadFileData()
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
	if (GetOpenFileNameA(&ofn))
	{
		LoadFile(szName);
	}
	ShowCursor(false);
}

void CScene::LoadFile(const char* _p)
{
	FILE* pFile = nullptr;
	fopen_s(&pFile, _p, "rb");
	assert(pFile);
	UINT iX = 0;
	UINT iY = 0;
	fread(&iX, sizeof(UINT), 1, pFile);
	fread(&iY, sizeof(UINT), 1, pFile);
	for (UINT i = 0; i < iY; ++i)
	{
		for (UINT j = 0; j < iX; ++j)
		{
			CObject* pObj = new Tile;
			pObj->Init();
			pObj->Load(pFile);
			m_vecObj[(UINT)GROUP_OBJECT::TILE].push_back(pObj);
		}
	}
	char word = 0;
	string strKey;
	size_t sizeKey = 0;
	fread(&sizeKey, sizeof(size_t), 1, pFile);
	for (size_t i = 0; i < sizeKey; ++i)
	{
		fread(&word, sizeof(char), 1, pFile);
		strKey += word;
	}
	string RelativePath;
	size_t size = 0;
	fread(&size, sizeof(size_t), 1, pFile);

	for (size_t i = 0; i < size; ++i)
	{
		fread(&word, sizeof(char), 1, pFile);
		RelativePath += word;
	}
	m_pTex = CResMgr::GetInst().GetTexture(strKey, RelativePath);
	LONG TexWidth = ((Texture*)m_pTex)->GetWidth();
	LONG TexHeight = ((Texture*)m_pTex)->GetHeight();
	PixelCollider* pPixel = nullptr;
	COLORREF eColor = {};
	PIXEL info = {};
	for (LONG i = 0; i < TexHeight; ++i)
	{
		for (LONG j = 0; j < TexWidth; ++j)
		{
			pPixel = new PixelCollider;
			fread(&info, sizeof(PIXEL), 1, pFile);
			pPixel->SetPixelInfo(info);
			m_vecCol.push_back(pPixel);
		}
	}
	size_t MonVecSize = 0;
	fread(&MonVecSize, sizeof(size_t), 1, pFile);
	Monster* pMonster = nullptr;
	Vec2 vMonsterPos;
	Vec2 vMonsterScale;
	for (size_t i = 0; i < MonVecSize; ++i)
	{
		string Name;
		char str;
		while (1)
		{
			fread(&str, sizeof(char), 1, pFile);
			if (';' == str)
			{
				break;
			}
			Name += str;
		}
		if ("Spoa" == Name)
		{
			pMonster = new Spoa;
		}
		fread(&vMonsterPos, sizeof(Vec2), 1, pFile);
		pMonster->SetPos(vMonsterPos);
		fread(&vMonsterScale, sizeof(Vec2), 1, pFile);
		pMonster->SetScale(vMonsterScale);
		pMonster->Init();
		m_vecObj[(UINT)GROUP_OBJECT::MONSTER].push_back(pMonster);
	}

	fclose(pFile);
}