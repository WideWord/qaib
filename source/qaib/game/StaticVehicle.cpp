#include <qaib/game/StaticVehicle.hpp>

namespace qaib {

	sf::Sprite* StaticVehicle::vehicleSprite = nullptr;
	sf::Texture* StaticVehicle::vehicleTexture = nullptr;

	sf::Sprite* StaticVehicle::getSprite() {
		if (vehicleSprite == nullptr) {
			vehicleSprite = new sf::Sprite();
			vehicleTexture = new sf::Texture();
			vehicleTexture->loadFromFile("data/art/static/veh_pickup.png");
			vehicleSprite->setTexture(*vehicleTexture);
			vehicleSprite->setOrigin(sf::Vector2f(vehicleTexture->getSize()) / 2.0f);
			vehicleSprite->setScale(1.0f / 50.0f, 1.0f / 50.0f);
		}
		return vehicleSprite;
	}

}