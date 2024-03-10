#include "pch.h"
#include "CEventMgr.h"
#include "CSceneMgr.h"
#include "CScene.h"
#include "CObject.h"
CEventMgr CEventMgr::m_mgr;
CEventMgr::CEventMgr()
{

}
CEventMgr::~CEventMgr()
{}
void CEventMgr::AddEvent(const Event& _eve)
{
	m_vecEvent.push_back(_eve);
}

void CEventMgr::Update()
{
	for (size_t i = 0; i < m_vecDead.size(); ++i)
	{
		assert(m_vecDead[i]);
		delete m_vecDead[i];
	}
	m_vecDead.clear();
	for (size_t i = 0; i < m_vecEvent.size(); ++i)
	{
		progress(m_vecEvent[i]);
	}
	m_vecEvent.clear();
}

void CEventMgr::progress(const Event& _eve)
{
	switch (_eve.event)
	{
	case GROUP_EVENT::CHANGE_SCENE:
		CSceneMgr::GetInst().ChangeScene(GROUP_SCENE(_eve.lParam));
		break;
	case GROUP_EVENT::CREATEOBJECT:
		CSceneMgr::GetInst().GetCurScene()->AddObject(((CObject*)_eve.lParam), (GROUP_OBJECT)_eve.wParam);
		break;
	case GROUP_EVENT::DEAD:
		((CObject*)_eve.lParam)->SetDead();
		m_vecDead.push_back(((CObject*)_eve.lParam));
		break;
	default:
		break;
	}
}
