#include "pch.h"
#include "Spoa.h"
#include "CRigidBody.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CResMgr.h"
#include "Monster.h"
#include "CObject.h"

void Spoa::Init()
{
	Monster::Init();

	m_strMonsterName = "Spoa";

	CreateCollider();
	m_pCollider->SetScale(Vec2(15.f, 15.f));

	CreateRigidBody();
	m_pRigidBody->SetMass(1.f);
	m_pRigidBody->SetMaxSpeed(80.f);
	m_pRigidBody->SetVelocity(Vec2(-80.f, 0.f));

	CreateAnimator();
	LoadAnime();

	m_pAnimator->SetCurAnime("Stand_Left", true);

	CreateAI();
	CreateGravity();
}

void Spoa::LoadAnime()
{
	// 애니메이션 넣기
	CRes* pTex = CResMgr::GetInst().GetTexture("Spoa_StandL", "texture\\monster\\Spoa\\Stand\\StandL.bmp");
	m_pAnimator->SetAnime("Stand_Left", pTex, Vec2(0, 0), Vec2(56, 56), Vec2(56, 0), 3, 0.2f);
	pTex = CResMgr::GetInst().GetTexture("Spoa_StandR", "texture\\monster\\Spoa\\Stand\\StandR.bmp");
	m_pAnimator->SetAnime("Stand_Right", pTex, Vec2(0, 0), Vec2(56, 56), Vec2(56, 0), 3, 0.2f);

	pTex = CResMgr::GetInst().GetTexture("Spoa_MoveL", "texture\\monster\\Spoa\\Move\\MoveL.bmp");
	m_pAnimator->SetAnime("Move_Left", pTex, Vec2(0, 0), Vec2(56, 56), Vec2(56, 0), 4, 0.2f);
	pTex = CResMgr::GetInst().GetTexture("Spoa_MoveR", "texture\\monster\\Spoa\\Move\\MoveR.bmp");
	m_pAnimator->SetAnime("Move_Right", pTex, Vec2(0, 0), Vec2(56, 56), Vec2(56, 0), 4, 0.2f);

	pTex = CResMgr::GetInst().GetTexture("Spoa_DieL", "texture\\monster\\Spoa\\Die\\DieL.bmp");
	m_pAnimator->SetAnime("Die_Left", pTex, Vec2(0, 0), Vec2(56, 56), Vec2(56, 0), 4, 0.2f);
	pTex = CResMgr::GetInst().GetTexture("Spoa_DieR", "texture\\monster\\Spoa\\Die\\DieR.bmp");
	m_pAnimator->SetAnime("Die_Right", pTex, Vec2(0, 0), Vec2(56, 56), Vec2(56, 0), 4, 0.2f);

	pTex = CResMgr::GetInst().GetTexture("Spoa_HitL", "texture\\monster\\Spoa\\Hit\\HitL.bmp");
	m_pAnimator->SetAnime("Hit_Left", pTex, Vec2(0, 0), Vec2(56, 56), Vec2(56, 0), 1, 0.2f);
	pTex = CResMgr::GetInst().GetTexture("Spoa_HitR", "texture\\monster\\Spoa\\Hit\\HitR.bmp");
	m_pAnimator->SetAnime("Hit_Right", pTex, Vec2(0, 0), Vec2(56, 56), Vec2(56, 0), 1, 0.2f);
}
