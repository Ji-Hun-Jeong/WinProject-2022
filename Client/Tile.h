#pragma once
#include "CObject.h"
#include "CRes.h"
class Tile :
    public CObject
{
private:
    int     m_iIdx;
public:
    Tile();
    ~Tile();
public:
    void Init() override;
    void Update() override;
    void Render(const HDC& _dc) override;

    void SetIndex(const UINT& _iIdx) { m_iIdx = _iIdx; }
    bool IsMouseOn();

    void Save(FILE* _p) override;
    void Load(FILE* _p) override;
    CLONE(Tile)
};

