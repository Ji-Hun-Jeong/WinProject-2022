#pragma once
class CObject;
class CEventMgr
{
	SINGLE(CEventMgr)
private:
	vector<Event>		m_vecEvent;
	vector<CObject*>	m_vecDead;
public:
	void AddEvent(const Event& _eve);
	void Update();
private:
	void progress(const Event& _eve);
};

