#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP

#include <vector>

#include <SFML/Graphics.hpp>

namespace graphics {

class Drawable : public sf::Drawable
{
  public:

    void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
      if(_visible)
        internalDraw(target, states);
    }

    virtual void update(const sf::Time& /*elapsed_time*/) {}

    void hide() { _visible = false; }
    void show() { _visible = true; }

    bool isVisible() const { return _visible; }

  protected:

    virtual void internalDraw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

  private:

    bool _visible {true};
};

}

#endif // DRAWABLE_HPP
