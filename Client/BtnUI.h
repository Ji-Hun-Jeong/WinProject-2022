#pragma once
#include "UI.h"
class BtnUI :
    public UI
{
private:
    CRes* m_arrTex[(UINT)GROUP_BTN_STATE::END];
    CRes* m_pCurTex;
public:
    BtnUI();
    BtnUI(const BtnUI& _other);
    ~BtnUI();
public:
    void AddTex(const string& _strSamepath, const string& _strNormal, const string& _strMouseOn, const string& _strPress, const string& _strDisabled);
    CRes* GetCurTex() { return m_pCurTex; }
    void SetCurTex(CRes* pCurTex) { m_pCurTex = pCurTex; }
public:
    void Init() override;
    void Update() override;
    
    void Render(const HDC& _dc) override;
    void StateUpdate() override;
    bool IsMouseOn() override;
    void MouseOn() override;
    void MouseLbtnDown() override;
    void MouseLbtnUP() override;
    void MouseLbtnClick() override;
    CLONE(BtnUI)
    friend class PanelUI;
};

