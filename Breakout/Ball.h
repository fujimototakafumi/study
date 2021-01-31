#pragma once
#include "Vector2D.h"
#include "Object.h"
#include "breakout_game_constant.h"
#include "DxLib.h"
#include "Screen.h"
#include "breakout_utility.h"
#include "FieldCollision.h"

struct Ball : public Object_GameObject {
public:
	Point2D ball_pos;
	int Color;
	float radius;
	Vector2D m_speed;

	void Init();
	void Update();
	void Draw();
	bool IsFalldeath(std::shared_ptr<Screen> screen);
};