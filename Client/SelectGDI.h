#pragma once
class SelectGDI
{
private:
	HPEN	m_hPen;
	HBRUSH  m_hBrush;

	HPEN	m_hReceivePen;
	HBRUSH  m_hReceiveBrush;

	HDC		m_tempDC;
public:
	SelectGDI(const HDC& _dc, const GROUP_PEN& _pen);
	SelectGDI(const HDC& _dc, const GROUP_BRUSH& _brush);
	~SelectGDI();
};

