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

		Vec2 SubDir = -m_vVelocity.Normallize();	// �ӵ��� �ݴ� ��������
		m_vAcc.x += SubDir.x * m_fFricCoeff;		// �������� ���Ѵ�.

		//m_vAcc += m_vOtherAcc;					

		m_vVelocity += m_vAcc * dt;					// �ӵ��� ���ӵ��� �ð�������ŭ ���Ѵ�.
		if (abs(m_vVelocity.x) <= 1.f)
			m_vVelocity = { 0,m_vVelocity.y };
	}

	if (m_fMaxSpeed <= m_vVelocity.GetLength())	// �ӷ��� �ִ�ӷº��� ũ��
	{
		Vec2 Dir = m_vVelocity.Normallize();	// �ӵ��� ��������
		m_vVelocity.x = Dir.x * m_fMaxSpeed;	// �ӵ��� �ִ� �ӷ����� �����Ѵ�.
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
