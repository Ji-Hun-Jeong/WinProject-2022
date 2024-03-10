#pragma once
#include "CScene.h"
class CRes;
class Texture;
class Scene_Start :
    public CScene
{
private:

public:
    Scene_Start();
    ~Scene_Start();
public:
    void Enter() override;
    void Update() override;
    void Render(const HDC& _dc) override;
};

