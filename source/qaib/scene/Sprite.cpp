#include "Sprite.hpp"
#include <SFML/Graphics.hpp>

namespace qaib {

	Sprite::Sprite(const sf::Texture& texture) {
		sfSprite = new sf::Sprite(texture);
	}

	Sprite::~Sprite() {
		delete sfSprite;
	}

	bool Sprite::hasAttachedDrawable() const {
		return true;
	}

	sf::Drawable* Sprite::getAttachedDrawable() {
		return sfSprite;
	}
}


