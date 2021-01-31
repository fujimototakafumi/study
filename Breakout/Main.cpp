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

//使いたいオブジェクトの抽象度によって中継のオブジェクトを増やしていく
//オブジェクトを外側でどう使うか
//先に基底クラスを作るのではなく、徐々に基底クラスを作っていくイメージ？
/// ---

void test()
{
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	ChangeWindowMode(TRUE);
	DxLib_Init();
	SetDrawScreen(DX_SCREEN_BACK);

	std::shared_ptr<Scene> scene;

	scene = std::shared_ptr<Scene_Game>(new Scene_Game());

	//初期処理
	scene->Create();

	int state = 0;

	while (ScreenFlip() == 0 && ProcessMessage() == 0
		&& ClearDrawScreen() == 0 && gpUpdateKey() == 0) {
		scene->Update();
		scene->Draw();
		test();
	}

	scene->Destroy();

	DxLib_End();

	return 0;

}