#pragma once

#include <qaib/util/Exception.hpp>

#include <glm/vec2.hpp>
#include <glm/mat3x3.hpp>
#include <list>

namespace qaib {

	class GameObject {
	private:
		glm::vec2 _position;
		float _rotation;
		std::list<GameObject*> _childs;
		GameObject* _parent;


	public:
		GameObject();

		void attachChild(GameObject* child);
		void detachChild(GameObject* child);

		inline auto position() { return _position; }
		inline void setPosition(const glm::vec2& pos) { _position = pos; }

		inline auto rotation() { return _rotation; }
		inline auto setRotation(float rot) { _rotation = rot; }

		glm::mat3 absoluteTransform();

		virtual ~GameObject();
	};


	qaibExceptionDecl(GameObjectException, "", Exception);

	qaibExceptionDecl(
		GameObjectAlreadyAttachedException,
		"GameObject already attached to other GameObject",
		GameObjectException);

	qaibExceptionDecl(
		GameObjectNotChildOfThisGameObjectException,
		"GameObject is not a child of this GameObject",
		GameObjectException
		);

}