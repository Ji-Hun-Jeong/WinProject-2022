#pragma once
class CObject;
class Animation;
class CRes;
class CAnimator
{
private:
	// 애니메이션들을 가진다.
	CObject*				m_pOwner;
	map<string, Animation*> m_mapAnime;
	Animation*				m_pCurAnime;

	UINT					m_iRepeat;

public:
	CAnimator();
	~CAnimator();
public:
	void Play(const HDC& _dc);
	void SetCurAnime(const string& _strName, const UINT& _iRepeat);
	void SetAnime(const string& _strName, CRes* _Tex, const Vec2& _StartPos, const Vec2& _Slice, const Vec2& _Next, const UINT& _Count,const double& _Time);
private:
	Animation* FindAnime(const string& _strName);
	friend class CObject;
	friend class Animation;
};

