#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

namespace qaib {

	class SceneNode;
	class Camera;

	class SceneRenderer {
	private:
		void drawSceneNode(
			const std::shared_ptr<sf::RenderTarget>& target,
			const std::shared_ptr<SceneNode>& sceneNode,
			const std::shared_ptr<Camera>& camera);
	public:
		void drawScene(
			const std::shared_ptr<sf::RenderTarget>& target,
			const std::shared_ptr<SceneNode>& rootSceneNode,
			const std::shared_ptr<Camera>& camera
			);

	};

}