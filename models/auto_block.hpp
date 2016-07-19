#ifndef AUTOBLOCK_HPP
#define AUTOBLOCK_HPP

#include "models/mapblock.hpp"

namespace model {

class AutoBlock : public MapBlock
{
  public:

    AutoBlock(const sf::Vector2f& position, float size, const Direction& direction, const sf::Color& color);

    virtual void collision(std::shared_ptr<Player>& player) = 0;
};

}

#endif // AUTOBLOCK_HPP
