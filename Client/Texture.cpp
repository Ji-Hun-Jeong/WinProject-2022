#include "pch.h"
#include "Texture.h"

#include "CPathMgr.h"
#include "CCore.h"

Texture::Texture()
	: m_hImage(0)
	, m_hDC(0)
	, m_hBitInfo{}
{
}

Texture::~Texture()
{
	DeleteObject(m_hImage);
	DeleteDC(m_hDC);
}

void Texture::Load()
{
	string FinalPath = CPathMgr::GetInst().GetFinalPath(m_strRelativePath);	// 최종경로 얻어온다
	m_hImage = (HBITMAP)LoadImageA(nullptr, FinalPath.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION); //이미지 로딩
	assert(m_hImage);
	m_hDC = CreateCompatibleDC(CCore::GetInst().GetHdc());
	SelectObject(m_hDC, m_hImage);
	GetObject(m_hImage, sizeof(BITMAP), &m_hBitInfo);	// 이미지 정보 얻어오기
}
