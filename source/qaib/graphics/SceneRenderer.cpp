#include <qaib/graphics/SceneRenderer.hpp>
#include <qaib/scene/SceneNode.hpp>
#include <qaib/scene/Camera.hpp>

namespace qaib {

	void SceneRenderer::drawScene(
		sf::RenderTarget* target,
		SceneNode* rootSceneNode,
		Camera* camera) {

		rootSceneNode->flushTransform();

		drawSceneNode(target, rootSceneNode, camera);
	}

	void SceneRenderer::drawSceneNode(
		sf::RenderTarget* target,
		SceneNode* sceneNode,
		Camera* camera) {

		if (sceneNode->hasAttachedDrawable()) {
			auto drawable = sceneNode->getAttachedDrawable();
			
			auto transform = sceneNode->getAbsoluteTransform();

			transform = transform.combine(camera->getAbsoluteTransform().getInverse());

			target->draw(*drawable, sf::RenderStates(transform));
		}

		for (auto childSceneNode : sceneNode->getChildSceneNodes()) {
			drawSceneNode(target, childSceneNode, camera);
		}
	}

}
