#pragma once
#include "CObject.h"
class Texture;
class CRes;
class UI :
    public CObject
{
protected:
    vector<UI*>     m_vecUI;
    UI*             m_pOwner;
    Vec2            m_vFinalPos;

    bool            m_bMouseOn;
    bool            m_bLbtnDown;
public:
    UI();
    UI(const UI& _other);
    virtual ~UI();
public:
    void ChildUpdate();
    void ChildRender(const HDC& _dc);
    vector<UI*>& GetVecUI() { return m_vecUI; }
public:
    virtual void StateUpdate() = 0;
    virtual void Update();
    virtual void Render(const HDC& _dc);
    virtual bool IsMouseOn();
    virtual void MouseOn() = 0;
    virtual void MouseLbtnDown() = 0;
    virtual void MouseLbtnUP() = 0;
    virtual void MouseLbtnClick() = 0;
    friend class CUIMgr;
};

