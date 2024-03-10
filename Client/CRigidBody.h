#pragma once
class CObject;
class CRigidBody
{
private:
	CObject*	m_pOwner;
	// 가속도 속도 힘 질량
	Vec2		m_vForce;		// 힘
	Vec2		m_vAcc;			// 가속도
	Vec2		m_vVelocity;	// 속도
	Vec2		m_vOtherAcc;

	double		m_fMaxSpeed;	// 최대 속력
	double		m_fFricCoeff;	// 마찰 계수
	double		m_fMass;		// 질량

	bool		m_bStop;
	Vec2		m_bStopDir;
public:
	CRigidBody();
	~CRigidBody();
public:
	void Update();
	void StopDir(const Vec2& _vDir);
	void SetMove() { m_bStop = false; }

	void SetForce(const Vec2& _vForce) { m_vForce = _vForce; }
	void SetAcc(const Vec2& _vAcc) { m_vAcc = _vAcc; }
	void SetOtherAcc(const Vec2& _vAcc) { m_vOtherAcc = _vAcc; }
	void SetVelocity(const Vec2& _vVelocity) { m_vVelocity = _vVelocity; }
	void SetMass(const double& _fMass) { m_fMass = _fMass; }
	void SetMaxSpeed(const double& _fMaxSpeed) { m_fMaxSpeed = _fMaxSpeed; }

	void AddForce(const Vec2& _vForce) { m_vForce += _vForce; }
	void AddAcc(const Vec2& _vAcc) { m_vAcc += _vAcc; }
	void AddVelocity(const Vec2 _vVelocity) { m_vVelocity += _vVelocity; }

	const Vec2& GetForce() { return m_vForce; }
	const Vec2& GetVelocity() { return m_vVelocity; }
	const Vec2& GetAcc() { return m_vAcc; }
	const double& GetMass() { return m_fMass; }
	const double& GetMaxSpeed() { return m_fMaxSpeed; }

	friend class CObject;
};

