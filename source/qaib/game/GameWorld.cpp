#include <qaib/game/GameWorld.hpp>
#include <qaib/game/Pawn.hpp>

namespace qaib {

	GameWorld::GameWorld() {}

	void GameWorld::addPawn(Pawn* pawn) {
		pawns.push_back(pawn);
		pawn->movedToGameWorld(this);
	}


	void GameWorld::doTick(float deltaTime) {
		for (auto pawn : pawns) {
			pawn->applyPawnControl(deltaTime);
		}
	}

	GameWorld::~GameWorld() {
		for (auto pawn : pawns) {
			delete pawn;
		}
	}

}