#pragma once
#include "Vector2D.h"
#include "breakout_game_constant.h"
#include "DxLib.h"
#include "Screen.h"
#include "Bar.h"
#include "Key.h"
#include "Object.h"

void Bar::Init() {
	pos.x = FIELD_START_X;
	pos.y = FIELD_HEIGHT - BAR_HEIGHT - 50;
	Color = GetColor(255, 0, 0);
	size.x = 100;
	size.y = BAR_HEIGHT;
}

void Bar::Update(std::shared_ptr<Screen> screen) {

	if (IsKeyPress(KEY_INPUT_RIGHT) && (pos.x + size.x) < screen->size.x + screen->field_start.x) {
		pos.x += BAR_SPEED;
	}
	if (IsKeyPress(KEY_INPUT_LEFT) && pos.x > screen->field_start.x) {
		pos.x -= BAR_SPEED;
	}
}

void Bar::Draw() {
	if (m_is_show)
	{
		DrawBoxAA(pos.x, pos.y, pos.x + size.x, pos.y + size.y, Color, true);
	}
}

std::shared_ptr<Box> Bar::CreateBox() {
	return Box::Create(pos, size);
}
