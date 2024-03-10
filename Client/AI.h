#pragma once
class CObject;
class AI
{
private:
	CObject*				m_pOwner;
	GROUP_MONSTER_STATE		m_eMonsterState;

	Vec2					m_vPrevDir;

	double					m_fAccTime;
	double					m_fChangeTime;

	double					m_fAlertTime;
	double					m_fAccAlertTime;
public:
	AI();
	~AI();
public:
	void StateUpdate();
	void Update();
	friend class Monster;
};

