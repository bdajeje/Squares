#ifndef UTILS_GRAPHICS_HPP
#define UTILS_GRAPHICS_HPP

#include <SFML/Graphics.hpp>

namespace utils {
namespace graphics{

/*! Horizontally and Vertically center a text */
void centerPosition(sf::Text& text, unsigned int total_width, unsigned int total_height);

/*! Horizontally center a text */
void centerHonrizontally(sf::Text& text, unsigned int total_width);

/*! Vertically align a list of texts (usefull to place menu items)
 *  Also centers texts horizontally
 */
void centerVerticalPosition(std::vector<sf::Text>& texts, unsigned int total_width, unsigned int total_height);

/*! Resize a sprite */
void resize(sf::Sprite& sprite, float x, float y);

}
}

#endif // UTILS_GRAPHICS_HPP

