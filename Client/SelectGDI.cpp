#include "pch.h"
#include "SelectGDI.h"

SelectGDI::SelectGDI(const HDC& _dc, const GROUP_PEN& _pen)
	: m_hPen(0)
	, m_hBrush(0)
	, m_tempDC(_dc)
	, m_hReceivePen(0)
	, m_hReceiveBrush(0)
{
	if (_pen == GROUP_PEN::RED)
		m_hPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	else if (_pen == GROUP_PEN::GREEN)
		m_hPen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	else
		m_hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	m_hReceivePen = (HPEN)SelectObject(_dc, m_hPen);
}

SelectGDI::SelectGDI(const HDC& _dc, const GROUP_BRUSH& _brush)
	 : m_hPen(0)
	 , m_hBrush(0)
	 , m_tempDC(_dc)
	 , m_hReceivePen(0)
	 , m_hReceiveBrush(0)
{
	if (_brush == GROUP_BRUSH::HOLLOW)
	{
		m_hBrush = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	}
	if (m_hBrush)
	{
		m_hReceiveBrush = (HBRUSH)SelectObject(_dc, m_hBrush);
	}
}

SelectGDI::~SelectGDI()
{
	SelectObject(m_tempDC, m_hReceivePen);
	SelectObject(m_tempDC, m_hReceiveBrush);
	DeleteObject(m_hPen);
	DeleteObject(m_hBrush);
}
