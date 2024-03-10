#include "pch.h"
#include "CAnimator.h"
#include "Animation.h"
#include "Player.h"

CAnimator::CAnimator()
	: m_pOwner(nullptr)
	, m_pCurAnime(nullptr)
	, m_iRepeat((UINT)GROUP_ANIMATION_REPEAT::REPEAT)
{
}

CAnimator::~CAnimator()
{
	Safe_Delete_Map(m_mapAnime);
}

void CAnimator::Play(const HDC& _dc)
{
	static int AnimationSelect = 0;
	AnimationSelect = m_pCurAnime->Play(_dc, m_iRepeat);
	// Play()에서 끝나면 값을 전달해줘서 현재 애니메이션을 기본 애니메이션으로 바꾼다.
	if (1 == AnimationSelect)
	{
		if (m_pCurAnime->m_strName.find("Left") != string::npos)
		{
			SetCurAnime("Stand_Left", UINT(GROUP_ANIMATION_REPEAT::REPEAT));
		}
		else
		{
			SetCurAnime("Stand_Right", UINT(GROUP_ANIMATION_REPEAT::REPEAT));
		}
		if (((Player*)m_pOwner)->GetPlayerState() == GROUP_PLAYER_STATE::ATTACK)
		{
			((Player*)m_pOwner)->FinishAttack();
		}
		((Player*)m_pOwner)->SetPlayerState(GROUP_PLAYER_STATE::STAND);
	}
}

void CAnimator::SetCurAnime(const string& _strName, const UINT& _iRepeat)
{
	m_iRepeat = _iRepeat;
	auto iter = m_mapAnime.find(_strName);
	assert(iter->second);
	m_pCurAnime = iter->second;
	if ((UINT)GROUP_ANIMATION_REPEAT::STOP == _iRepeat)
	{
		m_pCurAnime->Init();
	}
}

Animation* CAnimator::FindAnime(const string& _strName)
{
	auto iter = m_mapAnime.begin();
	for (iter; iter != m_mapAnime.end(); ++iter)
	{
		if (_strName == iter->first)
			return iter->second;
	}
	return nullptr;
}

void CAnimator::SetAnime(const string& _strName, CRes* _Tex, const Vec2& _StartPos, const Vec2& _Slice, const Vec2& _Next, const UINT& _Count, const double& _Time)
{
	Animation* pAnime = FindAnime(_strName);
	if (pAnime)
	{
		assert(nullptr);
	}
	else
	{
		pAnime = new Animation;
		pAnime->m_pOwner = this;
		pAnime->m_strName = _strName;
		pAnime->m_pTex = (Texture*)_Tex;
		pAnime->m_fTime = _Time;
		tFrmInfo frm = { };	
		for (int i = 0; i < (int)_Count; ++i)
		{
			Vec2 pos = _StartPos;
			Vec2 scale = _Next;
			frm = { pos + scale * i ,_Slice ,_Next };
			pAnime->m_vecFrmInfo.push_back(frm);
		}
		m_mapAnime.insert(make_pair(_strName, pAnime));
	}
}
