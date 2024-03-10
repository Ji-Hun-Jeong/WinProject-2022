#include "pch.h"
#include "Monster.h"
#include "CCollider.h"
#include "CRigidBody.h"
#include "CAnimator.h"
#include "AI.h"
#include "CResMgr.h"
#include "CTimeMgr.h"

Monster::Monster()
	: m_pAI(nullptr)
	, m_eState(GROUP_COLLISION_STATE::FLOOR)
	, m_bAttacked(false)
{
}

Monster::Monster(const Monster& _other)
	: CObject(_other)
	, m_pAI(nullptr)
	, m_eState(_other.m_eState)
	, m_bAttacked(false)
{
}

Monster::~Monster()
{
	if (m_pAI)
		delete m_pAI;
}


void Monster::CreateAI()
{
	m_pAI = new AI;
	m_pAI->m_pOwner = this;
}

void Monster::Attacked(const Vec2& _vecDistance)
{
	m_vPrevPos = m_vPos;
	m_bAttacked = true;
	m_vKnockbackDis = _vecDistance;
	m_vDestPos.x = m_vPos.x + m_vKnockbackDis.x;
}

void Monster::Init()
{
	CObject::Init();
	m_strName = "Monster";
}

void Monster::ComponentUpdate()
{
	CObject::ComponentUpdate();
	if (m_bAttacked)
	{
		m_vPos.x = m_vPrevPos.x + dt * m_vKnockbackDis.x;
		if (m_vKnockbackDis.x <= abs(m_vDestPos.x - m_vPrevPos.x))	// strange
		{
			m_vPos.x = m_vDestPos.x;
			m_bAttacked = false;
		}	
	}
	m_vPrevPos = m_vPos;
}

void Monster::Update()
{
	// 이시점에 방향전환 넣어야하나?
	if (m_pAI)
		m_pAI->Update();
}

void Monster::Render(const HDC& _dc)
{
	if (m_pAnimator)
		m_pAnimator->Play(_dc);
	if (m_pCollider)
		m_pCollider->Render(_dc);
	
}

void Monster::OnCollision(CObject* pObj)
{
}

void Monster::OnCollisionEnter(CObject* pObj)
{
	m_pCollider->OnCollisionEnter(pObj->GetCollider());
}

void Monster::OnCollisionExit(CObject* pObj)
{
	m_pCollider->OnCollisionExit(pObj->GetCollider());
}
