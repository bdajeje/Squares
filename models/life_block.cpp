#include "life_block.hpp"

#include "models/player.hpp"

namespace model {

LifeBlock::LifeBlock(const sf::Vector2f& position, float size, const Direction& direction, const std::string& sound_file)
  : AutoBlock {position, size, direction, sf::Color::Green, sound_file}
{}

void LifeBlock::collision(std::shared_ptr<Player>& player)
{
  if(!player->gainLife(_life_gain))
    player->gainScore(5);
}

}
