#include <qaib/app/PlayingGameApplication.hpp>
#include <qaib/game/Pawn.hpp>
#include <qaib/game/PlayerPawnController.hpp>

namespace qaib {

	PlayingGameApplication::PlayingGameApplication() {
		gameRenderer.setGameWorld(&gameWorld);

		Pawn* pawn = new Pawn();
		gameWorld.addPawn(pawn);

		pawn->setController(new PlayerPawnController());
	}

	void PlayingGameApplication::doFrame() {
		gameWorld.doTick(0.0f);
		gameRenderer.drawFrame(getMainTarget());
	}
}