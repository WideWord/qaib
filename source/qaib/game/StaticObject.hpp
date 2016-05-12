#pragma once

#include <qaib/game/Movable.hpp>

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <memory>
#include <list>
#include <yaml-cpp/yaml.h>

namespace qaib {

	class StaticObjectClass {
	private:
		std::string name;

		std::string textureFile;
		float spriteScale;
		glm::vec2 centerPoint;

		std::shared_ptr<sf::Texture> texture;
		std::shared_ptr<sf::Sprite> sprite;

		std::vector<b2Vec2> physicsShape;
	public:
		StaticObjectClass(const YAML::Node& def);
		std::shared_ptr<sf::Sprite> getSprite() const;
		std::shared_ptr<b2Shape> getShape() const;

		std::string getName() { return name; }
	};

	class StaticObject: public Movable {
	private:
		StaticObjectClass staticObjectClass;
		b2Body* physicsBody;
	protected:
		friend class GameWorld;
		void setPhysicsBody(b2Body* body) {
			physicsBody = body;
		}
	public:
		StaticObject(StaticObjectClass& cl) : staticObjectClass(cl) {}

		b2Body* getPhysicsBody() {
			return physicsBody;
		}

		inline std::shared_ptr<sf::Sprite> getSprite() const { return staticObjectClass.getSprite(); }
		inline std::shared_ptr<b2Shape> getShape() const { return staticObjectClass.getShape(); }

		virtual glm::vec2 getPosition() const override;
		virtual void setPosition(const glm::vec2& pos) override;

		virtual float getRotation() const override;
		virtual void setRotation(float rot) override;

		virtual ~StaticObject();
	};


}