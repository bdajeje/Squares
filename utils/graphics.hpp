#ifndef UTILS_GRAPHICS_HPP
#define UTILS_GRAPHICS_HPP

#include <SFML/Graphics.hpp>

namespace utils {
namespace graphics{

/*! Horizontally and Vertically center a text */
void centerPosition(sf::Text& text, unsigned int total_width, unsigned int total_height);

/*! Horizontally center a text */
void centerHonrizontally(sf::Text& text, unsigned int total_width);

/*! Resize a sprite */
void resize(sf::Sprite& sprite, float x, float y);

}
}

#endif // UTILS_GRAPHICS_HPP

