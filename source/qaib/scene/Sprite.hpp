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
		std::shared_ptr<sf::Sprite> sfSprite;
	protected:
		virtual bool hasAttachedDrawable() const override;
		virtual std::weak_ptr<sf::Drawable> getAttachedDrawable() override;
	public:
		Sprite(const sf::Texture& texture);

	};

}
