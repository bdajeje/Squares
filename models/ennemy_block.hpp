#ifndef ENNEMYBLOCK_HPP
#define ENNEMYBLOCK_HPP

#include "models/auto_block.hpp"

namespace model {

class EnnemyBlock final : public AutoBlock
{
  public:

    EnnemyBlock(const sf::Vector2f& position, float size, const Direction& direction, const std::string& sound_file);

    std::vector<BlockEffect> collision(std::shared_ptr<Player>& player);

  private:

    static constexpr int collision_strengh {20};
    static constexpr int score_lost {-10};
};


}
#endif // ENNEMYBLOCK_HPP
