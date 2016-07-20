#ifndef MOUSEITEMSSELECTABLED_HPP
#define MOUSEITEMSSELECTABLED_HPP

#include <vector>

#include <SFML/Graphics/Shape.hpp>

#include "graphics/drawable.hpp"

namespace game {

class MouseTextsFocusable
{
  protected:

    void addOverrableText(sf::Text* text);

    /*! Check if mouse is overred an item. If yes select it.
     *  \returns overred item or nullptr
     *  \note call focusOverrabledText when finding overred text
     */
    const sf::Text* checkTextOvered(const sf::Vector2i& mouse_position);

    virtual void focusOverrabledText(const sf::Text* text) = 0;

  protected:

    std::vector<const sf::Text*> _overrabled_texts;
};

}

#endif // MOUSEITEMSSELECTABLED_HPP
