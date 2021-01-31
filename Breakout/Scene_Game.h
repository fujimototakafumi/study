#pragma once
#include "DxLib.h"
#include "Key.h"
#include <math.h>
#include <vector>
#include <list>
#include <functional>
#include "Vector2d.h"
#include "breakout_utility.h"
#include "breakout_game_constant.h"
#include "fieldcollision.h"
#include "GameInfo.h"
#include "Object.h"
#include "Scene.h"
#include "BoxCollision.h"

class Scene_Game : public Scene {

	GameState m_game_state;

	//ステートパターンの親クラス
	class State : public State_Base {
	protected:
		Scene_Game *m_scene;
	public:
		State(Scene_Game *scene) : m_scene(scene) {}
		virtual ~State() {}

		virtual GameState CheckGameState(GameState game_state) = 0;
	};

	class State_Ready : public State {
	public:
		State_Ready(Scene_Game *scene);
		~State_Ready();

		void Update() override;
		void Draw() override;

		GameState CheckGameState(GameState game_state) override;
	};

	class State_Restart : public State {
	public:
		State_Restart(Scene_Game *scene);
		~State_Restart();

		void Update() override;
		void Draw() override;
		GameState CheckGameState(GameState game_state) override;
	};

	class State_Gameover : public State {
	public:
		State_Gameover(Scene_Game *scene);
		~State_Gameover();

		void Update() override;
		void Draw() override;
		GameState CheckGameState(GameState game_state) override;
	};

	class State_Clear : public State {
	public:
		State_Clear(Scene_Game *scene);
		~State_Clear();

		void Update() override;
		void Draw() override;
		GameState CheckGameState(GameState game_state) override;
	};

	class State_Playerdead : public State {
	public:
		State_Playerdead(Scene_Game *scene);
		~State_Playerdead();

		void Update() override;
		void Draw() override;
		GameState CheckGameState(GameState game_state) override;
	};

	class State_Play : public State {
	public:
		State_Play(Scene_Game *scene);
		~State_Play();
		void Update() override;
		void Draw() override;
		GameState CheckGameState(GameState game_state) override;
	};

	class State_Start : public State {
	public:
		State_Start(Scene_Game *scene);
		~State_Start();
		void Update() override;
		void Draw() override;
		GameState CheckGameState(GameState game_state) override;
	};

	class State_End : public State {
	public:
		State_End(Scene_Game *scene);
		~State_End();
		void Update() override;
		void Draw() override;
		GameState CheckGameState(GameState game_state) override;
	};

public:

	std::vector<std::shared_ptr <Block>> blocks;
	std::shared_ptr <Bar> bar;
	std::shared_ptr <Ball> ball;
	std::shared_ptr <Screen> screen;

	std::shared_ptr<GameOver> gameover;
	std::shared_ptr<Ready> ready;
	std::shared_ptr<Clear> clear;
	std::shared_ptr<PlayerDead> dead;
	std::shared_ptr <GameLife> life;
	std::shared_ptr <GameScore> score;
	std::shared_ptr <GameStageName> stage_name;

	BoxCollision m_ball_dynamics;
	FieldCollision field;

	Scene_Game();
	~Scene_Game();

	void Create() override;

	void Destroy();

	GameState CheckGameState(GameState game_state);

	void BlockInit();

	void BoxInit();
	void ObjInit();
	void Game_ObjInit();
	std::shared_ptr<State> CreateState(GameState state, Scene_Game *scene);

	void ChangeState(GameState old_state, GameState new_state);

	void OnUpdate() override;

	void CheckCollision();

	void OnDraw() override;

	bool CheckClear();
};