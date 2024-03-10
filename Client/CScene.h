#pragma once
class CObject;
class Texture;
class CRes;
class PixelCollider;
class CScene
{
protected:
	vector<CObject*>	m_vecObj[(UINT)GROUP_OBJECT::END];
	vector<PixelCollider*>  m_vecCol;
	CRes*				m_pTex;
	CRes*				m_pAnotherTex;

	bool				m_bShowCollider;
public:
	CScene();
	virtual ~CScene();
public:
	void AddObject(CObject* _obj, const GROUP_OBJECT& _group);
	void DeleteGroup(const GROUP_OBJECT& _group);
	void CreateTile(const UINT& _x, const UINT& _y);

	const vector<PixelCollider*>& GetColVec() { return m_vecCol; }
	vector<CObject*>& GetVec(const GROUP_OBJECT& _group) { return m_vecObj[(UINT)_group]; }
	CRes* GetTex() { return m_pTex; }

	virtual void LoadFileData();
	virtual void LoadFile(const char* _p);

	const bool& ShowCol() { return m_bShowCollider; }
public:
	virtual void Enter() = 0;
	virtual void Exit();
	virtual void Update();
	virtual void FinalUpdate();
	virtual void Render(const HDC& _dc);
private:
	void DeleteAll();
};

