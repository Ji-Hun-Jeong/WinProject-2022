#include "pch.h"
#include "CResMgr.h"
#include "CRes.h"
#include "Texture.h"
CResMgr CResMgr::m_mgr;
CResMgr::CResMgr()
{}
CResMgr::~CResMgr()
{
	Safe_Delete_Map(m_mapTex);
}

CRes* CResMgr::GetTexture(const string & _strKey, const string & _strRelativePath)
{
	CRes* pFind = FindTex(_strKey, _strRelativePath);
	if (pFind)
		return pFind;
	pFind = new Texture;
	pFind->SetKey(_strKey);
	pFind->SetRelativePath(_strRelativePath);
	pFind->Load();
	m_mapTex.insert(make_pair(_strKey, pFind));
	return pFind;
}

CRes* CResMgr::FindTex(const string& _strKey, const string& _strRelativePath)
{
	auto iter = m_mapTex.begin();
	for (iter; iter != m_mapTex.end(); ++iter)
	{
		if (_strKey == iter->first)
		{
			return iter->second;
		}
	}
	return nullptr;
}
