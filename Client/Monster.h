#pragma once
#include "CObject.h"
class AI;
class Monster :
    public CObject
{
protected:
    AI*                     m_pAI;

    string                  m_strMonsterName;

    GROUP_COLLISION_STATE	m_eState;

    bool                    m_bAttacked;
    Vec2                    m_vKnockbackDis;
    Vec2                    m_vPrevPos;
    Vec2                    m_vDestPos;
public:
    Monster();
    Monster(const Monster& _other);
    ~Monster();
public:
    void CreateAI();
    void Attacked(const Vec2& _vecDistance);
    const string& GetMonsterName() { return m_strMonsterName; }
public:
    void Init();
    virtual void LoadAnime() = 0;
    void ComponentUpdate() override;
    void SetObjState(const GROUP_COLLISION_STATE& _eState) { m_eState = _eState; }
    void OnCollision(CObject* pObj) override;
    void OnCollisionEnter(CObject* pObj) override;
    void OnCollisionExit(CObject* pObj) override;
    void Update() override;
    void Render(const HDC& _dc) override;
};

