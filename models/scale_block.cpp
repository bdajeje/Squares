#include "scale_block.hpp"

#include "models/player.hpp"

namespace model {

ScaleBlock::ScaleBlock(const sf::Vector2f& position, float size, const Direction& direction, const std::string& sound_file)
  : AutoBlock {position, size, direction, sf::Color::Cyan, sound_file}
{}

void ScaleBlock::collision(std::shared_ptr<Player>& player)
{
  player->gainScale(_scale_gain);
}

}
