#include <qaib/game/Movable.hpp>

#include <glm/gtx/matrix_transform_2d.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <math.h>

namespace qaib {



	sf::Transform Movable::getSFTransform() const
	{
		auto position = getPosition();
		auto rotation = getRotation();

		sf::Transform transform;
		transform = transform.translate(position.x, position.y);
		transform = transform.rotate(rotation / 3.1415f * 180.0f);
		return transform;
	}

	glm::vec2 Movable::getForward() const {
		using namespace glm;

		return rotate(vec2(1, 0), getRotation());
	}

}