#pragma once
class CCollider;
class CWeapon;
union CollisionKey
{
	struct
	{
		LONG x;
		LONG y;
	};
	ULONGLONG key;
};
class CCollisionMgr
{
	SINGLE(CCollisionMgr)
private:
	UINT					m_arrObj[(UINT)GROUP_OBJECT::END];
	map<ULONGLONG, bool>	m_mapCollisionKey;

	vector<CWeapon*>		m_vecAttackObj;
private:
	void CollisionCheck(const UINT& _i, const UINT& _j);
	bool IsCollision(CCollider* _obj1, CCollider* _obj2);
	bool RectToRect(CCollider* _obj1, CCollider* _obj2);
public:
	void Update();
	void ClearAll();
	void RequestAttackCheck(CWeapon* _obj1);
	void AttackCollisionCheck(CWeapon* _obj1);
	void RequestCheck(const GROUP_OBJECT& _obj1, const GROUP_OBJECT& _obj2);
};

