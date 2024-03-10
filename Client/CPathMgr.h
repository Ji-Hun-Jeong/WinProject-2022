#pragma once
class CPathMgr
{
	SINGLE(CPathMgr)
private:
	string m_strAbsPath;
public:
	string GetFinalPath(const string& _RelativePath) { return string(m_strAbsPath + _RelativePath); }
};

