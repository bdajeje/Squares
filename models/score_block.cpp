#include "score_block.hpp"

#include "models/player.hpp"

namespace model {

ScoreBlock::ScoreBlock(const sf::Vector2f& position, float size, const Direction& direction, const std::string& sound_file)
  : AutoBlock {position, size, direction, sf::Color::Yellow, sound_file}
{}

void ScoreBlock::collision(std::shared_ptr<Player>& player)
{
  player->gainScore(_score_gain);
}

}
