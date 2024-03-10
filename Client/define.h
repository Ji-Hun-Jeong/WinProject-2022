#pragma once
#define SINGLE(type) private:\
					 static type m_mgr;\
					 type();\
					 ~type();\
					 public:\
					 static type& GetInst() { return m_mgr; }

#define dt CTimeMgr::GetInst().GetDT()

#define KEYCHECK(KEY,STATE) CKeyMgr::GetInst().KeyCheck(GROUP_KEY::KEY, KEY_STATE::STATE)

#define MOUSE_POS CKeyMgr::GetInst().GetMousePos()

#define CLONE(type) CObject* Clone() override {return new type(*this);}

#define TILE_SIZE 32