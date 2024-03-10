#include "pch.h"
#include "RectCollider.h"
#include "CObject.h"
#include "CRigidBody.h"
#include "CTimeMgr.h"
#include "SelectGDI.h"
#include "CCamera.h"
#include "CSceneMgr.h"
#include "CScene.h"
#include "CCollider.h"

RectCollider::RectCollider()
{
	m_strType = "Rect";
}

RectCollider::~RectCollider()
{
}


void RectCollider::Render(const HDC& _dc)
{
	if (CSceneMgr::GetInst().GetCurScene()->ShowCol())
	{
		Vec2 renderPos = CCamera::GetInst().GetRenderPos(m_vPos);
		SelectGDI brush(_dc, GROUP_BRUSH::HOLLOW);
		if (m_bCollision)
		{
			SelectGDI pen(_dc, GROUP_PEN::RED);
			Rectangle(_dc
				, int(renderPos.x)
				, int(renderPos.y)
				, int(renderPos.x + m_vScale.x)
				, int(renderPos.y + m_vScale.y));
		}
		else
		{
			SelectGDI pen(_dc, GROUP_PEN::GREEN);
			Rectangle(_dc
				, int(renderPos.x)
				, int(renderPos.y)
				, int(renderPos.x + m_vScale.x)
				, int(renderPos.y + m_vScale.y));
		}
	}
}

void RectCollider::OnCollision(CCollider* _pCollider)
{
	//CObject* pOwner = _pCollider->GetOwner();
	//CRigidBody* p = pOwner->GetRigidBody();
	//if (p && m_pOwner->GetRigidBody())
	//{

	//}
	//else if (p)
	//{
	//	Vec2 vel = p->GetVelocity();
	//	//Vec2 Acc = p->GetAcc();
	//	Vec2 Dir = -vel.Normallize();
	//	Vec2 Pos = pOwner->GetPos();
	//	if (Dir.y < 0)
	//	{
	//		double disY = abs(m_vPos.y - (_pCollider->GetPos().y + _pCollider->GetScale().y));
	//		pOwner->SetPos(Vec2(Pos.x, Pos.y + (Dir.y * disY)));
	//		pOwner->SetAir(false);
	//		p->SetVelocity(Vec2(0.f, 0.f));	// 중력으로 남아있는 속도 없애기	
	//	}
	//}
}

void RectCollider::OnCollisionEnter(CCollider* _pCollider)
{	
	// 여기서 다른 오브젝트와의 충돌 검사 (픽셀 제외)

	//CObject* pOwner = _pCollider->GetOwner();
	//CRigidBody* p = pOwner->GetRigidBody();
	//if (p && m_pOwner->GetRigidBody())
	//{

	//}
	//else if (p)
	//{
	//	Vec2 vel = p->GetVelocity();
	//	//Vec2 Acc = p->GetAcc();
	//	Vec2 Dir = -vel.Normallize();
	//	Vec2 Pos = pOwner->GetPos();
	//	if (Dir.y < 0)
	//	{
	//		double disY = abs(m_vPos.y - (_pCollider->GetPos().y + _pCollider->GetScale().y));
	//		pOwner->SetPos(Vec2(Pos.x, Pos.y + (Dir.y * disY)));
	//		pOwner->SetAir(false);
	//		p->SetVelocity(Vec2(0.f, 0.f));	// 중력으로 남아있는 속도 없애기	
	//	}
	//}
	m_bCollision = true;
}

void RectCollider::OnCollisionExit(CCollider* _pCollider)
{
	m_bCollision = false;
}
