#ifndef RECTANGLESHAPE_HPP
#define RECTANGLESHAPE_HPP

#include <SFML/Graphics/RectangleShape.hpp>

#include "graphics/drawable.hpp"

namespace graphics {

class RectangleShape : public Drawable
{
  public:

    sf::RectangleShape& object() { return _shape; }

  protected:

    virtual void internalDraw(sf::RenderTarget& target, sf::RenderStates states) const
    {
      target.draw(_shape, states);
    }

  private:

    sf::RectangleShape _shape;
};

}

#endif // RECTANGLESHAPE_HPP
