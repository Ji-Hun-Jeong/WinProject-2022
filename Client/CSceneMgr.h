#pragma once
class CScene;
class CSceneMgr
{
	SINGLE(CSceneMgr)
private:
	CScene* m_arrScene[(UINT)GROUP_SCENE::END];
	CScene* m_CurScene;
public:
	void Init();
	void Update();
	void Render(const HDC& _dc);

	void ChangeScene(const GROUP_SCENE& _scene);
	
	CScene* GetCurScene() { return m_CurScene; }
};

