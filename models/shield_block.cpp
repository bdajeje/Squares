#include "shield_block.hpp"

#include "models/player.hpp"

namespace model {

ShieldBlock::ShieldBlock(const sf::Vector2f& position, float size, const Direction& direction, const std::string& sound_file)
  : AutoBlock {position, size, direction, ShieldColor, sound_file}
{}

std::vector<BlockEffect> ShieldBlock::collision(std::shared_ptr<Player>& player)
{
  std::vector<BlockEffect> effects;
  effects.reserve(1);

  if(player->gainShield(_shield_gain))
    effects.push_back(std::move(BlockEffect{ShieldText, ShieldColor}));
  else
  {
    player->gainScore(_score_gain);
    effects.push_back(std::move(BlockEffect{ScoreText, ScoreColor}));
  }

  return effects;
}

}
