#include <qaib/game/GameWorld.hpp>
#include <qaib/game/GameObject.hpp>

namespace qaib {

	GameWorld::GameWorld() {
		_rootGameObject = new GameObject();
	}

	GameWorld::~GameWorld() {
		delete _rootGameObject;
	}


}