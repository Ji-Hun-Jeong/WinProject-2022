#pragma once
class Texture;
class CRes;
class CResMgr
{
	SINGLE(CResMgr)
private:
	map<string, CRes*> m_mapTex;
public:
	CRes* GetTexture(const string& _strKey, const string& _strRelativePath);
private:
	CRes* FindTex(const string& _strKey, const string& _strRelativePath);
};

