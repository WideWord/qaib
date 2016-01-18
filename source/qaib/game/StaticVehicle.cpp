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

	std::shared_ptr<b2Shape> StaticVehicle::getShape() {
		auto shape = std::make_shared<b2PolygonShape>();
		shape->SetAsBox(0.7f, 1.9f);
		return shape;
	}

}