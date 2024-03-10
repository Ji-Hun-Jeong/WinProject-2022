#pragma once
#include "CObject.h"
class AttackCollider;
class CWeapon :
    public CObject
{
protected:
    AttackCollider*         m_pAttackCollider;

    map<string, AttackInfo> m_mapAttackInfo;
    float					m_fAccTime;
    float					m_fAttackTime;

    CObject*                m_pOwner;
public:
    CWeapon();
    ~CWeapon();
public:
    void Insert(const string& _strName, const AttackInfo& _eAttackInfo);
    void FinishAttack();
    void TakeAttack(const string& _strName);
    void SetAccTime(const float& _fAccTime) { m_fAccTime = _fAccTime; }

    const float& GetAccTime() { return m_fAccTime; }
    const float& GetAttackTime() { return m_fAttackTime; }

    CCollider* GetCollider() override { return ((CCollider*)m_pAttackCollider); } 

    void Init() override;
    void Update() override;
    void Render(const HDC& _dc) override;

    void OnCollision(CObject* pObj) override;
    void OnCollisionEnter(CObject* pObj) override;
    void OnCollisionExit(CObject* pObj) override;


    CLONE(CWeapon)

    friend class CObject;
};

