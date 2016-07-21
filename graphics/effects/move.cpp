#include "move.hpp"

namespace graphics {
namespace effect {

Move::Move(const std::shared_ptr<sf::Transformable>& target, const sf::Time& duration, const sf::Vector2f& move)
  : Effect {target, duration}
{
  // Prevent dividing by 0
  // Applying move effect with a duration of 0 actually means move target directly of total movement
  preventZeroDuration();

  const sf::Int32 milliseconds = _duration.asMilliseconds();
  _move_per_ms.x = move.x / milliseconds;
  _move_per_ms.y = move.y / milliseconds;
}

void Move::applyUpdate(sf::Int32 elapsed_ms)
{
  _target->move( _move_per_ms.x * elapsed_ms, _move_per_ms.y * elapsed_ms );
}

}
}
