#pragma once
class UI;
class CRes;
class CUIMgr
{
	SINGLE(CUIMgr)
private:
	Vec2 m_vMousePos;

	// ���콺�� �ִϸ����� ������ �� ���� �� ����
	CRes* m_arrTex;
public:
	void Init();
	void Update();
	void Render(const HDC& _dc);
private:
	void Progress();
	UI* GetTargetUI();
	void Sort();
};

