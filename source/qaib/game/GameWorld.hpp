#pragma once

namespace qaib {

	class GameObject;

	class GameWorld {
	private:
		GameObject* _rootGameObject;
	public:
		GameWorld();
		~GameWorld();

		inline GameObject* rootGameObject() { return _rootGameObject; }
	
	
	};

}