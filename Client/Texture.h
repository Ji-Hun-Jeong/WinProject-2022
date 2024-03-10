#pragma once
#include "CRes.h"
class Texture :
    public CRes
{
private:
    HBITMAP m_hImage;   // 이미지 가져올 비트맵
    HDC     m_hDC;      // 연결할 DC
    BITMAP  m_hBitInfo;  // 이미지 정보 저장
public:
    Texture();
    ~Texture();
public:
    LONG& GetWidth() { return m_hBitInfo.bmWidth; }
    LONG& GetHeight() { return m_hBitInfo.bmHeight; }

    const HDC& GetHdc() { return m_hDC; }
public:
    void Load() override;
};

