#pragma once
class CCore
{
	SINGLE(CCore)
private:
	POINT  m_Resolution;
	HWND  m_hWnd;
	HDC	  m_hDC;
/// <summary>
/// //////////////
/// </summary>
	HBITMAP m_hBitmap;
	HDC		m_hMemDC;
public:
	void Init(const HWND& _hWnd,POINT& _Resolution);
	void Progress();
	void SetResolution(const Vec2& _Resolution);
public:
	POINT& GetResolution() { return m_Resolution; }
	const HWND& GetHwnd() { return m_hWnd; }
	const HDC& GetHdc() { return m_hDC; }
};

