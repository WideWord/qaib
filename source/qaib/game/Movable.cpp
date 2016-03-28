#include <qaib/game/Movable.hpp>

#include <glm/gtx/matrix_transform_2d.hpp>
#include <math.h>

namespace qaib {

	Movable::Movable() {
		rotation = 0;
	}

	sf::Transform Movable::getSFTransform() const
	{
		sf::Transform transform;
		transform = transform.translate(position.x, position.y);
		transform = transform.rotate(rotation / 3.1415f * 180.0f);
		return transform;
	}

}