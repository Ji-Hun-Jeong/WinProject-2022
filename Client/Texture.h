#pragma once
#include "CRes.h"
class Texture :
    public CRes
{
private:
    HBITMAP m_hImage;   // �̹��� ������ ��Ʈ��
    HDC     m_hDC;      // ������ DC
    BITMAP  m_hBitInfo;  // �̹��� ���� ����
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

