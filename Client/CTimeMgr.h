#pragma once
class CTimeMgr
{
	SINGLE(CTimeMgr)
private:
	LARGE_INTEGER	m_llCurTime; // ���� �����ӿ����� �ð�
	LARGE_INTEGER	m_llPrevTime; // ���� �����ӿ����� �ð�
	LARGE_INTEGER	m_llFrequency; // 1�ʴ� ������

	UINT	m_iFps;  // FPS
	UINT	m_iCount; // 1�ʵ��� �� �������� ��������

	double	m_dDT;	// dt
	double	m_dAcc;  // 1�ʸ� �����ϴ� �ð�

	wchar_t m_szBuffer[256];
public:
	void Init();
	void Update();
public:
	const double& GetDT() { return m_dDT; }
	const UINT& GetFPS() { return m_iFps; }
};

