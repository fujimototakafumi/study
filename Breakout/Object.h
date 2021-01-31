#pragma once

class Object {
public:
	bool m_is_delete;

	Object() :m_is_delete(false) {

	}
	virtual ~Object() {}

	bool IsDelete() const {
		return m_is_delete;
	}
	void Delete() {
		m_is_delete = true;
	}
};

class Object_2D : public Object {
public:
	bool m_is_show;
	//bool m_is_delete;

	Object_2D() : m_is_show(false)/*, m_is_delete(false)*/ {
	}
	void Show(bool is_show) {
		m_is_show = is_show;
	}

	virtual void Draw() = 0;
};

class Object_GameObject : public Object {
public:
	bool m_is_show;

	Object_GameObject() : m_is_show(false) {
	}
	void Show(bool is_show) {
		m_is_show = is_show;
	}

	virtual void Draw() = 0;
};