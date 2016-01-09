#pragma once

#include <qaib/game/PawnController.hpp>
#include <SFML/Window.hpp>

namespace qaib {

	class PlayerPawnController: public PawnController {
	public:


		glm::vec2 movementDirection() override;
		float turningToAngle() override;
		bool shouldDropWeapon() override;
		bool shouldTakeWeapon() override;
		bool shouldAttack() override;
	};

}