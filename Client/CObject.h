#pragma once
class CAnimator;
class CCollider;
class CRigidBody;
class CGravity;
class CRes;
class CWeapon;
class CObject
{
protected:
	string					m_strName;
	Vec2					m_vPos;
	Vec2					m_vScale;

	UINT					m_iNum;
	int						m_iDir;

	
	CRes*					m_pTex;

	bool					m_bAlive;
	bool					m_bAir;
	bool					m_bStop;	// ??
	bool					m_bInCam;

	// 충돌체 
	CCollider*				m_pCollider;
	CWeapon*				m_pWeapon;

	// 강체
	CRigidBody*				m_pRigidBody;

	// 애니메이터
	CAnimator*				m_pAnimator;

	CGravity*				m_pGravity;

public:
	CObject();
	CObject(const CObject& _other);
	virtual ~CObject();
public:
	const Vec2& GetPos() { return m_vPos; }
	const Vec2& GetScale() { return m_vScale; }
	const UINT& GetNum() { return m_iNum; }
	const string& GetName() { return m_strName; }
	const int& GetDir() { return m_iDir; }
	bool IsDead() { return !m_bAlive; }
	bool IsAir() { return m_bAir; }
	bool IsStop() { return m_bStop; }
	bool IsInCam() { return m_bInCam; }

	virtual CCollider* GetCollider() { return m_pCollider; }
	CRigidBody* GetRigidBody() { return m_pRigidBody; }
	CGravity* GetGravity() { return m_pGravity; }
	CAnimator* GetAnimator() { return m_pAnimator; }
public:
	void SetPos(const Vec2& _vPos) { m_vPos = _vPos; }
	void SetScale(const Vec2& _vScale) { m_vScale = _vScale; }
	void SetDead() { m_bAlive = false; }
	void SetAir(const bool& _bAir) { m_bAir = _bAir; }
	void SetStop(const bool& _bStop) { m_bStop = _bStop; }
	void AddPos(const Vec2& _vPos) { m_vPos += _vPos; }

	void InputAttackData(const string& _strName, const AttackInfo& _eAttackInfo);
	void TakeAttack(const string& _strName);


	/*virtual void CollisionToPixel(const PIXEL& _eInfo, const GROUP_COLLISION_STATE& _eType) {}*/

	void CreateAnimator();
	void CreateCollider();
	void CreateRigidBody();
	void CreateGravity();
	void CreateWeapon();

	virtual void Save(FILE* _p);
	virtual void Load(FILE* _p);

public:
	// 만들어질 때 해야할 일 : 이름 정해주기 
	virtual void Init();	
	virtual void ComponentUpdate();

	virtual void OnCollision(CObject* pObj);
	virtual void OnCollisionEnter(CObject* pObj);
	virtual void OnCollisionExit(CObject* pObj);

	virtual void AnimationUpdate();
	virtual void StateUpdate();

	virtual void Update() = 0;
	virtual void Render(const HDC& _dc) = 0;
	virtual CObject* Clone() = 0;
};

