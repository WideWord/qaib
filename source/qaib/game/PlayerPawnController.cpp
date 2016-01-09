#include <qaib/game/PlayerPawnController.hpp>
#include <glm/geometric.hpp>

using glm::vec2;

namespace qaib {

	glm::vec2 PlayerPawnController::movementDirection() {
		vec2 dir;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) dir.x -= 1;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) dir.x += 1;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) dir.y -= 1;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) dir.y += 1;

		return dir;
	}

	float PlayerPawnController::turningToAngle() {
		return 0.0f;
	}

	bool PlayerPawnController::shouldDropWeapon() {
		return false;
	}

	bool PlayerPawnController::shouldTakeWeapon() {
		return false;
	}

	bool PlayerPawnController::shouldAttack() {
		return false;
	}



}