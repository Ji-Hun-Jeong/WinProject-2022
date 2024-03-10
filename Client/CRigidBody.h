#pragma once
class CObject;
class CRigidBody
{
private:
	CObject*	m_pOwner;
	// ���ӵ� �ӵ� �� ����
	Vec2		m_vForce;		// ��
	Vec2		m_vAcc;			// ���ӵ�
	Vec2		m_vVelocity;	// �ӵ�
	Vec2		m_vOtherAcc;

	double		m_fMaxSpeed;	// �ִ� �ӷ�
	double		m_fFricCoeff;	// ���� ���
	double		m_fMass;		// ����

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

