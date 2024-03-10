#pragma once
#include "BtnUI.h"
class TileBtn :
    public BtnUI
{
private:
    int     m_iIdx;
    bool    m_bAgainClick;
public:
    TileBtn(const int& _idx);
    TileBtn(const TileBtn& _other);
    ~TileBtn();
public:
    void Init() override;
    void NextIndex(const UINT& _iNextCount);
    void Render(const HDC& _dc) override;
    bool IsMouseOn() override;
    void MouseLbtnClick() override;
    CLONE(TileBtn)
};

