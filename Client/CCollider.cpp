#include "pch.h"
#include "CCollider.h"
#include "CObject.h"

#include "CCamera.h"
#include "SelectGDI.h"

#include "CRigidBody.h"
#include "PixelCollider.h"
#include "CResMgr.h"
#include "Texture.h"
#include "CSceneMgr.h"
#include "CScene.h"
#include "Player.h"
#include "Monster.h"

#include "CGravity.h"

CCollider::CCollider()
	: m_pOwner(nullptr)
	, m_iRopeXPos(0)
	, m_bCollision(false)
{
}

CCollider::~CCollider()
{
}

void CCollider::OnCollision(CCollider* _pCollider)
{
	
}

void CCollider::OnCollisionEnter(CCollider* _pCollider)
{
	m_bCollision = true;
}

void CCollider::OnCollisionExit(CCollider* _pCollider)
{
	m_bCollision = false;
}

void CCollider::Update()
{
	m_vPos = m_pOwner->GetPos();
	static const vector<PixelCollider*> vec = CSceneMgr::GetInst().GetCurScene()->GetColVec();
	if (0 == vec.size())
		return;
	UINT iMaxX = ((Texture*)CSceneMgr::GetInst().GetCurScene()->GetTex())->GetWidth();
	UINT iMaxY = ((Texture*)CSceneMgr::GetInst().GetCurScene()->GetTex())->GetHeight();
	if (m_vPos.y + m_vScale.y - 5 >= iMaxY || m_vPos.y <= 0)
		return;
	int PixelIndex = 0;
	PIXEL info = {};
	bool check = false;
	bool checkLadder = false;
	bool checkOnlyPlayer = false;
	if ("Player" == m_pOwner->GetName())
	{
		Player* pOwner = dynamic_cast<Player*>(m_pOwner);
		assert(pOwner);
		Vec2 PosScale = m_vPos + m_vScale;
		for (int i = int(PosScale.y - 1); i <= int(PosScale.y); ++i)	// 땅에 닿는지 체크
		{
			for (int j = int(m_vPos.x); j <= int(PosScale.x); ++j)
			{
				PixelIndex = i * iMaxX + j;
				info = vec[PixelIndex]->GetPixelInfo();
				if ((255 == info.R && 0 == info.G && 0 == info.B))
				{
					check = true;
				}
			}
		}
		for (int i = int(m_vPos.y); i <= int(PosScale.y + 5); ++i)	// 로프가 있는지 체크
		{
			for (int j = int(m_vPos.x + (m_vScale.x / 2)) - 5; j <= int(m_vPos.x + (m_vScale.x / 2)) + 5; ++j)
			{
				PixelIndex = i * iMaxX + j;
				info = vec[PixelIndex]->GetPixelInfo();
				if ((0 == info.R && 255 == info.G && 0 == info.B))
				{
					m_iRopeXPos = j;
					checkLadder = true;
				}
			}
		}
		if (check)		// 땅에 있음
		{
			if (checkLadder)
			{
				pOwner->SetObjState(GROUP_COLLISION_STATE::LADDER_WITH_FLOOR);
				m_pOwner->GetGravity()->SetGravity(false);
			}
			else
			{
				if (GROUP_COLLISION_STATE::FLOOR != pOwner->GetObjState()
					&& pOwner->GetRigidBody()->GetVelocity().y >= 0)
				{
					pOwner->SetObjState(GROUP_COLLISION_STATE::FLOOR);
					m_pOwner->GetGravity()->SetGravity(false);
				}
			}
		}
		else
		{
			if (checkLadder)
			{
				pOwner->SetObjState(GROUP_COLLISION_STATE::LADDER);
			}
			else
			{
				pOwner->SetObjState(GROUP_COLLISION_STATE::AIR);
				m_pOwner->GetGravity()->SetGravity(true);
			}
			/*if (!m_pOwner->GetGravity()->IsOnGravity())
			{

			}*/
		}
		for (int i = int(m_vPos.y); i <= int(PosScale.y - 2); ++i)
		{
			for (int j = int(m_vPos.x); j <= int(m_vPos.x + 2); ++j)
			{
				PixelIndex = i * iMaxX + j;
				info = vec[PixelIndex]->GetPixelInfo();
				if ((255 == info.R && 0 == info.G && 0 == info.B))
				{
					Vec2 velocity = pOwner->GetRigidBody()->GetVelocity();
					Vec2 Dir = velocity.Normallize();
					if (-1.f <= Dir.x && Dir.x < 0)
					{
						pOwner->GetRigidBody()->StopDir(Vec2(-1.f, 0.f));
						return;
					}
				}
			}
			for (int j = int(PosScale.x); j >= int(PosScale.x - 2); --j)
			{
				PixelIndex = i * iMaxX + j;
				info = vec[PixelIndex]->GetPixelInfo();
				if ((255 == info.R && 0 == info.G && 0 == info.B))
				{
					Vec2 velocity = pOwner->GetRigidBody()->GetVelocity();
					Vec2 Dir = velocity.Normallize();
					if (0.f < Dir.x && Dir.x <= 1.f)
					{
						pOwner->GetRigidBody()->StopDir(Vec2(1.f, 0.f));
						return;
					}
				}
			}
		}
	}
	else if ("Monster" == m_pOwner->GetName())
	{
		Monster* pOwner = dynamic_cast<Monster*>(m_pOwner);
		assert(pOwner);
		for (int i = int(m_vPos.y + m_vScale.y - 1); i <= int(m_vPos.y + m_vScale.y); ++i)
		{
			for (int j = int(m_vPos.x); j <= int(m_vPos.x + m_vScale.x); ++j)
			{
				PixelIndex = i * iMaxX + j;
				info = vec[PixelIndex]->GetPixelInfo();
				if ((255 == info.R && 0 == info.G && 0 == info.B))
				{
					check = true;
				}
				else if ((0 == info.R && 255 == info.G && 255 == info.B))
				{
					checkOnlyPlayer = true;
				}
			}
		}
		if (check)
		{
			pOwner->SetObjState(GROUP_COLLISION_STATE::FLOOR);
			m_pOwner->GetGravity()->SetGravity(false);
		}
		else
		{
			pOwner->SetObjState(GROUP_COLLISION_STATE::AIR);
			m_pOwner->GetGravity()->SetGravity(true);
		}
		if (checkOnlyPlayer)
		{
			Vec2 Velocity = m_pOwner->GetRigidBody()->GetVelocity();
			m_pOwner->GetRigidBody()->SetVelocity(Vec2(-Velocity.x, Velocity.y));
		}
	}

}

void CCollider::Render(const HDC& _dc)
{
	Vec2 Pos = CCamera::GetInst().GetRenderPos(m_vPos);
	Rectangle(_dc
		, int(Pos.x)
		, int(Pos.y)
		, int(Pos.x + m_vScale.x)
		, int(Pos.y + m_vScale.y));
}

