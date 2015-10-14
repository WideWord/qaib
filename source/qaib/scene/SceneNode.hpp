#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <list>
#include <memory>

namespace qaib {

	class SceneRenderer;

	class SceneNode : public std::enable_shared_from_this<SceneNode> {
	private:
		sf::Vector2f position;
		float rotation;
		std::list< std::shared_ptr<SceneNode> > childSceneNodes;

		sf::Transform absoluteTransform;

		void calculateAbsoluteTransform();
	protected:
		std::weak_ptr<SceneNode> parentSceneNode;

		friend class SceneRenderer;
		virtual bool hasAttachedDrawable() const;
		virtual std::weak_ptr<sf::Drawable> getAttachedDrawable();

		inline const std::list< std::shared_ptr<SceneNode> >& getChildSceneNodes() {
			return childSceneNodes;
		}
	public:
		inline SceneNode() {
			rotation = 0;
		}

		void addChild(const std::shared_ptr<SceneNode>& sceneNode);
		void removeChild(const std::shared_ptr<SceneNode>& sceneNode);

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
