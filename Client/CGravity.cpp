#include "pch.h"
#include "CGravity.h"
#include "CObject.h"
#include "CRigidBody.h"
#include "CTimeMgr.h"
CGravity::CGravity()
	: m_pOwner(nullptr)
	, m_fGravity(1000)
	, m_bOn(true)
{
}

CGravity::~CGravity()
{
}

void CGravity::Update()
{
	if (m_bOn)
	{
		m_pOwner->GetRigidBody()->AddVelocity(Vec2(0, m_fGravity * dt));
	}
	else
	{
		Vec2 OwnerVelocity = m_pOwner->GetRigidBody()->GetVelocity();
		m_pOwner->GetRigidBody()->SetVelocity(Vec2(OwnerVelocity.x, 0));
	}
}
