#pragma once
#include "Vector2D.h"
#include "Object.h"
#include "breakout_game_constant.h"
#include "DxLib.h"
#include "Screen.h"
#include "breakout_utility.h"
#include "FieldCollision.h"
#include "Ball.h"

void Ball::Init() {
	//ボールの初期位置
	ball_pos.Set(28, 300, 0);
	m_speed.Set(BALL_SPEED, BALL_SPEED, 0);
	m_speed.Normalize();
	m_speed *= BALL_SPEED;

	Color = GetColor(255, 255, 255);
	radius = BALL_SIZE;
}

void Ball::Update() {
	ball_pos.Add(m_speed);
}

void Ball::Draw() {
	DrawCircle((int)ball_pos.x, (int)ball_pos.y, BALL_SIZE, Color, true);
}

bool Ball::IsFalldeath(std::shared_ptr<Screen> screen) {
	return ball_pos.y >= screen->size.y + screen->field_start.y;
}
