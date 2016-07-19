#include "score_block.hpp"

#include "models/player.hpp"

namespace model {

ScoreBlock::ScoreBlock(const sf::Vector2f& position, float size, const Direction& direction)
  : AutoBlock {position, size, direction, sf::Color::Yellow}
{}

void ScoreBlock::collision(std::shared_ptr<Player>& player)
{
  player->gainScore(_score_gain);
}

}
