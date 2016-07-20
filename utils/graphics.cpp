#include "utils/graphics.hpp"

namespace utils {
namespace graphics{

void centerHonrizontally(sf::Text& text, unsigned int total_width)
{
  const sf::FloatRect bounds = text.getGlobalBounds();
  text.setPosition( (total_width - bounds.width) / 2, text.getPosition().y );
}

void centerVerticalPosition(std::vector<sf::Text>& texts, unsigned int total_width, unsigned int total_height)
{
  if( texts.empty() )
    return;

  const unsigned int y_margin = total_height / (texts.size() + 1);
  const size_t nbr_items = texts.size();
  for(size_t i = 0; i < nbr_items; ++i)
  {
    sf::Text& text = texts.at(i);
    const sf::FloatRect bounds = text.getGlobalBounds();
    text.setPosition( 0, (y_margin * (i+1)) - (bounds.height / 2));
    centerHonrizontally(text, total_width);
  }
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
