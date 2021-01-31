#pragma once
#include "breakout_game_constant.h"
#include "Vector2d.h"
#include "DxLib.h"


struct GameInfo {
private:
	GameInfo() {}
public:
	static GameInfo&	Instance() {
		static GameInfo m_instance;
		return m_instance;
	}

	int m_score;
	int m_life;
	int m_stage;

	void Init() {
		m_life = PLAYER_NUM;
		m_score = 0;
		m_stage = 1;
	};

	// スコアを足す
	void AddScore() {
		int temp = m_score / LEVELUP_VAL;
		m_score += ADD_SCORE;
		if (temp < m_score / LEVELUP_VAL) {
			m_life += 1;
		}
	}

	// Stageの表示を+1する(いつか使うかもしれない)
	void AddStage() {
		m_stage += 1;
	}

	void SubScore() {
		m_life -= 1;
	}

	bool IsNoLife() {
		return m_life <= 0;
	}

	int GetScore() {
		return m_score;
	}
	int GetLife() {
		return m_life;
	}
	int GetStage() {
		return 	m_stage;
	}
};