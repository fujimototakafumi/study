#pragma once
#include "Vector2D.h"
#include "breakout_game_constant.h"
#include "DxLib.h"
#include "Screen.h"
#include "Object.h"
#include "Key.h"
#include <math.h>

struct Bar;

struct BarDeathAnimation : public Object_GameObject {

	// Point2D pos;
	Point2D center;
	Size2D size;
	float  m_ratio;

	int Color;

	void Init(std::shared_ptr<Bar> bar);

	void Update();

	void Draw();

};
