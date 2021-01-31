#pragma once
#pragma once
#include "Vector2D.h"
#include "Object.h"
#include "breakout_game_constant.h"
#include "DxLib.h"
#include "Screen.h"
#include "breakout_utility.h"
#include "FieldCollision.h"
#include "Ball.h"

struct BoxCollision {

public:
	enum HitResult {
		HITRESULT_NONE,
		HITRESULT_HIT,
	};
	struct Hit {
		HitResult m_type;
		Point2D normal;
		Point2D pos;
	};

	void Update(std::shared_ptr <Ball> ball, FieldCollision* field);

	Hit HitTest(std::shared_ptr <Ball> ball, std::shared_ptr <Box> box);

	void CheckCollision(std::shared_ptr <Ball> ball, FieldCollision* field);

	bool BoxCollisionFunc(std::shared_ptr <Ball> ball, std::shared_ptr <Box> box);
};
