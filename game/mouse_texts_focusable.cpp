#include "mouse_texts_focusable.hpp"

namespace game {

const sf::Text* MouseTextsFocusable::checkTextOvered(const sf::Vector2i& mouse_position)
{
  const sf::Vector2f float_mouse_pos {static_cast<float>(mouse_position.x), static_cast<float>(mouse_position.y)};

  for(const sf::Text* _text : _overrabled_texts)
  {
    if( _text->getGlobalBounds().contains(float_mouse_pos) )
    {
      focusOverrabledText(_text);
      return _text;
    }
  }

  return nullptr;
}

void MouseTextsFocusable::addOverrableText(sf::Text* text)
{
  _overrabled_texts.push_back(text);
}

}
