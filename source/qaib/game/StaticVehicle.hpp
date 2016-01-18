#pragma once

#include <qaib/game/StaticObject.hpp>

namespace qaib {

	class StaticVehicle : public StaticObject {
	private:
		static sf::Sprite* vehicleSprite;
		static sf::Texture* vehicleTexture;
	public:
		sf::Sprite* getSprite() override;
		std::shared_ptr<b2Shape> getShape() override;
	};

}