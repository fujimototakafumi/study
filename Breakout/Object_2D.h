#pragma once
#include "Object.h"
#include "DxLib.h"

/// ファイル分別でObject_2DはObject_2Dで
struct GameOver : public Object_2D {
	void Init();
	void Draw();
};

struct PlayerDead : public Object_2D {
	void Init();
	void Draw();
};

struct Ready : public Object_2D {
	void Init();
	void Draw();

};

struct Clear : public Object_2D {
	void Init();
	void Draw();
};

struct GameScore : public Object_2D {
	void Init();
	void Draw();
};
struct GameStageName : public Object_2D {
	void Init();
	void Draw();
};
struct GameLife : public Object_2D {
	void Init();
	void Draw();
};
