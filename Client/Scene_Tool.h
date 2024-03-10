#pragma once
#include "CScene.h"
class Scene_Tool :
    public CScene
{
private:

public:
    Scene_Tool();
    ~Scene_Tool();
public:
    void Enter() override;
    void Update() override;
    void FinalUpdate() override;
    void Render(const HDC& _dc) override;
    void SaveFileData();
    void SaveFile(const char* _p);
};

