#pragma once

#include <qaib/game/Movable.hpp>
#include <qaib/game/KeptInGameWorld.hpp>

#include <Box2D/Box2D.h>

namespace qaib {

	class StaticObject: public Movable, public KeptInGameWorld {
	private:
	public:
		//virtual b2FixtureDef physicsShape();
	};

}