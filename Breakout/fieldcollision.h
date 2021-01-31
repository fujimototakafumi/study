#pragma once
#include "box.h"
#include <list>

class FieldCollision {
public:
	std::list<std::shared_ptr<Box>> m_collisions;

	void AddBox(std::shared_ptr<Box> box);
};
