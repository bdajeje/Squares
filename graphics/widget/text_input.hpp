#ifndef TEXTINPUT_HPP
#define TEXTINPUT_HPP

#include <regex>

#include "graphics/drawable.hpp"
#include "graphics/effects/blink.hpp"
#include "graphics/rectangle_shape.hpp"

namespace graphics {

class TextInput : public Drawable
{
  public:

    /*! Constructor
     *  \param max_length - maximum length of input text. Set to 0 for no limit.
     *  \param regex      - regex representing allowed characters
     */
    TextInput(const sf::Color& text_color, const sf::Font& font, unsigned int character_size,
              const sf::Color& background_color, const sf::Vector2f& sizes, const sf::Vector2f& position,
              unsigned int max_length, const std::__cxx11::string& regex);

    void update(const sf::Time& /*elapsed_time*/);

    void setText(const std::string& text);
    void addText(const std::string& text);
    void clear();

    /*! Remove X characters from the end */
    void removeFromEnd(unsigned int number);

    bool empty() const { return _text.getString().isEmpty(); }

    std::string getText() const { return _text.getString(); }

  protected:

    void updateCursorPosition();
    void internalDraw(sf::RenderTarget& target, sf::RenderStates states) const;

  private:

    sf::Text _text;
    sf::RectangleShape _shape;
    std::shared_ptr<RectangleShape> _cursor;
    unsigned int _max_length;
    std::unique_ptr<graphics::effect::Blink> _blinking_effect;
    std::regex _regex;
};

}

#endif // TEXTINPUT_HPP
