#include "pch.h"
#include "Player.h"
#include "CObject.h"

#include "CCamera.h"

#include "CSceneMgr.h"
#include "CScene.h"
#include "CGravity.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"

#include "CAnimator.h"
#include "CCollider.h"

#include "CCollider.h"
#include "AttackCollider.h"
#include "CCollisionMgr.h"

#include "CResMgr.h"
#include "CRes.h"

#include "CRigidBody.h"
#include "CWeapon.h"

Player::Player()
	: m_ePlayerState(GROUP_PLAYER_STATE::ALERT)
	, m_eState(GROUP_COLLISION_STATE::AIR)
{
	
}

Player::Player(const Player& _other)
	: CObject(_other)
	, m_ePlayerState(GROUP_PLAYER_STATE::ALERT)
	, m_eState(GROUP_COLLISION_STATE::AIR)
{
}

Player::~Player()
{
	
}

void Player::LoadAnime()
{
	/// <summary>
	/// Stand
	/// </summary>
	CRes* pTex = CResMgr::GetInst().GetTexture("Player_StandL", "texture\\charactor\\stand\\left\\StandL.bmp");
	m_pAnimator->SetAnime("Stand_Left", pTex, Vec2(0.f, 0.f), Vec2(60.f, 80.f), Vec2(60.f, 0.f), 3, 0.1f);
	pTex = CResMgr::GetInst().GetTexture("Player_StandR", "texture\\charactor\\stand\\right\\StandR.bmp");
	m_pAnimator->SetAnime("Stand_Right", pTex, Vec2(0.f, 0.f), Vec2(60.f, 80.f), Vec2(60.f, 0.f), 3, 0.1f);
	/// <summary>
	/// Attack
	/// </summary>
	pTex = CResMgr::GetInst().GetTexture("Player_AttackL", "texture\\charactor\\attack\\left\\AttackL.bmp");
	m_pAnimator->SetAnime("Attack_Left", pTex, Vec2(0.f, 0.f), Vec2(60.f, 80.f), Vec2(60.f, 0.f), 3, 0.3f);
	pTex = CResMgr::GetInst().GetTexture("Player_AttackR", "texture\\charactor\\attack\\right\\AttackR.bmp");
	m_pAnimator->SetAnime("Attack_Right", pTex, Vec2(0.f, 0.f), Vec2(60.f, 80.f), Vec2(60.f, 0.f), 3, 0.3f);
	/// <summary>
	/// Alert
	/// </summary>
	pTex = CResMgr::GetInst().GetTexture("Player_AlertL", "texture\\charactor\\alert\\left\\AlertL.bmp");
	m_pAnimator->SetAnime("Alert_Left", pTex, Vec2(0.f, 0.f), Vec2(60.f,80.f), Vec2(60.f, 0.f), 3, 0.1f);
	pTex = CResMgr::GetInst().GetTexture("Player_AlertR", "texture\\charactor\\alert\\right\\AlertR.bmp");
	m_pAnimator->SetAnime("Alert_Right", pTex, Vec2(0.f, 0.f), Vec2(60.f, 80.f), Vec2(60.f, 0.f), 3, 0.1f);
	/// <summary>
	/// Walk
	/// </summary>
	pTex = CResMgr::GetInst().GetTexture("Player_WalkL", "texture\\charactor\\walk\\left\\WalkL.bmp");
	m_pAnimator->SetAnime("Walk_Left", pTex, Vec2(0.f, 0.f), Vec2(60.f, 80.f), Vec2(60.f, 0.f), 4, 0.2f);
	pTex = CResMgr::GetInst().GetTexture("Player_WalkR", "texture\\charactor\\walk\\right\\WalkR.bmp");
	m_pAnimator->SetAnime("Walk_Right", pTex, Vec2(0.f, 0.f), Vec2(60.f, 80.f), Vec2(60.f, 0.f), 4, 0.2f);
	/// <summary>
	/// Rope, Ladder
	/// </summary>
	pTex = CResMgr::GetInst().GetTexture("Player_Rope", "texture\\charactor\\rope\\Rope.bmp");
	m_pAnimator->SetAnime("Rope", pTex, Vec2(0.f, 0.f), Vec2(60.f, 80.f), Vec2(60.f, 0.f), 2, 0.3f);
	pTex = CResMgr::GetInst().GetTexture("Player_Ladder", "texture\\charactor\\ladder\\Ladder.bmp");
	m_pAnimator->SetAnime("Ladder", pTex, Vec2(0.f, 0.f), Vec2(60.f, 80.f), Vec2(60.f, 0.f), 2, 0.3f);
	/// <summary>
	/// ProneAttack
	/// </summary>
	pTex = CResMgr::GetInst().GetTexture("Player_ProneAttackL", "texture\\charactor\\prone\\attack\\ProneAttackL.bmp");
	m_pAnimator->SetAnime("ProneAttack_Left", pTex, Vec2(0.f, 0.f), Vec2(90.f, 60.f), Vec2(90.f, 0.f), 2, 0.1f);
	pTex = CResMgr::GetInst().GetTexture("Player_ProneAttackR", "texture\\charactor\\prone\\attack\\ProneAttackR.bmp");
	m_pAnimator->SetAnime("ProneAttack_Right", pTex, Vec2(0.f, 0.f), Vec2(90.f, 60.f), Vec2(90.f, 0.f), 2, 0.1f);
	/// <summary>
	/// Prone
	/// </summary>
	pTex = CResMgr::GetInst().GetTexture("Player_ProneL", "texture\\charactor\\prone\\left\\ProneL.bmp");
	m_pAnimator->SetAnime("Prone_Left", pTex, Vec2(0.f, 0.f), Vec2(90.f, 60.f), Vec2(90.f, 0.f), 1, 0.1f);
	pTex = CResMgr::GetInst().GetTexture("Player_ProneR", "texture\\charactor\\prone\\right\\ProneR.bmp");
	m_pAnimator->SetAnime("Prone_Right", pTex, Vec2(0.f, 0.f), Vec2(90.f, 60.f), Vec2(90.f, 0.f), 1, 0.1f);
	/// <summary>
	/// Jump
	/// </summary>
	pTex = CResMgr::GetInst().GetTexture("Player_JumpL", "texture\\charactor\\jump\\left\\JumpL.bmp");
	m_pAnimator->SetAnime("Jump_Left", pTex, Vec2(0.f, 0.f), Vec2(60.f, 80.f), Vec2(60.f, 0.f), 1, 0.1f);
	pTex = CResMgr::GetInst().GetTexture("Player_JumpR", "texture\\charactor\\jump\\right\\JumpR.bmp");
	m_pAnimator->SetAnime("Jump_Right", pTex, Vec2(0.f, 0.f), Vec2(60.f, 80.f), Vec2(60.f, 0.f), 1, 0.1f);
	/// <summary>
	/// Dead
	/// </summary>
	pTex = CResMgr::GetInst().GetTexture("Player_DeadL", "texture\\charactor\\dead\\left\\DeadL.bmp");
	m_pAnimator->SetAnime("Dead_Left", pTex, Vec2(0.f, 0.f), Vec2(60.f, 80.f), Vec2(60.f, 0.f), 1, 0.1f);
	pTex = CResMgr::GetInst().GetTexture("Player_DeadR", "texture\\charactor\\dead\\right\\DeadR.bmp");
	m_pAnimator->SetAnime("Dead_Right", pTex, Vec2(0.f, 0.f), Vec2(60.f, 80.f), Vec2(60.f, 0.f), 1, 0.1f);

}


void Player::AttackCheck()
{
	if (KEYCHECK(A, TAP) && m_ePlayerState != GROUP_PLAYER_STATE::ATTACK)
	{
		// weapon쪽에 어떤 공격인지 전달
		m_ePlayerState = GROUP_PLAYER_STATE::ATTACK;
		TakeAttack("Normal");
	}
}

void Player::FinishAttack()
{
	m_pWeapon->FinishAttack();
}

void Player::Init()
{
	CObject::Init();
	m_strName = "Player";

	CCamera::GetInst().Setplayer(this);

	CreateGravity();					// 중력 생성

	CreateRigidBody();
	m_pRigidBody->SetMass(1.f);

	CreateCollider();
	m_pCollider->SetScale(Vec2(50.f, 50.f));

	CreateAnimator();
	LoadAnime();
	m_pAnimator->SetCurAnime("Stand_Right",true);

	CreateWeapon();
	AttackInfo info = {};
	info.Offset = Vec2(m_pCollider->GetScale().x, 0.f);
	info.Range = Vec2(50.f, 50.f);
	info.Time = 1.f;
	InputAttackData("Normal", info);
}

void Player::Update()
{
	if (KEYCHECK(LEFT, HOLD) && GROUP_PLAYER_STATE::ATTACK != m_ePlayerState)
	{
		/*if (GROUP_PLAYER_STATE::JUMP_RIGHT == m_ePlayerState)
		{
			m_pRigidBody->AddForce(Vec2(700.f, 0.f));
		}*/
		if (GROUP_PLAYER_STATE::CLIMB != m_ePlayerState)
		{
			m_iDir = -1;
			m_pRigidBody->AddVelocity(Vec2(-200.f, 0.f));
			m_pRigidBody->AddForce(Vec2(-200.f, 0.f));
		}
	}
	if (KEYCHECK(RIGHT, HOLD) && GROUP_PLAYER_STATE::ATTACK != m_ePlayerState)
	{
		/*if (GROUP_PLAYER_STATE::JUMP_LEFT == m_ePlayerState)
		{
			m_pRigidBody->AddForce(Vec2(-700.f, 0.f));
		}*/
		if (GROUP_PLAYER_STATE::CLIMB != m_ePlayerState)
		{
			m_iDir = 1;
			m_pRigidBody->AddVelocity(Vec2(200.f, 0.f));
			m_pRigidBody->AddForce(Vec2(200.f, 0.f));
		}
	}
	if (KEYCHECK(UP, HOLD) && GROUP_PLAYER_STATE::ATTACK != m_ePlayerState)
	{
		if (GROUP_COLLISION_STATE::LADDER == m_eState|| GROUP_COLLISION_STATE::LADDER_WITH_FLOOR == m_eState)
		{
			m_vPos.x += m_pCollider->GetRopeXPos() - (m_vPos.x + m_vScale.x / 2.f) + 1;
			m_pGravity->SetGravity(false);
			m_pRigidBody->SetVelocity(Vec2(0, -200.f));
			m_pRigidBody->AddForce(Vec2(0.f, -200.f));
		}
	}
	if (KEYCHECK(DOWN, HOLD) && GROUP_PLAYER_STATE::ATTACK != m_ePlayerState)
	{
		if (GROUP_COLLISION_STATE::LADDER == m_eState || GROUP_COLLISION_STATE::LADDER_WITH_FLOOR == m_eState)
		{
			m_vPos.x += m_pCollider->GetRopeXPos() - (m_vPos.x + m_vScale.x / 2.f) + 1;
			m_pGravity->SetGravity(false);
			m_pRigidBody->SetVelocity(Vec2(0, 200.f));
			m_pRigidBody->AddForce(Vec2(0.f, 200.f));
		}
	}
	if (KEYCHECK(SPACE, TAP))
	{
		if (!m_pGravity->IsOnGravity())
		{
			m_pRigidBody->AddVelocity(Vec2(0, -450.f));
			m_pRigidBody->AddForce(Vec2(0.f, -200.f));
		}
	}
	// 이러고 컴포넌트 업데이트
}

void Player::ComponentUpdate()
{
	/*
	if (m_pRigidBody)
		m_pRigidBody->Update();
	if (m_pCollider)
		m_pCollider->Update();
	if (m_pGravity)
		m_pGravity->Update();
	*/
	CObject::ComponentUpdate();
	if (m_pWeapon)
	{
		CCollisionMgr::GetInst().RequestAttackCheck(m_pWeapon);
		m_pWeapon->Update();
	}
	StateUpdate();
	AnimationUpdate();
}

void Player::Render(const HDC& _dc)
{
	/*Vec2 RenderPos = CCamera::GetInst().GetRenderPos(m_vPos);
	Rectangle(_dc
		, int(RenderPos.x - m_vScale.x / 2.f)
		, int(RenderPos.y - m_vScale.y)
		, int(RenderPos.x + m_vScale.x / 2.f)
		, int(RenderPos.y));*/
	if (m_pCollider)
		m_pCollider->Render(_dc);
	if (m_pAnimator)
		m_pAnimator->Play(_dc);
	if (m_pWeapon)
		m_pWeapon->Render(_dc);

}

void Player::OnCollision(CObject* pObj)
{
	m_pCollider->OnCollision(pObj->GetCollider());
}

void Player::OnCollisionEnter(CObject* pObj)
{
	m_bAir = false;
	m_pCollider->OnCollisionEnter(pObj->GetCollider());
}

void Player::OnCollisionExit(CObject* pObj)
{
	m_bAir = true;
	m_pCollider->OnCollisionExit(pObj->GetCollider());
}

void Player::AnimationUpdate()
{
	if (1 == m_iDir)
	{
		switch (m_ePlayerState)
		{
		case GROUP_PLAYER_STATE::ALERT:
			m_pAnimator->SetCurAnime("Alert_Right",(UINT)GROUP_ANIMATION_REPEAT::REPEAT);
			break;
		case GROUP_PLAYER_STATE::STAND:
			m_pAnimator->SetCurAnime("Stand_Right", (UINT)GROUP_ANIMATION_REPEAT::REPEAT);
			break;
		case GROUP_PLAYER_STATE::WALK:
			m_pAnimator->SetCurAnime("Walk_Right", (UINT)GROUP_ANIMATION_REPEAT::REPEAT);
			break;
		case GROUP_PLAYER_STATE::JUMP:
			m_pAnimator->SetCurAnime("Jump_Right", (UINT)GROUP_ANIMATION_REPEAT::REPEAT);
			break;
		case GROUP_PLAYER_STATE::CLIMB:
			m_pAnimator->SetCurAnime("Rope", (UINT)GROUP_ANIMATION_REPEAT::REPEAT);
			break;
		case GROUP_PLAYER_STATE::DOWN:
			m_pAnimator->SetCurAnime("Rope", (UINT)GROUP_ANIMATION_REPEAT::REPEAT);
			break;
		case GROUP_PLAYER_STATE::ATTACK:
			m_pAnimator->SetCurAnime("Attack_Right", (UINT)GROUP_ANIMATION_REPEAT::RETURN);
			break;
		case GROUP_PLAYER_STATE::DEAD:
			m_pAnimator->SetCurAnime("Dead_Right", (UINT)GROUP_ANIMATION_REPEAT::REPEAT);
			break;
		default:
			break;
		}
	}
	else if (-1 == m_iDir)
	{
		switch (m_ePlayerState)
		{
		case GROUP_PLAYER_STATE::ALERT:
			m_pAnimator->SetCurAnime("Alert_Left", (UINT)GROUP_ANIMATION_REPEAT::REPEAT);
			break;
		case GROUP_PLAYER_STATE::STAND:
			m_pAnimator->SetCurAnime("Stand_Left", (UINT)GROUP_ANIMATION_REPEAT::REPEAT);
			break;
		case GROUP_PLAYER_STATE::WALK:
			m_pAnimator->SetCurAnime("Walk_Left", (UINT)GROUP_ANIMATION_REPEAT::REPEAT);
			break;
		case GROUP_PLAYER_STATE::JUMP:
			m_pAnimator->SetCurAnime("Jump_Left", (UINT)GROUP_ANIMATION_REPEAT::REPEAT);
			break;
		case GROUP_PLAYER_STATE::CLIMB:
			m_pAnimator->SetCurAnime("Rope", (UINT)GROUP_ANIMATION_REPEAT::REPEAT);
			break;
		case GROUP_PLAYER_STATE::DOWN:
			m_pAnimator->SetCurAnime("Rope", (UINT)GROUP_ANIMATION_REPEAT::REPEAT);
			break;
		case GROUP_PLAYER_STATE::ATTACK:
			m_pAnimator->SetCurAnime("Attack_Left", (UINT)GROUP_ANIMATION_REPEAT::RETURN);
			break;
		case GROUP_PLAYER_STATE::DEAD:
			m_pAnimator->SetCurAnime("Dead_Left", (UINT)GROUP_ANIMATION_REPEAT::REPEAT);
			break;
		default:
			break;
		}
	}
}

void Player::StateUpdate()
{
	switch (m_eState)
	{
	case GROUP_COLLISION_STATE::FLOOR:
	{
		switch (m_ePlayerState)
		{
		case GROUP_PLAYER_STATE::ALERT:
		{
			if (KEYCHECK(SPACE, TAP))
			{
				m_ePlayerState = GROUP_PLAYER_STATE::JUMP;
			}
			else
			{
				if (KEYCHECK(LEFT, HOLD))
				{
					m_ePlayerState = GROUP_PLAYER_STATE::WALK;
				}
				else if (KEYCHECK(RIGHT, HOLD))
				{
					m_ePlayerState = GROUP_PLAYER_STATE::WALK;
				}
				else
				{
					m_ePlayerState = GROUP_PLAYER_STATE::STAND;
				}
			}
			AttackCheck();
		}
		break;
		case GROUP_PLAYER_STATE::STAND:
		{
			if (KEYCHECK(SPACE, TAP))
			{
				m_ePlayerState = GROUP_PLAYER_STATE::JUMP;
			}
			else
			{
				if (KEYCHECK(LEFT, HOLD))
				{
					m_ePlayerState = GROUP_PLAYER_STATE::WALK;
				}
				else if (KEYCHECK(RIGHT, HOLD))
				{
					m_ePlayerState = GROUP_PLAYER_STATE::WALK;
				}
				else
				{
					m_ePlayerState = GROUP_PLAYER_STATE::STAND;
				}
			}
			AttackCheck();
		}
		break;
		case GROUP_PLAYER_STATE::WALK:
		{
			if (KEYCHECK(SPACE, TAP))
			{
				m_ePlayerState = GROUP_PLAYER_STATE::JUMP;
			}
			else
			{
				if (KEYCHECK(LEFT, HOLD))
				{
					m_ePlayerState = GROUP_PLAYER_STATE::WALK;
				}
				else if (KEYCHECK(RIGHT, HOLD))
				{
					m_ePlayerState = GROUP_PLAYER_STATE::WALK;
				}
				else
				{
					m_ePlayerState = GROUP_PLAYER_STATE::STAND;
				}
			}
			AttackCheck();
		}
		break;
		case GROUP_PLAYER_STATE::JUMP:
		{
			if (KEYCHECK(SPACE, TAP))
			{
				m_ePlayerState = GROUP_PLAYER_STATE::JUMP;
			}
			else
			{
				if (KEYCHECK(LEFT, HOLD))
				{
					m_ePlayerState = GROUP_PLAYER_STATE::WALK;
				}
				else if (KEYCHECK(RIGHT, HOLD))
				{
					m_ePlayerState = GROUP_PLAYER_STATE::WALK;
				}
				else
				{
					m_ePlayerState = GROUP_PLAYER_STATE::STAND;
				}
			}
			AttackCheck();
		}
		break;
		case GROUP_PLAYER_STATE::ATTACK:
		{
			/*if (KEYCHECK(SPACE, TAP))
			{
				m_ePlayerState = GROUP_PLAYER_STATE::JUMP;
			}
			else
			{
				if (KEYCHECK(LEFT, HOLD))
				{
					m_ePlayerState = GROUP_PLAYER_STATE::JUMP;
				}
				else if (KEYCHECK(RIGHT, HOLD))
				{
					m_ePlayerState = GROUP_PLAYER_STATE::JUMP;
				}
				else if (KEYCHECK(A, TAP))
				{
					m_ePlayerState = GROUP_PLAYER_STATE::ATTACK;
				}
				else
				{
					m_ePlayerState = GROUP_PLAYER_STATE::JUMP;
				}
			}*/
		}
		break;
		case GROUP_PLAYER_STATE::DOWN:
			m_ePlayerState = GROUP_PLAYER_STATE::STAND;
			break;
		case GROUP_PLAYER_STATE::DEAD:
			m_ePlayerState = GROUP_PLAYER_STATE::DEAD;
			break;
		default:
			break;
		}

	}
	break;
	case GROUP_COLLISION_STATE::AIR:
	{
		if (m_ePlayerState == GROUP_PLAYER_STATE::ATTACK)
		{
			/*if (KEYCHECK(SPACE, TAP))
			{
				m_ePlayerState = GROUP_PLAYER_STATE::JUMP;
			}
			else
			{
				if (KEYCHECK(LEFT, HOLD))
				{
					m_ePlayerState = GROUP_PLAYER_STATE::JUMP;
				}
				else if (KEYCHECK(RIGHT, HOLD))
				{
					m_ePlayerState = GROUP_PLAYER_STATE::JUMP;
				}
				else if (KEYCHECK(A, TAP))
				{
					m_ePlayerState = GROUP_PLAYER_STATE::ATTACK;
				}
				else
				{
					m_ePlayerState = GROUP_PLAYER_STATE::JUMP;
				}
			}*/
			float fAccTime = m_pWeapon->GetAccTime();
			float fAttackTime = m_pWeapon->GetAttackTime();
			fAccTime += dt;
			if (fAttackTime <= fAccTime)
			{
				m_ePlayerState = GROUP_PLAYER_STATE::ALERT;
			}
		}
		else if (m_ePlayerState == GROUP_PLAYER_STATE::DEAD)
		{
			m_ePlayerState = GROUP_PLAYER_STATE::DEAD;
		}
		else
		{
			m_ePlayerState = GROUP_PLAYER_STATE::JUMP;
		}
		AttackCheck();
	}
	break;
	case GROUP_COLLISION_STATE::ONLYPLAYER:
	{

	}
	break;
	case GROUP_COLLISION_STATE::LADDER:
	{
		switch (m_ePlayerState)
		{
		case GROUP_PLAYER_STATE::ALERT:
			if (KEYCHECK(UP, HOLD))
			{
				m_ePlayerState = GROUP_PLAYER_STATE::CLIMB;
			}
			break;
		case GROUP_PLAYER_STATE::STAND:
			if (KEYCHECK(UP, HOLD))
			{
				m_ePlayerState = GROUP_PLAYER_STATE::CLIMB;
			}
			break;
		case GROUP_PLAYER_STATE::WALK:
			if (KEYCHECK(UP, HOLD))
			{
				m_ePlayerState = GROUP_PLAYER_STATE::CLIMB;
			}
			break;
		case GROUP_PLAYER_STATE::JUMP:
		{
			if (KEYCHECK(UP, HOLD))
			{
				m_ePlayerState = GROUP_PLAYER_STATE::CLIMB;
			}
		}
		break;
		case GROUP_PLAYER_STATE::DEAD:
			m_ePlayerState = GROUP_PLAYER_STATE::DEAD;
			break;
		default:
			break;
		}

	}
	break;
	case GROUP_COLLISION_STATE::LADDER_WITH_FLOOR:
	{
		switch (m_ePlayerState)
		{
		case GROUP_PLAYER_STATE::ALERT:
		{
			if (KEYCHECK(UP, HOLD))
			{
				m_ePlayerState = GROUP_PLAYER_STATE::CLIMB;
			}
			// 아래로 갈때 로프 모션 대신 땅에 닿으면 내리게 해야됌....
		}
		break;
		case GROUP_PLAYER_STATE::STAND:
		{
			if (KEYCHECK(UP, HOLD))
			{
				m_ePlayerState = GROUP_PLAYER_STATE::CLIMB;
			}
		}
		break;
		case GROUP_PLAYER_STATE::WALK:
		{
			if (KEYCHECK(UP, HOLD))
			{
				m_ePlayerState = GROUP_PLAYER_STATE::CLIMB;
			}
		}
		break;
		case GROUP_PLAYER_STATE::JUMP:
		{
			if (KEYCHECK(UP, HOLD))
			{
				m_ePlayerState = GROUP_PLAYER_STATE::CLIMB;
			}
			else
			{
				m_ePlayerState = GROUP_PLAYER_STATE::STAND;
			}
		}
		break;
		case GROUP_PLAYER_STATE::CLIMB:
			if (KEYCHECK(UP, HOLD))
			{
				m_ePlayerState = GROUP_PLAYER_STATE::CLIMB;
			}
			break;
		case GROUP_PLAYER_STATE::DOWN:
		{

		}
		break;
		case GROUP_PLAYER_STATE::ATTACK:
		{
			/*if (KEYCHECK(SPACE, TAP))
			{
				m_ePlayerState = GROUP_PLAYER_STATE::JUMP;
			}
			else
			{
				if (KEYCHECK(LEFT, HOLD))
				{
					m_ePlayerState = GROUP_PLAYER_STATE::JUMP;
				}
				else if (KEYCHECK(RIGHT, HOLD))
				{
					m_ePlayerState = GROUP_PLAYER_STATE::JUMP;
				}
				else if (KEYCHECK(A, TAP))
				{
					m_ePlayerState = GROUP_PLAYER_STATE::ATTACK;
				}
				else
				{
					m_ePlayerState = GROUP_PLAYER_STATE::JUMP;
				}
			}*/
		}
		break;
		case GROUP_PLAYER_STATE::DEAD:
			m_ePlayerState = GROUP_PLAYER_STATE::DEAD;
			break;
		default:
			break;
		}
	}
	break;
	case GROUP_COLLISION_STATE::END:
		break;
	default:
		break;
	}
}