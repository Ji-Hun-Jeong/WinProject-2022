#pragma once
class CObject;
class CGravity
{
private:
	CObject* m_pOwner;
	Vec2	 m_vVelocity;

	float	 m_fGravity;

	bool	 m_bOn;
public:
	CGravity();
	~CGravity();
public:
	void Update();
	void SetGravity(const bool& _bGravity) { m_bOn = _bGravity; }
	const bool& IsOnGravity() { return m_bOn; }
	friend class CObject;
};

