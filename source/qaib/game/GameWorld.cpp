#include <qaib/game/GameWorld.hpp>
#include <qaib/game/Pawn.hpp>

namespace qaib {

	GameWorld::GameWorld() {}

	void GameWorld::addPawn(Pawn* pawn) {
		_pawns.push_back(pawn);
		pawn->movedToGameWorld(this);
	}


	void GameWorld::doTick(float deltaTime) {
		for (auto pawn : _pawns) {
			pawn->applyPawnControl();
		}
	}

	GameWorld::~GameWorld() {
		for (auto pawn : _pawns) {
			delete pawn;
		}
	}

}