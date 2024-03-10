#pragma once
enum class GROUP_KEY
{
	LEFT, RIGHT, UP, DOWN,
	Q, W, E, R, T, Y, U, I, O, P, A, S, D, F, G, H, J, K, L, Z, X, C, V, B, N, M,
	ALT, CONTROL, SPACE, ENTER, ESC,
	LBTN, RBTN,
	END
};

enum class KEY_STATE
{
	NONE,
	TAP,
	AWAY,
	HOLD,
};

enum class GROUP_OBJECT
{
	TILE,
	MONSTER,
	PLAYER,
	UI,
	END,
};

enum class GROUP_SCENE
{
	TOOL,
	START,
	SCENE_01,
	END,
};

enum class GROUP_PEN
{
	RED,
	GREEN,
	BLUE,
	END,
};

enum class GROUP_BRUSH
{
	HOLLOW,
	BALCK,
	END,
};

enum class GROUP_EVENT
{
	CHANGE_SCENE,
	CREATEOBJECT,
	DEAD,
	END,
};

enum class GROUP_CAMERA_STATE
{
	FIX,
	PLAYER,
	FREE,
	END,
};

enum class GROUP_BTN_STATE
{
	NORMAL,
	MOUSEON,
	PRESS,
	DISABLED,
	END,
};

enum class GROUP_PLAYER_STATE
{
	ALERT,
	STAND,
	WALK,
	JUMP,
	CLIMB,
	DOWN,
	ATTACK,
	DEAD,
	END,
};

enum class GROUP_COLLISION_STATE
{
	FLOOR,
	AIR,
	ONLYPLAYER,
	LADDER,
	LADDER_WITH_FLOOR,
	END,
};

enum class GROUP_MONSTER_STATE
{
	ALERT,
	IDLE,
	TRACE,
	ATTACK,
	DEAD,
	END,
};

enum class GROUP_ANIMATION_REPEAT
{
	REPEAT,
	STOP,
	RETURN,
	END,
};

enum class GROUP_PLAYER_ATTACK
{
	NORMAL,
	END,
};