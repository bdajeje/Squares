#include "ennemy_block.hpp"

#include "models/player.hpp"

namespace model {

EnnemyBlock::EnnemyBlock(const sf::Vector2f& position, float size, const Direction& direction, const std::string& sound_file)
  : AutoBlock {position, size, direction, sf::Color::Red, sound_file}
{}

void EnnemyBlock::collision(std::shared_ptr<Player>& player)
{
  player->hit(collision_strengh);
  player->gainScore(-10);
}

}
