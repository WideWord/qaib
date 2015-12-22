#include <qaib/game/GameObject.hpp>

#include <glm/gtx/matrix_transform_2d.hpp>

namespace qaib {

	GameObject::GameObject() {
		_rotation = 0;
		_parent = nullptr;
	}

	void GameObject::attachChild(GameObject* child) {
		if (child->_parent != nullptr && child->_parent != this) {
			qaibRaise(GameObjectAlreadyAttachedException);
		}
		if (child->_parent != this) {
			_childs.push_back(child);
			child->_parent = this;
		}
	}

	void GameObject::detachChild(GameObject* child) {
		if (child->_parent != this) {
			qaibRaise(GameObjectNotChildOfThisGameObjectException);
		}
		for (auto it = _childs.begin(); it != _childs.end(); ++it) {
			if (*it == child) {
				_childs.erase(it);
				break;
			}
		}
		child->_parent = nullptr;
	}

	
	glm::mat3 GameObject::absoluteTransform() {
		glm::mat3 transform;

		if (_parent != nullptr)
			transform = _parent->absoluteTransform();

		return glm::translate(glm::rotate(transform, _rotation), _position);
	}

	GameObject::~GameObject() {}

}