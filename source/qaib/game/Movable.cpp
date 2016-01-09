#include <qaib/game/Movable.hpp>

#include <glm/gtx/matrix_transform_2d.hpp>

namespace qaib {

	Movable::Movable() {
		rotation = 0;
	}

	sf::Transform Movable::getSFTransform()
	{
		sf::Transform transform;
		transform = transform.translate(position.x, position.y);
		transform = transform.rotate(rotation);
		return transform;
	}

}