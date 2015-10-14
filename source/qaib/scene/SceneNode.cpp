#include "SceneNode.hpp"
#include <assert.h>

namespace qaib {

	bool SceneNode::hasAttachedDrawable() const {
		return false;
	}

	std::weak_ptr<sf::Drawable> SceneNode::getAttachedDrawable() {
		return std::weak_ptr<sf::Drawable>();
	}

	void SceneNode::addChild(const std::shared_ptr<SceneNode>& sceneNode) {
		assert(sceneNode->parentSceneNode.expired());
		sceneNode->parentSceneNode = shared_from_this();
		childSceneNodes.push_back(sceneNode);
	}

	void SceneNode::removeChild(const std::shared_ptr<SceneNode>& sceneNode) {
		for (auto it = childSceneNodes.begin(); it != childSceneNodes.end(); ++it) {
			if (*it == sceneNode) {
				childSceneNodes.erase(it);
				return;
			}
		}
	}

	void SceneNode::calculateAbsoluteTransform() {
		sf::Transform newAbsoluteTransform;

		if (parentSceneNode.expired()) {
			newAbsoluteTransform = sf::Transform();
		}
		else {
			newAbsoluteTransform = parentSceneNode.lock()->getAbsoluteTransform();
		}

		newAbsoluteTransform = newAbsoluteTransform.translate(position).rotate(rotation);

		absoluteTransform = newAbsoluteTransform;
	}

	void SceneNode::flushTransform() {
		calculateAbsoluteTransform();

		for (auto& child : childSceneNodes) {
			child->flushTransform();
		}
	}
}