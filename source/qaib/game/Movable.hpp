#pragma once

#include <qaib/util/Exception.hpp>

#include <glm/vec2.hpp>
#include <glm/mat3x3.hpp>
#include <list>

#include <SFML/Graphics/Transform.hpp>

namespace qaib {

	class Movable {
	public:

		virtual glm::vec2 getPosition() const = 0;
		virtual void setPosition(const glm::vec2& pos) = 0;

		virtual float getRotation() const = 0;
		virtual void setRotation(float rot) = 0;

		glm::vec2 getForward() const;

		sf::Transform getSFTransform() const;
	};


}