#include "life_block.hpp"

#include "models/player.hpp"

namespace model {

LifeBlock::LifeBlock(const sf::Vector2f& position, float size, const Direction& direction, const std::string& sound_file)
  : AutoBlock {position, size, direction, LifeColor, sound_file}
{}

std::vector<BlockEffect> LifeBlock::collision(std::shared_ptr<Player>& player)
{
  std::vector<BlockEffect> effects;
  effects.reserve(1);

  if(player->gainLife(_life_gain))
    effects.push_back(std::move(BlockEffect{LifeText, LifeColor}));
  else
  {
    player->gainScore(_score_gain);
    effects.push_back(std::move(BlockEffect{ScoreText, ScoreColor}));
  }

  return std::move(effects);
}

}
