#pragma once
class CObject;
class CCollider
{
protected:
	Vec2		m_vPos;
	Vec2		m_vScale;

	int			m_iRopeXPos;

	bool		m_bCollision;

	string		m_strType;

	CObject*	m_pOwner;
public:
	CCollider();
	virtual ~CCollider();
public:
	void SetPos(const Vec2& _Pos) { m_vPos = _Pos; }
	void SetScale(const Vec2& _Scale) { m_vScale = _Scale; }
	void SetOwner(CObject* _pOwner) { m_pOwner = _pOwner; }

	CObject* GetOwner() { return m_pOwner; }
	const int& GetRopeXPos() { return m_iRopeXPos; }
	const Vec2& GetPos() { return m_vPos; }
	const Vec2& GetScale() { return m_vScale; }
	const string& GetType() { return m_strType; }
	const bool& IsCollision() { return m_bCollision; }


public:
	virtual void Update();
	virtual void Render(const HDC& _dc);
	virtual void OnCollision(CCollider* _pCollider);
	virtual void OnCollisionEnter(CCollider* _pCollider);
	virtual void OnCollisionExit(CCollider* _pCollider);
	friend class CObject;
};

