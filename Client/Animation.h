#pragma once
class CAnimator;
class CRes;
class Texture;
struct tFrmInfo
{
	Vec2 StartPos;
	Vec2 Slice;
	Vec2 Next;
};
class Animation			
{
private:
	vector<tFrmInfo>		m_vecFrmInfo;

	string					m_strName;

	CAnimator*				m_pOwner;
	Texture*				m_pTex;

	UINT					m_iCount;
	double					m_fTime;
	double					m_fAccTime;
public:
	Animation();
	~Animation();
public:
	const int Play(const HDC& _dc, const UINT& _iRepeat);
	void Init();
	friend class CAnimator;
};

