#pragma once
class UI;
class CRes;
class CUIMgr
{
	SINGLE(CUIMgr)
private:
	Vec2 m_vMousePos;

	// 마우스는 애니메이터 형식이 더 나을 것 같음
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

