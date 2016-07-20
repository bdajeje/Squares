#ifndef SCOREBLOCK_HPP
#define SCOREBLOCK_HPP

#include "models/auto_block.hpp"

namespace model {

class ScoreBlock final : public AutoBlock
{
  public:

    ScoreBlock(const sf::Vector2f& position, float size, const Direction& direction, const std::string& sound_file);

    void collision(std::shared_ptr<Player>& player);

  private:

    static constexpr int _score_gain {100};
};

}

#endif // SCOREBLOCK_HPP
