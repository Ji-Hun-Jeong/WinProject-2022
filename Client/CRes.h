#pragma once
class CRes
{
protected:
	string m_strKey;
	string m_strRelativePath;
public:
	CRes();
	~CRes();
public:
	void SetKey(const string& _strKey) { m_strKey = _strKey; }
	void SetRelativePath(const string& _strRelativePath) { m_strRelativePath = _strRelativePath; }

	const string& GetKey() { return m_strKey; }
	const string& GetRelativePath() { return m_strRelativePath; }
public:
	virtual void Load() = 0;
};

