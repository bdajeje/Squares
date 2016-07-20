#ifndef SCALEBONUS_HPP
#define SCALEBONUS_HPP

#include "models/auto_block.hpp"

namespace model {

class ScaleBlock final : public AutoBlock
{
  public:

    ScaleBlock(const sf::Vector2f& position, float size, const Direction& direction, const std::string& sound_file);

    void collision(std::shared_ptr<Player>& player);

  private:

    static constexpr float _scale_gain {-1};
};

}

#endif // SCALEBONUS_HPP
