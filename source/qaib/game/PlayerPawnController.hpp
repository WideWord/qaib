#pragma once

#include <qaib/game/PawnController.hpp>
#include <SFML/Window.hpp>

namespace qaib {

	class GameRenderer;

	class PlayerPawnController: public PawnController {
	private:
		GameRenderer& gameRenderer;
		sf::Window& window;
	public:
		PlayerPawnController(GameRenderer& gameRenderer, sf::Window& window);

		glm::vec2 movementDirection() override;
		glm::vec2 turningTo() override;
		bool shouldAttack() override;
	};

}