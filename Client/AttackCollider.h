#pragma once
#include "RectCollider.h"
class AttackCollider :
    public RectCollider
{
protected:
    string m_strAttackName;
public:
    AttackCollider();
    ~AttackCollider();
public:
    void SetAttackName(const string& _strName) { m_strAttackName = _strName; }
    const string& GetAttackName() { return m_strAttackName; }
    friend class CWeapon;
};

