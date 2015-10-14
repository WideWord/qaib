#include <qaib/graphics/SceneRenderer.hpp>
#include <qaib/scene/SceneNode.hpp>
#include <qaib/scene/Camera.hpp>

namespace qaib {

	void SceneRenderer::drawScene(
		const std::shared_ptr<sf::RenderTarget>& target,
		const std::shared_ptr<SceneNode>& rootSceneNode,
		const std::shared_ptr<Camera>& camera) {

		rootSceneNode->flushTransform();

		drawSceneNode(target, rootSceneNode, camera);
	}

	void SceneRenderer::drawSceneNode(
		const std::shared_ptr<sf::RenderTarget>& target,
		const std::shared_ptr<SceneNode>& sceneNode,
		const std::shared_ptr<Camera>& camera) {

		if (sceneNode->hasAttachedDrawable()) {
			std::shared_ptr<sf::Drawable> drawable = sceneNode->getAttachedDrawable().lock();
			
			sf::Transform transform = sceneNode->getAbsoluteTransform();

			transform = transform.combine(camera->getAbsoluteTransform().getInverse());

			target->draw(*drawable, sf::RenderStates(transform));
		}

		for (auto& childSceneNode : sceneNode->getChildSceneNodes()) {
			drawSceneNode(target, childSceneNode, camera);
		}
	}

}
