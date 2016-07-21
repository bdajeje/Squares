#ifndef SHIELDBLOCK_HPP
#define SHIELDBLOCK_HPP

#include "models/auto_block.hpp"

namespace model {

class ShieldBlock final : public AutoBlock
{
  public:

    ShieldBlock(const sf::Vector2f& position, float size, const Direction& direction, const std::string& sound_file);

    std::vector<BlockEffect> collision(std::shared_ptr<Player>& player);

  private:

    static constexpr int _shield_gain {20};
    static constexpr int _score_gain {5};
};

}

#endif // SHIELDBLOCK_HPP
