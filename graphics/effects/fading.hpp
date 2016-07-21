#ifndef FADING_HPP
#define FADING_HPP

#include "graphics/effects/text_effect.hpp"

namespace graphics {
namespace effect {

class Fading final : public TextEffect
{
  public:

    /*! Fade target element until it reaches wanted transparency */
    Fading(const std::shared_ptr<sf::Text>& target, const sf::Time& duration, short target_transparency);

  protected:

    void applyUpdate(sf::Int32 elapsed_ms);

  private:

    float _step_per_ms;
    float _current_transparency; // keep current target transparency here as float (so we keep decimals) because sf::Transformable transparency is kept as integer (and so, decimals would be lost)
};

}
}

#endif // FADING_HPP
