#include <qaib/game/KeptInGameWorld.hpp>

#include <assert.h>

namespace qaib {

	void KeptInGameWorld::movedToGameWorld(GameWorld* newWorld) {
		assert(_world == nullptr || _world == newWorld);
		_world = newWorld;
	}

}