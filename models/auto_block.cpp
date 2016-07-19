#include "auto_block.hpp"

namespace model {

AutoBlock::AutoBlock(const sf::Vector2f& position, float size, const Direction& direction, const sf::Color& color)
  : MapBlock {position, size, color}
{
  setDirection(direction.x, direction.y);
}

}
