#include "pch.h"
#include "CCollisionMgr.h"
#include "CSceneMgr.h"
#include "CScene.h"
#include "CObject.h"
#include "CCollider.h"
#include "PixelCollider.h"
#include "Texture.h"
#include "CWeapon.h"
#include "AttackCollider.h"
CCollisionMgr CCollisionMgr::m_mgr;
CCollisionMgr::CCollisionMgr()
	: m_arrObj{}
{}
CCollisionMgr::~CCollisionMgr()
{}

void CCollisionMgr::Update()
{
	for (UINT i = 0; i < (UINT)GROUP_OBJECT::END; ++i)
	{
		for (UINT j = i; j < (UINT)GROUP_OBJECT::END; ++j)
		{
			if ((m_arrObj[i] & (1 << j)))
			{
				CollisionCheck(i, j);
			}
		}
	}
	for (size_t i = 0; i < m_vecAttackObj.size(); ++i)
	{
		AttackCollisionCheck(m_vecAttackObj[i]);
	}
	m_vecAttackObj.clear();
}

void CCollisionMgr::CollisionCheck(const UINT& _i, const UINT& _j)
{
	const auto& vec1 = CSceneMgr::GetInst().GetCurScene()->GetVec((GROUP_OBJECT)_i);
	const auto& vec2 = CSceneMgr::GetInst().GetCurScene()->GetVec((GROUP_OBJECT)_j);
	CollisionKey key = {};
	for (UINT i = 0; i < vec1.size(); ++i)
	{
		for (UINT j = 0; j < vec2.size(); ++j)
		{
			if (vec1[i]->GetCollider() && vec2[j]->GetCollider())
			{
				key.x = vec1[i]->GetNum();
				key.y = vec2[j]->GetNum();
				auto iter = m_mapCollisionKey.find(key.key);
				if (iter == m_mapCollisionKey.end())
				{
					m_mapCollisionKey.insert(make_pair(key.key, false));
					iter = m_mapCollisionKey.find(key.key);
				}
				if (IsCollision(vec1[i]->GetCollider(), vec2[j]->GetCollider()))	// 이번 프레임에 충돌
				{
					if (iter->second)		// 이전 프레임에도 충돌
					{
						if (vec1[i]->IsDead() || vec2[j]->IsDead())	// 만약 충돌중이지만 이번 프레임에 죽을 놈이면 exit발생
						{
							vec1[i]->OnCollisionExit(vec2[j]);
							vec2[j]->OnCollisionExit(vec1[i]);
							iter->second = false;
						}
						else
						{
							vec1[i]->OnCollision(vec2[j]);
							vec2[j]->OnCollision(vec1[i]);
						}
					}
					else					// 이전 프레임에는 충돌하지 않음
					{
						if (!vec1[i]->IsDead() && !vec2[j]->IsDead())
						{
							vec1[i]->OnCollisionEnter(vec2[j]);
							vec2[j]->OnCollisionEnter(vec1[i]);
							iter->second = true;
						}
					}
				}
				else			// 이번 프레임에 충돌하지 않음
				{
					if (iter->second)
					{
						vec1[i]->OnCollisionExit(vec2[j]);
						vec2[j]->OnCollisionExit(vec1[i]);
					}
					iter->second = false;
				}
			}
		}
	}
}

bool CCollisionMgr::IsCollision(CCollider* _obj1, CCollider* _obj2)
{
	if ("Rect" == _obj1->GetType() && "Rect" == _obj2->GetType())	// RectToRect
	{
		return RectToRect(_obj1, _obj2);
	}
	return false;
}

bool CCollisionMgr::RectToRect(CCollider* _obj1, CCollider* _obj2)
{
	Vec2 Pos1 = {};
	Vec2 Pos2 = {};
	Vec2 Scale1 = {};
	Vec2 Scale2 = {};
	Pos1 = _obj1->GetPos();
	Scale1 = _obj1->GetScale();
	Pos2 = _obj2->GetPos();
	Scale2 = _obj2->GetScale();
	if (abs((Pos1.x + Scale1.x / 2) - (Pos2.x + Scale2.x / 2)) <= (Scale1.x / 2 + Scale2.x / 2) && abs((Pos1.y + Scale1.y / 2) - (Pos2.y + Scale2.y / 2)) <= (Scale1.y / 2 + Scale2.y / 2))
	{
		return true;
	}
	return false;
}

void CCollisionMgr::RequestCheck(const GROUP_OBJECT& _obj1, const GROUP_OBJECT& _obj2)
{
	UINT row = 0;
	UINT col = 0;
	if (_obj1 < _obj2)
	{
		row = (UINT)_obj1;
		col = (UINT)_obj2;
	}
	else
	{
		row = (UINT)_obj2;
		col = (UINT)_obj1;
	}
	m_arrObj[row] = 1 << col;
}

void CCollisionMgr::ClearAll()
{
	for (UINT i = 0; i < (UINT)GROUP_OBJECT::END; ++i)
	{
		m_arrObj[i] = 0;
	}
}

void CCollisionMgr::RequestAttackCheck(CWeapon* _obj1)
{
	m_vecAttackObj.push_back(_obj1);
}

void CCollisionMgr::AttackCollisionCheck(CWeapon* _obj1)
{
	CCollider* p = ((CObject*)_obj1)->GetCollider();
	static const vector<CObject*>& vec = CSceneMgr::GetInst().GetCurScene()->GetVec(GROUP_OBJECT::MONSTER);
	CollisionKey key = {};
	for (size_t i = 0; i < vec.size(); ++i)
	{
		if (p && vec[i]->GetCollider())
		{
			key.x = _obj1->GetNum();
			key.y = vec[i]->GetNum();
			auto iter = m_mapCollisionKey.find(key.key);
			if (iter == m_mapCollisionKey.end())
			{
				m_mapCollisionKey.insert(make_pair(key.key, false));
				iter = m_mapCollisionKey.find(key.key);
			}
			if (IsCollision(p, vec[i]->GetCollider()))
			{
				if (iter->second)		// 이전 프레임에도 충돌
				{
					if (_obj1->IsDead() || vec[i]->IsDead())	// 만약 충돌중이지만 이번 프레임에 죽을 놈이면 exit발생
					{
						_obj1->OnCollisionExit(vec[i]);
						vec[i]->OnCollisionExit(_obj1);
						iter->second = false;
					}
					else
					{
						_obj1->OnCollision(vec[i]);
						vec[i]->OnCollision(_obj1);
					}
				}
				else					// 이전 프레임에는 충돌하지 않음
				{
					if (!_obj1->IsDead() && !vec[i]->IsDead())
					{
						_obj1->OnCollisionEnter(vec[i]);
						vec[i]->OnCollisionEnter(_obj1);
						iter->second = true;
					}
				}
			}
			else			// 이번 프레임에 충돌하지 않음
			{
				if (iter->second)
				{
					_obj1->OnCollisionExit(vec[i]);
					vec[i]->OnCollisionExit(_obj1);
				}
				iter->second = false;
			}
		}
	}
}

