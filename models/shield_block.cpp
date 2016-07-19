#include "shield_block.hpp"

#include "models/player.hpp"

namespace model {

ShieldBlock::ShieldBlock(const sf::Vector2f& position, float size, const Direction& direction)
  : AutoBlock {position, size, direction, sf::Color::Blue}
{}

void ShieldBlock::collision(std::shared_ptr<Player>& player)
{
  if(!player->gainShield(_shield_gain))
    player->gainScore(5);
}

}
