#include "SceneNode.hpp"
#include <assert.h>

namespace qaib {

	void SceneNode::addChild(const std::shared_ptr<SceneNode>& sceneNode) {
		assert(sceneNode->parentSceneNode.expired());
		sceneNode->parentSceneNode = shared_from_this();
		childSceneNodes.push_back(sceneNode);
	}

	void SceneNode::removeChild(const std::shared_ptr<SceneNode>& sceneNode) {
		
	}

	void SceneNode::setPosition(const sf::Vector2f & position) {
		this->position = position;
	}

	const sf::Vector2f & SceneNode::getPosition() {
		return position;
	}

	void SceneNode::setRotation(float rotation) {
		this->rotation = rotation;
	}

	float SceneNode::getRotation() {
		return this->rotation;
	}

}