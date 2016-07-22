#ifndef BLINK_HPP
#define BLINK_HPP

#include "graphics/effects/drawable_effect.hpp"

namespace graphics {
namespace effect {

class Blink final : public DrawableEffect
{
  public:

    /*! Constructor */
    Blink(const std::shared_ptr<Drawable>& target, const sf::Time& duration, const sf::Time& blink_time);

  private:

    void applyUpdate(sf::Int32 elapsed_ms);
    void internalDraw(sf::RenderTarget& target, sf::RenderStates states) const;

  private:

    sf::Int32 _blink_time;

    /*! Elapsed time since last target visibility update (in milliseconds) */
    sf::Int32 _elapsed_time_since_toggle_ms;
};

}
}

#endif // BLINK_HPP
