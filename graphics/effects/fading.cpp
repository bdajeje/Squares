#include "fading.hpp"

namespace graphics {
namespace effect {

Fading::Fading(const std::shared_ptr<sf::Text>& target, const sf::Time& duration, short target_transparency)
  : TextEffect {target, duration}
{
  _step_per_ms = (float)(target_transparency - target->getColor().a) / (float)duration.asMilliseconds();
}

void Fading::applyUpdate(sf::Int32 elapsed_ms)
{
  sf::Text* target = dynamic_cast<sf::Text*>(_target.get());
  sf::Color updated_color = target->getColor();
  _current_transparency += _step_per_ms * elapsed_ms;
  updated_color.a = _current_transparency;
  target->setColor( updated_color );
}

}
}
