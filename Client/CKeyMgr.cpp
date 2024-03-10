#include "pch.h"
#include "CKeyMgr.h"
#include "CCore.h"
CKeyMgr CKeyMgr::m_mgr;
CKeyMgr::CKeyMgr()
	: m_arrKey{}
{}
CKeyMgr::~CKeyMgr()
{}
int g_key[(UINT)GROUP_KEY::END] =
{
	VK_LEFT,VK_RIGHT,VK_UP,VK_DOWN,
	'Q','W','E','R','T','Y','U','I','O','P','A','S','D','F','G','H','J','K','L','Z','X','C','V','B','N','M',
	VK_MENU,VK_CONTROL,VK_SPACE,VK_RETURN,VK_ESCAPE,
	VK_LBUTTON,VK_RBUTTON,
	//END
};

void CKeyMgr::Update()
{
	if (GetFocus())		// ���α׷��� ��Ŀ�� ���� ��
	{
		for (UINT i = 0; i < (UINT)GROUP_KEY::END; ++i)
		{
			if (GetAsyncKeyState(g_key[i]) & 0x8000)	// �̹� �����ӿ� Ű�� ������ ���
			{
				if (m_arrKey[i].PrevPress)				// ���� �����ӿ��� Ű�� ������ ���
				{
					m_arrKey[i].KeyState = KEY_STATE::HOLD;
				}
				else									// ���� �����ӿ��� Ű�� ������ �ʾ��� ���
				{
					m_arrKey[i].KeyState = KEY_STATE::TAP;
				}
				m_arrKey[i].PrevPress = true;
			}
			else										// �̹� �����ӿ� Ű�� ������ �ʾ��� ���
			{
				if (m_arrKey[i].PrevPress)				// ���� �����ӿ� Ű�� ������ ���
				{
					m_arrKey[i].KeyState = KEY_STATE::AWAY;
				}
				else									// ���� �����ӿ��� Ű�� ������ �ʾ��� ���
				{
					m_arrKey[i].KeyState = KEY_STATE::NONE;
				}
				m_arrKey[i].PrevPress = false;
			}
		}
		GetCursorPos(&m_MousePos);
		ScreenToClient(CCore::GetInst().GetHwnd(), &m_MousePos);
	}
	else
	{
		// ü������ ���� �����̱� ������ �׳� ���� noneó���ؼ� �ӵ� ��� ���(for�� �ȿ� ���ǹ� ���ֱ�)
		for (UINT i = 0; i < (UINT)GROUP_KEY::END; ++i)
		{
			//if (m_arrKey[i].PrevPress)				// ���� �����ӿ� Ű�� ������ ���
			//{
			//	m_arrKey[i].KeyState = KEY_STATE::AWAY;
			//}
			// ���� �����ӿ� Ű�� ������ �ʾ��� ���			
			m_arrKey[i].KeyState = KEY_STATE::NONE;			
			m_arrKey[i].PrevPress = false;
		}
	}
}

bool CKeyMgr::KeyCheck(const GROUP_KEY& _Key, const KEY_STATE& _State)
{
	if (m_arrKey[(UINT)_Key].KeyState == _State)
		return true;
	return false;
}
