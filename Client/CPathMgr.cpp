#include "pch.h"
#include "CPathMgr.h"
CPathMgr CPathMgr::m_mgr;
CPathMgr::CPathMgr()
{
	char szBuffer[256] = {};
	GetCurrentDirectoryA(256, szBuffer);
	size_t len = strlen(szBuffer);
	for (len; len > 0; --len)
	{
		if ('\\' == szBuffer[len])
		{
			szBuffer[len + 1] = '\0';
			break;
			// Output
		}
	}
	m_strAbsPath = szBuffer;
	m_strAbsPath += "bin\\content\\";

}
CPathMgr::~CPathMgr()
{}