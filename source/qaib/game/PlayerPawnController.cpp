#include <qaib/game/PlayerPawnController.hpp>

#include <qaib/gfx/GameRenderer.hpp>
#include <qaib/game/Pawn.hpp>
#include <glm/geometric.hpp>
using glm::vec2;

namespace qaib {

	PlayerPawnController::PlayerPawnController(GameRenderer& gameRenderer, sf::Window& window)
		: gameRenderer(gameRenderer), window(window) {

	}

	glm::vec2 PlayerPawnController::movementDirection() {
		vec2 dir;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) dir.x -= 1;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) dir.x += 1;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) dir.y -= 1;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) dir.y += 1;



		return dir;
	}

	glm::vec2 PlayerPawnController::turningTo() {
		
		sf::Vector2f mouseScreenPos = sf::Vector2f(sf::Mouse::getPosition(window));
		//mouseScreenPos.y = window.getSize().y - mouseScreenPos.y;


		glm::vec2 mouseWorldPos = gameRenderer.screenToWorldPosition(glm::vec2(mouseScreenPos.x, mouseScreenPos.y));
	
		glm::vec2 playerToMouse = mouseWorldPos - getPawn()->getPosition();

		return playerToMouse;
	}

	bool PlayerPawnController::shouldAttack() {
		return sf::Mouse::isButtonPressed(sf::Mouse::Left);
	}



}