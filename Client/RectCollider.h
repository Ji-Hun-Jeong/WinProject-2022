#pragma once
#include "CCollider.h"
class RectCollider :
    public CCollider
{
protected:

public:
    RectCollider();
    virtual ~RectCollider();
public:
    void Render(const HDC& _dc) override;
    void OnCollision(CCollider* _pCollider) override;
    void OnCollisionEnter(CCollider* _pCollider) override;
    void OnCollisionExit(CCollider* _pCollider) override;
};
