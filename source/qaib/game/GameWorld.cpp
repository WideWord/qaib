#include <qaib/game/GameWorld.hpp>
#include <qaib/game/Pawn.hpp>

namespace qaib {

	void GameWorld::addPawn(Pawn* pawn) {
		pawns.push_back(pawn);
		pawn->movedToGameWorld(this);
	}


	void GameWorld::doTick(float deltaTime) {

	}

	GameWorld::~GameWorld() {
		for (auto pawn : pawns) {
			delete pawn;
		}
	}

}