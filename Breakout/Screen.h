#pragma once
#include "Vector2D.h"
#include "Object.h"
#include "Box.h"
#include "breakout_game_constant.h"

struct Screen : public Object {

	Point2D field_start;
	Size2D size;

	void Init();
	std::shared_ptr<Box> CreateBox();
};
