#include <qaib/game/StaticObject.hpp>
#include <qaib/util/VectorConversion.hpp>

namespace qaib {

	StaticObject::~StaticObject() {}

	StaticObjectClass::StaticObjectClass(const YAML::Node &def) {
		name = def["name"].as<std::string>();

		auto spriteNode = def["sprite"];

		textureFile = spriteNode["texture"].as<std::string>();
		spriteScale = spriteNode["scale"].as<float>();

		auto centerNode = spriteNode["center"];
		centerPoint = glm::vec2(centerNode[0].as<float>(), centerNode[1].as<float>());

		auto physicsShapeNode = def["collider"];

		for (int i = 0; i < physicsShapeNode.size(); ++i) {
			auto pointNode = physicsShapeNode[i];

			b2Vec2 point(pointNode[0].as<float>(), pointNode[1].as<float>());

			physicsShape.push_back(point);
		}
	}

	std::shared_ptr<sf::Sprite> StaticObjectClass::getSprite() {
		if (sprite == nullptr) {
			texture = std::make_shared<sf::Texture>();
			texture->loadFromFile(textureFile);
			sprite = std::make_shared<sf::Sprite>(*texture);
			sprite->setOrigin(convert<sf::Vector2f>(centerPoint));
			sprite->setScale(sf::Vector2f(spriteScale, spriteScale));
		}
		return sprite;
	}

	std::shared_ptr<b2Shape> StaticObjectClass::getShape() {
		auto shape = std::make_shared<b2PolygonShape>();
		shape->Set(&physicsShape.front(), physicsShape.size());
		return shape;
	}

}