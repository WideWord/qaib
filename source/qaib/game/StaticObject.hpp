#pragma once

#include <qaib/game/Movable.hpp>
#include <qaib/game/KeptInGameWorld.hpp>

#include <SFML/Graphics.hpp>

#include <Box2D/Box2D.h>

namespace qaib {

	class StaticObject: public Movable, public KeptInGameWorld {
	public:
		virtual sf::Sprite* getSprite() = 0;
		virtual ~StaticObject();
	};

}