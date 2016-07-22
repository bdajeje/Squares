#include "text_input.hpp"

namespace graphics {

TextInput::TextInput(const sf::Color& text_color, const sf::Font& font, unsigned int character_size,
                     const sf::Color& background_color, const sf::Vector2f& sizes, const sf::Vector2f& position,
                     unsigned int max_length, const std::string& regex)
  : _shape {sizes}  
  , _max_length {max_length}
  , _regex {regex}
{
  _text.setCharacterSize(character_size);
  _text.setFont(font);
  _text.setColor(text_color);
  _text.setPosition(position.x, position.y);

  _cursor = std::make_shared<RectangleShape>();
  _cursor->object().setSize(sf::Vector2f{3.f, sizes.y - sizes.y * 0.3f});
  _cursor->object().setFillColor(sf::Color::Black);

  _shape.setFillColor(background_color);
  _shape.setPosition(position);

  // Set cursor Y position (will not be update), then set X position
  _cursor->object().setPosition(0, position.y + ((_shape.getGlobalBounds().height - _cursor->object().getGlobalBounds().height) / 2));
  updateCursorPosition();

  // Add blinking effect on cursor
  _blinking_effect.reset( new graphics::effect::Blink{_cursor, sf::Time::Zero, sf::milliseconds(750)} );
}

void TextInput::internalDraw(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw(_shape, states);
  target.draw(_text, states);
  target.draw(*_cursor, states);
}

void TextInput::update(const sf::Time& elapsed_time)
{
  _blinking_effect->update(elapsed_time);
}

void TextInput::updateCursorPosition()
{
  _cursor->object().setPosition(_shape.getPosition().x + _text.getGlobalBounds().width + 5, _cursor->object().getPosition().y);
}

void TextInput::clear()
{
  _text.setString("");
}

void TextInput::setText(const std::string& text)
{
  clear();
  addText(text);
}

void TextInput::addText(const std::string &text)
{
  // Is there remaining place?
  if(_text.getString().getSize() == _max_length)
    return;

  // Is given text allowed?
  if(!std::regex_match(text, _regex))
    return;

  std::string new_text = _text.getString() + text;

  if(new_text.length() > _max_length)
    _text.setString( new_text.substr(0, _max_length) );
  else
    _text.setString( new_text );

  updateCursorPosition();
}

void TextInput::removeFromEnd(unsigned int number)
{
  const sf::String& current_text = _text.getString();
  if(current_text.isEmpty())
    return;

  _text.setString( current_text.substring(0, current_text.getSize() - number) );

  updateCursorPosition();
}

}
