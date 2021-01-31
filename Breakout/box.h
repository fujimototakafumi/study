#pragma once
#include "Vector2d.h"

struct Box {
	bool m_is_inner;
	Point2D pos1;
	Size2D size;
	bool m_is_delete;

	Box();

	void Delete();

	virtual void OnContact();

	static std::shared_ptr<Box> Create(const Point2D &pos, const Size2D &size) {
		std::shared_ptr<Box> box(new Box);
		box->pos1 = pos;
		box->size = size;
		return box;
	}

	template<typename T>
	static std::shared_ptr<T> Create(const Point2D &pos, const Size2D &size) {
		std::shared_ptr<T> box(new T);
		box->pos1 = pos;
		box->size = size;
		return box;
	}
};
