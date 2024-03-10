#pragma once
#include "CObject.h"
class CObject;
class PixelCollider;
class PlayerWeapon;
class Player :
    public CObject
{
private:
    // hp, exp, power, mp, speed(?) 

    GROUP_PLAYER_STATE      m_ePlayerState;

    GROUP_COLLISION_STATE   m_eState;
public:
    Player();
    Player(const Player& _other);
    ~Player();
public:
    void SetObjState(const GROUP_COLLISION_STATE& _eState) { m_eState = _eState; }
    void SetPlayerState(const GROUP_PLAYER_STATE& _eState) { m_ePlayerState = _eState; }
    void LoadAnime();

    const GROUP_COLLISION_STATE& GetObjState() { return m_eState; }
    const GROUP_PLAYER_STATE& GetPlayerState() { return m_ePlayerState; }

    void AttackCheck();
    void FinishAttack();
public:
    void Init() override;
    void Update() override;
    void ComponentUpdate() override;
    void Render(const HDC& _dc) override;

    /*void CollisionToPixel(const PIXEL& _eInfo, const GROUP_COLLISION_STATE& _eType) override;*/
    void AnimationUpdate() override;
    void StateUpdate() override;

    void OnCollision(CObject* pObj) override;
    void OnCollisionEnter(CObject* pObj) override;
    void OnCollisionExit(CObject* pObj) override;
    CLONE(Player)
};

