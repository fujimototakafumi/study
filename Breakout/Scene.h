#pragma once
#include<memory>
#include<list>

#include "Object.h"

//ヘッダファイルには基本宣言のみを記述、実体はcppで記述する。
class Scene {
protected:
	class State_Base {
	public:
		virtual ~State_Base() {}

		virtual void Update() = 0;
		virtual void Draw() = 0;
	};

	std::shared_ptr<State_Base> m_current_state;

	std::list< std::shared_ptr<Object_GameObject> > m_game_objects;
	std::list< std::shared_ptr<Object_2D> > m_2d_objects;

	template<typename T>
	void ObjectsRemove(std::list<T> &container) {
		std::list<T> removes;
		for (auto &obj : container)
		{
			if (obj->IsDelete()) {
				removes.push_back(obj);
			}
		}

		for (auto &iter : removes) {
			container.remove(iter);
		}
	}
protected:
	virtual void OnUpdate() = 0;
	virtual void OnDraw() = 0;
public:
	virtual void Create() = 0;

	void Update() {
		OnUpdate();

		// 削除フラグが立っている2Dオブジェクトを管理コンテナから除去する
		ObjectsRemove(m_2d_objects);
		// 削除フラグが立っているゲームオブジェクトを管理コンテナから除去する
		ObjectsRemove(m_game_objects);
	}
	void Draw() {
		for (std::shared_ptr<Object_GameObject> obj : m_game_objects) {
			obj->Draw();
		}
		for (std::shared_ptr<Object_2D> obj : m_2d_objects) {
			obj->Draw();
		}

		OnDraw();
	}

	virtual void Destroy() = 0;

};