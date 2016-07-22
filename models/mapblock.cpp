#include "mapblock.hpp"

#include "utils/mathematics.hpp"

namespace model {

MapBlock::MapBlock(const sf::Vector2f& position, float size, const sf::Color& color)
  : _shape {sf::Vector2f(size, size)}
{
  _shape.setFillColor(color);

  const sf::FloatRect bounds = _shape.getLocalBounds();
  _shape.setOrigin( bounds.width / 2, bounds.height / 2 );
  setPosition(position);

  // Randomly invert rotation
  if(utils::maths::random(0, 2) == 1)
    _rotation_speed = -_rotation_speed;
}

void MapBlock::internalDraw(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw(_shape, states);
}

void MapBlock::setPosition(const sf::Vector2f& position)
{
  _shape.setPosition(position);
}

void MapBlock::update(const sf::Time& elapsed_time)
{
  rotate(elapsed_time);

  const sf::Int32 elapsed_ms = elapsed_time.asMilliseconds();
  _shape.move( _direction.x * elapsed_ms, _direction.y * elapsed_ms );
}

void MapBlock::rotate(const sf::Time& elapsed_time)
{
  _angle = static_cast<float>(elapsed_time.asMilliseconds()) * _rotation_speed;
  _shape.rotate( _angle );
}

}
