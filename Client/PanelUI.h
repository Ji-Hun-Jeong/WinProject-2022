#pragma once
#include "UI.h"
class BtnUI;
class PanelUI :
    public UI
{
private:
    Vec2   m_vCurPos;
    Vec2   m_vPrevPos;
public:
    PanelUI();
    PanelUI(const PanelUI& _other);
    ~PanelUI();
public:
    void CreateBtnUI(BtnUI* pBtn, const Vec2& _vPos, const Vec2& _vScale);
public:
    void Init() override;
    void StateUpdate() override;
    void Update() override;
    void MouseOn() override;
    void MouseLbtnDown() override;
    void MouseLbtnUP() override;
    void MouseLbtnClick() override;
    CLONE(PanelUI)
};

