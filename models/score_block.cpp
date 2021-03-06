#include "score_block.hpp"

#include "models/player.hpp"

namespace model {

ScoreBlock::ScoreBlock(const sf::Vector2f& position, float size, const Direction& direction, const std::string& sound_file)
  : AutoBlock {position, size, direction, ScoreColor, sound_file}
{}

std::vector<BlockEffect> ScoreBlock::collision(std::shared_ptr<Player>& player)
{
  std::vector<BlockEffect> effects;
  effects.reserve(1);

  player->gainScore(_score_gain);

  effects.push_back( std::move(BlockEffect{ScoreText, ScoreColor}));
  return std::move(effects);
}

}
