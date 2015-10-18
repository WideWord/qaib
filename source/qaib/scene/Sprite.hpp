#pragma once

#include <qaib/scene/SceneNode.hpp>

#include <memory>

namespace sf {
	class Sprite;
	class Texture;
	class Drawable;
}

namespace qaib {

	class Sprite : public SceneNode {
	private:
		sf::Sprite* sfSprite;
	protected:
		virtual bool hasAttachedDrawable() const override;
		virtual sf::Drawable* getAttachedDrawable() override;
	public:
		Sprite(const sf::Texture& texture);
		virtual ~Sprite();

	};

}
