#pragma once

struct KeyInfo
{
	KEY_STATE KeyState;
	bool	  PrevPress;
};

class CKeyMgr
{
	SINGLE(CKeyMgr)
private:
	KeyInfo m_arrKey[(UINT)GROUP_KEY::END];			// 이번 프레임에서의 상태값을 키 마다 저장
	POINT	m_MousePos;
public:
	void Update();

public:
	bool KeyCheck(const GROUP_KEY& _Key, const KEY_STATE& _State);
	POINT& GetMousePos() { return m_MousePos; }
};

