#pragma once
#include "PanelUI.h"
class TileUI :
    public PanelUI
{
private:
    UINT widthCount;
    UINT heightCount;

    bool m_bIsFinish;
public:
    TileUI(const UINT& _x,const UINT& _y);
    TileUI(const TileUI& _other);
    ~TileUI();
public:
    void IsFinish(const bool& _bTF) { m_bIsFinish = _bTF; }
    void NextIdx();
public:
    void Init() override;
    void Update() override;
    bool IsMouseOn() override;
    CLONE(TileUI)
};

