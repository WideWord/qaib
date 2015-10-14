#include "Sprite.hpp"
#include <SFML/Graphics.hpp>

namespace qaib {

	Sprite::Sprite(const sf::Texture & texture) {
		sfSprite = std::make_shared<sf::Sprite>(texture);
	}

	bool Sprite::hasAttachedDrawable() const {
		return true;
	}

	std::weak_ptr<sf::Drawable> Sprite::getAttachedDrawable() {
		return std::weak_ptr<sf::Drawable>(sfSprite);
	}
}


