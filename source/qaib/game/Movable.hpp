#pragma once

#include <qaib/util/Exception.hpp>

#include <glm/vec2.hpp>
#include <glm/mat3x3.hpp>
#include <list>

namespace qaib {

	class Movable {
	private:
		glm::vec2 _position;
		float _rotation;
	public:
		Movable();

		inline auto position() { return _position; }
		inline void setPosition(const glm::vec2& pos) { _position = pos; }

		inline auto rotation() { return _rotation; }
		inline auto setRotation(float rot) { _rotation = rot; }
	};


}