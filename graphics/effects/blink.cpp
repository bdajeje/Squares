#include "blink.hpp"

namespace graphics {
namespace effect {

Blink::Blink(const std::shared_ptr<Drawable>& target, const sf::Time& duration, const sf::Time& blink_time)
  : DrawableEffect {target, duration}
  , _blink_time {blink_time.asMilliseconds()}
{}

void Blink::applyUpdate(sf::Int32 elapsed_ms)
{
  _elapsed_time_since_toggle_ms += elapsed_ms;

  if( _elapsed_time_since_toggle_ms < _blink_time )
    return;

  _elapsed_time_since_toggle_ms = _elapsed_time_since_toggle_ms - _blink_time;
  _target->isVisible() ? _target->hide() : _target->show();
}

}
}
