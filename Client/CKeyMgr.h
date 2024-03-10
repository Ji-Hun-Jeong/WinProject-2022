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
	KeyInfo m_arrKey[(UINT)GROUP_KEY::END];			// �̹� �����ӿ����� ���°��� Ű ���� ����
	POINT	m_MousePos;
public:
	void Update();

public:
	bool KeyCheck(const GROUP_KEY& _Key, const KEY_STATE& _State);
	POINT& GetMousePos() { return m_MousePos; }
};

