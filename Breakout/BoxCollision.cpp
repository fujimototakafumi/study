﻿#pragma once
#include "Vector2D.h"
#include "Object.h"
#include "breakout_game_constant.h"
#include "DxLib.h"
#include "Screen.h"
#include "breakout_utility.h"
#include "FieldCollision.h"
#include "Ball.h"
#include "BoxCollision.h"


void BoxCollision::Update(std::shared_ptr <Ball> ball, FieldCollision* field)
{
	CheckCollision(ball, field);
}

BoxCollision::Hit BoxCollision::HitTest(std::shared_ptr <Ball> ball, std::shared_ptr <Box> box)
{
	sgs::mt::ClosestPtSegmentSegment_Result result;
	Hit r;
	r.m_type = HITRESULT_NONE;
	//ボールのベクトル
	sgs::mt::Vector ball_v = ball->m_speed;
	//ボールの単位ベクトルのを出す
	ball_v.Normalize();
	ball_v *= BALL_SIZE;

	//ボールの現在座標からベクトルを引き前フレの座標を出す
	Vector2D a = ball->ball_pos;
	a.Sub(ball->m_speed);

	//ボールの現在座標からベクトルを加算し次フレの座標を出す?(反射後)？意味あんまない？
	Vector2D b = ball->ball_pos;
	b.Add(ball_v);

	Vector2D c[4];
	Vector2D d[4];

	// 線分Aの開始点の判定が来た場合だけ除外する
	auto IsBeginPos = [&a](const sgs::mt::ClosestPtSegmentSegment_Result &r) {
		return 0 == a.Distance(r.c1);
	};

	float l;
	float mini = ball->m_speed.Length() * 2;

	Vector2D z_axis;
	if (box->m_is_inner) {
		z_axis.Set(0, 0, -1);
	}
	else {
		z_axis.Set(0, 0, 1);
	}

	// 上
	c[0] = box->pos1;
	d[0] = box->pos1;
	d[0].x += box->size.x;
	// 下
	c[1] = box->pos1;
	c[1].Add(box->size);
	d[1] = c[1];
	d[1].x -= box->size.x;
	// 左
	d[2] = box->pos1;
	c[2] = d[2];
	c[2].y += box->size.y;
	// 右
	d[3] = box->pos1;
	d[3].Add(box->size);
	c[3] = d[3];
	c[3].y -= box->size.y;

	for (int i = 0; i < 4; i++) {
		Vector2D ee;

		//法線の単位ベクトルを出す？
		ee = d[i] - c[i];
		ee.Normalize();
		ee.Cross(z_axis);

		//法線とボールのベクトルとの内積で除外したい入射方向を見る
		float dot = ee.Dot(ball->m_speed);
		if (0 <= dot) {
			continue;
		}

		//最接近点を算出
		l = ClosestPtSegSeg(a, b, c[i], d[i], result);
		if (0.0001f >= fabsf(l) && !IsBeginPos(result)) {

			float dist = a.Distance(result.c1);
			if (dist < mini) {
				mini = dist;
				r.pos = result.c1;
				r.m_type = HITRESULT_HIT;
				r.normal = ee;
			}
		}
	}
	return r;
}

void BoxCollision::CheckCollision(std::shared_ptr <Ball> ball, FieldCollision* field) {
	std::list<std::list<std::shared_ptr<Box>>::iterator> removes;

	for (auto iter = field->m_collisions.begin(); iter != field->m_collisions.end(); ++iter) {
		auto &box = *iter;

		if (box->m_is_delete) {
			removes.push_back(iter);
			continue;
		}

		if (BoxCollisionFunc(ball, box)) {
			box->OnContact();
		}
	}

	for (auto &iter : removes) {
		field->m_collisions.erase(iter);
	}
}

bool BoxCollision::BoxCollisionFunc(std::shared_ptr <Ball> ball, std::shared_ptr <Box> box) {

	Hit result = HitTest(ball, box);
	if (result.m_type == HITRESULT_NONE) {
		return false;
	}

	//反射後のポジションを反映させる
	sgs::mt::Vector v = ball->m_speed;
	//単位ベクトル化
	v.Normalize();
	v *= BALL_SIZE;
	result.pos -= v;

	if (fabsf(result.normal.y)) {
		ball->m_speed.y *= -1;
	}
	else if (fabsf(result.normal.x)) {
		ball->m_speed.x *= -1;
	}

	float d = ball->ball_pos.Distance(result.pos);
	float d2 = ball->m_speed.Length();

	d = d / d2;
	ball->ball_pos = result.pos;
	ball->ball_pos.x += (float)ball->m_speed.x * d;
	ball->ball_pos.y += (float)ball->m_speed.y * d;

	return true;
}
