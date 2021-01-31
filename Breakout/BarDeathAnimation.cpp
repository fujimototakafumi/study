#pragma once
#include "Vector2D.h"
#include "breakout_game_constant.h"
#include "DxLib.h"
#include "Screen.h"
#include "Key.h"
#include "Object.h"
#include "BarDeathAnimation.h"
#include "Bar.h"
#include <math.h>

void BarDeathAnimation::Init(std::shared_ptr<Bar> bar)
{
	// pos = bar->pos;
	Color = bar->Color;
	size = bar->size;
	m_ratio = 1.0;
	Show(true);

	size = bar->size / 2;
	center = bar->pos + size;
}

void BarDeathAnimation::Update() {
	m_ratio -= 0.01f;
	if (m_ratio < 0) {
		Delete();
		return;
	}
}

sgs::mt::Vector Rot(sgs::mt::Vector xy, float theta)
{
	sgs::mt::Vector r;

	float cos_theta = cos(theta);
	float sin_theta = sin(theta);

	r.x = xy.x * cos_theta - xy.y * sin_theta;
	r.y = xy.x * sin_theta + xy.y * cos_theta;
	return r;
}

void BarDeathAnimation::Draw() {
	if (m_is_show)
	{
		Update();

		auto left_top = size * -1; // 左上
		auto right_top = left_top; // 右上
		auto right_bottom = size; // 右下
		auto left_bottom = right_bottom; // 左下
		right_top.x = right_bottom.x;
		left_bottom.x = left_top.x;

		float ratio = m_ratio;


		float theta = ratio;
		left_top = Rot(left_top, theta);
		right_top = Rot(right_top, theta);
		right_bottom = Rot(right_bottom, theta);
		left_bottom = Rot(left_bottom, theta);

		/*left_top *= ratio;
		right_top *= ratio;
		right_bottom *= ratio;
		left_bottom *= ratio;
		*/

		left_top += center;
		right_top += center;
		right_bottom += center;
		left_bottom += center;

		/// ----

		DrawTriangle(left_top.x, left_top.y, right_top.x, right_top.y, left_bottom.x, left_bottom.y, Color, true);
		DrawTriangle(right_top.x, right_top.y, left_bottom.x, left_bottom.y, right_bottom.x, right_bottom.y, Color, true);
	}
}

