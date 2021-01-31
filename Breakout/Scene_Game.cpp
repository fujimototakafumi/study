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
#include "box.h"
#include "fieldcollision.h"
#include "GameInfo.h"
#include "Object.h"
#include "Object_2D.h"
#include "Block.h"
#include "Screen.h"
#include "Bar.h"
#include "Ball.h"
#include "Scene.h"
#include "Scene_Game.h"
#include "BoxCollision.h"
#include "BarDeathAnimation.h"

Scene_Game::State_Ready::State_Ready(Scene_Game *scene) : State(scene) {
	GameInfo::Instance().Init();
	m_scene->bar->Init();
	m_scene->bar->Show(true);
	m_scene->BlockInit();
	m_scene->screen->Init();
	m_scene->life->Show(true);
	m_scene->score->Show(true);
	m_scene->stage_name->Show(true);
	m_scene->BoxInit();

	m_scene->ready = std::shared_ptr <Ready>(new Ready);
	m_scene->m_2d_objects.push_back(m_scene->ready);
	m_scene->ready->Show(true);

	m_scene->ball->Init();

}
Scene_Game::State_Ready::~State_Ready() {
	m_scene->ready->Delete();
	m_scene->ready.reset();
}

void Scene_Game::State_Ready::Update() {
}

void Scene_Game::State_Ready::Draw() {
	m_scene->ready->Draw();
}

GameState Scene_Game::State_Ready::CheckGameState(GameState game_state) {
	if (IsKeyPress(KEY_INPUT_RETURN)) {
		game_state = START;
	}
	return game_state;
}

Scene_Game::State_Restart::State_Restart(Scene_Game *scene) : State(scene) {
	m_scene->ball->Init();
	m_scene->bar->Show(true);
}
Scene_Game::State_Restart::~State_Restart() {
}

void Scene_Game::State_Restart::Update() {
}
void Scene_Game::State_Restart::Draw() {
}

GameState Scene_Game::State_Restart::CheckGameState(GameState game_state) {
	game_state = PLAY;
	return game_state;
}

Scene_Game::State_Gameover::State_Gameover(Scene_Game *scene) : State(scene) {
	m_scene->gameover->Show(true);
}
Scene_Game::State_Gameover::~State_Gameover() {
	m_scene->gameover->Show(false);
}

void Scene_Game::State_Gameover::Update() {}
void Scene_Game::State_Gameover::Draw() {}

GameState Scene_Game::State_Gameover::CheckGameState(GameState game_state) {
	if (IsKeyPress(KEY_INPUT_SPACE)) {
		game_state = NONE;
	}
	return game_state;
}

Scene_Game::State_Clear::State_Clear(Scene_Game *scene) : State(scene) {
	m_scene->clear->Show(true);
}
Scene_Game::State_Clear::~State_Clear() {
	m_scene->clear->Show(false);
}

void Scene_Game::State_Clear::Update() {
}
void Scene_Game::State_Clear::Draw() {
}

GameState Scene_Game::State_Clear::CheckGameState(GameState game_state) {
	if (IsKeyPress(KEY_INPUT_SPACE)) {
		game_state = NONE;
	}
	return game_state;
}

Scene_Game::State_Playerdead::State_Playerdead(Scene_Game *scene) : State(scene) {
	GameInfo::Instance().SubScore();
	m_scene->bar->Show(false);
	m_scene->dead->Show(true);

	auto bar_dead_animation = std::shared_ptr<BarDeathAnimation>(new BarDeathAnimation());
	bar_dead_animation->Init(m_scene->bar);
	m_scene->m_game_objects.push_back(bar_dead_animation);
}
Scene_Game::State_Playerdead::~State_Playerdead() {
	m_scene->dead->Show(false);
}

void Scene_Game::State_Playerdead::Update() {}
void Scene_Game::State_Playerdead::Draw() {}
GameState Scene_Game::State_Playerdead::CheckGameState(GameState game_state) {
	if (GameInfo::Instance().IsNoLife()) {
		game_state = GAME_OVER;
	}

	if (IsKeyPress(KEY_INPUT_Y)) {
		game_state = RESTART;
	}
	return game_state;
}

Scene_Game::State_Play::State_Play(Scene_Game *scene) : State(scene) {
}
Scene_Game::State_Play::~State_Play() {
}

void Scene_Game::State_Play::Update() {
	m_scene->ball->Update();
	m_scene->bar->Update(m_scene->screen);
}
void Scene_Game::State_Play::Draw() {
}
GameState Scene_Game::State_Play::CheckGameState(GameState game_state) {
	if (m_scene->CheckClear()) {
		game_state = CLEAR;
	}
	if (m_scene->ball->IsFalldeath(m_scene->screen)) {
		game_state = PLAYER_DEAD;
	}
	return game_state;
}

Scene_Game::State_Start::State_Start(Scene_Game *scene) : State(scene) {
}
Scene_Game::State_Start::~State_Start() {
}

void Scene_Game::State_Start::Update() {}
void Scene_Game::State_Start::Draw() {}
GameState Scene_Game::State_Start::CheckGameState(GameState game_state) {
	game_state = PLAY;
	return game_state;
}

Scene_Game::State_End::State_End(Scene_Game *scene) : State(scene) {}
Scene_Game::State_End::~State_End() {}

void Scene_Game::State_End::Update() {
}
void Scene_Game::State_End::Draw() {
}
GameState Scene_Game::State_End::CheckGameState(GameState game_state) {
	return game_state;
}


Scene_Game::Scene_Game() {
	m_current_state = nullptr;
}
Scene_Game::~Scene_Game() {
	Destroy();
}

void Scene_Game::Create() {
	m_game_state = NONE;

	ObjInit();
	Game_ObjInit();
}

void Scene_Game::Destroy() {
	blocks.clear();
}

GameState Scene_Game::CheckGameState(GameState game_state)
{
	if (!m_current_state) {
		game_state = READY;
	}
	else {
		std::shared_ptr<State> p = std::dynamic_pointer_cast<State>(m_current_state);
		game_state = p->CheckGameState(game_state);
	}
	return game_state;
}

void Scene_Game::BlockInit() {
	//ブロック
	int j = 0;
	int next = 0;
	for (int i = 0; i < BLOCK_NUM; i++) {
		if (i % 11 == 0) {
			next += 20;
			j = 0;
		}

		int x1 = 25 + 40 * j;
		int y1 = 100 + next;

		blocks[i]->Init(x1, y1, GetColor(200 + j, 20 * j, 255));
		j++;
	}
}

void Scene_Game::BoxInit() {
	field.m_collisions.clear();
	//壁
	{
		std::shared_ptr<Box> box = screen->CreateBox();
		field.AddBox(box);
	}

	//ブロック
	for (int i = 0; i < BLOCK_NUM; i++) {
		if (blocks[i]->IsLived()) {
			std::shared_ptr<Box> box = blocks[i]->CreateBox();
			field.AddBox(box);
		}
	}
}
void Scene_Game::ObjInit() {
	gameover = std::shared_ptr<GameOver>(new GameOver);
	clear = std::shared_ptr <Clear>(new Clear);
	dead = std::shared_ptr <PlayerDead>(new PlayerDead);

	life = std::shared_ptr <GameLife>(new GameLife);
	score = std::shared_ptr <GameScore>(new GameScore);
	stage_name = std::shared_ptr <GameStageName>(new GameStageName);

	m_2d_objects.push_back(gameover);
	//m_2d_objects.push_back(ready);
	m_2d_objects.push_back(clear);
	m_2d_objects.push_back(dead);
	m_2d_objects.push_back(life);
	m_2d_objects.push_back(score);
	m_2d_objects.push_back(stage_name);
}
void Scene_Game::Game_ObjInit() {

	ball = std::shared_ptr <Ball>(new Ball);
	m_game_objects.push_back(ball);

	for (int i = 0; i < BLOCK_NUM; i++) {
		std::shared_ptr < Block> block = std::shared_ptr<Block>(new Block);
		blocks.push_back(block);
	}
	bar = std::shared_ptr<Bar>(new Bar);
	screen = std::shared_ptr <Screen>(new Screen);

	m_game_objects.push_back(bar);
	for (std::shared_ptr<Block> block : blocks) {
		m_game_objects.push_back(block);
	}

}
std::shared_ptr<Scene_Game::State> Scene_Game::CreateState(GameState state, Scene_Game *scene) {
	std::shared_ptr<State> new_state;

	switch (state) {
	case READY:
		new_state = std::shared_ptr<State>(new State_Ready(scene));
		break;
	case RESTART:
		new_state = std::shared_ptr<State>(new State_Restart(scene));
		break;
	case GAME_OVER:
		new_state = std::shared_ptr<State>(new State_Gameover(scene));
		break;
	case CLEAR:
		new_state = std::shared_ptr<State>(new State_Clear(scene));
		break;
	case PLAYER_DEAD:
		new_state = std::shared_ptr<State>(new State_Playerdead(scene));
		break;
	case PLAY:
		new_state = std::shared_ptr<State>(new State_Play(scene));
		break;
	case START:
		new_state = std::shared_ptr<State>(new State_Start(scene));
		break;
	case END:
		new_state = std::shared_ptr<State>(new State_End(scene));
		break;
	}
	return new_state;
}

void Scene_Game::ChangeState(GameState old_state, GameState new_state)
{
	m_current_state.reset();

	m_current_state = CreateState(new_state, this);
}


void Scene_Game::OnUpdate() {
	while (true) {
		const auto old_state = m_game_state;
		const auto new_state = CheckGameState(m_game_state);
		if (old_state != new_state) {
			ChangeState(old_state, new_state);
			m_game_state = new_state;
		}
		else {
			break;
		}
	}


	/* ObjectsRemoveと同じことやってる
	生成されたObjectの継承クラスのインスタンスを削除
	std::list< std::shared_ptr<Object_GameObject> > game_obj_removes;
	for (std::list< std::shared_ptr<Object_GameObject> >::iterator iter = m_game_objects.begin(); iter != m_game_objects.end(); ++iter)
	{
		auto obj = *iter;

		if (obj->IsDelete()) {
			game_obj_removes.push_back(obj);
		}
	}

	for (auto &iter : game_obj_removes) {
		m_game_objects.remove(iter);
	}
	*/

	if (m_current_state) {
		m_current_state->Update();
		m_current_state->Draw();
	}

	//衝突周り
	CheckCollision();
}

void Scene_Game::CheckCollision() {
	//バー
	auto box = bar->CreateBox();
	field.AddBox(box);

	m_ball_dynamics.Update(ball, &field);

	box->Delete();
}

void Scene_Game::OnDraw() {
}

bool Scene_Game::CheckClear() {
	for (int i = 0; i < BLOCK_NUM; i++) {
		if (blocks[i]->IsLived()) {
			return false;
		}
	}
	return true;
}