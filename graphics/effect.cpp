#include "effect.hpp"

namespace graphics {

Effect::Effect(const std::shared_ptr<sf::Transformable>& target, const sf::Time& duration)
  : _target {target}
  , _duration {duration}
{
  _infinite = _duration == sf::Time::Zero;
}

void Effect::update(const sf::Time& elapsed_time)
{
  sf::Int32 elapsed_ms;

  if(!_infinite)
  {
    elapsed_ms = ((elapsed_time > _duration) ? _duration : elapsed_time).asMilliseconds();
    _duration -= elapsed_time;
  }
  else
    elapsed_ms = elapsed_time.asMilliseconds();

  applyUpdate(elapsed_ms);
}

bool Effect::isFinished() const
{
  if(_infinite)
    return false;

  return _duration <= sf::Time::Zero;
}

void Effect::preventZeroDuration()
{
  if( _duration <= sf::Time::Zero )
    _duration = sf::milliseconds(1);
}

}
