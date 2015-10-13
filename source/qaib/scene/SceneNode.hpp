#pragma once
#include <SFML/System.hpp>
#include <list>
#include <memory>

namespace qaib {

	class SceneNode : std::enable_shared_from_this<SceneNode> {
	private:
		sf::Vector2f position;
		float rotation;
		std::list< std::shared_ptr<SceneNode> > childSceneNodes;
	protected:
		std::weak_ptr<SceneNode> parentSceneNode;
	public:
		void addChild(const std::shared_ptr<SceneNode>& sceneNode);
		void removeChild(const std::shared_ptr<SceneNode>& sceneNode);

		void setPosition(const sf::Vector2f& position);
		const sf::Vector2f& getPosition();

		void setRotation(float rotation);
		float getRotation();


	};

}
