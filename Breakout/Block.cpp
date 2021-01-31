#pragma once
#include "DxLib.h"
#include "Vector2d.h"
#include "Box.h"
#include "GameInfo.h"
#include "Object.h"
#include "Block.h"


void Block::Init(int x, int y, int color) {
	pos.x = (float)x;
	pos.y = (float)y;

	//size.x = 10;
	//size.y = 100;

	size.x = 35;
	size.y = 15;

	//本物
	//x2 = x1 + 35;
	//y2 = y1 + 15;

	Color = color;
	islive = true;
}

void Block::Draw() {
	if (islive) {
		DrawBoxAA(pos.x, pos.y, pos.x + size.x, pos.y + size.y, Color, true);
	}
};

bool Block::IsLived() {
	return islive;
}

std::shared_ptr<Box> Block::CreateBox() {
	box = std::shared_ptr<Block_Box>(new Block_Box());
	box->pos1 = pos;
	box->size = size;
	box->Init(this);

	//box = Box::Create<Block_Box>(pos, size);
	//box->Init(this);
	return box;
}


void Block::OnContact() {
	box->Delete();
	box.reset();
	islive = false;

	GameInfo::Instance().AddScore();
}

