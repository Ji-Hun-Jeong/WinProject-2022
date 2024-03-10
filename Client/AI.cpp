#include "pch.h"
#include "AI.h"
#include "CScene.h"
#include "CSceneMgr.h"
#include "CObject.h"
#include "Player.h"
#include "CRigidBody.h"
#include "CAnimator.h"
#include "CTimeMgr.h"

AI::AI()
	: m_pOwner(nullptr)
	, m_eMonsterState(GROUP_MONSTER_STATE::IDLE)
	, m_fAccTime(0.f)
	, m_fChangeTime(0.f)
	, m_fAlertTime(3.f)
	, m_fAccAlertTime(0.f)
{
	int randomnum = rand() % 15 + 5;
	m_fChangeTime = randomnum;
}

AI::~AI()
{
}

// 돌아다니다가 OnlyPlayer Collider와 충돌하면 방향바꾸기(1픽셀정도 이동시켜주기)
void AI::StateUpdate()
{
	CObject* pPlayer = nullptr;
	if (CSceneMgr::GetInst().GetCurScene()->GetVec(GROUP_OBJECT::PLAYER).size() == 0)	// Tool 씬에서만
	{
		m_eMonsterState = GROUP_MONSTER_STATE::IDLE;
		return;
	}
	if (!CSceneMgr::GetInst().GetCurScene()->GetVec(GROUP_OBJECT::PLAYER)[0]->IsDead())
	{
		pPlayer = CSceneMgr::GetInst().GetCurScene()->GetVec(GROUP_OBJECT::PLAYER)[0];
	}
	if (pPlayer)
	{
		if (GROUP_MONSTER_STATE::IDLE == m_eMonsterState)
		{
			m_fAccTime += dt;
			if (m_fChangeTime <= m_fAccTime)
			{
				m_vPrevDir = m_pOwner->GetRigidBody()->GetVelocity();
				m_vPrevDir = m_vPrevDir.Normallize();
				m_eMonsterState = GROUP_MONSTER_STATE::ALERT;
				m_fAccTime = 0.f;
			}
		}
		else if (GROUP_MONSTER_STATE::ALERT == m_eMonsterState)
		{
			m_fAccAlertTime += dt;
			if (m_fAlertTime <= m_fAccAlertTime)
			{
				m_fAccAlertTime = 0.f;
				m_eMonsterState = GROUP_MONSTER_STATE::IDLE;
				double maxspeed = m_pOwner->GetRigidBody()->GetMaxSpeed();
				m_pOwner->GetRigidBody()->SetVelocity(Vec2(m_vPrevDir.x * maxspeed, m_vPrevDir.y * m_pOwner->GetRigidBody()->GetVelocity().y));
			}
		}		
	}
	else
	{
		m_eMonsterState = GROUP_MONSTER_STATE::IDLE;
	}
}

void AI::Update()
{
	StateUpdate();
	switch (m_eMonsterState)
	{
	case GROUP_MONSTER_STATE::ALERT:
	{
		Vec2 Velocity = m_pOwner->GetRigidBody()->GetVelocity();
		Vec2 Dir = Velocity.Normallize();
		m_pOwner->GetRigidBody()->SetVelocity(Vec2(0.f, 0.f));
		if (Dir.x > 0)
		{
			m_pOwner->GetAnimator()->SetCurAnime("Stand_Right", (UINT)GROUP_ANIMATION_REPEAT::REPEAT);
		}
		else if (Dir.x < 0)
		{
			m_pOwner->GetAnimator()->SetCurAnime("Stand_Left", (UINT)GROUP_ANIMATION_REPEAT::REPEAT);
		}
	}
		break;
	case GROUP_MONSTER_STATE::IDLE:
	{
		Vec2 Velocity = m_pOwner->GetRigidBody()->GetVelocity();
		Vec2 Dir = Velocity.Normallize();
		double speed = m_pOwner->GetRigidBody()->GetMaxSpeed();
		m_pOwner->GetRigidBody()->SetVelocity(Vec2(Dir.x * speed, Velocity.y));
		if (Dir.x > 0)
		{
			m_pOwner->GetAnimator()->SetCurAnime("Move_Right", (UINT)GROUP_ANIMATION_REPEAT::REPEAT);
		}
		else if (Dir.x < 0)
		{
			m_pOwner->GetAnimator()->SetCurAnime("Move_Left", (UINT)GROUP_ANIMATION_REPEAT::REPEAT);
		}
	}
		break;
	case GROUP_MONSTER_STATE::TRACE:
		break;
	case GROUP_MONSTER_STATE::ATTACK:
		break;
	case GROUP_MONSTER_STATE::DEAD:
		break;
	case GROUP_MONSTER_STATE::END:
		break;
	default:
		break;
	}
}
