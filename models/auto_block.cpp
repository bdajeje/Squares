#include "auto_block.hpp"

#include "managers/sound_manager.hpp"

namespace model {

AutoBlock::AutoBlock(const sf::Vector2f& position, float size, const Direction& direction, const sf::Color& color, const std::string& sound_file)
  : MapBlock {position, size, color}
  , _sound_file {sound_file}
{
  setDirection(direction.x, direction.y);
}

}
