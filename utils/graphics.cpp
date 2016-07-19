#include "utils/graphics.hpp"

namespace utils {
namespace graphics{

void centerHonrizontally(sf::Text& text, unsigned int total_width)
{
  const sf::FloatRect bounds = text.getGlobalBounds();
  text.setPosition( (total_width - bounds.width) / 2, text.getPosition().y );
}

void centerPosition(sf::Text& text, unsigned int total_width, unsigned int total_height)
{
  const sf::FloatRect bounds = text.getGlobalBounds();
  text.setPosition( (total_width - bounds.width) / 2, (total_height - bounds.height) / 2 );
}

void resize(sf::Sprite& sprite, float x, float y)
{
  sprite.setScale( x / sprite.getGlobalBounds().width,
                   y / sprite.getGlobalBounds().height );
}

}
}
