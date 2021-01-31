#pragma once
#include "DxLib.h"
#include "Vector2d.h"
#include "Box.h"
#include "GameInfo.h"
#include "Object.h"

struct Block : public Object_GameObject {

	class Block_Box : public Box {
	public:
		Block *m_block;

		Block_Box() {
			m_block = nullptr;
		}

		void Init(Block *block) {
			m_block = block;
		}

		void OnContact() override {
			m_block->OnContact();
		}
	};

	Point2D pos;
	Size2D size;

	std::shared_ptr<Block_Box> box;

	int Color;

	bool islive;

	void Init(int x, int y, int color);

	void Draw();

	bool IsLived();
	std::shared_ptr<Box> CreateBox();

	void OnContact();
};
