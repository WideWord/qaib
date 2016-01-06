#pragma once

namespace qaib {

	class GameWorld;

	class KeptInGameWorld {
	private:
		GameWorld* _world;
	public:
		GameWorld* gameWorld() { return _world; }
		void movedToGameWorld(GameWorld* newWorld); // weak ref
	};

}