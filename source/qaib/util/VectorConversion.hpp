#pragma once

#include <glm/vec2.hpp>
#include <SFML/System/Vector2.hpp>
#include <Box2D/Common/b2Math.h>

namespace qaib {

    template<typename F, typename T> F convert(const T& smth) {
        return F();
    };

    template<> b2Vec2 convert<b2Vec2, glm::vec2>(const glm::vec2& vec) {
        return b2Vec2(vec.x, vec.y);
    };

    template<> b2Vec2 convert<b2Vec2, sf::Vector2f>(const sf::Vector2f& vec) {
        return b2Vec2(vec.x, vec.y);
    };

    template<> sf::Vector2f convert<sf::Vector2f, b2Vec2>(const b2Vec2& vec) {
        return sf::Vector2f(vec.x, vec.y);
    };

    template<> sf::Vector2f convert<sf::Vector2f, glm::vec2>(const glm::vec2& vec) {
        return sf::Vector2f(vec.x, vec.y);
    };

    template<> glm::vec2 convert<glm::vec2, b2Vec2>(const b2Vec2& vec) {
        return glm::vec2(vec.x, vec.y);
    };

    template<> glm::vec2 convert<glm::vec2, sf::Vector2f>(const sf::Vector2f& vec) {
        return glm::vec2(vec.x, vec.y);
    };
}