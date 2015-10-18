#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <list>

namespace qaib {

	class SceneRenderer;

	class SceneNode {
	private:
		sf::Vector2f position;
		float rotation;

		std::list<SceneNode*> childSceneNodes;

		sf::Transform absoluteTransform;

		void calculateAbsoluteTransform();
	protected:
		SceneNode* parentSceneNode;

		friend SceneRenderer;
		virtual bool hasAttachedDrawable() const;
		virtual sf::Drawable* getAttachedDrawable();

		inline const std::list<SceneNode*>& getChildSceneNodes() {
			return childSceneNodes;
		}
	public:
		inline SceneNode() {
			rotation = 0;
			parentSceneNode = nullptr;
		}
		virtual ~SceneNode();

		void addChild(SceneNode* sceneNode);
		void removeChild(SceneNode* sceneNode);

		inline void setPosition(const sf::Vector2f& _position) {
			position = _position;
		}

		inline const sf::Vector2f& getPosition() const {
			return position;
		}

		inline void setRotation(float _rotation) {
			rotation = _rotation;
		}

		inline float getRotation() const {
			return rotation;
		}

		inline const sf::Transform& getAbsoluteTransform() const {
			return absoluteTransform;
		}

		virtual void flushTransform();
	};

}
