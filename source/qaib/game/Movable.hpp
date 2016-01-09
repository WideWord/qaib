#pragma once

#include <qaib/util/Exception.hpp>

#include <glm/vec2.hpp>
#include <glm/mat3x3.hpp>
#include <list>

#include <SFML/Graphics/Transform.hpp>

namespace qaib {

	class Movable {
	private:
		glm::vec2 position;
		float rotation;
	public:
		Movable();

		inline glm::vec2 getPosition() { return position; }
		inline void setPosition(const glm::vec2& pos) { position = pos; }

		inline float getRotation() { return rotation; }
		inline void setRotation(float rot) { rotation = rot; }

		sf::Transform getSFTransform();
	};


}