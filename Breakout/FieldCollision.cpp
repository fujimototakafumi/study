#pragma once
#include "box.h"
#include <list>
#include "FieldCollision.h"

void FieldCollision::AddBox(std::shared_ptr<Box> box)
{
	m_collisions.push_back(box);
}