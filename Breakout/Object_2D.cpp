#pragma once
#include "Object.h"
#include "Object_2D.h"
#include "DxLib.h"
#include "GameInfo.h"

void GameOver::Init() {}

void GameOver::Draw() {
	if (m_is_show) {
		DrawFormatString(250, 200, GetColor(255, 255, 255), "gameover");
		DrawFormatString(200, 250, GetColor(255, 255, 255), "press space key");
	}
}

void PlayerDead::Init() {}

void PlayerDead::Draw() {
	if (m_is_show) {
		DrawFormatString(250, 200, GetColor(255, 255, 255), "dead");
		DrawFormatString(200, 250, GetColor(255, 255, 255), "press y key");
	}
}

void Ready::Init() {}

void Ready::Draw() {
	if (m_is_show) {
		DrawFormatString(230, 200, GetColor(255, 255, 255), "ready");
		DrawFormatString(200, 250, GetColor(255, 255, 255), "press enter key");
	}
}

void Clear::Init() {}

void Clear::Draw() {
	if (m_is_show) {
		DrawFormatString(250, 200, GetColor(255, 255, 255), "Clear");
		DrawFormatString(200, 250, GetColor(255, 255, 255), "press space key");
	}
}

void GameScore::Init() {}

void GameScore::Draw() {
	if (m_is_show) {
		DrawFormatString(490, 50, GetColor(255, 255, 255), "Score:%d ", GameInfo::Instance().GetScore());
	}
}

void GameStageName::Init() {}

void GameStageName::Draw() {
	if (m_is_show) {
		DrawFormatString(490, 300, GetColor(255, 255, 255), "Stage:%d ", GameInfo::Instance().GetStage());// GameInfo::Instance()
	}
}

void GameLife::Init() {}

void GameLife::Draw() {
	//残機を表示
	if (m_is_show) {
		Point2D pos;
		Size2D size;
		size.x = 35;
		size.y = 10;

		int next_row = 0;
		int j = 0;
		for (int i = 0; i < GameInfo::Instance().GetLife(); i++) {
			if (i % 4 == 0) {
				next_row += 15;
				j = 0;
			}
			pos.x = 490.0f + 40.0f * j;
			pos.y = 100.0f + next_row;
			DrawBoxAA(pos.x, pos.y, pos.x + size.x, pos.y + size.y, GetColor(100, 100, 100), true);
			j++;
		}
	}
}
