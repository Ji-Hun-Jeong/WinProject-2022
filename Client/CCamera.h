#pragma once
class CObject;
class CCamera
{
	SINGLE(CCamera)
private:
	Vec2				m_vCorePos;
	Vec2				m_vDestPos;
	Vec2				m_vCurPos;
	Vec2				m_vPrevPos;
	Vec2				m_vDiff;
	Vec2				m_vDir;

	GROUP_CAMERA_STATE	m_State;

	double				m_fTime;	// 주어진 거리를 몇초동안 가야하는지 
	double				m_fSpeed;
	double				m_fAccTime;

	// 플레이어 포인터
	CObject* m_pPlayer;
public:
	void Init();
	void Update();	
	void Render(const HDC& _dc);	// 화면에 효과 주기위한 렌더링
	void SetCamState(const GROUP_CAMERA_STATE& _state) { m_State = _state; }
	void Setplayer(CObject* _pPlayer) { m_pPlayer = _pPlayer; }

	const Vec2& GetDestPos() { return m_vDestPos; }
	Vec2 GetRealPos(Vec2& _Pos);
	Vec2 GetRenderPos(Vec2& _Pos);

private:
	void Calculate();
	void CalDiff();
};

