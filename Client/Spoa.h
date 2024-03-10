#pragma once
#include "Monster.h"
class Spoa :
    public Monster
{
private:
public:
    void Init() override;
    void LoadAnime() override;
    CLONE(Spoa)
};

