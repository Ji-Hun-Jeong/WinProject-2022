#include "pch.h"
#include "CRigidBody.h"
#include "CTimeMgr.h"
#include "CObject.h"
#include "CCollider.h"

CRigidBody::CRigidBody()
	: m_pOwner(nullptr)
	, m_fMaxSpeed(300.f)
	, m_fFricCoeff(700.f)
	, m_fMass(0.f)
	, m_bStop(false)

{
}

CRigidBody::~CRigidBody()
{
}

void CRigidBody::Update()
{
	if ("Player" == m_pOwner->GetName())
	{
		m_vAcc = m_vForce / m_fMass;				// F = m * a

		Vec2 SubDir = -m_vVelocity.Normallize();	// 속도의 반대 방향으로
		m_vAcc.x += SubDir.x * m_fFricCoeff;		// 마찰력을 더한다.

		//m_vAcc += m_vOtherAcc;					

		m_vVelocity += m_vAcc * dt;					// 속도는 가속도를 시간단위만큼 더한다.
		if (abs(m_vVelocity.x) <= 1.f)
			m_vVelocity = { 0,m_vVelocity.y };
	}

	if (m_fMaxSpeed <= m_vVelocity.GetLength())	// 속력이 최대속력보다 크면
	{
		Vec2 Dir = m_vVelocity.Normallize();	// 속도의 방향으로
		m_vVelocity.x = Dir.x * m_fMaxSpeed;	// 속도를 최대 속력으로 설정한다.
	}

	if (m_bStop)
	{
		Vec2 Dir = m_vVelocity.Normallize();
		if (Dir.x == m_bStopDir.x)
		{
			m_vForce = { 0,0 };
			return;
		}
	}

	Vec2 Pos = m_pOwner->GetPos();
	m_pOwner->SetPos(Pos + m_vVelocity * dt);
	
	m_vForce = { 0,0 };
	m_bStop = false;
}

void CRigidBody::StopDir(const Vec2& _vDir)
{
	m_bStop = true;
	m_bStopDir = _vDir;
}
