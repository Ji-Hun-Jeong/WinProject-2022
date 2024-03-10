#include "pch.h"
#include "CWeapon.h"
#include "AttackCollider.h"
#include "CRigidBody.h"
#include "Monster.h"

CWeapon::CWeapon()
	: m_pAttackCollider(nullptr)
	, m_fAccTime(0.f)
	, m_fAttackTime(0.f)
	, m_pOwner(nullptr)
{
	m_pAttackCollider = new AttackCollider;
	m_pAttackCollider->m_pOwner = this;
}

CWeapon::~CWeapon()
{
	if (m_pAttackCollider)
		delete m_pAttackCollider;
}

void CWeapon::Insert(const string& _strName, const AttackInfo& _eAttackInfo)
{
	auto iter = m_mapAttackInfo.find(_strName);
	assert((m_mapAttackInfo.end() == iter));
	m_mapAttackInfo.insert(make_pair(_strName, _eAttackInfo));
}

void CWeapon::FinishAttack()
{
	m_pAttackCollider->SetScale(Vec2(0.f, 0.f));
	m_fAccTime = 0.f;
}

void CWeapon::TakeAttack(const string& _strName)
{
	auto iter = m_mapAttackInfo.find(_strName);
	m_pAttackCollider->SetAttackName(_strName);
	m_vPos = m_pOwner->GetPos();
	if (-1 == m_pOwner->GetDir())
		m_pAttackCollider->SetPos(Vec2(m_vPos.x - iter->second.Offset.x, m_vPos.y - iter->second.Offset.y));
	else
		m_pAttackCollider->SetPos(Vec2(m_vPos.x + iter->second.Offset.x, m_vPos.y - iter->second.Offset.y));
	m_pAttackCollider->SetScale(iter->second.Range);
	m_fAttackTime = iter->second.Time;
	m_fAccTime = 0.f;
}

void CWeapon::Init()
{
	CObject::Init();
	m_strName = "Weapon";
}

void CWeapon::Update()
{
	string name = m_pAttackCollider->GetAttackName();
	auto iter = m_mapAttackInfo.find(name);
	m_vPos = m_pOwner->GetPos();
	if (iter != m_mapAttackInfo.end())
	{
		if (-1 == m_pOwner->GetDir())
			m_pAttackCollider->SetPos(Vec2(m_vPos.x - iter->second.Offset.x, m_vPos.y - iter->second.Offset.y));
		else
			m_pAttackCollider->SetPos(Vec2(m_vPos.x + iter->second.Offset.x, m_vPos.y - iter->second.Offset.y));
	}
}

void CWeapon::Render(const HDC& _dc)
{
	if (m_pAttackCollider)
		m_pAttackCollider->Render(_dc);
}

void CWeapon::OnCollision(CObject* pObj)
{
	m_pAttackCollider->OnCollision(pObj->GetCollider());
}

void CWeapon::OnCollisionEnter(CObject* pObj)
{
	m_pAttackCollider->OnCollisionEnter(pObj->GetCollider());
	if ("Monster" == pObj->GetName())
	{
		Monster* monster = dynamic_cast<Monster*>(pObj);
		int Dir = m_pOwner->GetDir();
		monster->Attacked(Vec2(Dir * 50.f, 0.f));
	}
}

void CWeapon::OnCollisionExit(CObject* pObj)
{
	m_pAttackCollider->OnCollisionExit(pObj->GetCollider());
}
