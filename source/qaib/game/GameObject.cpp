#include <qaib/game/GameObject.hpp>

namespace qaib {

	void GameObject::attachChild(GameObject* child) {
		if (child->parent != nullptr && child->parent != this) {
			qaibRaise(GameObjectAlreadyAttachedException);
		}
		if (child->parent != this) {
			childs.push_back(child);
			child->parent = this;
		}
	}

	void GameObject::detachChild(GameObject* child) {
		if (child->parent != this) {
			qaibRaise(GameObjectNotChildOfThisGameObjectException);
		}
		for (auto it = childs.begin(); it != childs.end(); ++it) {
			if (*it == child) {
				childs.erase(it);
				break;
			}
		}
		child->parent = nullptr;
	}

	GameObject::~GameObject() {}

}