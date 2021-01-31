#pragma once
#include "Vector2D.h"
#include "Object.h"
#include "Screen.h"
#include "Box.h"
#include "breakout_game_constant.h"

void Screen::Init() {
	field_start.x = FIELD_START_X;
	field_start.y = FIELD_START_Y;
	size.x = FIELD_WIDTH;
	size.y = FIELD_HEIGHT;
}

std::shared_ptr<Box> Screen::CreateBox() {
	auto _size = size;
	_size.y += 40;
	auto box = Box::Create(field_start, _size);
	box->m_is_inner = true;
	return box;
}
