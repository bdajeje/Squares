#ifndef ENNEMYBLOCK_HPP
#define ENNEMYBLOCK_HPP

#include "models/auto_block.hpp"

namespace model {

class EnnemyBlock final : public AutoBlock
{
  public:

    EnnemyBlock(const sf::Vector2f& position, float size, const Direction& direction, const std::string& sound_file);

    void collision(std::shared_ptr<Player>& player);

  private:

    static constexpr unsigned int collision_strengh {20};
};


}
#endif // ENNEMYBLOCK_HPP
