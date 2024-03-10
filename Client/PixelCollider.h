#pragma once
#include "CCollider.h"
class PixelCollider :
    public CCollider
{
private:
    PIXEL m_ePixelInfo;

    bool  m_bRender;

public:
    PixelCollider();
    virtual ~PixelCollider();
public:
    void SetPixelInfo(const PIXEL& _ePixel) { m_ePixelInfo = _ePixel; }
    void SetBoolRender(const bool& _bRender = false) { m_bRender = _bRender; }

    const PIXEL& GetPixelInfo() { return m_ePixelInfo; }
    const bool& IsRender() { return m_bRender; }

    void Render(const HDC& _dc) override;
};

