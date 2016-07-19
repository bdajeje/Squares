#ifndef SHIELDBLOCK_HPP
#define SHIELDBLOCK_HPP

#include "models/auto_block.hpp"

namespace model {

class ShieldBlock final : public AutoBlock
{
  public:

    ShieldBlock(const sf::Vector2f& position, float size, const Direction& direction);

    void collision(std::shared_ptr<Player>& player);

  private:

    static constexpr int _shield_gain {20};
};

}

#endif // SHIELDBLOCK_HPP
