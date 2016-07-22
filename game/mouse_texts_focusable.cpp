#include "mouse_texts_focusable.hpp"

namespace game {

const sf::Text* MouseTextsFocusable::checkTextOvered(const sf::Vector2i& mouse_position)
{
  const sf::Vector2f float_mouse_pos {static_cast<float>(mouse_position.x), static_cast<float>(mouse_position.y)};
  const sf::Text* overred_text {nullptr};

  for(const sf::Text* _text : _overrabled_texts)
  {
    if( _text->getGlobalBounds().contains(float_mouse_pos) )
    {
      overred_text = _text;
      break;
    }
  }

  focusOverrabledText(overred_text);
  return overred_text;
}

void MouseTextsFocusable::addOverrableText(sf::Text* text)
{
  _overrabled_texts.push_back(text);
}

}
