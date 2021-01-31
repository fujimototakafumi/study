#pragma once
#include "Vector2D.h"
#include "breakout_game_constant.h"
#include "DxLib.h"
#include "Screen.h"
#include "Object.h"
#include "Key.h"

struct Bar : public Object_GameObject {

	Point2D pos;
	Size2D size;

	int Color;

	void Init();

	void Update(std::shared_ptr<Screen> screen);

	void Draw();

	std::shared_ptr<Box> CreateBox();

};
