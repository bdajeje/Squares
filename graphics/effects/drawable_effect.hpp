#ifndef DRAWABLEEFFECT_HPP
#define DRAWABLEEFFECT_HPP

#include <memory>

#include <SFML/Graphics.hpp>

#include "graphics/drawable.hpp"

namespace graphics {
namespace effect {

class DrawableEffect
{
  public:

    DrawableEffect(const std::shared_ptr<Drawable>& target, const sf::Time& duration);

    void update(const sf::Time& elapsed_time);

    bool isFinished() const;

  protected:

    virtual void applyUpdate(sf::Int32 elapsed_ms) = 0;

    /*! Helper method to call to prevent given duration to be equal to 0 (usefull for some effects) */
    void preventZeroDuration();

  protected:

    std::shared_ptr<Drawable> _target;
    sf::Time _duration;
    bool _infinite;
};

}
}

#endif // DRAWABLEEFFECT_HPP
