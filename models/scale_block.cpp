#include "scale_block.hpp"

#include "models/player.hpp"

namespace model {

ScaleBlock::ScaleBlock(const sf::Vector2f& position, float size, const Direction& direction, const std::string& sound_file)
  : AutoBlock {position, size, direction, ScaleColor, sound_file}
{}

std::vector<BlockEffect> ScaleBlock::collision(std::shared_ptr<Player>& player)
{
  std::vector<BlockEffect> effects;
  effects.reserve(1);

  player->gainScale(_scale_gain);

  effects.push_back(std::move(BlockEffect{ScaleText, ScaleColor}));
  return std::move(effects);
}

}
