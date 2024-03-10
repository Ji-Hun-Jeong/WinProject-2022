#include "pch.h"
#include "Animation.h"
#include "CAnimator.h"

#include "CObject.h"
#include "CCollider.h"

#include "Texture.h"

#include "CCamera.h"

#include "CTimeMgr.h"

Animation::Animation()
	: m_pOwner(nullptr)
	, m_pTex(nullptr)
	, m_iCount(0)
	, m_fTime(0.f)
	, m_fAccTime(0.f)
{
}

Animation::~Animation()
{
}

const int Animation::Play(const HDC& _dc, const UINT& _iRepeat)
{
	Vec2 Pos = {};
	Vec2 Scale = {};
	// 시간을 축적해서 시간에 다다르면 그 다음 인덱스로
	m_fAccTime += dt;
	if (m_fAccTime >= m_fTime)
	{
		m_fAccTime = 0;
		++m_iCount;
	}
	if (m_vecFrmInfo.size() == m_iCount)
	{
		if ((UINT)GROUP_ANIMATION_REPEAT::RETURN == _iRepeat)		// 기본 애니메이션으로 전환하라고 알림
		{
			m_iCount = 0;
			return 1;
		}
		else if ((UINT)GROUP_ANIMATION_REPEAT::REPEAT == _iRepeat)
		{
			m_iCount = 0;
		}
		else if ((UINT)GROUP_ANIMATION_REPEAT::STOP == _iRepeat)
		{
			m_iCount = UINT(m_vecFrmInfo.size() - 1);
		}
	}
	Pos = m_pOwner->m_pOwner->GetPos();
	Pos = CCamera::GetInst().GetRenderPos(Pos);
	Scale = m_pOwner->m_pOwner->GetScale();
	Vec2 colPos = m_pOwner->m_pOwner->GetCollider()->GetPos();
	Vec2 colScale = m_pOwner->m_pOwner->GetCollider()->GetScale();
	TransparentBlt(_dc
		, int(Pos.x - abs(Scale.x - colScale.x) / 2.f)
		, int(Pos.y - abs(Scale.y - colScale.y) / 2.f - 10)
		, int(Scale.x)
		, int(Scale.y)
		, m_pTex->GetHdc()
		, int(m_vecFrmInfo[m_iCount].StartPos.x)
		, int(m_vecFrmInfo[m_iCount].StartPos.y)
		, int(m_vecFrmInfo[m_iCount].Slice.x)
		, int(m_vecFrmInfo[m_iCount].Slice.y)
		, RGB(255, 255, 255));
	return 0;
}

void Animation::Init()
{
	if (m_iCount == m_vecFrmInfo.size() - 1)
		m_iCount = 0;
}
