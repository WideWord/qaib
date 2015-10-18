#include "SceneNode.hpp"
#include <assert.h>

namespace qaib {

	SceneNode::~SceneNode() {
		for (auto child : childSceneNodes) {
			delete child;
		}
	}

	bool SceneNode::hasAttachedDrawable() const {
		return false;
	}

	sf::Drawable* SceneNode::getAttachedDrawable() {
		return nullptr;
	}

	void SceneNode::addChild(SceneNode* sceneNode) {
		assert(sceneNode->parentSceneNode == nullptr);
		sceneNode->parentSceneNode = this;
		childSceneNodes.push_back(sceneNode);
	}

	void SceneNode::removeChild(SceneNode* sceneNode) {
		for (auto it = childSceneNodes.begin(); it != childSceneNodes.end(); ++it) {
			if (*it == sceneNode) {
				childSceneNodes.erase(it);
				sceneNode->parentSceneNode = nullptr;
				return;
			}
		}
	}

	void SceneNode::calculateAbsoluteTransform() {
		sf::Transform newAbsoluteTransform;

		if (parentSceneNode == nullptr) {
			newAbsoluteTransform = sf::Transform();
		}
		else {
			newAbsoluteTransform = parentSceneNode->getAbsoluteTransform();
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