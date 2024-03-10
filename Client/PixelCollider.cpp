#include "pch.h"
#include "PixelCollider.h"
#include "SelectGDI.h"
#include "CScene.h"
#include "CSceneMgr.h"
#include "Texture.h"
#include "CObject.h"
#include "Player.h"
#include "Monster.h"
#include "CGravity.h"
#include "CRigidBody.h"

PixelCollider::PixelCollider()
	: m_bRender(false)
{
	m_strType = "Pixel";
}

PixelCollider::~PixelCollider()
{
}


void PixelCollider::Render(const HDC& _dc)
{
	HPEN pen = CreatePen(PS_SOLID, 1, RGB(m_ePixelInfo.R, m_ePixelInfo.G, m_ePixelInfo.B));
	HPEN oldpen = (HPEN)SelectObject(_dc, pen);
	Rectangle(_dc
		, int(m_vPos.x)
		, int(m_vPos.y)
		, int(m_vPos.x + m_vScale.x)
		, int(m_vPos.y + m_vScale.y));
	DeleteObject(oldpen);
}
