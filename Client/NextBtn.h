#pragma once
#include "BtnUI.h"
class NextBtn :
    public BtnUI
{
private:
public:
    NextBtn();
    NextBtn(const NextBtn& _other);
    ~NextBtn();
public:
    void Init() override;
    void Render(const HDC& _dc) override;
    void MouseLbtnClick() override;
    CLONE(NextBtn)
};

