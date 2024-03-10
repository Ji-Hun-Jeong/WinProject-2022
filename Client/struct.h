#pragma once
struct Vec2
{
	double x;
	double y;
public:
	Vec2()
		: x(0)
		, y(0)
	{}
	Vec2(double _x,double _y)
		: x(_x)
		, y(_y)
	{}
	Vec2(POINT& _point)
		: x((double)_point.x)
		, y((double)_point.y)
	{}
	double GetLength()
	{
		return sqrt(x * x + y * y);
	}
	bool IsZero()
	{
		return x == 0 && y == 0 ? true : false;
	}
	Vec2 operator -()
	{
		return Vec2(-x, -y);
	}
	Vec2 Normallize()
	{
		double len = GetLength();
		if (0 == len)
		{
			return Vec2(0.f, 0.f);
		}
		return Vec2(x / len, y / len);
	}
	Vec2& operator = (POINT& _point)
	{
		x = _point.x;
		y = _point.y;
		return *this;
	}
	Vec2 operator +(Vec2 _other)
	{
		return Vec2(x + _other.x, y + _other.y);
	}
	Vec2 operator -(Vec2 _other)
	{
		return Vec2(x - _other.x, y - _other.y);
	}
	Vec2 operator *(Vec2 _other)
	{
		return Vec2(x * _other.x, y * _other.y);
	}
	Vec2 operator /(Vec2 _other)
	{
		assert(_other.x && _other.y);
		return Vec2(x / _other.x, y / _other.y);
	}
	Vec2 operator +(double _f)
	{
		return Vec2(x + _f, y + _f);
	}
	Vec2 operator -(double _f)
	{
		return Vec2(x - _f, y - _f);
	}
	Vec2 operator *(double _f)
	{
		return Vec2(x * _f, y * _f);
	}
	Vec2 operator /(double _f)
	{
		assert(_f);
		return Vec2(x / _f, y / _f);
	}
	Vec2 operator +(int _f)
	{
		return Vec2(x + _f, y + _f);
	}
	Vec2 operator -(int _f)
	{
		return Vec2(x - _f, y - _f);
	}
	Vec2 operator *(int _f)
	{
		return Vec2(x * _f, y * _f);
	}
	Vec2 operator /(int _f)
	{
		assert(_f);
		return Vec2(x / _f, y / _f);
	}
	Vec2& operator +=(const Vec2& _other)
	{
		x += _other.x;
		y += _other.y;
		return *this;
	}
	Vec2& operator -=(const Vec2& _other)
	{
		x -= _other.x;
		y -= _other.y;
		return *this;
	}
	Vec2& operator *=(const Vec2& _other)
	{
		x *= _other.x;
		y *= _other.y;
		return *this;
	}
	Vec2& operator /=(const Vec2& _other)
	{
		if (0 == _other.x || 0 == _other.y)
			assert(0);
		x /= _other.x;
		y /= _other.y;
		return *this;
	}
	Vec2& operator +=(double _other)
	{
		x += _other;
		y += _other;
		return *this;
	}
	Vec2& operator -=(double _other)
	{
		x -= _other;
		y -= _other;
		return *this;
	}
	Vec2& operator *=(double _other)
	{
		x *= _other;
		y *= _other;
		return *this;
	}
	Vec2& operator /=(double _other)
	{
		if (0 == _other)
			assert(0);
		x /= _other;
		y /= _other;
		return *this;
	}
};

struct Event
{
	DWORD_PTR	lParam;
	DWORD_PTR	wParam;
	GROUP_EVENT event;
};

struct PIXEL
{
	UINT R;
	UINT G;
	UINT B;
};

struct AttackInfo
{
	Vec2 Offset;
	Vec2 Range;
	float Time;
};