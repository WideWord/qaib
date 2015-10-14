#include <qaib/graphics/SceneRenderer.hpp>
#include <qaib/scene/SceneNode.hpp>

namespace qaib {

	void SceneRenderer::drawScene(
		const std::shared_ptr<sf::RenderTarget>& target,
		const std::shared_ptr<SceneNode>& rootSceneNode) {

		rootSceneNode->flushTransform();

		drawSceneNode(target, rootSceneNode);
	}

	void SceneRenderer::drawSceneNode(
		const std::shared_ptr<sf::RenderTarget>& target,
		const std::shared_ptr<SceneNode>& sceneNode) {

		if (sceneNode->hasAttachedDrawable()) {
			std::shared_ptr<sf::Drawable> drawable = sceneNode->getAttachedDrawable().lock();
			sf::RenderStates states;
			states.transform = sceneNode->getAbsoluteTransform();
			target->draw(*drawable, states);
		}

		for (auto& childSceneNode : sceneNode->getChildSceneNodes()) {
			drawSceneNode(target, childSceneNode);
		}
	}

}
