#pragma once

#include <qaib/util/Exception.hpp>

#include <SFML/System.hpp>
#include <list>

namespace qaib {

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

	class GameObject {
	private:
		sf::Vector2f position;
		float rotation;
		std::list<GameObject*> childs;
		GameObject* parent;
	public:
		void attachChild(GameObject* child);
		void detachChild(GameObject* child);

		virtual ~GameObject();
	};

}