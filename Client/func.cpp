#include "pch.h"
#include "func.h"
#include "CEventMgr.h"
void CreateObject(CObject* _pobj, const GROUP_OBJECT& _group)
{
	Event eve = { (DWORD_PTR)_pobj,(DWORD_PTR)_group,GROUP_EVENT::CREATEOBJECT };
	CEventMgr::GetInst().AddEvent(eve);
}
void DeadObject(CObject* _pobj)
{
	Event eve = { (DWORD_PTR)_pobj,0,GROUP_EVENT::DEAD };
	CEventMgr::GetInst().AddEvent(eve);
}

void ChangeScene(const GROUP_SCENE& _scene)
{
	Event eve = { DWORD_PTR(_scene),0,GROUP_EVENT::CHANGE_SCENE };
	CEventMgr::GetInst().AddEvent(eve);
}
