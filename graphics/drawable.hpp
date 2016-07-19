#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP

#include <vector>

#include <SFML/Graphics.hpp>

namespace graphics {

class Drawable : public sf::Drawable
{
  public:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

    virtual void update(const sf::Time& /*elapsed_time*/) {}
};

}

#endif // DRAWABLE_HPP
