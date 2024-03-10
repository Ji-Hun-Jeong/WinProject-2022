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
	if (GetFocus())		// 프로그램이 포커싱 받을 때
	{
		for (UINT i = 0; i < (UINT)GROUP_KEY::END; ++i)
		{
			if (GetAsyncKeyState(g_key[i]) & 0x8000)	// 이번 프레임에 키가 눌렸을 경우
			{
				if (m_arrKey[i].PrevPress)				// 이전 프레임에도 키가 눌렸을 경우
				{
					m_arrKey[i].KeyState = KEY_STATE::HOLD;
				}
				else									// 이전 프레임에는 키가 눌리지 않았을 경우
				{
					m_arrKey[i].KeyState = KEY_STATE::TAP;
				}
				m_arrKey[i].PrevPress = true;
			}
			else										// 이번 프레임에 키가 눌리지 않았을 경우
			{
				if (m_arrKey[i].PrevPress)				// 이전 프레임에 키가 눌렸을 경우
				{
					m_arrKey[i].KeyState = KEY_STATE::AWAY;
				}
				else									// 이전 프레임에도 키가 눌리지 않았을 경우
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
		// 체감하지 못할 수준이기 때문에 그냥 전부 none처리해서 속도 상승 기대(for문 안에 조건문 없애기)
		for (UINT i = 0; i < (UINT)GROUP_KEY::END; ++i)
		{
			//if (m_arrKey[i].PrevPress)				// 이전 프레임에 키가 눌렸을 경우
			//{
			//	m_arrKey[i].KeyState = KEY_STATE::AWAY;
			//}
			// 이전 프레임에 키가 눌리지 않았을 경우			
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
