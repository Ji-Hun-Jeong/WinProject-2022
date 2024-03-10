#include "pch.h"
#include "CObject.h"
#include "CAnimator.h"
#include "CCollider.h"
#include "CRigidBody.h"
#include "CCamera.h"
#include "CCore.h"
#include "RectCollider.h"
#include "CSceneMgr.h"
#include "CScene.h"
#include "CGravity.h"
#include "PixelCollider.h"
#include "CTimeMgr.h"
#include "AttackCollider.h"
#include "CWeapon.h"

CObject::CObject()
	: m_iNum(0)
	, m_iDir(1)
	, m_bAlive(true)
	, m_bAir(true)
	, m_bStop(false)
	, m_bInCam(false)
	, m_pTex(nullptr)
	, m_pCollider(nullptr)
	, m_pWeapon(nullptr)
	, m_pRigidBody(nullptr)
	, m_pAnimator(nullptr)
	, m_pGravity(nullptr)
{}

CObject::CObject(const CObject& _other)	// 복사 생성자
	: m_strName(_other.m_strName)
	, m_iNum(0)
	, m_iDir(_other.m_iDir)
	, m_bAlive(true)
	, m_bAir(_other.m_bAir)
	, m_bInCam(_other.m_bInCam)
	, m_vPos(_other.m_vPos)
	, m_vScale(_other.m_vScale)
	, m_pTex(nullptr)
	, m_pCollider(nullptr)
	, m_pWeapon(nullptr)
	, m_pRigidBody(nullptr)
	, m_pAnimator(nullptr)
	, m_pGravity(nullptr)
{

}

CObject::~CObject()
{
	if (m_pCollider)
		delete m_pCollider;
	if (m_pAnimator)
		delete m_pAnimator;
	if (m_pRigidBody)
		delete m_pRigidBody;
	if (m_pGravity)
		delete m_pGravity;
	if (m_pWeapon)
		delete m_pWeapon;
}


void CObject::InputAttackData(const string& _strName, const AttackInfo& _eAttackInfo)
{
	m_pWeapon->Insert(_strName,_eAttackInfo);
}

void CObject::TakeAttack(const string& _strName)
{
	m_pWeapon->TakeAttack(_strName);
}


void CObject::CreateAnimator()
{
	assert(!m_pAnimator);
	if (!m_pAnimator)
	{
		m_pAnimator = new CAnimator;
		m_pAnimator->m_pOwner = this;
	}
}

void CObject::CreateCollider()
{
	assert(!m_pCollider);
	if (!m_pCollider)
	{
		m_pCollider = new RectCollider;
		m_pCollider->SetPos(m_vPos);
		m_pCollider->m_pOwner = this;
	}
}


void CObject::CreateRigidBody()
{
	assert(!m_pRigidBody);
	if (!m_pRigidBody)
	{
		m_pRigidBody = new CRigidBody;
		m_pRigidBody->m_pOwner = this;
	}
}

void CObject::CreateGravity()
{
	assert(!m_pGravity);
	if (!m_pGravity)
	{
		m_pGravity = new CGravity;
		m_pGravity->m_pOwner = this;
	}
}

void CObject::CreateWeapon()
{
	assert(!m_pWeapon);
	m_pWeapon = new CWeapon;
	m_pWeapon->m_pOwner = this;
	m_pWeapon->Init();
}

void CObject::ComponentUpdate()
{
	if (m_pRigidBody)
		m_pRigidBody->Update();
	if (m_pCollider)
		m_pCollider->Update();
	if (m_pGravity)
		m_pGravity->Update();
}

void CObject::Save(FILE* _p)
{

}

void CObject::Load(FILE* _p)
{
}

void CObject::Init()
{
	static UINT Num = 0;	// 번호를 부여해서 충돌체크
	m_iNum = Num++;
}

void CObject::OnCollision(CObject* pObj)
{
	m_pCollider->OnCollision(pObj->GetCollider());
}

void CObject::OnCollisionEnter(CObject* pObj)
{
	m_pCollider->OnCollisionEnter(pObj->GetCollider());
}

void CObject::OnCollisionExit(CObject* pObj)
{
	m_pCollider->OnCollisionExit(pObj->GetCollider());
}

void CObject::AnimationUpdate()
{
}

void CObject::StateUpdate()
{
}
