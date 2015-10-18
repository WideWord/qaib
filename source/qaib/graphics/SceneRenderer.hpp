#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

namespace qaib {

	class SceneNode;
	class Camera;

	class SceneRenderer {
	private:
		void drawSceneNode(
			sf::RenderTarget* target,
			SceneNode* sceneNode,
			Camera* camera
			);
	public:
		void drawScene(
			sf::RenderTarget* target,
			SceneNode* sceneNode,
			Camera* camera
			);

	};

}