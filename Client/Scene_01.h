#pragma once
#include "CScene.h"
class CScene;
class Scene_01 :
    public CScene
{
private:
    CObject* m_pPlayer;
public:
    Scene_01();
    ~Scene_01();
public:
    CObject* GetPlayer() { return m_pPlayer; }
public:
    void Enter() override;
    void Render(const HDC& _dc) override;
};

