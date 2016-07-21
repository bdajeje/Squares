#ifndef LIFEBLOCK_HPP
#define LIFEBLOCK_HPP

#include "models/auto_block.hpp"

namespace model {

class LifeBlock final : public AutoBlock
{
  public:

    LifeBlock(const sf::Vector2f& position, float size, const Direction& direction, const std::string& sound_file);

    std::vector<BlockEffect> collision(std::shared_ptr<Player>& player);

  private:

    static constexpr int _life_gain {20};
    static constexpr int _score_gain {5};
};

}

#endif // LIFEBLOCK_HPP
