#include "shield_block.hpp"

#include "models/player.hpp"

namespace model {

ShieldBlock::ShieldBlock(const sf::Vector2f& position, float size, const Direction& direction, const std::string& sound_file)
  : AutoBlock {position, size, direction, sf::Color::Blue, sound_file}
{}

void ShieldBlock::collision(std::shared_ptr<Player>& player)
{
  if(!player->gainShield(_shield_gain))
    player->gainScore(5);
}

}
