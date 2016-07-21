#include "ennemy_block.hpp"

#include "models/player.hpp"

namespace model {

EnnemyBlock::EnnemyBlock(const sf::Vector2f& position, float size, const Direction& direction, const std::string& sound_file)
  : AutoBlock {position, size, direction, EnnemyColor, sound_file}
{}

std::vector<BlockEffect> EnnemyBlock::collision(std::shared_ptr<Player>& player)
{
  std::vector<BlockEffect> effects;
  effects.reserve(2);

  player->hit(collision_strengh);
  player->gainScore(score_lost);

  effects.push_back( std::move(BlockEffect{EnnemyLifeText, EnnemyColor}) );
  effects.push_back( std::move(BlockEffect{EnnemyScoreText, ScoreColor}) );
  return std::move(effects);
}

}
